#pragma once

#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <string>

#define vtkSPtr vtkSmartPointer
#define vtkSPtrNew(Var, Type) vtkSPtr<Type> Var = vtkSPtr<Type>::New();

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
