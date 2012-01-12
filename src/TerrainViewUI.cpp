/**
 * @author Pierre-Luc Bacon <pbacon@cim.mcgill.ca>
 */
#include "ui_TerrainViewUI.h"
#include "TerrainViewUI.h"

#include "util/QuaternionToRotationMatrix.h"
#include "util/RotationMatrix3x3To4x4.h"
#include "util/Quaternion.h"

#include <qinputdialog.h>

#include <vtkMath.h>
#include <vtkCommand.h>
#include <vtkRenderer.h>
#include <vtkProperty.h>
#include <vtkMatrix4x4.h>
#include <vtkAxesActor.h>
#include <vtkTransform.h>
#include <vtkAxisActor2D.h>
#include <vtkPlaneSource.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkInteractorStyleJoystickCamera.h>

// Constructor
TerrainView::TerrainView() {
	this->ui = new Ui_TerrainView;
	this->ui->setupUi(this);

	// Used back the rendering callback to synchronize
	// new update/recomputation
	renderLock = vtkMutexLock::New(); // TODO Delete !
	framesLock = vtkMutexLock::New();

	// Create robot model actor
	robotActor = vtkSmartPointer<RobotActor>::New();

	// Terrain actor
	terrainActor = vtkSmartPointer<TerrainActor>::New();

	// Create a ground plane actor
	groundPlaneActor = createGroundPlane();

	// Create a axes actor at the origin
	axesActor = vtkSmartPointer<vtkAxesActor>::New();
	axesActor->SetZAxisLabelText("Z Origin");
	axesActor->SetVisibility(0);

	scale = vtkSmartPointer<ElevationWidget>::New();

	// Create camera for renderer
	camera = vtkSmartPointer<vtkCamera>::New();
	camera->SetPosition(-4, 0, 1.0);
	camera->SetViewUp(0, 0, 1);

	  // Screenshot
	windowToImageFilter = vtkSmartPointer<vtkWindowToImageFilter>::New();
	windowToImageFilter->SetInput(this->ui->qvtkWidget->GetRenderWindow());
	windowToImageFilter->SetMagnification(3);
	windowToImageFilter->SetInputBufferTypeToRGBA();

	imageWriter = vtkSmartPointer<vtkPNGWriter>::New();
	imageWriter->SetFileName("terrain.png");
	imageWriter->SetInput(windowToImageFilter->GetOutput());

	// VTK Renderer
	renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(robotActor);
	renderer->AddActor(terrainActor);
	renderer->AddActor(groundPlaneActor);
	renderer->AddActor(axesActor);
	//renderer->AddActor(scale);

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
	connect(this->ui->actionConnect, SIGNAL(triggered()), this, SLOT(slotConnect()));
	connect(this->ui->actionTerrain, SIGNAL(triggered()), this, SLOT(slotTerrain()));
	connect(this->ui->actionFrame, SIGNAL(triggered()), this, SLOT(slotFrame()));
	connect(this->ui->actionAttitude, SIGNAL(triggered()), this, SLOT(slotAttitude()));
	connect(this->ui->actionGroundPlane, SIGNAL(triggered()), this, SLOT(slotGroundPlane()));
	connect(this->ui->actionOrigin, SIGNAL(triggered()), this, SLOT(slotOrigin()));
	connect(this->ui->actionScreenshot, SIGNAL(triggered()), this, SLOT(slotScreenshot()));
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

void TerrainView::slotTerrain()
{
	if (this->ui->actionTerrain->isChecked()) {
		terrainActor->SetVisibility(1);
	} else {
		terrainActor->SetVisibility(0);
	}
}

void TerrainView::setFramesVisibility(int v)
{
	framesLock->Lock();
	std::vector<vtkAxesActor*>::iterator it;
	for (it = frames.begin(); it != frames.end(); it++) {
		(*it)->SetVisibility(v);
	}
	framesLock->Unlock();
}

void TerrainView::slotFrame()
{
	if (this->ui->actionFrame->isChecked()) {
		setFramesVisibility(1);
	} else {
		setFramesVisibility(0);
	}
}

void TerrainView::slotAttitude()
{
	if (this->ui->actionAttitude->isChecked()) {
		robotAttitudeWidget->SetEnabled(1);
	} else {
		robotAttitudeWidget->SetEnabled(0);
	}
}

void TerrainView::slotGroundPlane()
{
	if (this->ui->actionGroundPlane->isChecked()) {
		groundPlaneActor->SetVisibility(1);
	} else {
		groundPlaneActor->SetVisibility(0);
	}
}

void TerrainView::slotOrigin()
{
	if (this->ui->actionOrigin->isChecked()) {
		axesActor->SetVisibility(1);
	} else {
		axesActor->SetVisibility(0);
	}
}

void TerrainView::slotScreenshot()
{
	windowToImageFilter->Update();
	imageWriter->Write();
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

void TerrainView::plotFrame(double x, double y, double z, double w)
{
	vtkSmartPointer<vtkAxesActor> frame = vtkSmartPointer<vtkAxesActor>::New();
	frame->SetAxisLabels(0);

	// Convert quaternion to 3x3 rotation matrix
	QuaternionToRotationMatrix quatToRot;
	boost::numeric::ublas::matrix<double> rotationMatrix3x3 =
			boost::numeric::ublas::trans(quatToRot(x, y, z, w));

	// Convert 3x3 rotation matrix to 4x4
	RotationMatrix3x3To4x4 rot3To4;
	boost::numeric::ublas::matrix<double> rotationMatrix4x4 = rot3To4(
			rotationMatrix3x3);

	// Convert to vtkMatrix4x4
	vtkSmartPointer<vtkMatrix4x4> rotation =
			vtkSmartPointer<vtkMatrix4x4>::New();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			rotation->SetElement(i, j, rotationMatrix4x4(i, j));
		}
	}

	vtkSmartPointer<vtkTransform> transform =
			vtkSmartPointer<vtkTransform>::New();
	transform->Identity();
	transform->PostMultiply();

	// Rotate the axes according to the quaternion
	transform->Concatenate(rotation);

	double position[3];
	robotActor->GetPosition(position);
	transform->Translate(position);

	frame->SetUserTransform(transform);
	frame->Modified();
	renderer->AddActor(frame);

	framesLock->Lock();
	frames.push_back(frame);
	framesLock->Unlock();
}

void TerrainView::setIMURotation(double x, double y, double z, double w) {
	renderLock->Lock();
	robotActor->setIMURotation(x,y,z,w);
	robotAttitudeWidget->setIMURotation(x,y,z,w);

	if (this->ui->actionFrame->isChecked()) {
		plotFrame(x, y, z, w);
	}
	renderLock->Unlock();
}

void TerrainView::setIMUPosition(double x, double y, double z) {
	renderLock->Lock();
	robotActor->setIMUPosition(x,y,z);
	scale->setElevation(z);
	renderLock->Unlock();
}

void TerrainView::insertPoint(double x, double y, double z) {
	renderLock->Lock();
	if (this->ui->actionTerrain->isChecked()) {
		terrainActor->insertPoint(x, y, z);
	}
	renderLock->Unlock();
}
