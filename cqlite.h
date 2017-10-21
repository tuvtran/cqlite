#ifndef CQLITE_H
#define CQLITE_H


/**
 * buffer store the buffer
 * buffer_length size of the allocated buffer
 * input_length number of bytes read
 */
typedef struct InputBuffer_t {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;


/**
 * Declare a new type - MetaCommand
 * to handle commands like "\exit"
 */
typedef enum MetaCommandResult_t {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;


typedef enum PrepareResult_t {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;


typedef enum StatementType_t {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;


typedef struct Statement_t {
    StatementType type;
} Statement;


// create new input buffer
InputBuffer *new_input_buffer();
// print a prompt to the user
void print_prompt();
// read input from the command line
void read_input(InputBuffer *);

// handle the meta command
// this is a wrapper function
MetaCommandResult handle_meta_command(InputBuffer *);

// prepare_statement convert our statement
// into the result
PrepareResult prepare_statement(InputBuffer *, Statement *);

// execute a SQL statement
void execute_statement(Statement *);


#endif