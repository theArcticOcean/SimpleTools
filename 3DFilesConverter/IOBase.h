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
    virtual bool Read(std::string filePath){ return true; }
    vtkSmartPointer<vtkPolyData> GetData();
    virtual std::string Write( vtkSmartPointer<vtkPolyData> data, std::string filePath ){ return ""; }

protected:
    vtkSmartPointer<vtkPolyData> m_Data;
};
