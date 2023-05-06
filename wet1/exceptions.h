#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <stdexcept>
    class nodeExists : public std::exception
    {
    };
    class nodeNotExists : public std::exception
    {
    };
    class allocationError : public std::exception
    {
    };
    class invalidInput : public std::exception
    {
    };

#endif
