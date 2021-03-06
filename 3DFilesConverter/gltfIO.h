#pragma once

#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <string>
#include <vtkGLTFImporter.h>
#include <vtkGLTFExporter.h>
#include <vtkRenderWindow.h>

#include "IOBase.h"

class MyGLTFImporter: public vtkGLTFImporter
{
public:
    static MyGLTFImporter* New();

    vtkSmartPointer<vtkPolyData> GetMesh();
protected:
    MyGLTFImporter() = default;
};

class gltfIO: public IOBase
{
public:
    gltfIO();
    ~gltfIO();
    virtual void Read(std::string filePath);
    virtual std::string Write( vtkSmartPointer<vtkPolyData> data, std::string filePath );
};
