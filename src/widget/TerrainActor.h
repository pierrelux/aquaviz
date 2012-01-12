/**
 * @author Pierre-Luc Bacon <pbacon@cim.mcgill.ca>
 */

#ifndef TERRAINACTOR_H_
#define TERRAINACTOR_H_

#include <vtkActor.h>

class vtkPoints;
class vtkPolyData;
class vtkDelaunay2D;
class vtkPolyDataMapper;

class VTK_HYBRID_EXPORT TerrainActor : public vtkActor
{
 public:
  vtkTypeRevisionMacro(TerrainActor,vtkActor);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Creates a follower with no camera set
  static TerrainActor *New();

  // Description:
  // This causes the actor to be rendered. It in turn will render the actor's
  // property, texture map and then mapper. If a property hasn't been
  // assigned, then the actor will create one automatically.
  virtual int RenderOpaqueGeometry(vtkViewport *viewport);
  virtual int RenderTranslucentGeometry(vtkViewport *viewport);
  virtual void Render(vtkRenderer *ren);

  // Description:
  // Shallow copy of a follower. Overloads the virtual vtkProp method.
  void ShallowCopy(vtkProp *prop);

  void insertPoint(double x, double y, double z);

  unsigned long GetMTime();

  unsigned long GetRedrawMTime();

protected:
  TerrainActor();
  ~TerrainActor();

  // hide the two parameter Render() method from the user and the compiler.
  virtual void Render(vtkRenderer *, vtkMapper *) {};
private:
  TerrainActor(const TerrainActor&);  // Not implemented.
  void operator=(const TerrainActor&);  // Not implemented.

  vtkPoints* points;
  vtkPolyData* polydata;
  vtkDelaunay2D* delaunay;
  vtkPolyDataMapper* polyMapper;
};

#endif /* TERRAINACTOR_H_ */
