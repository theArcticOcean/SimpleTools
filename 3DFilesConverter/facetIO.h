#pragma once

#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <string>

#include "IOBase.h"

class facetIO : public IOBase
{
public:
    facetIO();
    ~facetIO();
    virtual void Read(std::string filePath);
    virtual std::string Write( vtkSmartPointer<vtkPolyData> data, std::string filePath );
};
