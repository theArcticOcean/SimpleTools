#ifndef Window_H
#define Window_H

#include <QWidget>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkPlane.h>
#include <vtkClipPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkImplicitPlaneWidget.h>
#include <vtkSTLReader.h>
#include <vtkThreshold.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vector>

#include "Tools.h"

#define vSP vtkSmartPointer
#define vSPNew(Var, Type)    vSP<Type> Var = vSP<Type>::New();

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_verticalSlider_valueChanged(int value);

private:
    void loadSTLFile();
    void ShowArch();
    void AddThresholdArray();
    //void InitalPolyDatas();

    Ui::Widget *ui;
    vSP<vtkSTLReader> m_STLReader;
    vSP<vtkRenderer> m_Renderer;
    vSP<vtkRenderWindow> m_RenderWindow;
    vSP<vtkPlane> m_ClipPlane;
    vSP<vtkActor> m_ArchActor;
    vSP<vtkPolyDataMapper> m_ArchMapper;
    vSP<vtkThreshold> m_Threshold;
    vSP<vtkDataSetSurfaceFilter> m_SurfaceFilter;
    PointStruct m_ClipPlaneNormal;
    vector<vSP<vtkPolyData>> m_PolyDatas;
    int m_LastValue;
    double m_ZLength;
};

#endif // Window_H
