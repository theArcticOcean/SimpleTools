#pragma once

#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <string>

#include "IOBase.h"

class objIO : public IOBase
{
public:
    objIO();
    ~objIO();
    virtual void Read(std::string filePath);
    virtual void Write( vtkSmartPointer<vtkPolyData> data, std::string filePath );
};
