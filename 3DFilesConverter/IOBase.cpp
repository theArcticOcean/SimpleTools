#include "IOBase.h"
#include "ULog.h"

#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>

IOBase::IOBase()
{
    m_Data = nullptr;
}

IOBase::~IOBase()
{

}

vtkSmartPointer<vtkPolyData> IOBase::GetData()
{
    return m_Data;
}

std::string IOBase::GetBaseName(std::string filePath)
{
    int found = filePath.find_last_of(".");
    std::string result = filePath;
    if( found >= 0 )
    {
        result = filePath.substr( 0, found );
    }
    return result;
}

int IOBase::RemoveDir(const char *dir)
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
