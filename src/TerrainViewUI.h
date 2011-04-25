#ifndef TerrainViewUI_H
#define TerrainViewUI_H

#include "widget/ScaleActor.h"
#include "widget/RobotActor.h"
#include "widget/TerrainActor.h"
#include "widget/RobotAttitudeWidget.h"

#include <vector>

#include <QMainWindow>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkPoints.h>
#include <vtkCommand.h>
#include <vtkPNGWriter.h>
#include <vtkMutexLock.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkWindowToImageFilter.h>

// Forward Qt class declarations
class Ui_TerrainView;
class Quaternion;

class TerrainView: public QMainWindow {
Q_OBJECT
public:
	TerrainView();
	~TerrainView() {};

	/**
	 * Insert a new point
	 * @param x
	 * @param y
	 * @param z
	 */
	void insertPoint(double x, double y, double z);


	/**
	 * The quaternion that represents the rotation from the
	 * global frame to the IMU frame on the robot.
	 * @param x
	 * @param y
	 * @param z
	 * @param w
	 */
	void setIMURotation(double x, double y, double z, double w);

	/**
	 * The position of the IMU frame in
     * global coordinates (in meters).
	 * @param x
	 * @param y
	 * @param z
	 */
	void setIMUPosition(double x, double y, double z);

protected slots:
	virtual void slotExit();
	virtual void slotConnect();
	virtual void slotTerrain();
	virtual void slotFrame();
	virtual void slotAttitude();
	virtual void slotGroundPlane();
	virtual void slotOrigin();
	virtual void slotScreenshot();

private:
	vtkMutexLock* renderLock;

	vtkSmartPointer<vtkCamera> camera;
	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<RobotActor> robotActor;
	vtkSmartPointer<TerrainActor> terrainActor;
	vtkSmartPointer<RobotAttitudeWidget> robotAttitudeWidget;

	vtkSmartPointer<vtkPNGWriter> imageWriter;
	vtkSmartPointer<vtkActor> groundPlaneActor;
	vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter;

	vtkMutexLock* framesLock;
	std::vector<vtkAxesActor*> frames;
	vtkSmartPointer<vtkAxesActor> axesActor;

	// Designer form
	Ui_TerrainView *ui;

	/**
	 * Rendering Callback. Refreshes the display at a
	 * constant interval.
	 */
	class RenderingTimerCallback: public vtkCommand {
	public:
		RenderingTimerCallback(TerrainView* parent, vtkSmartPointer<vtkRenderWindow> renderWindow) :
			parent(parent),
		    renderWindow(renderWindow) {};
		virtual ~RenderingTimerCallback() {};

		virtual void Execute(vtkObject *vtkNotUsed(caller), unsigned long eventId,
				void *vtkNotUsed(callData)) {
			//std::cout << "refreshing" << std::endl;
			parent->renderLock->Lock();
			renderWindow->Render();
			parent->renderLock->Unlock();
		}
	private:
		TerrainView* parent;
		vtkSmartPointer<vtkRenderWindow> renderWindow;
	};

	/**
	 * Create a virtual ground plane (horizon) below the robot on the sea floor.
	 * @return A plane actor.
	 */
	vtkSmartPointer<vtkActor> createGroundPlane();

	/**
	 * Set visibility on all the frames rendered so far.
	 * @param v Visibility : 0 invisible, 1 visible.
	 */
	void setFramesVisibility(int v);

	/**
	 * Create a new axes actor.
	 * @param x
	 * @param y
	 * @param z
	 * @param w
	 */
	void plotFrame(double x, double y, double z, double w);
};

#endif // TerrainViewUI_H
