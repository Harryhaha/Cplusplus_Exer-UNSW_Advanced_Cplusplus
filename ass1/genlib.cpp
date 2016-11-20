/*
 * File: genlib.cpp
 * ----------------
 * This file implements the genlib.h interface
 */

#include "genlib.h"
#include <cstdlib>
#include <iostream>

ErrorException::ErrorException(string m) : msg(m) { }

ErrorException::~ErrorException() throw() {}

const char* ErrorException::what() const throw() {
    return this->msg.c_str(); 
}

void Error(string str) {
    ErrorException err(str);
    throw err;
}


