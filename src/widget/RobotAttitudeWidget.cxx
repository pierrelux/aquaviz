#include "RobotAttitudeWidget.h"

#include <vtkCubeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkAxesActor.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkProperty.h>
#include <vtkCommand.h>

#include <vtkObjectFactory.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCamera.h>

vtkCxxRevisionMacro(RobotAttitudeWidget, "$Revision: 1.0 $");
vtkStandardNewMacro( RobotAttitudeWidget);

RobotAttitudeWidget::RobotAttitudeWidget() {
	vtkCubeSource* cubeSource = vtkCubeSource::New();
	cubeSource->SetYLength(0.25);
	cubeSource->SetXLength(0.50);
	cubeSource->SetZLength(0.10);

	vtkPolyDataMapper* cubeMapper = vtkPolyDataMapper::New();
	cubeMapper->SetInputConnection(cubeSource->GetOutputPort());

	robotActor = vtkActor::New();
	robotActor->SetMapper(cubeMapper);
	robotActor->GetProperty()->SetColor(1, 1, 0);

	// Create Axes Actor
	axes = vtkAxesActor::New();

	camera = vtkCamera::New();
	camera->SetPosition(3, 3, 0.5);
	camera->SetViewUp(0, 0, 1);

	renderer = vtkRenderer::New();
	renderer->SetViewport(0.0, 0.0, 0.3, 0.3);
	renderer->SetLayer(1);
	//renderer->InteractiveOff();
	renderer->SetBackground(1,0,0);
	renderer->AddViewProp(robotActor);
	renderer->SetActiveCamera(camera);
}

RobotAttitudeWidget::~RobotAttitudeWidget() {
	renderer->Delete();
	robotActor->Delete();
	axes->Delete();
}

void RobotAttitudeWidget::SetEnabled(int enabling) {
	if (enabling == 1) {
		if (!this->CurrentRenderer) {
			this->SetCurrentRenderer(this->Interactor->FindPokedRenderer(
					this->Interactor->GetLastEventPosition()[0],
					this->Interactor->GetLastEventPosition()[1]));

			if (this->CurrentRenderer == NULL) {
				return;
			}
		}

		vtkRenderWindow* renwin = this->CurrentRenderer->GetRenderWindow();
		// FIXME Check if NULL
		renwin->AddRenderer(renderer);
		if (renwin->GetNumberOfLayers() < 2) {
			renwin->SetNumberOfLayers(2);
		}

		renderer->AddViewProp(robotActor);
		renderer->AddViewProp(axes);

		robotActor->VisibilityOn();
		axes->VisibilityOn();
	} else {
		renderer->RemoveViewProp(robotActor);
		renderer->RemoveViewProp(axes);
		robotActor->VisibilityOff();
		axes->VisibilityOff();
		if (this->CurrentRenderer->GetRenderWindow()) {
			this->CurrentRenderer->GetRenderWindow()->RemoveRenderer(renderer);
		}
		this->InvokeEvent(vtkCommand::DisableEvent, NULL);
		this->SetCurrentRenderer(NULL);
	}
}

void RobotAttitudeWidget::SetViewport(double minX, double minY, double maxX,
		double maxY) {
	renderer->SetViewport(minX, minY, maxX, maxY);
}

double* RobotAttitudeWidget::GetViewport() {
	return renderer->GetViewport();
}

void RobotAttitudeWidget::PrintSelf(std::ostream& os, vtkIndent indent) {
	this->Superclass::PrintSelf(os, indent);
	os << indent << "RobotAttitudeWidget:" << endl;
}

void RobotAttitudeWidget::onIMUPoseUpdate(vtkMatrix4x4* matrix)
{
	robotActor->SetUserMatrix(matrix);
	robotActor->Modified();
}

