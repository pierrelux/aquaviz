#ifndef ROBOTATTITUDEWIDGET_H__
#define ROBOTATTITUDEWIDGET_H__

#include <vtkInteractorObserver.h>
#include <vtkObjectFactory.h>

class vtkActor;
class vtkRenderer;

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

protected:
	RobotAttitudeWidget();
	~RobotAttitudeWidget();

	vtkRenderer *renderer;
	vtkActor *robotActor;
};


#endif // ROBOTATTITUDEWIDGET_H__
