#include "Classes.h"
#include <algorithm>
using namespace std;


Wireframe Projection2D::create3D(){
    vector<Point> allpoints = determineAllPoints();
    vector<Edge> doublecalculatedpossibleedges;
    // doublecalculatedpossibleedges has all the edges calculated twice
    vector<vector<Edge> > correspondingpossibleedges;
    vector<vector<Point> > correspondingtopviewneighbours;
    vector<vector<Point> > correspondingfronviewneighbours;
    vector<Edge> definiteedges;
    for(auto allpointitr = allpoints.begin();allpointitr!=allpoints.begin();allpointitr++){
        vector<Point> topviewpossibleneighbours = topview.possibleNeighbours(*(allpointitr));
        vector<Point> frontviewpossibleneighbours = frontview.possibleNeighbours(*(allpointitr));
        vector<Edge> possibleedges = determinePossibleEdges(*(allpointitr),&(topviewpossibleneighbours),&(frontviewpossibleneighbours),&(allpoints));
        for(auto possibleedgesitr = possibleedges.begin();possibleedgesitr!=possibleedges.end();possibleedgesitr++){
            doublecalculatedpossibleedges.push_back(* possibleedgesitr);
        }
        correspondingpossibleedges.push_back(possibleedges);
        correspondingtopviewneighbours.push_back(topviewpossibleneighbours);
        correspondingfronviewneighbours.push_back(frontviewpossibleneighbours);
        //same cluster from top and corresponding in front
        Point thispoint = * allpointitr;
        vector<Point> sametopcluster = topview.sameclusterpoints(* (allpointitr));
        for(auto sametopclusteritr = sametopcluster.begin();sametopclusteritr!=sametopcluster.end();sametopclusteritr++){
            auto corresfrontpointptr = find_if(frontviewpossibleneighbours.begin(),frontviewpossibleneighbours.end(),[sametopclusteritr](Point p)->bool{
                return(sametopclusteritr->label==p.label);
            });
            if(corresfrontpointptr!= frontviewpossibleneighbours.end()){
                Edge definitepoint;
                definitepoint.p1 = *allpointitr;
                definitepoint.p2 = determinePoint(*sametopclusteritr,*corresfrontpointptr);
                definiteedges.push_back(definitepoint);
            }
        }
        //same cluster from front and corresponding in top
        thispoint = * allpointitr;
        vector<Point> samefrontcluster = frontview.sameclusterpoints(* (allpointitr));
        for(auto samefrontclusteritr = samefrontcluster.begin();samefrontclusteritr!=samefrontcluster.end();samefrontclusteritr++){
            auto correstoppointptr = find_if(topviewpossibleneighbours.begin(),topviewpossibleneighbours.end(),[samefrontclusteritr](Point p)->bool{
                return(samefrontclusteritr->label==p.label);
            });
            if(correstoppointptr!= topviewpossibleneighbours.end()){
                Edge definitepoint;
                definitepoint.p1 = *allpointitr;
                definitepoint.p2 = determinePoint(*samefrontclusteritr,*correstoppointptr);
                definiteedges.push_back(definitepoint);
            }
        }
        //corollary 1 complete
        
    }

    //doublecalculaedpossibleedges has all the edges calculated twice now

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

vector<Edge> Projection2D::determinePossibleEdges(Point vertex, vector<Point> *topneighbourptr, vector<Point> *frontneighbourptr, vector<Point> *determinedpointsptr) {
    ///
    /// This function determines the edges containing the Point vertex as one of the endpoints
    /// By interpreting its neighbours from the top view and front view
    ///
    vector<Edge> answer;
    vector<Point> intersection;
    vector<Point> topneighbour = * (topneighbourptr);
    vector<Point> frontneighbour = * (frontneighbourptr);
    for(auto topneighbouritr=topneighbourptr->begin();topneighbouritr!=topneighbourptr->end();topneighbouritr++){
        auto correspondingpointinfrontasptr = find_if(frontneighbourptr->begin(),frontneighbourptr->end(),[topneighbouritr](Point p)->bool{
            if(p.label==topneighbouritr->label){
                return true;
            }else{
                return false;
            }
        });
        if(correspondingpointinfrontasptr!=frontneighbourptr->end()){
            Point collidedpoint = determinePoint(*(topneighbouritr),*(correspondingpointinfrontasptr));
            intersection.push_back(collidedpoint);
        }
    }
    for(auto intersectionitr = intersection.begin();intersectionitr!=intersection.end();intersectionitr++){
        Edge tempedge;
        tempedge.p1 = vertex;
        tempedge.p2 = *(intersectionitr);
        answer.push_back(tempedge);
    }
    return answer;
    
}
