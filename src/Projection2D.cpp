#include "Classes.h"
#include <Eigen/Dense>
#include <algorithm>
using namespace std;
using namespace Eigen;

Wireframe Projection2D::create3D(){
    cout << "lets start"<<endl;
    allpoints = determineAllPoints();
    cout <<"adjacencyMatrix point" <<endl;
    printmatrix(adjacencyMatrix);
    // cout << "allpoints detected and their number are "<< allpoints.size()<<endl;
    // for(int i=0;i<allpoints.size();i++){
    //     cout << allpoints[i] << endl;
    //     cout << "i is "<< i<<endl;
    //     cout << "check if index to points map ======================================================================"<< endl;
        
    //     //cout << allpoints[i].label << " maps to "<< * (labeltopointmap[allpoints[i].label])<<endl;
    //     cout << allpoints[i].adjacencyIndex << " maps to "<< * (indextopointmap.at(i))<<endl;
    // }
    determineIntersectedEdges();
    cout << "determineintersected edges complete "<< endl;
    printmatrix(adjacencyMatrix);
    cout << "execute corollary 1" <<endl;
    executeCorollary1();
    printmatrix(adjacencyMatrix);



    cout << "corollary 1 finished chek3edge ==================================================="<< endl;
    chkif3edgesanddefthem();
    printmatrix(adjacencyMatrix);

    cout<< "chek3edge finished loop starting==================================================="<< endl;
    int numcountwhile = 0;
    while(numofpossibleedge()!=0){
        //function below checks if for a point a possible and definite point are collinear and removes the possible point
        cout << "chekcollinearpossanddef started ================================================================" << endl;
        bool ifcollinearpossanddef = chkcollinearpossanddef();
        printmatrix(adjacencyMatrix);
        cout << "chkcollinearpossandposs started ================================================================" <<endl;
        bool ifcollinearpossandposs = chkcollinearpossandposs();
        printmatrix(adjacencyMatrix);
        cout << "chkposshasdefinanother started ================================================================" <<endl;

        bool ifposshasdefinother = chkposshasdefinother();
        printmatrix(adjacencyMatrix);
        cout << "chk3dgesanddefthem started ================================================================" <<endl;

        chkif3edgesanddefthem();
        printmatrix(adjacencyMatrix);
        numcountwhile++;
        if(numcountwhile==50){
            cout << "wrong answer"<<endl;
            break;
        }
        // break;
    }
    cout << "numcount is "<< numcountwhile << endl;
    Wireframe answer;
    answer.vertices = allpoints;
    for(auto verticesitr = answer.vertices.begin();verticesitr!=answer.vertices.end();verticesitr++){
        cout << "final points are "<< *verticesitr<<endl;
    }
    int numpoints = allpoints.size();
    for(int i=0;i<numpoints;i++){
        for(int j=0;j<numpoints;j++){
            if(adjacencyMatrix[i][j]==2){
                Edge thisedge;
                thisedge.p1 = * (indextopointmap[i]);
                thisedge.p2 = * (indextopointmap[j]);
                answer.edges.push_back(thisedge);
            }
        }
    }
    int numedges = answer.edges.size();
    for(int i=0;i<numedges;i++){
        cout << "thisedge is " << answer.edges[i].p1 << " is connected to " << answer.edges[i].p2 << endl;
    }
    answer.adjacencyMatrix = adjacencyMatrix;
    cout << "final print of adjacencyMatrix"<<endl;
    printmatrix(answer.adjacencyMatrix);
    return answer;
}

//doublecalculaedpossibleedges has all the edges calculated twice now

vector<Point> Projection2D::determineAllPoints(){
    vector<Point> answer;    
    for(auto it=(frontview.vertices.begin());it!=frontview.vertices.end();it++){
        for(auto nestit=(it->points.begin());nestit!=it->points.end();nestit++){
            string thislabel = nestit->label;
            //cout << "iteration on front label "<<thislabel<<endl;
            for(auto itfind=topview.vertices.begin();itfind!=topview.vertices.end();itfind++){
                bool found = false;
                for(auto nestitfind=itfind->points.begin();nestitfind!= itfind->points.end();nestitfind++){
                    string findlabel = nestitfind->label;
                    //cout << "   corresponding iteration on top label " << findlabel <<endl;
                    if(thislabel==findlabel){
                        //cout << "   aloha found the same label"<<endl;
                        found=true;
                        //Point determinedpoint = new Point;
                        Point determinedpoint = determinePoint(*nestit, *nestitfind);
                        //cout << "   determined point is "<< determinedpoint << endl;
                        int sizeanswer = answer.size();
                        determinedpoint.adjacencyIndex=sizeanswer;
                        answer.push_back(determinedpoint);
                        sizeanswer = answer.size();
                        //determinedpoint = answer[sizeanswer-1];

                        //Point * pointerdeterpoint = new Point;
                        //Point * pointerdeterpoint = &(determinedpoint);
                        //cout << "   determined point is "<< * pointerdeterpoint << endl;
                        //cout << "sizeanswer is "<<sizeanswer <<endl;
                        //indextopointmap.insert(make_pair(sizeanswer-1,&(determinedpoint)));
                        // indextopointmap[sizeanswer-1] = & (answer[sizeanswer-1]);
                        //labeltopointmap.insert(make_pair(determinedpoint.label,&(determinedpoint)));
                        // labeltopointmap[determinedpoint.label]=& (answer[sizeanswer-1]);
                        //knownpoints.push_back(&determinedpoint);
                        //cout << "sizeanswer - 1 is" << (sizeanswer-1) <<endl;
                        //cout << "label is " << determinedpoint.label<<endl;
                        //cout << "   isindextopoint working "<< * indextopointmap[sizeanswer-1]<<endl;
                        //cout << "   islabeltopoint working "<< * labeltopointmap[determinedpoint.label]<<endl;
                        break;
                    }
                    
                }
                if(found==true){
                    break;
                }
            }

        }

    }
    // cout << "lets make the indextopointmap ============================================================="<< endl;
    int numpoints = answer.size();
    for(vector<Point>::iterator iteranswer = answer.begin();iteranswer!=answer.end();iteranswer++){
        // cout<< "adding " << * iteranswer << endl;
        indextopointmap.insert(make_pair(iteranswer->adjacencyIndex,&(* iteranswer)));
    }
    for(vector<Point>::iterator iteranswer = answer.begin();iteranswer!=answer.end();iteranswer++){
        // cout<< "adding " << * iteranswer << endl;
        labeltopointmap.insert(make_pair(iteranswer->label,&(* iteranswer)));
    }
    //adjacencyMatrix(numpoints,temp);
    // cout << "iterating over labeltopointmap========================================================================================" <<endl;
    // for(map<string,Point *>::iterator it = labeltopointmap.begin();it!=labeltopointmap.end();it++){
    //     cout << it->first << " " << * (it->second) << endl;
    // }
    // cout << "iterating over indextopointmap========================================================================================" <<endl;

    // for(map<int,Point *>::iterator it = indextopointmap.begin();it!=indextopointmap.end();it++){
    //     cout << it->first << " " << * (it->second) << endl;
    // }
    for(int i=0;i<numpoints;i++){
        // cout << "answer[i] is " << answer[i]<<endl;
        // cout << "check for label to point" << * labeltopointmap.at(answer[i].label)<< endl;
        // cout << "check for int to point" << * indextopointmap.at(answer[i].adjacencyIndex)<< endl;

        vector<int> temp(numpoints,0);
        adjacencyMatrix.push_back(temp);
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

pair <vector<Edge>, vector<vector<int> > > Projection2D::determinePossibleEdges(Point vertex, vector<Point> *topneighbourptr, vector<Point> *frontneighbourptr) {
    ///
    /// This function determines the edges containing the Point vertex as one of the endpoints
    /// By interpreting its neighbours from the top view and front view
    ///
    vector<Edge> answer;
    vector<vector<int> > thismatrix;
    int numpoints = allpoints.size();
    for(int i=0;i<numpoints;i++){
        vector<int> temp(numpoints,0);
        thismatrix.push_back(temp);
    }



    vector<Point> intersection;
    vector<Point> topneighbour = * (topneighbourptr);
 
    vector<Point> frontneighbour = * (frontneighbourptr);
    // cout<< "secondneighbours of consideration are --------------------------------------------"<< endl;
    // for(int i=0;i<frontneighbour.size();i++){
    //     cout << frontneighbour[i] << endl;
    // }
    for(auto topneighbouritr=topneighbourptr->begin();topneighbouritr!=topneighbourptr->end();topneighbouritr++){
        auto correspondingpointinfrontasptr = find_if(frontneighbourptr->begin(),frontneighbourptr->end(),[topneighbouritr](Point p)->bool{
            return(p.label==topneighbouritr->label);
        });
        if(correspondingpointinfrontasptr!=frontneighbourptr->end()){
            // cout<< "the collided point will be "<< correspondingpointinfrontasptr->label<<endl;
            Point collidedpoint = * labeltopointmap[correspondingpointinfrontasptr->label];
            intersection.push_back(collidedpoint);
        }
    }
    int numintersectionp = intersection.size();
    // for(int i=0;i<numintersectionp;i++){
    //     cout << "intersection points are "<< intersection[i]<<endl;
    // }
    int numpointsaa = allpoints.size();

    for(auto intersectionitr = intersection.begin();intersectionitr!=intersection.end();intersectionitr++){
        Edge tempedge;
        tempedge.p1 = vertex;
        tempedge.p2 = *(labeltopointmap[intersectionitr->label]);
        //int i = vertex.adjacencyIndex;
        int i = labeltopointmap[vertex.label]->adjacencyIndex;
        int j = labeltopointmap[intersectionitr->label]->adjacencyIndex;
        //adjacencyMatrix[i][j]=adjacencyMatrix[i][j]+1;
        //adjacencyMatrix[j][i]=adjacencyMatrix[j][i]+1;
        thismatrix[i][j] = 1;
        thismatrix[j][i] = 1;
        answer.push_back(tempedge);
    }


    return make_pair(answer,thismatrix);
    
}

void Projection2D::determineIntersectedEdges(){
    for(auto pointitr=allpoints.begin();pointitr!=allpoints.end();pointitr++){
        // cout << "-----------------------------------------------------------------------" <<endl;
        // cout << "iterating on point "<< pointitr->label <<endl;
        // cout << "-----------------------------------------------------------------------" <<endl;
        vector<Point> topneighbours = topview.possibleNeighbours(* pointitr);
        // cout << "-----------------------------------------------------------------------" <<endl;
        // cout << "topneighbours are "<<endl;
        // for(int i=0;i<topneighbours.size();i++){
        //     cout << topneighbours[i]<< endl;
        // }
        // cout << "-----------------------------------------------------------------------" <<endl;
        vector<Point> frontneighbours = frontview.possibleNeighbours(* pointitr);
        // cout << "-----------------------------------------------------------------------" <<endl;
        // cout << "frontneighbours are "<<endl;
        // for(int i=0;i<frontneighbours.size();i++){
        //     cout << frontneighbours[i]<< endl;
        // }
        // cout << "-----------------------------------------------------------------------" <<endl;
        vector<Point> sideneighbours = sideview.possibleNeighbours(* pointitr);
        // cout << "-----------------------------------------------------------------------" <<endl;
        // cout << "sideneighbours are "<<endl;
        // for(int i=0;i<sideneighbours.size();i++){
        //     cout << sideneighbours[i]<< endl;
        // }
        // cout << "-----------------------------------------------------------------------" <<endl;
        // cout<< "we have to intersect topandfront ------------------------------"<<endl;
        // vector<Edge> topAndFront = determinePossibleEdges(*pointitr,&topneighbours,&frontneighbours).first;
        auto topandfrontmatrix = determinePossibleEdges(*pointitr,&topneighbours,&frontneighbours).second;
        // cout<< "topandfronthasbeenintersected -------------------"<<endl;
        // int numpointsaa = allpoints.size();
        // for(int i= (-1);i<numpointsaa;i++){
        //     //cout<<"why not working"<<endl;
        //     for(int j= (-1);j<numpointsaa;j++){
        //         //cout<<"why not working"<<endl;
        //         if(i==-1){
        //             if(j!=-1){
        //                 cout << allpoints[j].label << " ";
        //                 if(j==allpoints.size()-1){
        //                     cout << endl;
        //                 }
        //             }else{
        //                 cout << "  ";
        //             }
        //         }else{
        //             if(j!=-1){
        //                 cout << topandfrontmatrix[i][j]<< " ";
        //                 if(j == allpoints.size()-1){
        //                     cout << endl;
        //                 }
        //             }else{
        //                 cout << allpoints[i].label << " ";
        //             }
                    
        //         }           
        //     }       
        // }
        // cout<< "we have to intersect sideandfront ------------------------------"<<endl;
        
        // vector<Edge> sideAndFront = determinePossibleEdges(*pointitr,&sideneighbours,&frontneighbours).first;
        auto sideandfrontmatrix = determinePossibleEdges(*pointitr,&sideneighbours,&frontneighbours).second;
        // cout << "sideandfronthasbeenintersected -----------------------"<<endl;
        // numpointsaa = allpoints.size();
        // for(int i= (-1);i<numpointsaa;i++){
        //     //cout<<"why not working"<<endl;
        //     for(int j= (-1);j<numpointsaa;j++){
        //         //cout<<"why not working"<<endl;
        //         if(i==-1){
        //             if(j!=-1){
        //                 cout << allpoints[j].label << " ";
        //                 if(j==allpoints.size()-1){
        //                     cout << endl;
        //                 }
        //             }else{
        //                 cout << "  ";
        //             }
        //         }else{
        //             if(j!=-1){
        //                 cout << sideandfrontmatrix[i][j]<< " ";
        //                 if(j == allpoints.size()-1){
        //                     cout << endl;
        //                 }
        //             }else{
        //                 cout << allpoints[i].label << " ";
        //             }
                    
        //         }           
        //     }       
        // }


        // cout<< "we have to intersect topandside ------------------------------"<<endl;
        
        // vector<Edge> sideAndFront = determinePossibleEdges(*pointitr,&sideneighbours,&frontneighbours).first;
        auto topandsidematrix = determinePossibleEdges(*pointitr,&topneighbours,&sideneighbours).second;
        // cout << "topandfronthasbeenintersected -----------------------"<<endl;
        // numpointsaa = allpoints.size();
        // for(int i= (-1);i<numpointsaa;i++){
        //     //cout<<"why not working"<<endl;
        //     for(int j= (-1);j<numpointsaa;j++){
        //         //cout<<"why not working"<<endl;
        //         if(i==-1){
        //             if(j!=-1){
        //                 cout << allpoints[j].label << " ";
        //                 if(j==allpoints.size()-1){
        //                     cout << endl;
        //                 }
        //             }else{
        //                 cout << "  ";
        //             }
        //         }else{
        //             if(j!=-1){
        //                 cout << topandsidematrix[i][j]<< " ";
        //                 if(j == allpoints.size()-1){
        //                     cout << endl;
        //                 }
        //             }else{
        //                 cout << allpoints[i].label << " ";
        //             }
                    
        //         }           
        //     }       
        // }



        int numpoints = allpoints.size();
        for(int i = 0; i<numpoints;i++){
            for(int j=0;j<numpoints;j++){
                if(topandfrontmatrix[i][j]==1 && sideandfrontmatrix[i][j]==1 && topandsidematrix[i][j]==1){
                    adjacencyMatrix[i][j] =1;
                }else{
                    //adjacencyMatrix[i][j]=0;
                }
            }
        }
        // cout<< "allpoints size is "<< allpoints.size()<<endl;
        // int numpointsaa = allpoints.size();
        // for(int i= (-1);i<numpointsaa;i++){
        //     //cout<<"why not working"<<endl;
        //     for(int j= (-1);j<numpointsaa;j++){
        //         //cout<<"why not working"<<endl;
        //         if(i==-1){
        //             if(j!=-1){
        //                 cout << allpoints[j].label << " ";
        //                 if(j==allpoints.size()-1){
        //                     cout << endl;
        //                 }
        //             }else{
        //                 cout << "  ";
        //             }
        //         }else{
        //             if(j!=-1){
        //                 cout << adjacencyMatrix[i][j]<< " ";
        //                 if(j == allpoints.size()-1){
        //                     cout << endl;
        //                 }
        //             }else{
        //                 cout << allpoints[i].label << " ";
        //             }
                    
        //         }           
        //     }       
        // }

    }
}

void Projection2D::executeCorollary1onebyone(OrthoProjection* view1, OrthoProjection* view2, OrthoProjection* view3){
    for(auto clusteritr = view1->vertices.begin();clusteritr!=view1->vertices.end();clusteritr++){
        if(clusteritr->points.size()==2){
            bool isconnectedinotherview2 = view2->isConnected(clusteritr->points[0].label,clusteritr->points[1].label);
            bool isconnectedinotherview3 = view3->isConnected(clusteritr->points[0].label,clusteritr->points[1].label);
            if(isconnectedinotherview2 && isconnectedinotherview3){
                int i = labeltopointmap[clusteritr->points[0].label]->adjacencyIndex;
                int j = labeltopointmap[clusteritr->points[1].label]->adjacencyIndex;
                if(adjacencyMatrix[i][j]==1 || adjacencyMatrix[j][i]==1){
                    adjacencyMatrix[i][j] = 2;
                    adjacencyMatrix[j][i] = 2;
                }               
            }     
        }
    }
}
void Projection2D::executeCorollary1(){
    executeCorollary1onebyone(&topview,&frontview,&sideview);

    executeCorollary1onebyone(&frontview,&topview,&sideview);
    // executeCorollary1onebyone(&frontview,&sideview);
    executeCorollary1onebyone(&sideview,&frontview,&topview);
    // executeCorollary1onebyone(&topview,&sideview);
    // executeCorollary1onebyone(&sideview,&topview);

}
void Projection2D::chkif3edgesanddefthem(){
    int numpointsall = allpoints.size();
    for(int i=0; i<numpointsall;i++){
        int numedge = count_if(adjacencyMatrix[i].begin(),adjacencyMatrix[i].end(),[](int v)->bool{
            return(v>0);
        });
        // cout << "for int i " << i << " " << numedge << endl;
        if(numedge==3){
            for(int j=0;j<numpointsall;j++){
                if(adjacencyMatrix[i][j]==1){
                    adjacencyMatrix[i][j] = 2;
                    adjacencyMatrix[j][i] = 2;
                }
            }
        }
    }
}
int Projection2D::numofpossibleedge(){
    int num1=0;
    int numpointsall = allpoints.size();
    for(int i=0;i<numpointsall;i++){
        num1 = num1 + count(adjacencyMatrix[i].begin(),adjacencyMatrix[i].end(),1);
    }
    return num1;
}
bool Projection2D::chkcollinearpossanddef(){
    int numpoints = allpoints.size();
    bool ret =false;
    for(int i=0;i<numpoints;i++){
        Point * thispoint = & (allpoints[i]);

        vector<int> thisvec = adjacencyMatrix[i];
        int numposs = count(thisvec.begin(),thisvec.end(),1);
        int numdef = count(thisvec.begin(),thisvec.end(),2);
        if(numposs>0 && numdef>0){
            vector<int> defindexvec;
            for(int j=0;j<numpoints;j++){
                if(thisvec[j]==2){
                    defindexvec.push_back(j);
                }
            }
            for(int j=0;j<numpoints;j++){
                if(thisvec[j]==1){
                    Point * posspoint = (indextopointmap[j]);
                    for(auto defindexvecitr = defindexvec.begin();defindexvecitr!=defindexvec.end();defindexvecitr++){
                        Point * defpoint = indextopointmap[(* defindexvecitr)];
                        bool iscollinear = thispoint->checkcollinear(posspoint, defpoint);
                        if(iscollinear){
                            adjacencyMatrix[i][j] = 0;
                            adjacencyMatrix[j][i] = 0;
                            ret = true;
                            break;
                        }
                    }
                }
            }
        }
    }
    return ret;
}
bool Projection2D::chkcollinearpossandposs(){
    // cout << "poss and poss started "<< endl;
    int numpoints = allpoints.size();
    bool ret =false;
    for(int i=0;i<numpoints;i++){
        Point * thispoint = new Point;
        thispoint = & (allpoints[i]);
        // cout << "point of consideration is " << *thispoint << endl;
        vector<int> thisvec = adjacencyMatrix[i];
        int numposs = count(thisvec.begin(),thisvec.end(),1);
        int numdef = count(thisvec.begin(),thisvec.end(),2);
        // cout << "numpos and numdef are " << numposs << " " << numdef << endl;
        if(numposs>=2){
            for(int j=0;j<numpoints;j++){
                if(adjacencyMatrix[i][j]==1){
                    for(int k=j+1;k<numpoints;k++){
                        if(adjacencyMatrix[i][k]==1){
                            // cout << "j and k are " << j << " " << k << endl;
                            if(thispoint->checkcollinear(indextopointmap[j],indextopointmap[k])){
                                // cout << "j and k are collinear "<< endl;
                                Point * jpointptr = new Point;
                                Point * kpointptr = new Point;
                                jpointptr = indextopointmap[j];
                                kpointptr = indextopointmap[k];
                                // cout << "jpoint is " << *jpointptr << endl;
                                // cout << "kpoint is " << *kpointptr << endl;
                                for(int it=0;it<3;it++){
                                    // cout << "it is " <<it << endl;
                                    vector<Point> topcluster;
                                    if(it==0){
                                        topcluster =topview.sameclusterpointsincluded(*thispoint);
                                    }else if(it==1){
                                        topcluster = frontview.sameclusterpointsincluded(*thispoint);
                                    }else{
                                        topcluster = sideview.sameclusterpointsincluded(*thispoint);
                                    }
                                    // cout << "topcluster computed" <<endl;
                                    if(topcluster.size()==0){
                                        continue;
                                    }
                                    // cout << "topcluster size isnt 0" << endl;
                                    auto jiterator = find_if(topcluster.begin(),topcluster.end(),[jpointptr](Point p)->bool{
                                        return(jpointptr->label==p.label);
                                    });
                                    if(jiterator!=topcluster.end()){
                                        // cout << "it must enter in this j"<< endl;
                                        auto kiterator = find_if(topcluster.begin(),topcluster.end(),[kpointptr](Point p)->bool{
                                            return(kpointptr->label==p.label);
                                        });
                                        if(kiterator!=topcluster.end()){
                                            // cout << "it must enter in this k"<< endl;
                                            int topclustersize = topcluster.size();
                                            // cout << "end and start of this cluster are "<< topcluster[0].label << " and "<< topcluster[topclustersize-1].label << endl;
                                            if((topcluster[0].label)==(thispoint->label) || (topcluster[topclustersize-1].label)==(thispoint->label)){
                                                // cout << "do not change the end part "<< endl;
                                                Vector3d a1(thispoint->x,thispoint->y,thispoint->z);
                                                Vector3d a2(jpointptr->x,jpointptr->y,jpointptr->z);
                                                Vector3d a3(kpointptr->x,kpointptr->y,kpointptr->z);
                                                double dis1 = (a2-a1).norm();
                                                double dis2 = (a3-a1).norm();
                                                if(dis1<dis2){
                                                    adjacencyMatrix[i][j]=2;
                                                    adjacencyMatrix[j][i]=2;
                                                    adjacencyMatrix[i][k]=0;
                                                    adjacencyMatrix[k][i]=0;
                                                }else{
                                                    adjacencyMatrix[i][j]=0;
                                                    adjacencyMatrix[j][i]=0;
                                                    adjacencyMatrix[i][k]=2;
                                                    adjacencyMatrix[k][i]=2;
                                                }
                                                ret = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return ret;
}
bool Projection2D::chkposshasdefinother(){
    int numpoints = allpoints.size();
    bool ret =false;
    for(int i=0;i<numpoints;i++){
        Point * thispoint = & (allpoints[i]);
        //vector<int> thisvec = adjacencyMatrix[i];
        vector<int> posspointsvec,defpointsvec;
        for(int j=0;j<numpoints;j++){
            if(adjacencyMatrix[i][j]==1){
                posspointsvec.push_back(j);
            }else if(adjacencyMatrix[i][j]==2){
                defpointsvec.push_back(j);
            }
        }
        if(defpointsvec.size()<2){
            continue;
        }
        for(int j=0;j<posspointsvec.size();j++){
            int thisposspointindex = posspointsvec[j];
            int numberofintersections = 0;
            for(int k=0;k<defpointsvec.size();k++){
                if(adjacencyMatrix[thisposspointindex][defpointsvec[k]]==2){
                    numberofintersections++;
                }
            }
            if(numberofintersections>=2){
                adjacencyMatrix[i][thisposspointindex]=0;
                adjacencyMatrix[thisposspointindex][i]=0;
                ret =true;
            }
        }
    }
    return ret;
}
void Projection2D::printmatrix(vector<vector<int> > thisone){
    int tempint = allpoints.size();
        for(int i=-1;i<tempint;i++){
        for(int j=-1;j<tempint;j++){
            if(i==-1){
                if(j!=-1){
                    cout << allpoints[j].label << " ";
                    if(j==allpoints.size()-1){
                        cout << endl;
                    }
                }else{
                    cout << "  ";
                }
            }else{
                if(j!=-1){
                    cout << thisone[i][j]<< " ";
                    if(j == allpoints.size()-1){
                        cout << endl;
                    }
                }else{
                    cout << allpoints[i].label << " ";
                }
                
            }           
        }       
    }
}