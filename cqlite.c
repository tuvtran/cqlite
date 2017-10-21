#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "cqlite.h"


int main(int argc, char** argv) {
    InputBuffer* input_buffer = new_input_buffer();
    /**
     * our program will have an infinite loop that prints the prompt
     * get a line of input then processes that line of input
     */
    while (1) {
        print_prompt();
        read_input(input_buffer);

        // if it's the exit command
        if (strcmp(input_buffer->buffer, "\\exit") == 0) {
            exit(EXIT_SUCCESS);
        } else {
            printf("Unknown command '%s'.\n", input_buffer->buffer);
        }
    }
}


void print_prompt() {
    printf("cqlite> ");
}


InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer;

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


void read_input(InputBuffer* input_buffer) {
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