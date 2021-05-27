#include "IOBase.h"
#include "ULog.h"

#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
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
