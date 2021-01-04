#include "zipManager.h"
#include "ULog.h"
#include "IOBase.h"
#include <dirent.h>
#include <stdlib.h>

/*
*   command format: 'unzip -d gltf.zip'
*   return folder path.
*/
std::string zipManager::unzip(std::string filePath)
{
    if( !endsWith( filePath, ".zip" ) )
    {
        return "";
    }
    std::string baseName = IOBase::GetBaseName( filePath );
    std::string commandStr = "unzip -d " + baseName + " " + filePath;
    int ret = system( commandStr.c_str() );
    Log( IInfo, "baseName: ", baseName );
    return baseName;
}

/*
*   command format: 'zip -j gltf.zip gltf/*'
*   return zip file path.
*/
std::string zipManager::zip(std::string folderPath)
{
    std::string zipPath = folderPath + ".zip";
    std::string commandStr = "zip -j " + zipPath + " " + folderPath + "/*";
    int ret = system( commandStr.c_str() );
    Log( IInfo, "ret: ", ret );
    return zipPath;
}

std::string zipManager::FindFilePath(std::string suffix, std::string folderPath)
{
    DIR* dir = opendir( folderPath.c_str() );
    dirent* p = nullptr;
    std::string path = "";
    while( (p = readdir(dir)) != nullptr )
    {
        if( p->d_name[0] == '.' )
        {
            continue;
        }
        if( p->d_type == DT_DIR )
        {
            Log( IInfo, "p->d_name: ", (folderPath + "/" + p->d_name) );
            std::string tmp = FindFilePath( suffix, folderPath + "/" + p->d_name );
            if( tmp.size() > 0 )
            {
                return tmp;
            }
        }

        if( endsWith( p->d_name, suffix ) )
        {
            path = folderPath;
            if( endsWith( path, "/" ) )
            {
                path = path.substr(0, path.size() - 1);
            }
            path = path + "/" + p->d_name;
        }
    }
    closedir(dir);
    Log( IInfo, "path: ", path );
    return path;
}

bool zipManager::endsWith(const std::string &mainStr, const std::string &toMatch)
{
    if( mainStr.size() >= toMatch.size() &&
        mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}
