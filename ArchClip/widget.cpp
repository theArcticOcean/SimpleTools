#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <vtkSphereSource.h>
#include <vtkClipPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPlane.h>
#include <vtkActor.h>
#include <QCoreApplication>
#include <vtkSTLReader.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkUnstructuredGrid.h>
#include <vtkCamera.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_STLReader( vtkSmartPointer<vtkSTLReader>::New() ),
    m_Renderer( vtkSmartPointer<vtkRenderer>::New() ),
    m_RenderWindow( vtkSmartPointer<vtkRenderWindow>::New() ),
    m_ClipPlane( vtkSmartPointer<vtkPlane>::New() ),
    m_ArchActor( vtkSmartPointer<vtkActor>::New() ),
    m_ArchMapper( vtkSmartPointer<vtkPolyDataMapper>::New() ),
    m_Threshold( vtkSmartPointer<vtkThreshold>::New() ),
    m_SurfaceFilter( vtkSmartPointer<vtkDataSetSurfaceFilter>::New() ),
    m_ClipPlaneNormal( PointStruct( 0, 0, 1 ) ),
    m_LastValue( 0 )
{
    ui->setupUi(this);
    ui->verticalSlider->setMaximum( 100 );
    loadSTLFile();
    
    double *bounds = m_STLReader->GetOutput()->GetBounds();
    printf( "bounds: (%lf, %lf, %lf, %lf, %lf, %lf)\n",
            bounds[0], bounds[1], bounds[2], bounds[3], bounds[4], bounds[5] );
    m_ZLength = bounds[5] - bounds[4];
    m_ZLength = m_ZLength + 0.5;

    m_ClipPlane->SetNormal( m_ClipPlaneNormal.point );
    m_ClipPlane->SetOrigin( 0.0, 0.0, m_ZLength/2 );

    AddThresholdArray();
    m_Threshold->SetInputData( m_STLReader->GetOutput() );
    //InitalPolyDatas();
    ShowArch();

    m_Renderer->GetActiveCamera()->Elevation( 90 );
    m_Renderer->GetActiveCamera()->SetViewUp( 0, -1, 0 );
    m_Renderer->ResetCamera();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_verticalSlider_valueChanged(int value)
{
    qDebug() << "valueChanged: " << value;

    double Z = m_ZLength/2.0 - value / 100.0 * m_ZLength;
    m_Threshold->ThresholdByLower( Z );
    m_Threshold->SetInputArrayToProcess( 0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, "ZValues" );
    m_Threshold->Update();

    vtkUnstructuredGrid *thresholdPd = m_Threshold->GetOutput();
    m_SurfaceFilter->SetInputData( thresholdPd );
    m_SurfaceFilter->Update();

    m_ArchMapper->SetInputData( m_SurfaceFilter->GetOutput() );
    ui->qvtkWidget->GetRenderWindow()->Render();
}

void Widget::loadSTLFile()
{
    QString dir = QCoreApplication::applicationDirPath();
    dir = dir + "/LingerBar.stl";
    qDebug() << "dir: " << dir;

    m_STLReader->SetFileName( dir.toStdString().c_str() );
    m_STLReader->Update();
}

void Widget::ShowArch()
{
    m_ArchMapper->SetInputData( m_STLReader->GetOutput() );
    m_ArchMapper->Update();

    m_ArchActor->SetMapper( m_ArchMapper );

    m_Renderer->AddActor( m_ArchActor );
    m_RenderWindow->AddRenderer( m_Renderer );

    ui->qvtkWidget->SetRenderWindow( m_RenderWindow );
}

void Widget::AddThresholdArray()
{
    vtkPolyData *pd = m_STLReader->GetOutput();
    vtkPoints *points = pd->GetPoints();
    vSPNew( ZValues, vtkDoubleArray );
    ZValues->SetNumberOfComponents( 1 );
    ZValues->SetName( "ZValues" );
    int count = points->GetNumberOfPoints();
    for( int i = 0; i < count; ++i )
    {
        PointStruct pt( points->GetPoint( i ) );
        ZValues->InsertNextValue( pt[2] );
    }
    pd->GetPointData()->AddArray( ZValues );
    m_STLReader->Update();
}

/*
void Widget::InitalPolyDatas()
{
    for( int i = 0; i <= 100; ++i )
    {
        double Z = m_ZLength/2.0 - i / 100.0 * m_ZLength;
        m_Threshold->ThresholdByLower( Z );
        m_Threshold->SetInputArrayToProcess( 0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, "ZValues" );
        m_Threshold->Update();

        vtkUnstructuredGrid *thresholdPd = m_Threshold->GetOutput();
        m_SurfaceFilter->SetInputData( thresholdPd );
        m_SurfaceFilter->Update();

        vSPNew( pd, vtkPolyData );
        pd->ShallowCopy( m_SurfaceFilter->GetOutput() );
        m_PolyDatas.push_back( pd );
    }
}
*/
