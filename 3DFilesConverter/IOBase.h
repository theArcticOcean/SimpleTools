#pragma once

#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <string>

class IOBase
{
public:
    IOBase();
    virtual ~IOBase();
    virtual void Read(std::string filePath){}
    vtkSmartPointer<vtkPolyData> GetData();
    virtual void Write( vtkSmartPointer<vtkPolyData> data, std::string filePath ){}
    std::string GetBaseName(std::string filePath);
protected:
    vtkSmartPointer<vtkPolyData> m_Data;
};
