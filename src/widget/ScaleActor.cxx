#include "ScaleActor.h"

#include "vtkAxisActor2D.h"
#include "vtkCommand.h"
#include "vtkObjectFactory.h"
#include "vtkMath.h"
#include "vtkCamera.h"
#include "vtkRenderer.h"
#include "vtkEvent.h"
#include "vtkWindow.h"
#include "vtkPolyData.h"
#include "vtkPoints.h"
#include "vtkCellArray.h"
#include "vtkUnsignedCharArray.h"
#include "vtkActor2D.h"
#include "vtkPolyDataMapper2D.h"
#include "vtkTextMapper.h"
#include "vtkTextProperty.h"
#include "vtkCellData.h"
#include "vtkCoordinate.h"

vtkCxxRevisionMacro(ScaleActor, "$Revision: 1.1.1.1 $");
vtkStandardNewMacro( ScaleActor);

ScaleActor::ScaleActor() {
	this->RightBorderOffset = 50;
	this->TopBorderOffset = 30;
	this->LeftBorderOffset = 50;
	this->BottomBorderOffset = 30;

	axis = vtkAxisActor2D::New();
	axis->GetPositionCoordinate()->SetCoordinateSystemToViewport();
	axis->GetPosition2Coordinate()->SetCoordinateSystemToViewport();
	axis->GetPositionCoordinate()->SetReferenceCoordinate(NULL);
	axis->SetFontFactor(0.6);
	axis->SetNumberOfLabels(5);
	axis->AdjustLabelsOff();

	this->Coordinate = vtkCoordinate::New();
	this->Coordinate->SetCoordinateSystemToDisplay();
}

ScaleActor::~ScaleActor() {
	axis->Delete();
	this->Coordinate->Delete();
}

void ScaleActor::GetActors2D(vtkPropCollection *pc) {
	pc->AddItem(axis);
}

void ScaleActor::ReleaseGraphicsResources(vtkWindow *w) {
	axis->ReleaseGraphicsResources(w);
}

int ScaleActor::RenderOpaqueGeometry(vtkViewport *viewport) {
	this->BuildRepresentation(viewport);
	return axis->RenderOpaqueGeometry(viewport);
}

int ScaleActor::RenderOverlay(vtkViewport *viewport) {
	return axis->RenderOverlay(viewport);;
}

void ScaleActor::BuildRepresentation(vtkViewport *viewport) {
	// Specify the locations of the axes.
	int *size = viewport->GetSize();

	axis->GetPositionCoordinate()-> SetValue(size[0] - this->RightBorderOffset,
			2.0 * this->BottomBorderOffset, 0.0);
	axis->GetPosition2Coordinate()-> SetValue(
			size[0] - this->RightBorderOffset, size[1] - 2.0
					* this->TopBorderOffset, 0.0);
}

void ScaleActor::PrintSelf(ostream& os, vtkIndent indent) {
	//Superclass typedef defined in vtkTypeMacro() found in vtkSetGet.h
	this->Superclass::PrintSelf(os, indent);
}
