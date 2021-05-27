#include "IOBase.h"
#include "ULog.h"

#include <sys/stat.h>
#ifdef Q_OS_UNIX
#include <dirent.h>
#include <unistd.h>
#endif

#include <fcntl.h>

IOBase::IOBase()
{
    m_Data = vtkSmartPointer<vtkPolyData>::New();
}

IOBase::~IOBase()
{

}

vtkSmartPointer<vtkPolyData> IOBase::GetData()
{
    return m_Data;
}
