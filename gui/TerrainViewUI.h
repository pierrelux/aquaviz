#ifndef TerrainViewUI_H
#define TerrainViewUI_H
 
#include "vtkSmartPointer.h"
#include <vtkPoints.h>
#include <vtkMath.h>
#include <QMainWindow>
 
// Forward Qt class declarations
class Ui_TerrainView;
 
class TerrainView : public QMainWindow
{
  Q_OBJECT
public:
 
  // Constructor/Destructor
  TerrainView(); 
  ~TerrainView() {};
 
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
 
  // Designer form
  Ui_TerrainView *ui;
};
 
#endif // TerrainViewUI_H
