#pragma once

#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <string>

#include "IOBase.h"

class byuIO: public IOBase
{
public:
    byuIO();
    ~byuIO();
    virtual bool Read(std::string filePath);
    virtual std::string Write( vtkSmartPointer<vtkPolyData> data, std::string filePath );
};
