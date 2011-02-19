#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkDelaunay2D.h>
#include <vtkMath.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVertexGlyphFilter.h>

#include <vtkCommand.h>
#include <vtkProgrammableFilter.h>

#include <thread>
#include <iostream>
#include <functional>

class RenderingRefresher: public vtkCommand {
public:
	vtkTypeRevisionMacro(RenderingRefresher, vtkCommand);
	static RenderingRefresher *New() {
		return new RenderingRefresher;
	}

	void Execute(vtkObject *caller, unsigned long vtkNotUsed(eventId),
			void *vtkNotUsed(callData)) {
		std::cout << "timer callback" << std::endl;

		vtkRenderWindowInteractor *iren =
				static_cast<vtkRenderWindowInteractor*> (caller);

		iren->Render();

	}
};
vtkCxxRevisionMacro(RenderingRefresher, "$Revision: 1.1 $");

/**
 * VTK Does not allow vtkActor do be subclassed easily.
 * This class provides a "Terrain" actor for a set of points.
 */
class Terrain {
public:
	Terrain() {
		// Generate a set of points
		points = generateRandomPoints(10);

		// Add the grid points to a polydata object
		polydata = vtkSmartPointer<vtkPolyData>::New();
		polydata->SetPoints(points);

		// Triangulate the grid points
		delaunay = vtkSmartPointer<vtkDelaunay2D>::New();
		delaunay->SetInput(polydata);
		delaunay->Update();

		// Create a mapper and actor
		vtkSmartPointer<vtkPolyDataMapper> triangulatedMapper =
				vtkSmartPointer<vtkPolyDataMapper>::New();
		triangulatedMapper->SetInputConnection(delaunay->GetOutputPort());

		triangulatedActor = vtkSmartPointer<vtkActor>::New();
		triangulatedActor->SetMapper(triangulatedMapper);
		triangulatedActor->RotateX(45);

	}
	virtual ~Terrain() {
	}
	;

	/**
	 * @return The underlying vtkActor
	 */
	vtkSmartPointer<vtkActor> getActor() {
		return triangulatedActor;
	}

	/**
	 * @param points The underlying points being triangulated.
	 */
	void setPoints(vtkPoints* points) {
		this->points = points;
		polydata->SetPoints(points);
		delaunay->Update();
		polydata->Modified();
	}

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

private:
	vtkSmartPointer<vtkPoints> points;
	vtkSmartPointer<vtkPolyData> polydata;
	vtkSmartPointer<vtkDelaunay2D> delaunay;
	vtkSmartPointer<vtkActor> triangulatedActor;
};

class PointsGenerator {
public:
	explicit PointsGenerator(Terrain& terrain,
			vtkSmartPointer<vtkRenderer>& renderer) :
		terrain(terrain), renderer(renderer) {
		std::cout << "Constructing" << std::endl;
	}

	void operator()() {
		while (1) {
			std::cout << "Generating points" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			terrain.setPoints(terrain.generateRandomPoints(10));
		}
	}

	Terrain& terrain;
	vtkSmartPointer<vtkRenderer>& renderer;
};

int main(int, char *[]) {
	// Create renderer
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

	// Add renderer to render window
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<
			vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

	// Add Interactor to render window
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
			vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	// Add the actor to the scene
	Terrain terrain;
	renderer->AddActor(terrain.getActor());

	renderer->SetBackground(.5, .5, 1.0);

	// Start thread
	std::thread t((PointsGenerator(terrain, renderer)));

	// Render and interact
	renderWindow->Render();

	// Initialize must be called prior to creating timer events.
	renderWindowInteractor->Initialize();

	// Sign up to receive TimerEvent
	vtkSmartPointer<RenderingRefresher> cb =
			vtkSmartPointer<RenderingRefresher>::New();
	renderWindowInteractor->AddObserver(vtkCommand::TimerEvent, cb);

	int timerId = renderWindowInteractor->CreateRepeatingTimer(100);
	std::cout << "timerId: " << timerId << std::endl;

	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}

