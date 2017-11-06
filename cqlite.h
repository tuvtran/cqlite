#ifndef CQLITE_H
#define CQLITE_H

static const u_int32_t COLUMN_USERNAME_SIZE = 32;
static const u_int32_t COLUMN_EMAIL_SIZE = 255;

/**
 * An awesome way to get the size of an attribute of a struct
 * without resorting to initializing a new varialbe
 * Source: https://stackoverflow.com/questions/3553296/c-sizeof-single-struct-member
 */
#define attr_size(Struct, Attribute) sizeof(((Struct *)0) -> Attribute)


/**
 * Defining some constants for Row
 */
static const u_int32_t ID_SIZE = attr_size(Row, id);
static const u_int32_t USERNAME_SIZE = attr_size(Row, username);
static const u_int32_t EMAIL_SIZE = attr_size(Row, email);
static const u_int32_t ID_OFFSET = 0;
static const u_int32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
static const u_int32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
static const u_int32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;


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
    PREPARE_UNRECOGNIZED_STATEMENT,
    PREPARE_SYNTAX_ERROR
} PrepareResult;


typedef enum StatementType_t {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;


typedef struct Row_t {
    u_int32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_USERNAME_SIZE];
} Row;


typedef struct Statement_t {
    StatementType type;
    Row row_to_insert; // only used by insert statement
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