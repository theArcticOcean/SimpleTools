/*
*   use libzip to manage compressed file.
*/
#pragma once

//#include <zlib.h>
#include <string>
#include <vtkPolyData.h>
#include <vtkImageData.h>

#ifndef INVALID_FILE
#define INVALID_FILE "NAN.txt"
#endif

class filesManager
{
public:
    static filesManager *GetInstance()
    {
        static filesManager g_FilesManager;
        return &g_FilesManager;
    }

    bool endsWith( const std::string &mainStr, const std::string &toMatch );
    std::string GetBaseName(std::string filePath);
    std::string GetFolderName(std::string filePath);
    int RemoveDir(const char *dir);
    vtkSmartPointer<vtkImageData> ConvertPolydataToImage(vtkPolyData *polydata);
    vtkSmartPointer<vtkPolyData> ConvertImageToPolydata(vtkImageData *imageData);
protected:
    unsigned char m_ImageInval;
    unsigned char m_ImageOutval;
    double m_ImageSpaceVal;

    filesManager();
};
