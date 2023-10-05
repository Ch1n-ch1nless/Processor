#include "log.h"

FILE* OpenFile(const char* FILE_NAME, const char* mode)
{
    assert(FILE_NAME);
    assert(mode);

    //Pointer the file where errors will be printed
    FILE* LOG_FILE_PTR = stderr;

    //Allocate the memory to string, that will contain the name of file
    char* file_name = (char*) calloc(strlen(FILE_NAME) + strlen(EXTENSION) + 1, sizeof(char));

    //Check the correct functioning of the calloc()
    if (file_name == nullptr)
    {
        fprintf(LOG_FILE_PTR, "ERROR! Program can NOT allocate memory in log.cpp\n");
        return LOG_FILE_PTR;
    }

    file_name = strcpy(file_name, FILE_NAME);

    file_name = strcat(file_name, EXTENSION);

    //Open the file
    LOG_FILE_PTR = fopen(file_name, mode);

    //File opening check
    if (LOG_FILE_PTR == nullptr)
    {
        LOG_FILE_PTR = stderr;
        fprintf(LOG_FILE_PTR, "ERROR! Program can NOT open file %s.log\n", FILE_NAME);
    }

    fprintf(LOG_FILE_PTR, "=========FILE WAS OPENED AT %s=========\n", __TIME__);

    free(file_name);

    return LOG_FILE_PTR;
}

void CloseFile(FILE* LOG_FILE_PTR)
{
    fprintf(LOG_FILE_PTR, "=========FILE WAS CLOSED AT %s=========\n", __TIME__);
    fclose(LOG_FILE_PTR);
}
