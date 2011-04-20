/*
 * TerrainActor.cpp
 *
 *  Created on: 2011-04-17
 *      Author: pierre-luc
 */

#include "TerrainActor.h"

#include <vtkObjectFactory.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkTransform.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkDelaunay2D.h>
#include <vtkPolyDataMapper.h>
#include <vtkMath.h>

vtkCxxRevisionMacro(TerrainActor, "$Revision: 1.45 $");
vtkStandardNewMacro( TerrainActor);

// Creates a follower with no camera set
TerrainActor::TerrainActor() {
	this->points = vtkPoints::New();
	this->points->SetDataTypeToDouble();

	this->polydata = vtkPolyData::New();
	this->polydata->SetPoints(this->points);

	this->delaunay = vtkDelaunay2D::New();
	this->delaunay->SetInput(this->polydata);

	this->polyMapper = vtkPolyDataMapper::New();
	this->polyMapper->SetInputConnection(this->delaunay->GetOutputPort());

	this->SetMapper(this->polyMapper);

	std::cerr << "TerrainActor created" << std::endl;
}

TerrainActor::~TerrainActor() {
	this->points->Delete();
	this->polydata->Delete();
	this->delaunay->Delete();
	this->polyMapper->Delete();
}


void TerrainActor::PrintSelf(ostream& os, vtkIndent indent) {
	this->Superclass::PrintSelf(os, indent);

	os << indent << "TerrainActor: (none)\n";
}

int TerrainActor::RenderOpaqueGeometry(vtkViewport *vp) {
	std::cerr << "RenderOpaqueGeometry" << std::endl;
	if (!this->Mapper) {
		return 0;
	}

	if (!this->Property) {
		// force creation of a property
		this->GetProperty();
	}

	if (this->GetIsOpaque()) {
		vtkRenderer *ren = static_cast<vtkRenderer *> (vp);
		this->Render(ren);
		return 1;
	}
	return 0;
}

int TerrainActor::RenderTranslucentGeometry(vtkViewport *vp) {
	std::cerr << "RenderTranslucentGeometry" << std::endl;

	if (!this->Mapper) {
		return 0;
	}

	if (!this->Property) {
		// force creation of a property
		this->GetProperty();
	}

	if (!this->GetIsOpaque()) {
		vtkRenderer *ren = static_cast<vtkRenderer *> (vp);
		this->Render(ren);
		return 1;
	}
	return 0;
}

void TerrainActor::Render(vtkRenderer* renderer)
{
	std::cerr << "Rendering " << std::endl;
	this->delaunay->Modified();
	this->Property->Render(this, renderer);
	this->polyMapper->Render(renderer, this);
}

void TerrainActor::ShallowCopy(vtkProp *prop) {
	// Now do superclass
	this->vtkActor::ShallowCopy(prop);
}

unsigned long TerrainActor::GetMTime()
{
	return this->points->GetMTime();
}

unsigned long TerrainActor::GetRedrawMTime() {
	return this->points->GetMTime();
}

void TerrainActor::insertPoint(double x, double y, double z)
{
	//std::cout << "M time before " << this->points->GetMTime() << std::endl;
	this->points->InsertNextPoint(x, y, z);
	this->points->Modified();
	//std::cout << "M time after " << this->points->GetMTime() << std::endl;
}

