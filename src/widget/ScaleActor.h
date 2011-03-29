#ifndef SCALEACTOR_H__
#define SCALEACTOR_H__

#include "vtkProp.h"
#include "vtkCoordinate.h" // For vtkViewportCoordinateMacro

class vtkAxisActor2D;


class VTK_HYBRID_EXPORT ScaleActor : public vtkProp
{
public:
  // Description:
  // Instantiate the class.
  static ScaleActor *New();

  // Description:
  // Standard methods for the class.
  vtkTypeRevisionMacro(ScaleActor,vtkProp);
  void PrintSelf(ostream& os, vtkIndent indent);

  vtkGetObjectMacro(axis,vtkAxisActor2D);

  // Decsription:
  // Standard methods supporting the rendering process.
  virtual void BuildRepresentation(vtkViewport *viewport);
  virtual void GetActors2D(vtkPropCollection*);
  virtual void ReleaseGraphicsResources(vtkWindow*);
  virtual int RenderOverlay(vtkViewport*);
  virtual int RenderOpaqueGeometry(vtkViewport*);

protected:
  ScaleActor();
  ~ScaleActor();

  int    LabelMode;
   int    RightBorderOffset;
   int    TopBorderOffset;
   int    LeftBorderOffset;
   int    BottomBorderOffset;

  vtkAxisActor2D *axis;
  vtkCoordinate       *Coordinate;

  vtkTimeStamp         BuildTime;

private:
  ScaleActor(const ScaleActor&);  //Not implemented
  void operator=(const ScaleActor&);  //Not implemented
};

#endif
