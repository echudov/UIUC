/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;

Point<3> convertToXYZ(LUVAPixel pixel)
{
    return Point<3>(pixel.l, pixel.u, pixel.v);
}

MosaicCanvas *mapTiles(SourceImage const &theSource,
                       vector<TileImage> &theTiles)
{
    /**
     * @todo Implement this function!
     */

    vector<Point<3>> points;
    map<Point<3>, TileImage *> map;

    for (auto &elem : theTiles)
    {
        LUVAPixel pixel = elem.getAverageColor();
        Point<3> point = convertToXYZ(pixel);
        points.push_back(point);
        map[point] = &elem;
    }
    KDTree<3> averageColorKD(points);

    MosaicCanvas *toReturn = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

    for (int i = 0; i < toReturn->getRows(); ++i)
    {
        for (int j = 0; j < toReturn->getColumns(); ++j)
        {
            Point<3> target = convertToXYZ(theSource.getRegionColor(i, j));
            Point<3> best = averageColorKD.findNearestNeighbor(target);
            TileImage *correctImg = map[best];
            toReturn->setTile(i, j, correctImg);
        }
    }

    return toReturn;
}
