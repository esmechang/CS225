/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    int column = theSource.getColumns();
    int row = theSource.getRows();
    MosaicCanvas *result = new MosaicCanvas(row, column);
    vector<Point<3>> vec;
    map<Point<3>, TileImage*> tileMap;
    for (vector<TileImage>::iterator iter = theTiles.begin(); iter != theTiles.end(); ++iter) {
      LUVAPixel pixel = iter->getAverageColor();
      Point<3> temp = convertToXYZ(pixel);
      tileMap.insert(pair<Point<3>, TileImage*>(temp, &(*iter)));
      vec.push_back(temp);
    }
    KDTree<3> tilesTree = KDTree<3>(vec);
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < column; j++) {
        LUVAPixel pixel = theSource.getRegionColor(i, j);
        Point<3> temp = convertToXYZ(pixel);
        Point<3> neighbor = tilesTree.findNearestNeighbor(temp);
        result->setTile(i, j, tileMap[neighbor]);
      }
    }
    return result;
}
