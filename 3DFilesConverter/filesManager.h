/*
*   use libzip to manage compressed file.
*/
#pragma once

#include <zlib.h>
#include <string>

#ifndef INVALID_FILE
#define INVALID_FILE "NAN.txt"
#endif

class filesManager
{
public:
    static filesManager *GetInstance()
    {
        static filesManager g_FilesManager;
        return &g_FilesManager;
    }

    std::string unzip( std::string filePath );
    std::string zip( std::string folderPath );
    bool FindFilePath( std::string suffix, std::string folderPath, std::string &result );
    bool endsWith( const std::string &mainStr, const std::string &toMatch );
    std::string GetBaseName(std::string filePath);
    std::string GetFolderName(std::string filePath);
    int RemoveDir(const char *dir);
protected:
    filesManager();
};
