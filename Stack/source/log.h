///@file log.h
#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Pointer to string: ".log"
 */
const char* const EXTENSION = ".log";

/**
 *@brief Create and open file with extension = EXTENSION(constant in log.h)
 *
 *@param [in] FILE_NAME - string, which contains name of file without extension
 *@param [in] mode      - string, which contains the mode of reading the file
 *
 *@return pointer to file
 */
FILE* OpenFile(const char* FILE_NAME, const char* mode);

/**
 *@brief Close the file which was opened
 *
 *@param [in] LOG_FILE_PTR - pointer to file
 */
void CloseFile(FILE* LOG_FILE_PTR);

#endif // LOG_H_INCLUDED
