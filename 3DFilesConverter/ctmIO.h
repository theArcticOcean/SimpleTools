#pragma once

#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <string>

#include "IOBase.h"
#include "openctmpp.h"

class ctmIO : public IOBase
{
public:
    ctmIO();
    ~ctmIO();
    virtual void Read(std::string filePath);
    virtual void Write( vtkSmartPointer<vtkPolyData> data, std::string filePath );
protected:
    void SaveFile(CTMuint aVertCount, CTMuint aTriCount, CTMfloat *aVertices,
                  CTMuint *aIndices, const char *aFileName,
                  const CTMfloat *aAttribValues, const char *aName);
};
