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
    //cout<<"samecluster points found "<<endl;
    for(auto it= samecluster->points.begin();it!=samecluster->points.end();it++){
        if(it->label != point.label){
            //cout <<"same cluster point being added is "<< it->label <<endl;
            answer.push_back((* it));
        }
    }
    //cout << "samecluster points added "<<endl;
    auto pointeranswer= &answer;
    // cout<< "checking edges"<<endl;
    // cout << "num edges is " <<edges.size() << endl;
    // cout << "last edge is " << edges[edges.size()-1].cp1.points[0] << " : " << edges[edges.size()-1].cp2.points[0] << endl;
    auto thisedge = find_if(edges.begin(),edges.end(),[point,pointeranswer](Edge2D thisoneedge)->bool{
        // cout << "new edge being iterated"<<endl;
        // cout << "lests check in cp1"<<endl;
        // cout << "considering "<<thisoneedge.cp1.points[0] << " : " << thisoneedge.cp2.points[0] <<endl;
        auto p1cluster =  find_if(thisoneedge.cp1.points.begin(),thisoneedge.cp1.points.end(),[point](Point p)->bool{
                                if(p.label==point.label){
                                    // cout << "found the point in cp1 cluster"<<endl;
                                }

                                return(p.label==point.label);
                            });
        //cout << "lets add the correspoding neighbours if any "<<endl;
        //cout << (*p1cluster)<<endl;
        //cout << (*thisoneedge.cp1.points.end())<<endl;
        if(p1cluster!=thisoneedge.cp1.points.end()){
            // cout << "hurray a succesful edge cp1 has been obtained"<<endl;
            for(auto cp2iterator= thisoneedge.cp2.points.begin();cp2iterator!=thisoneedge.cp2.points.end();++cp2iterator){
                //cout<< answer.size()<<endl;
                Point cp2point = * cp2iterator;
                // cout << "adding the neighbour "<< cp2point.label <<endl;
                pointeranswer->push_back(cp2point);
                // cout << (*pointeranswer)[pointeranswer->size() -1].label << " has been added"<<endl;
            }
            return false;
        }else{
            // cout << "lets check in cp2 "<<endl;
            auto p2cluster =  find_if(thisoneedge.cp2.points.begin(),thisoneedge.cp2.points.end(),[point](Point p)->bool{
                                if(p.label==point.label){
                                    // cout << "found the point in cp2 cluster"<<endl;
                                }
                                
                                return(p.label==point.label);
                            });
            if(p2cluster!=thisoneedge.cp2.points.end()){
                // cout << "hurray a succesful edge cp2 has been obtained"<<endl;
                for(vector<Point>::iterator cp1iterator= thisoneedge.cp1.points.begin();cp1iterator != thisoneedge.cp1.points.end();cp1iterator++){
                    //cout<< answer.size()<<endl;
                    Point cp1point = * cp1iterator;
                    // cout << "adding the neighbour "<< cp1point.label <<endl;
                    pointeranswer->push_back(cp1point);
                    // cout << (*pointeranswer)[pointeranswer->size() -1].label << " has been added"<<endl;
                }
                return false;
            }else{
                return false;
            }
        }
    });
    if(thisedge==edges.end()){
        // cout << "this is not possible as all edges have been iterated and point is found nowhere"<< endl;
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
    // cout<<"dekho bhai "<<endl;
    for(auto it= samecluster->points.begin();it!=samecluster->points.end();it++){
        if(it->label != point.label){
            // cout <<"vertice wala" <<endl;
            answer.push_back((* it));
        }
    } 
    return answer;
}
vector<Point> OrthoProjection::sameclusterpointsincluded(Point point){
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
    // cout<<"dekho bhai "<<endl;
    for(auto it= samecluster->points.begin();it!=samecluster->points.end();it++){
        // if(it->label != point.label){
            // cout <<"vertice wala" <<endl;
            answer.push_back((* it));
        // }
    } 
    return answer;
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

