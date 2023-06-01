#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <stdexcept>
    class KeyAlreadyExists : public std::exception
    {
    };
    class KeyMissing : public std::exception
    {
    };

#endif
