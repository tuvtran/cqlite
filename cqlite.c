#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "cqlite.h"


int main(int argc, char **argv) {
    InputBuffer *input_buffer = new_input_buffer();
    /**
     * our program will have an infinite loop that prints the prompt
     * get a line of input then processes that line of input
     */
    while (1) {
        print_prompt();
        read_input(input_buffer);

        // if the command is empty
        if (input_buffer->buffer[0] == '\0')
            continue;

        // if the command is a meta command
        if (input_buffer->buffer[0] == '\\') {
            switch (handle_meta_command(input_buffer)) {
                // if the meta command is executed successfully
                case META_COMMAND_SUCCESS:
                    continue;
                case META_COMMAND_UNRECOGNIZED_COMMAND:
                    fprintf(stderr, "Unrecognized command '%s'.\n",
                            input_buffer->buffer);
                    continue;
            }
        }

        Statement statement;
        // convert the line of input into our internal
        // representation of a statement
        switch (prepare_statement(input_buffer, &statement)) {
            case PREPARE_SUCCESS:
                break;
            case PREPARE_UNRECOGNIZED_STATEMENT:
                fprintf(stderr, "Unrecognized statement '%s'.\n",
                        input_buffer->buffer);
                continue;
        }

        // execute a statement, ie., a SQL queries
        execute_statement(&statement);
        printf("Executed.\n");
    }
}


void print_prompt() {
    printf("cqlite> ");
}


InputBuffer *new_input_buffer() {
    InputBuffer *input_buffer;

    // allocating blocks of memory in the heap
    // for the input buffer
    if ((input_buffer = malloc(sizeof(InputBuffer))) == NULL) {
        fprintf(stderr, "Error allocating blocks for buffer %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}


void read_input(InputBuffer *input_buffer) {
    ssize_t bytes_read;
    
    if ((bytes_read = getline(
        &(input_buffer->buffer),
        &(input_buffer->buffer_length), stdin)) == 0) {
            fprintf(stderr, "Error reading input from user %s.\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

    // ignore trailing newline
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = '\0';
}


MetaCommandResult handle_meta_command(InputBuffer *input_buffer) {
    if (strcmp(input_buffer->buffer, "\\exit") == 0) {
        free(input_buffer);
        exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}


PrepareResult prepare_statement(InputBuffer *input_buffer,
                                Statement *statement) {

    // now our "compiler" only understands two words
    // "insert" and "select"
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    } else if (strncmp(input_buffer->buffer, "select", 6) == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}


void execute_statement(Statement *statement) {
    switch (statement->type) {
        case STATEMENT_INSERT:
            printf("We would do an INSERT here.\n");
            break;
        case STATEMENT_SELECT:
            printf("We would do a SELECT here.\n");
            break;
    }
}