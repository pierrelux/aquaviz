#ifndef TerrainViewUI_H
#define TerrainViewUI_H

#include "widget/ScaleActor.h"
#include "widget/TerrainActor.h"
#include "widget/RobotAttitudeWidget.h"

#include "vtkSmartPointer.h"
#include <vtkPoints.h>
#include <vtkMath.h>
#include <vtkMutexLock.h>
#include <vtkDelaunay2D.h>
#include <vtkCommand.h>
#include <vtkPolyData.h>
#include <vtkRenderWindow.h>
#include <vtkTransform.h>
#include <vtkActor.h>
#include <vtkCubeSource.h>

#include <QMainWindow>

// Forward Qt class declarations
class Ui_TerrainView;
class Quaternion;

class TerrainView: public QMainWindow {
Q_OBJECT
public:

	// Constructor/Destructor
	TerrainView();
	~TerrainView() {
	}
	;

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

	/**
	 * Clear the vertices
	 * @postcondition The set of vertices will be cleared.
	 */
	void clear();

	/**
	 * Flush the points to the display.
	 * @postcondition The triangulation will be computed from the
	 * set of points and the rendering thread will render the triangulation.
	 */
	void flush();

public slots:
	virtual void slotExit();
	virtual void slotConnect();
protected slots:

private:
	vtkMutexLock* renderLock;
	vtkSmartPointer<vtkActor> robotActor;
	vtkSmartPointer<TerrainActor> terrainActor;
	vtkSmartPointer<RobotAttitudeWidget> robotAttitudeWidget;
	vtkSmartPointer<vtkRenderer> renderer;

	vtkSmartPointer<vtkMatrix4x4> oldRotation;

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
	 * Create a simplified model of the robot in 3D
	 * @return A robot actor.
	 */
	vtkSmartPointer<vtkActor> createRobotModel();
};

#endif // TerrainViewUI_H
