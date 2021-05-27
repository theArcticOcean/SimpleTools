#pragma once

#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <string>

#include "IOBase.h"

class w3DSIO: public IOBase
{
public:
    w3DSIO();
    ~w3DSIO();
    virtual bool Read(std::string filePath);
    virtual std::string Write( vtkSmartPointer<vtkPolyData> data, std::string filePath );
};
