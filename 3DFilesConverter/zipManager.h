/*
*   use libzip to manage compressed file.
*/
#pragma once

#include <zlib.h>
#include <string>

class zipManager
{
public:
    std::string unzip( std::string filePath );
    std::string zip( std::string folderPath );
    std::string FindFilePath( std::string suffix, std::string folderPath );
    bool endsWith( const std::string &mainStr, const std::string &toMatch );
};
