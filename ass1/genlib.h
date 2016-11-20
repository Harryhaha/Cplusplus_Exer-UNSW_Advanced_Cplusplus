/*
 * File: genlib.h
 * -----------------------------------------------------
 * This header file is iincluded in Assignment 1 to provide a few
 * common definitions. Note this header has a "using namespace std"
 * clause. If a file includes this header, it can then use
 * features from the std namespace without qualifying by scope.
 *
 */

#ifndef _genlib_h
#define _genlib_h

#include <string>
#include <exception>
using namespace std;

/*
 * Class: ErrorException
 * ---------------------
 * This exception is raised by calls to the Error function, which
 * makes it possible for clients to respond to error conditions
 * without having their programs bomb completely.
 */

class ErrorException : public exception {
public:
    ErrorException(string msg = "unspecified custom error");
    virtual ~ErrorException() throw ();
    virtual const char* what() const throw ();
    //virtual string getMessage();
private:
    string msg;
};

/*
 * Function: Error
 * Usage: Error(msg);
 * ------------------
 * Error is used to signal an error condition in a program.  It first
 * throws an ErrorException.  If that isn't caught, it outputs the
 * error message string to the cerr stream and then exits the program
 * with a status code indicating failure.
 */

void Error(string str);

#endif
