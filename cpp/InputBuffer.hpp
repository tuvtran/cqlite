#ifndef INPUTBUFFER_H
#define INPUTBUFFER_H

#include <string>

class InputBuffer
{
    public:
        std::string buffer;
        std::string::size_type buffer_length;
        std::string::size_type input_length;

        InputBuffer();
};

#endif