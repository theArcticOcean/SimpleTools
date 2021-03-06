#pragma once

#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <string>

#include "IOBase.h"
#include "ULog.h"
#include "filesManager.h"

class facetIO : public IOBase
{
public:
    facetIO();
    ~facetIO();
    virtual bool Read(std::string filePath);
    virtual std::string Write( vtkSmartPointer<vtkPolyData> data, std::string filePath );
};
