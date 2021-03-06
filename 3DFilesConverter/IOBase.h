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
    virtual std::string Write( vtkSmartPointer<vtkPolyData> data, std::string filePath ){ return ""; }
    static std::string GetBaseName(std::string filePath);
    static int RemoveDir(const char *dir);
protected:
    vtkSmartPointer<vtkPolyData> m_Data;
};
