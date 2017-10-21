#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argc) {
    InputBuffer* input_buffer = new_input_buffer();
    /**
     * our program will have an infinite loop that prints the prompt
     * get a line of input then processes that line of input
     */
    while (true) {
        print_prompt();
        read_input(input_buffer);

        // if it's the exit command
        if (strcmp(input_buffer->buffer, ".exit") == 0) {
            exit(EXIT_SUCCESS);
        } else {
            printf("Unknown command '%s'.\n", input_buffer->buffer);
        }
    }
}