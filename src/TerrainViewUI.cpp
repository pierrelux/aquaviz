#include "ui_TerrainViewUI.h"
#include "TerrainViewUI.h"

#include "util/QuaternionToEuler.h"

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkCamera.h>
#include <qinputdialog.h>
#include <vtkProperty.h>
#include <vtkAxesActor.h>
#include <vtkInteractorStyleTerrain.h>
#include <vtkMath.h>

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

	// Create delaunay actor
	vtkSmartPointer<vtkActor> triangulatedActor =
			vtkSmartPointer<vtkActor>::New();
	triangulatedActor->SetMapper(triangulatedMapper);
	triangulatedActor->RotateX(-75);

	// Create robot model
	vtkSmartPointer<vtkCubeSource> cubeSource =
			vtkSmartPointer<vtkCubeSource>::New();
	cubeSource->SetYLength(0.10);
	cubeSource->SetXLength(0.50);
	cubeSource->SetZLength(0.25);

	// Create a cube mapper and actor.
	transform = vtkSmartPointer<vtkTransform>::New();

	vtkSmartPointer<vtkPolyDataMapper> cubeMapper = vtkSmartPointer<
			vtkPolyDataMapper>::New();
	cubeMapper->SetInputConnection(cubeSource->GetOutputPort());
	cubeActor = vtkSmartPointer<vtkActor>::New();
	cubeActor->SetMapper(cubeMapper);
	cubeActor->GetProperty()->SetColor(1,1,0);
	cubeActor->SetUserTransform(transform);

	// Create Axes Actor
	vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();

	// Create camera for renderer
	vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
	//camera->SetUserTransform(transform);
	camera->SetPosition(0, 0, 100);
	camera->SetFocalPoint(0, 0, 0);

	// VTK Renderer
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(cubeActor);
	renderer->AddActor(triangulatedActor);
	renderer->AddActor(axes);

	renderer->SetBackground(.5, .5, 1.0);
	renderer->SetActiveCamera(camera);

	// VTK/Qt
	this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

	// Setup rendering callback
	vtkRenderWindowInteractor* interactor =
			this->ui->qvtkWidget->GetInteractor();

	vtkSmartPointer<RenderingTimerCallback> callback =
			new RenderingTimerCallback(this,
					this->ui->qvtkWidget->GetRenderWindow());
	interactor->AddObserver(vtkCommand::TimerEvent, callback);

	interactor->CreateRepeatingTimer(100);

	// Set a new interactor style
	vtkSmartPointer<vtkInteractorStyleTerrain> style = vtkSmartPointer<vtkInteractorStyleTerrain>::New();
	interactor->SetInteractorStyle(style);

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

void TerrainView::setIMURotation(double x, double y, double z, double w) {
	//transform->RotateWXYZ(w, x, y, z);
	//transform->Modified();

	QuaternionToEuler quatToEuler;
	boost::numeric::ublas::vector<double> euler = quatToEuler(x, y, z, w);

	//cubeActor->RotateY(vtkMath::DegreesFromRadians(euler(0)));
	//cubeActor->RotateX(vtkMath::DegreesFromRadians(euler(1)));
	//cubeActor->RotateZ(vtkMath::DegreesFromRadians(euler(2)));

	cubeActor->SetOrientation(vtkMath::DegreesFromRadians(euler(0)), vtkMath::DegreesFromRadians(euler(1)), vtkMath::DegreesFromRadians(euler(2)));
	cubeActor->Modified();
}

void TerrainView::setIMUPosition(double x, double y, double z) {
	//transform->Translate(x, y, z);
	//transform->Modified();

	// Important ! : VTK Coordinate system is right-handed,
	// with the Z axis pointing towards the viewer.
	// Coordinates from ROS are such that y points towards the viewer
	// and z points up. Therefore, we need to take that into account below !
	cubeActor->SetPosition(x, z, y);
	cubeActor->Modified();
}

void TerrainView::clear() {
	renderLock->Lock();
	points->Reset();
	renderLock->Unlock();
}

void TerrainView::flush() {
	//renderLock->Lock();

	//polydata->Update();
	delaunay->Update();
	polydata->Modified();

	//renderLock->Unlock();
}

