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
vector<Point> OrthoProjection::sameclusterpoints(Point point){
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
}
bool OrthoProjection::isConnected(string s1,string s2){
    auto edge2ditr = find_if(edges.begin(),edges.end(),[s1,s2](Edge2D thisedge)->bool{
        auto p1pointitr = find_if(thisedge.cp1.points.begin(),thisedge.cp1.points.end(),[s1,s2](Point p)->bool{
            return(p.label==s1 || p.label==s2);
        });
        if(p1pointitr!=thisedge.cp1.points.end()){
            auto p2pointitr =find_if(thisedge.cp2.points.begin(),thisedge.cp2.points.end(),[s1,s2,p1pointitr](Point p)->bool{
                if(p.label==s1 || p.label==s2){
                    if(p.label==p1pointitr->label){
                        cout << "major error encountered: same point present in both edges "<<endl;
                    }
                }
                return(p.label==s1 || p.label==s2);
            });
            if(p2pointitr!=thisedge.cp2.points.end()){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    });
    if(edge2ditr!=edges.end()){
        return true;
    }else{
        return false;
    }
}

