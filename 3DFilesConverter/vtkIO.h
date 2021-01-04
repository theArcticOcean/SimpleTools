#pragma once

#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <string>

#include "IOBase.h"

class vtkIO: public IOBase
{
public:
    vtkIO();
    ~vtkIO();
    virtual void Read(std::string filePath);
    virtual void Write( vtkSmartPointer<vtkPolyData> data, std::string filePath );
};