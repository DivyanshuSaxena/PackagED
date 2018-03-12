#include "Classes.h"

using namespace std;


Wireframe Projection2D::create3D(){

}
vector<Point> Projection2D::determineAllPoints(){
    vector<Point> answer;
    for(auto it=(frontview.vertices.begin());it!=frontview.vertices.end();it++){
        for(auto nestit=(it->points.begin());nestit!=it->points.end();nestit++){
            string thislabel = nestit->label;
            for(auto itfind=topview.vertices.begin();itfind!=topview.vertices.end();itfind++){
                bool found = false;
                for(auto nestitfind=itfind->points.begin();nestitfind!= itfind->points.end();nestitfind++){
                    string findlabel = nestitfind->label;
                    if(thislabel==findlabel){
                        found=true;
                        Point determinedpoint = determinePoint(*nestit, *nestitfind);
                        answer.push_back(determinedpoint);
                        break;
                    }
                    
                }
                if(found==true){
                    break;
                }
            }

        }
    }
    return answer;
}

Point Projection2D::determinePoint(Point pfront, Point ptop) {
    ///
    /// This function extends the points from the top view and front view to give the 3D projection of the Point
    ///
    Point coincidingpoint;
    if(!(pfront.x == ptop.x)){
        //throw exception that not possible
        cout << "not possible projection" << endl;
    }
    coincidingpoint.setCoordinatesAndLabel(ptop.x,ptop.y,pfront.z,ptop.label);
    return coincidingpoint;
}

vector<Edge> Projection2D::determineEdges(Point vertex, Point topNeighbours[], Point frontNeighbours[]) {
    ///
    /// This function determines the edges containing the Point vertex as one of the endpoints
    /// By interpreting its neighbours from the top view and front view
    ///
    
}
