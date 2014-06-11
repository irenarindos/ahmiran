#include "path.h"
#include <stdlib.h>

Path::Path(Vector2f start, Vector2f dest):
    start(start),
    dest(dest),
    waypoints(),
    steps(5),
    next(1)
{
    waypoints.reserve((steps+1)*2);
    createPath();
}

void Path::createPath(){
    //C = A + k(B - A)
    //k = (the distance you want) / (distance from A to B)
    float distAB = Vector2f::distance(start, dest);
    float stepDist = distAB / steps;
    Vector2f AtoB = start - dest;
    float scale;
    std::vector<Vector2f> points;
    int i;

    //calculate points on line between start and dest vectors
    points.push_back(start);
    for(i = 1; i <= steps; ++i){
        scale = (i*stepDist)/distAB;
        points.push_back(start+scale*AtoB);
    }
    points.push_back(dest);

    std::vector<Vector2f>::iterator cur, next;
    for(i = 0; i < (steps+1)*2 - 1; ++i){
        Vector2f p1 = points[i];
        Vector2f p2 = points[i+1];
        if(rand()%2){
            waypoints.push_back(Vector2f(p1[0], p2[1]));
            travelDist = std::abs(p2[1] - p1[1]);
        }
        else{
            waypoints.push_back(Vector2f(p2[0], p1[1]));
            travelDist = std::abs(p2[0] - p1[0]);
        }        
        waypoints.push_back(p2);
    }
}
