/*
*   use libzip to manage compressed file.
*/
#pragma once

#include <zlib.h>
#include <string>

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
protected:
    filesManager();
};
