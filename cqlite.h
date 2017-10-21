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


// create new input buffer
InputBuffer* new_input_buffer();
// print a prompt to the user
void print_prompt();
// read input from the command line
void read_input(InputBuffer*);

#endif