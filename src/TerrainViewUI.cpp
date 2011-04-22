#include "ui_TerrainViewUI.h"
#include "TerrainViewUI.h"

#include "util/QuaternionToRotationMatrix.h"
#include "util/RotationMatrix3x3To4x4.h"
#include "util/Quaternion.h"

#include <vtkRenderer.h>
#include <vtkCubeSource.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkCamera.h>
#include <qinputdialog.h>
#include <vtkProperty.h>
#include <vtkPlaneSource.h>
#include <vtkMath.h>
#include <vtkMatrix4x4.h>
#include <vtkAxesActor.h>
#include <vtkAxisActor2D.h>
#include <vtkCommand.h>
#include <vtkInteractorStyleJoystickCamera.h>

// Constructor
TerrainView::TerrainView() {
	this->ui = new Ui_TerrainView;
	this->ui->setupUi(this);

	// Used back the rendering callback to synchronize
	// new update/recomputation
	renderLock = vtkMutexLock::New();

	// Create robot model actor
	robotActor = createRobotModel();

	// Terrain actor
	terrainActor = vtkSmartPointer<TerrainActor>::New();

	// Create a ground plane actor
	vtkSmartPointer<vtkActor> groundPlaneActor = createGroundPlane();

	// Create a axes actor at the origin
	vtkSmartPointer<vtkAxesActor> axesActor = vtkSmartPointer<vtkAxesActor>::New();

	// Create camera for renderer
	vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
	camera->SetPosition(-4, 0, 1.0);
	camera->SetViewUp(0, 0, 1);

	// VTK Renderer
	renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(robotActor);
	renderer->AddActor(terrainActor);
	renderer->AddActor(groundPlaneActor);
	renderer->AddActor(axesActor);

	renderer->SetBackground(.5, .5, 1.0);
	renderer->SetActiveCamera(camera);

	// VTK/Qt
	this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
	vtkRenderWindowInteractor* interactor =
			this->ui->qvtkWidget->GetInteractor();

	// Set a new interactor style
	vtkSmartPointer<vtkInteractorStyleJoystickCamera> style = vtkSmartPointer<
			vtkInteractorStyleJoystickCamera>::New();
	interactor->SetInteractorStyle(style);

	// Create attitude widget to display robot attitude in the lower left corner
	robotAttitudeWidget = vtkSmartPointer<RobotAttitudeWidget>::New();
	robotAttitudeWidget->SetInteractor(interactor);
	robotAttitudeWidget->SetEnabled(1);

	// Setup rendering callback
	vtkSmartPointer<RenderingTimerCallback> callback =
			new RenderingTimerCallback(this,
					this->ui->qvtkWidget->GetRenderWindow());
	interactor->AddObserver(vtkCommand::TimerEvent, callback);
	interactor->CreateRepeatingTimer(100);

	// Set up action signals and slots
	connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
	connect(this->ui->actionQuit, SIGNAL(triggered()), this, SLOT(slotExit()));
	connect(this->ui->actionConnect, SIGNAL(triggered()), this, SLOT(
			slotConnect()));
}

vtkSmartPointer<vtkActor> TerrainView::createGroundPlane() {
	vtkSmartPointer<vtkPlaneSource> planeSource = vtkSmartPointer<
			vtkPlaneSource>::New();
	planeSource->SetCenter(-10.0, -10.0, -1.0);
	planeSource->SetNormal(0.0, 0.0, 1.0);
	planeSource->SetResolution(100, 100);

	planeSource->SetPoint1(10.0, -10.0, -1.0);
	planeSource->SetPoint2(-10.0, 10.0, -1.0);

	vtkSmartPointer<vtkPolyDataMapper> groundPlaneMapper = vtkSmartPointer<
			vtkPolyDataMapper>::New();
	groundPlaneMapper->SetInput(planeSource->GetOutput());

	vtkSmartPointer<vtkActor> groundPlaneActor =
			vtkSmartPointer<vtkActor>::New();
	groundPlaneActor->SetMapper(groundPlaneMapper);
	groundPlaneActor->GetProperty()->SetRepresentationToWireframe();

	return groundPlaneActor;
}

vtkSmartPointer<vtkActor> TerrainView::createRobotModel() {
	vtkSmartPointer<vtkCubeSource> cubeSource =
			vtkSmartPointer<vtkCubeSource>::New();
	cubeSource->SetYLength(0.25);
	cubeSource->SetXLength(0.50);
	cubeSource->SetZLength(0.10);

	vtkSmartPointer<vtkPolyDataMapper> cubeMapper = vtkSmartPointer<
			vtkPolyDataMapper>::New();
	cubeMapper->SetInputConnection(cubeSource->GetOutputPort());
	vtkSmartPointer<vtkActor> robotActor = vtkSmartPointer<vtkActor>::New();
	robotActor->SetMapper(cubeMapper);
	robotActor->GetProperty()->SetColor(1, 1, 0);

	return robotActor;
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

void TerrainView::setIMURotation(double x, double y, double z, double w) {
	renderLock->Lock();
		// Convert quaternion to 3x3 rotation matrix
		QuaternionToRotationMatrix quatToRot;
		boost::numeric::ublas::matrix<double> rotationMatrix3x3 = boost::numeric::ublas::trans(quatToRot(x,y,z,w));

		// Convert 3x3 rotation matrix to 4x4
		RotationMatrix3x3To4x4 rot3To4;
		boost::numeric::ublas::matrix<double> rotationMatrix4x4 = rot3To4(rotationMatrix3x3);

		// Convert to vtkMatrix4x4
		vtkSmartPointer<vtkMatrix4x4> rotation = vtkSmartPointer<vtkMatrix4x4>::New();
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				rotation->SetElement(i, j, rotationMatrix4x4(i, j));
			}
		}

		// Get current position
		double position[3];
		robotActor->GetPosition(position);

		// Plot axes
//		vtkSmartPointer<vtkAxesActor> axesActor = vtkSmartPointer<vtkAxesActor>::New();
//		axesActor->SetAxisLabels(0);
//		vtkSmartPointer<vtkTransform> transformActor = vtkSmartPointer<vtkTransform>::New();
//		transformActor->Identity();
//		transformActor->PostMultiply();
//
//		boost::numeric::ublas::matrix<double> rotationMatrix3x3Axes = boost::numeric::ublas::trans(quatToRot(x, y, z, w));
//
//		boost::numeric::ublas::matrix<double> rotationMatrix4x4Axes = rot3To4(rotationMatrix3x3Axes);
//
//		vtkSmartPointer<vtkMatrix4x4> rotationAxes = vtkSmartPointer<vtkMatrix4x4>::New();
//		for (int i = 0; i < 4; i++) {
//			for (int j = 0; j < 4; j++) {
//				rotationAxes->SetElement(i, j, rotationMatrix4x4Axes(i, j));
//			}
//		}
//
//
//		transformActor->Concatenate(rotationAxes);
//		transformActor->Translate(position);
//		axesActor->SetUserTransform(transformActor);
//		axesActor->Modified();
//		renderer->AddActor(axesActor);

		// Robot model
		vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
		transform->Identity();
		transform->PostMultiply();

		// Rotate the robot back to the origin
		transform->Translate(-position[0], -position[1], -position[2]);

		// Rotate the robot according to the quaternion
		transform->Concatenate(rotation);

		// Translate the robot forward with the new position
		transform->Translate(position);

		robotActor->SetUserTransform(transform);
		robotActor->Modified();

		robotAttitudeWidget->onIMUPoseUpdate(rotation);

	renderLock->Unlock();
}

void TerrainView::setIMUPosition(double x, double y, double z) {
	renderLock->Lock();
	robotActor->SetPosition(x,y,z);
	renderLock->Unlock();
}

void TerrainView::insertPoint(double x, double y, double z) {
	renderLock->Lock();
	terrainActor->insertPoint(x, y, z);
	renderLock->Unlock();
}
