/**
 * @author Pierre-Luc Bacon <pbacon@cim.mcgill.ca>
 */
#ifndef ELEVATIONWIDGET_H__
#define ELEVATIONWIDGET_H__

#include "vtkProp.h"
#include "vtkCoordinate.h" // For vtkViewportCoordinateMacro

class vtkAxisActor2D;
class vtkTextMapper;
class vtkActor2D;

class VTK_HYBRID_EXPORT ElevationWidget : public vtkProp
{
public:
  // Description:
  // Instantiate the class.
  static ElevationWidget *New();

  // Description:
  // Standard methods for the class.
  vtkTypeRevisionMacro(ElevationWidget,vtkProp);
  void PrintSelf(ostream& os, vtkIndent indent);

  vtkGetObjectMacro(axis,vtkAxisActor2D);

  // Decsription:
  // Standard methods supporting the rendering process.
  virtual void BuildRepresentation(vtkViewport *viewport);
  virtual void GetActors2D(vtkPropCollection*);
  virtual void ReleaseGraphicsResources(vtkWindow*);
  virtual int RenderOverlay(vtkViewport*);
  virtual int RenderOpaqueGeometry(vtkViewport*);

  void setElevation(double z);

protected:
  ElevationWidget();
  ~ElevationWidget();

  int    LabelMode;
   int    RightBorderOffset;
   int    TopBorderOffset;
   int    LeftBorderOffset;
   int    BottomBorderOffset;

  vtkAxisActor2D *axis;
  vtkCoordinate       *Coordinate;

  vtkTextMapper *TitleMapper;
  vtkActor2D    *TitleActor;

  vtkTimeStamp         BuildTime;

private:
  ElevationWidget(const ElevationWidget&);  //Not implemented
  void operator=(const ElevationWidget&);  //Not implemented
};

#endif
