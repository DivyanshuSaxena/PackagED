#include "Classes.h"
//using namespace std;
#include <algorithm>
vector<Point> OrthoProjection::possibleNeighbours(Point point) {
    ///
    /// Function that returns a list of possible neighbors of the point passed in parameter, from the current orthographic projection
    ///
    vector<Point> answer;
    auto samecluster = find_if(vertices.begin(),vertices.end(),[point](ClusteredPoint p)->bool{
        if(find_if(p.points.begin(),p.points.end(),[point](Point thispoint)->bool{
            return(thispoint.label==point.label);            
        })!= p.points.end()){
            return true;
        }else{
            return false;
        }
    });
    cout<<"dekho bhai "<<endl;
    for(auto it= samecluster->points.begin();it!=samecluster->points.end();it++){
        if(it->label != point.label){
            cout <<"vertice wala" <<endl;
            answer.push_back((* it));
        }
    }
    cout << "yha tk chala hai "<<endl;
    auto pointeranswer= &answer;
    auto thisedge = find_if(edges.begin(),edges.end(),[point,pointeranswer](Edge2D thisoneedge)->bool{
        auto p1cluster =  find_if(thisoneedge.cp1.points.begin(),thisoneedge.cp1.points.end(),[point](Point p)->bool{
                                return(p.label==point.label);
                            });
        if(p1cluster!=thisoneedge.cp1.points.end()){
            for(auto cp2iterator= thisoneedge.cp2.points.begin();cp2iterator!=thisoneedge.cp2.points.end();cp2iterator++){
                //cout<< answer.size()<<endl;
                Point cp2point = * cp2iterator;
                pointeranswer->push_back(cp2point);
            }
            return true;
        }else{
            auto p2cluster =  find_if(thisoneedge.cp2.points.begin(),thisoneedge.cp2.points.end(),[point](Point p)->bool{
                                return(p.label==point.label);
                            });
            if(p2cluster!=thisoneedge.cp2.points.end()){
                for(auto cp1iterator= thisoneedge.cp1.points.begin();cp1iterator!=thisoneedge.cp1.points.end();cp1iterator++){
                    //cout<< answer.size()<<endl;
                    Point cp1point = * cp1iterator;
                    pointeranswer->push_back(cp1point);
                }
                return true;
            }else{
                return false;
            }
        }
    });
    if(thisedge==edges.end()){
        cout << "this is not possible"<< endl;
    }
    return answer;
}

