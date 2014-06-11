#include "vector2f.h"
#include <vector>

class Path{
    public:
        Path(): start(), dest(), waypoints(), steps(5), next(0), travelDist(0){}
        Path(Vector2f, Vector2f);
        ~Path(){ waypoints.clear(); }
        void setStartPoint(Vector2f start) { 
            this->start = start;
            waypoints.reserve((steps+1)*2); 
        }
        void updateDestination(Vector2f newDest){
            dest = newDest;
            createPath();
        }
        Vector2f getNextPoint() {
            if(next >= waypoints.size()) return dest;
            else return waypoints[next++];
        }
        Vector2f getCurrentPoint(){
            return waypoints[next];
        }
        float getTravelDistance(){ return travelDist; }
    private:
        Vector2f start;
        Vector2f dest;
        std::vector<Vector2f> waypoints;
        int steps;
        int next;
        float travelDist;
        
        void createPath();

        Path(const Path&);
        Path& operator=(const Path&);
};
