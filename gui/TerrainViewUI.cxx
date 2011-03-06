#include "ui_TerrainViewUI.h"
#include "TerrainViewUI.h"

#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkDelaunay2D.h>

#include "vtkSmartPointer.h"

#include <qinputdialog.h>

// Constructor
TerrainView::TerrainView() {
	this->ui = new Ui_TerrainView;
	this->ui->setupUi(this);

	// Add the grid points to a polydata object
	vtkSmartPointer<vtkPoints> points = generateRandomPoints(10);

	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
	polydata->SetPoints(points);

	// Triangulate the grid points
	vtkSmartPointer<vtkDelaunay2D> delaunay =
			vtkSmartPointer<vtkDelaunay2D>::New();
	delaunay->SetInput(polydata);
	delaunay->Update();

	// Create a mapper
	vtkSmartPointer<vtkPolyDataMapper> triangulatedMapper = vtkSmartPointer<
			vtkPolyDataMapper>::New();
	triangulatedMapper->SetInputConnection(delaunay->GetOutputPort());

	// Create actor
	vtkSmartPointer<vtkActor> triangulatedActor =
			vtkSmartPointer<vtkActor>::New();
	triangulatedActor->SetMapper(triangulatedMapper);
	triangulatedActor->RotateX(45);

	// VTK Renderer
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(triangulatedActor);
	renderer->SetBackground(.5, .5, 1.0);

	// VTK/Qt wedded
	this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

	// Set up action signals and slots
	connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
	connect(this->ui->actionQuit, SIGNAL(triggered()), this, SLOT(slotExit()));
	connect(this->ui->actionConnect, SIGNAL(triggered()), this, SLOT(
			slotConnect()));
}
;

void TerrainView::slotExit() {
	qApp->exit();
}

void TerrainView::slotConnect() {
	bool ok;
	QString text = QInputDialog::getText(this, tr("Connect"), tr(
			"Enter the ROS node to connect to:"), QLineEdit::Normal, tr(
			"127.0.0.1"), &ok);
	if (ok && !text.isEmpty()) {
	}
}
