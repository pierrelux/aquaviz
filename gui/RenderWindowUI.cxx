#include <QApplication>
#include "TerrainViewUI.h"
 
int main( int argc, char** argv )
{
  // QT Stuff
  QApplication app( argc, argv );
 
  TerrainView myTerrainView;
  myTerrainView.show();
 
  return app.exec();
}
