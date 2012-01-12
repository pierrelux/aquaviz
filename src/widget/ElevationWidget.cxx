/**
 * @author Pierre-Luc Bacon <pbacon@cim.mcgill.ca>
 */
#include "ElevationWidget.h"

#include <vtkAxisActor2D.h>
#include <vtkCommand.h>
#include <vtkObjectFactory.h>
#include <vtkMath.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkEvent.h>
#include <vtkWindow.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkUnsignedCharArray.h>
#include <vtkActor2D.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>
#include <vtkCellData.h>
#include <vtkCoordinate.h>
#include <vtkTextMapper.h>
#include <vtkActor2D.h>

vtkCxxRevisionMacro(ElevationWidget, "$Revision: 1.1.1.1 $");
vtkStandardNewMacro( ElevationWidget);

ElevationWidget::ElevationWidget() {
	this->RightBorderOffset = 50;
	this->TopBorderOffset = 30;
	this->LeftBorderOffset = 50;
	this->BottomBorderOffset = 30;

	axis = vtkAxisActor2D::New();
	axis->GetPositionCoordinate()->SetCoordinateSystemToViewport();
	axis->GetPosition2Coordinate()->SetCoordinateSystemToViewport();
	axis->GetPositionCoordinate()->SetReferenceCoordinate(NULL);
	axis->SetFontFactor(0.6);
	axis->SetNumberOfLabels(20);
	axis->AdjustLabelsOn();
	//axis->SetTitle("Elevation");
	axis->SetTitlePosition(1);
	axis->SetRange(-20,0);
	axis->SetTickVisibility (1);
    axis->SetTickOffset(1);
    axis->SetNumberOfMinorTicks(10);

	this->Coordinate = vtkCoordinate::New();
	this->Coordinate->SetCoordinateSystemToDisplay();

	this->TitleMapper = vtkTextMapper::New();
	this->TitleActor = vtkActor2D::New();
	this->TitleActor->SetMapper(this->TitleMapper);
}

ElevationWidget::~ElevationWidget() {
	axis->Delete();
	this->Coordinate->Delete();
}

void ElevationWidget::GetActors2D(vtkPropCollection *pc) {
	pc->AddItem(axis);
}

void ElevationWidget::ReleaseGraphicsResources(vtkWindow *w) {
	this->TitleActor->ReleaseGraphicsResources(w);
	this->axis->ReleaseGraphicsResources(w);
}

int ElevationWidget::RenderOpaqueGeometry(vtkViewport *viewport) {
	this->BuildRepresentation(viewport);
	return this->axis->RenderOpaqueGeometry(viewport) + this->TitleActor->RenderOpaqueGeometry(viewport);
}

int ElevationWidget::RenderOverlay(vtkViewport *viewport) {
	return axis->RenderOverlay(viewport) + this->TitleActor->RenderOpaqueGeometry(viewport);
}

void ElevationWidget::BuildRepresentation(vtkViewport *viewport) {
	// Specify the locations of the axes.
	int *size = viewport->GetSize();

	axis->GetPositionCoordinate()->SetValue(size[0] - this->RightBorderOffset,
			2.0 * this->BottomBorderOffset, 0.0);
	axis->GetPosition2Coordinate()-> SetValue(
			size[0] - this->RightBorderOffset, size[1] - 2.0
					* this->TopBorderOffset, 0.0);
}

void ElevationWidget::PrintSelf(ostream& os, vtkIndent indent) {
	//Superclass typedef defined in vtkTypeMacro() found in vtkSetGet.h
	this->Superclass::PrintSelf(os, indent);
}

void ElevationWidget::setElevation(double elevation)
{
	this->axis->SetRange(elevation-(elevation/2), elevation+(elevation/2));
	this->axis->Modified();
	this->TitleMapper->SetInput("asdfasf");
}

