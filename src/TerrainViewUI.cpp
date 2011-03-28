#include "ui_TerrainViewUI.h"
#include "TerrainViewUI.h"

#include "util/QuaternionToRotationMatrix.h"
#include "util/RotationMatrix3x3To4x4.h"

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkCamera.h>
#include <qinputdialog.h>
#include <vtkProperty.h>
#include <vtkAxesActor.h>
#include <vtkCubeAxesActor.h>
#include <vtkInteractorStyleJoystickCamera.h>
#include <vtkMath.h>
#include <vtkMatrix4x4.h>

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
	//triangulatedActor->RotateX(-75);

	// Create robot model
	cubeSource =
			vtkSmartPointer<vtkCubeSource>::New();
	cubeSource->SetYLength(0.25);
	cubeSource->SetXLength(0.50);
	cubeSource->SetZLength(0.10);

	// Create a cube mapper and actor.
	vtkSmartPointer<vtkPolyDataMapper> cubeMapper = vtkSmartPointer<
			vtkPolyDataMapper>::New();
	cubeMapper->SetInputConnection(cubeSource->GetOutputPort());
	cubeActor = vtkSmartPointer<vtkActor>::New();
	cubeActor->SetMapper(cubeMapper);
	cubeActor->GetProperty()->SetColor(1,1,0);

	// Create Axes Actor
	vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();

	// Create camera for renderer
	vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
	camera->SetPosition(0, 0, 50);
	//camera->SetFocalPoint(0, 0, 0);
	camera->SetViewUp(0,-1, 0);

	// Create axes actor
	vtkSmartPointer<vtkCubeAxesActor> cubeAxesActor =   vtkSmartPointer<vtkCubeAxesActor>::New();
	cubeAxesActor->SetCamera(camera);

	// VTK Renderer
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(cubeActor);
	renderer->AddActor(triangulatedActor);
	renderer->AddActor(axes);
	//renderer->AddActor(cubeAxesActor);

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
	vtkSmartPointer<vtkInteractorStyleJoystickCamera> style = vtkSmartPointer<vtkInteractorStyleJoystickCamera>::New();
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
	boost::numeric::ublas::vector<double> q(4);
	q(0) = x; q(1) = y; q(2) = z; q(3) = w;

	QuaternionToRotationMatrix quatToRot;
	boost::numeric::ublas::matrix<double> rotationMatrix3x3 = quatToRot(q);

	RotationMatrix3x3To4x4 rot3To4;
	boost::numeric::ublas::matrix<double> rotationMatrix4x4 = rot3To4(rotationMatrix3x3);

	vtkSmartPointer<vtkMatrix4x4> rotation = vtkSmartPointer<vtkMatrix4x4>::New();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			rotation->SetElement(i, j, rotationMatrix4x4(i,j));
		}
	}

	std::cout << "Matrix " << *rotation << std::endl;
	renderLock->Lock();
    //double position[3];
    //cubeActor->GetPosition(position);
    //cubeActor->SetOrigin(position);

    cubeActor->SetUserMatrix(rotation);
	cubeActor->Modified();
	renderLock->Unlock();
}

void TerrainView::setIMUPosition(double x, double y, double z) {
	// Important ! : VTK Coordinate system is right-handed,
	// with the Z axis pointing towards the viewer.
	// Coordinates from ROS are such that y points towards the viewer
	// and z points up. Therefore, we need to take that into account below !
	renderLock->Lock();
	cubeActor->SetPosition(x, y, z);
	cubeActor->Modified();
	renderLock->Unlock();
}

void TerrainView::clear() {
	renderLock->Lock();
	points->Reset();
	renderLock->Unlock();
}

void TerrainView::flush() {
	renderLock->Lock();
	delaunay->Update();
	polydata->Modified();
	renderLock->Unlock();
}

