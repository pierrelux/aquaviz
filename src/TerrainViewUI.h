#ifndef TerrainViewUI_H
#define TerrainViewUI_H

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

protected:
	/**
	 * Generate a set of random points.
	 * For testing purpose only.
	 * @param gridSize The desired grid size.
	 * @return The generated random points in a vtkPoints object.
	 */
	static vtkSmartPointer<vtkPoints> generateRandomPoints(
			unsigned int gridSize) {
		// Create points on an XY grid with random Z coordinate
		vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

		for (unsigned int x = 0; x < gridSize; x++) {
			for (unsigned int y = 0; y < gridSize; y++) {
				points->InsertNextPoint(x, y, vtkMath::Random(0.0, 3.0));
			}
		}

		return points;
	}

protected slots:

private:
	vtkSmartPointer<vtkPoints> points;
	vtkSmartPointer<vtkPolyData> polydata;
	vtkSmartPointer<vtkDelaunay2D> delaunay;

	vtkMutexLock* renderLock;
	vtkSmartPointer<vtkActor> cubeActor;
	vtkSmartPointer<vtkCubeSource> cubeSource;

	// Designer form
	Ui_TerrainView *ui;

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
};

#endif // TerrainViewUI_H
