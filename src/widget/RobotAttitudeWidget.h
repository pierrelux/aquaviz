/**
 * @author Pierre-Luc Bacon <pbacon@cim.mcgill.ca>
 */
#ifndef ROBOTATTITUDEWIDGET_H__
#define ROBOTATTITUDEWIDGET_H__

#include <vtkInteractorObserver.h>
#include <vtkMatrix4x4.h>

// Forward declaration
class vtkActor;
class vtkRenderer;
class vtkAxesActor;
class vtkCamera;

class RobotAttitudeWidget: public vtkInteractorObserver {
public:
	vtkTypeRevisionMacro(RobotAttitudeWidget, vtkInteractorObserver);
	static RobotAttitudeWidget* New();

	void PrintSelf(ostream& os, vtkIndent indent);

	/**
	 * Enable/disable the widget.
	 */
	virtual void SetEnabled(int);

	/**
	 * Set/get the viewport to position/size this widget.
	 */
	void SetViewport(double minX, double minY, double maxX, double maxY);

	double* GetViewport();

	/**
	 * @param
	 */
	void setIMURotation(double x, double y, double z, double w);

protected:
	RobotAttitudeWidget();
	~RobotAttitudeWidget();

	vtkRenderer *renderer;
	vtkActor *robotActor;
	vtkAxesActor *axes;
	vtkCamera* camera;
};


#endif // ROBOTATTITUDEWIDGET_H__
