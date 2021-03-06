#include "filesManager.h"
#include "ULog.h"
#include "IOBase.h"
#include <dirent.h>
#include <stdlib.h>

/*
*   command format: 'unzip -d gltf.zip'
*   return folder path.
*/
std::string filesManager::unzip(std::string filePath)
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
std::string filesManager::zip(std::string folderPath)
{
    std::string zipPath = folderPath + ".zip";
    if ( access( zipPath.c_str(), F_OK ) == 0 )
    {
        IOBase::RemoveDir( zipPath.c_str() );
    }
    std::string commandStr = "zip -j " + zipPath + " " + folderPath + "/*";
    int ret = system( commandStr.c_str() );
    Log( IInfo, "ret: ", ret );
    return zipPath;
}

bool filesManager::FindFilePath(std::string suffix, std::string folderPath, std::string &result)
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
            auto flag = FindFilePath( suffix, folderPath + "/" + p->d_name, result );
            if( flag ) {
                closedir(dir);
                return true;
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
            result = path;
            closedir(dir);
            return true;
        }
    }
    closedir(dir);
    return false;
}

bool filesManager::endsWith(const std::string &mainStr, const std::string &toMatch)
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

filesManager::filesManager()
{

}
