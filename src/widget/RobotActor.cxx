#include "RobotActor.h"

// FIXME : Should not have relative paths
#include "../util/QuaternionToRotationMatrix.h"
#include "../util/RotationMatrix3x3To4x4.h"
#include "../util/Quaternion.h"

#include "vtkActor.h"
#include "vtkAppendPolyData.h"
#include "vtkAssembly.h"
#include "vtkCubeSource.h"
#include "vtkFeatureEdges.h"
#include "vtkObject.h"
#include "vtkObjectFactory.h"
#include "vtkPropCollection.h"
#include "vtkProperty.h"
#include "vtkRenderWindow.h"
#include "vtkPolyDataMapper.h"
#include "vtkPolyData.h"
#include "vtkRenderer.h"
#include "vtkTransform.h"
#include "vtkTransformFilter.h"
#include "vtkVectorText.h"
#include "vtkSmartPointer.h"

vtkCxxRevisionMacro(RobotActor, "$Revision: 1.1.1.1 $");
vtkStandardNewMacro(RobotActor);

RobotActor::RobotActor()
{

  this->Assembly = vtkAssembly::New();

  this->CubeSource = vtkCubeSource::New();
	this->CubeSource->SetYLength(0.25);
	this->CubeSource->SetXLength(0.50);
	this->CubeSource->SetZLength(0.10);
	this->CubeSource->SetCenter(0, 0, 0);

  vtkPolyDataMapper *cubeMapper = vtkPolyDataMapper::New();
  this->CubeActor = vtkActor::New();
  cubeMapper->SetInput( this->CubeSource->GetOutput() );
  this->CubeActor->SetMapper( cubeMapper );
  cubeMapper->Delete();

  this->Assembly->AddPart( this->CubeActor );

  vtkProperty* prop = this->CubeActor->GetProperty();
  prop->SetColor(1, 1, 0);

  this->UpdateProps();
}

RobotActor::~RobotActor()
{
  this->CubeSource->Delete();
  this->CubeActor->Delete();

  this->TransformFilter->Delete();
  this->Transform->Delete();

  this->Assembly->Delete();
}

void RobotActor::ShallowCopy(vtkProp *prop)
{
  RobotActor *a = RobotActor::SafeDownCast(prop);
  if ( a != NULL )
    {
	  /** Do nothing. For now */
    }

  // Now do superclass
  this->vtkProp3D::ShallowCopy(prop);
}

void RobotActor::GetActors(vtkPropCollection *ac)
{
  this->Assembly->GetActors( ac );
}

int RobotActor::RenderOpaqueGeometry(vtkViewport *vp)
{
  this->UpdateProps();

  return this->Assembly->RenderOpaqueGeometry(vp);
}

int RobotActor::RenderTranslucentPolygonalGeometry(vtkViewport *vp)
{
  this->UpdateProps();

  return this->Assembly->RenderTranslucentPolygonalGeometry( vp );
}


int RobotActor::HasTranslucentPolygonalGeometry()
{
  this->UpdateProps();

  return this->Assembly->HasTranslucentPolygonalGeometry();
}

void RobotActor::ReleaseGraphicsResources(vtkWindow *win)
{
  this->Assembly->ReleaseGraphicsResources( win );
}

void RobotActor::GetBounds(double bounds[6])
{
  this->Assembly->GetBounds( bounds );
}

double *RobotActor::GetBounds()
{
  return this->Assembly->GetBounds( );
}

unsigned long int RobotActor::GetMTime()
{
  return this->Assembly->GetMTime();
}

void RobotActor::UpdateProps()
{

}

void RobotActor::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "RobotActor" << endl;
}

void RobotActor::setIMURotation(double x, double y, double z, double w) {
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

	// Get current position
	double position[3];
	this->Assembly->GetPosition(position);

	// Robot model
	vtkSmartPointer<vtkTransform> transform =
			vtkSmartPointer<vtkTransform>::New();
	transform->Identity();
	transform->PostMultiply();

	// Rotate the robot back to the origin
	transform->Translate(-position[0], -position[1], -position[2]);

	// Rotate the robot according to the quaternion
	transform->Concatenate(rotation);

	// Translate the robot forward with the new position
	transform->Translate(position);

	this->Assembly->SetUserTransform(transform);
	this->Assembly->Modified();
}

void RobotActor::setIMUPosition(double x, double y, double z) {
	this->Assembly->SetPosition(x, y, z);
	this->Assembly->Modified();
}

void RobotActor::GetPosition(double position[3])
{
	this->Assembly->GetPosition(position);
}

