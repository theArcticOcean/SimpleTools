#include "IOBase.h"

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
    std::size_t found = filePath.find_last_of(".");
    std::string result = filePath;
    if( found >= 0 )
    {
        result = filePath.substr( 0, found );
    }
    return result;
}
