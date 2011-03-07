#include "ui_TerrainViewUI.h"
#include "TerrainViewUI.h"

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>

#include <qinputdialog.h>


// Constructor
TerrainView::TerrainView() {
	this->ui = new Ui_TerrainView;
	this->ui->setupUi(this);
	renderLock = vtkMutexLock::New();

	// Add the grid points to a polydata object
	points = vtkSmartPointer<vtkPoints>::New();
	points->SetDataTypeToDouble();

	polydata = vtkSmartPointer<vtkPolyData>::New();
	polydata->SetPoints(points);

	// Triangulate the grid points
	delaunay = vtkSmartPointer<vtkDelaunay2D>::New();
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
	triangulatedActor->RotateX(-75);

	// VTK Renderer
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(triangulatedActor);
	renderer->SetBackground(.5, .5, 1.0);

	// VTK/Qt
	this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

	// Setup rendering callback
	vtkRenderWindowInteractor* interactor =
			this->ui->qvtkWidget->GetInteractor();

	vtkSmartPointer<RenderingTimerCallback> callback = new RenderingTimerCallback(this,
			                                                              this->ui->qvtkWidget->GetRenderWindow());
	interactor->AddObserver(vtkCommand::TimerEvent, callback);

	interactor->CreateRepeatingTimer(100);

	// Set up action signals and slots
	connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
	connect(this->ui->actionQuit, SIGNAL(triggered()), this, SLOT(slotExit()));
	connect(this->ui->actionConnect, SIGNAL(triggered()), this, SLOT(
			slotConnect()));
}

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

void TerrainView::insertPoint(double x, double y, double z) {
	renderLock->Lock();
	points->InsertNextPoint(x, y, z);
	renderLock->Unlock();
}

void TerrainView::clear() {
	renderLock->Lock();
	points->Reset();
	renderLock->Unlock();
}

void TerrainView::flush() {
	renderLock->Lock();
	//points = generateRandomPoints(25);
	//polydata->SetPoints(points);
	polydata->Modified();
	polydata->Update();
	delaunay->Update();
	polydata->Modified();
	renderLock->Unlock();
}

