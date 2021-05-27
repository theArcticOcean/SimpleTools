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
    virtual bool Read(std::string filePath);
    virtual std::string Write( vtkSmartPointer<vtkPolyData> data, std::string filePath );
protected:
    void SaveFile(CTMuint aVertCount, CTMuint aTriCount, CTMfloat *aVertices,
                  CTMuint *aIndices, const char *aFileName,
                  const CTMfloat *aAttribValues0, const char *aName0,
                  const CTMfloat *aAttribValues1, const char *aName1);
};
