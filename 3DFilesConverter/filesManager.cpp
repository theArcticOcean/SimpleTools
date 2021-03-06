#include "filesManager.h"
#include "ULog.h"
#include "IOBase.h"

#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

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
    std::string baseName = filesManager::GetInstance()->GetBaseName( filePath );
    std::string commandStr = "unzip -d " + baseName + " " + filePath;
    int ret = system( commandStr.c_str() );
    Log( IInfo, "commandStr: ", commandStr );
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
        RemoveDir( zipPath.c_str() );
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

std::string filesManager::GetBaseName(std::string filePath)
{
    int found = filePath.find_last_of(".");
    std::string result = filePath;
    if( found >= 0 )
    {
        result = filePath.substr( 0, found );
    }
    return result;
}

std::string filesManager::GetFolderName(std::string filePath)
{
    int found = filePath.find_last_of("/");
    std::string result = filePath;
    if( found >= 0 )
    {
        result = filePath.substr( 0, found );
    }
    return result;
}

int filesManager::RemoveDir(const char *dir)
{
    char cur_dir[] = ".";
    char up_dir[] = "..";
    char dir_name[128];
    DIR *dirp = nullptr;
    struct dirent *dp = nullptr;
    struct stat dir_stat;

    if ( 0 != access(dir, F_OK) )
    {
        return 0;
    }

    if ( 0 > stat(dir, &dir_stat) )
    {
        Log( IError, strerror(errno) );
        return -1;
    }

    if ( S_ISREG(dir_stat.st_mode) )
    {
        remove(dir);
    }
    else if ( S_ISDIR(dir_stat.st_mode) )
    {
        dirp = opendir(dir);
        while ( ( dp=readdir(dirp) ) != nullptr )
        {
            if ( (0 == strcmp(cur_dir, dp->d_name)) || (0 == strcmp(up_dir, dp->d_name)) ) {
                continue;
            }

            sprintf(dir_name, "%s/%s", dir, dp->d_name);
            RemoveDir(dir_name);
        }
        closedir(dirp);

        rmdir( dir ); // delete empty dir
    }
    else
    {
        Log( IError, strerror(errno) );
    }
    return 0;
}
