/**
 * @author Pierre-Luc Bacon <pbacon@cim.mcgill.ca>
 */

#ifndef ROBOTACTOR_H_
#define ROBOTACTOR_H_

#include "vtkProp3D.h"

class vtkActor;
class vtkAppendPolyData;
class vtkAssembly;
class vtkCubeSource;
class vtkFeatureEdges;
class vtkPropCollection;
class vtkProperty;
class vtkRenderer;
class vtkTransform;
class vtkTransformFilter;
class vtkVectorText;

class VTK_HYBRID_EXPORT RobotActor : public vtkProp3D
{
public:
  static RobotActor *New();
  vtkTypeRevisionMacro(RobotActor,vtkProp3D);
  void PrintSelf(ostream& os, vtkIndent indent);

  /**
   * For some exporters and other other operations we must be
   * able to collect all the actors or volumes. These methods
   * are used in that process.
   */
  virtual void GetActors(vtkPropCollection *);
  virtual int RenderOpaqueGeometry(vtkViewport *viewport);
  virtual int RenderTranslucentPolygonalGeometry(vtkViewport *viewport);
  virtual int HasTranslucentPolygonalGeometry();
  void ShallowCopy(vtkProp *prop);

  /**
   * Release any graphics resources that are being consumed by this actor.
   * The parameter window could be used to determine which graphic
   * resources to release.
   */
  void ReleaseGraphicsResources(vtkWindow *);

  /**
   * Get the bounds for this Actor as (Xmin,Xmax,Ymin,Ymax,Zmin,Zmax). (The
   * method GetBounds(double bounds[6]) is available from the superclass.)
   */
  void GetBounds(double bounds[6]);
  double *GetBounds();

  /**
   * Get the actors mtime plus consider its properties and texture if set.
   */
  unsigned long int GetMTime();

  void setIMURotation(double x, double y, double z, double w);

  void setIMUPosition(double x, double y, double z);

  void GetPosition(double position[3]);

protected:
  RobotActor();
  ~RobotActor();
  vtkCubeSource      *CubeSource;
  vtkActor           *CubeActor;

  vtkTransformFilter *TransformFilter;
  vtkTransform       *Transform;

  vtkAssembly        *Assembly;

  void                UpdateProps();

private:
  RobotActor(const RobotActor&);  // Not implemented.
  void operator=(const RobotActor&);  // Not implemented.
};

#endif /* ROBOTACTOR_H_ */
