#pragma once

#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <string>

#include "IOBase.h"

class x3dIO: public IOBase
{
public:
    x3dIO();
    ~x3dIO();
    virtual bool Read(std::string filePath);
    virtual std::string Write( vtkSmartPointer<vtkPolyData> data, std::string filePath );
};
