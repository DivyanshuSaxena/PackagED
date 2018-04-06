#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <gtkmm.h>
#include "gui.h"
#include <fstream>

using namespace std;
using Eigen::MatrixXd;

int main(int argc, char *argv[]) {
    /// 
    /// The main function shall be responsible for calling various other functions and instantiating the classes for using their functions cop290
    ///
        
    // check3Dfile();
    auto app =
        Gtk::Application::create(argc, argv,
        "org.gtkmm.examples");
    MainWindow window;
    return app->run(window);
    // check2D();
    // return 0;
}

int check3D() {
    double thisarr [4] = {0,1,0,0};
    Object3D obj;
    Point v1,v2,v3,v4,v5;
    v1.setCoordinates(2,2,0);
    v2.setCoordinates(2,1,0);
    v3.setCoordinates(1,1,0);
    v4.setCoordinates(2,1,1); 
    v5.setCoordinates(1,1,1);
    obj.vertices.push_back(v1);
    obj.vertices.push_back(v2);
    obj.vertices.push_back(v3);
    obj.vertices.push_back(v4);
    obj.vertices.push_back(v5);
    Edge e1,e2,e3,e4,e5,e6,e7,e8;
    e1.p1 = v1; e1.p2 = v2; e2.p1 = v1; e2.p2 = v3;
    e3.p1 = v1; e3.p2 = v4; e4.p1 = v1; e4.p2 = v5;
    e5.p1 = v2; e5.p2 = v4; e6.p1 = v2; e6.p2 = v3;
    e7.p1 = v4; e7.p2 = v5; e8.p1 = v3; e8.p2 = v5;
    obj.edges.push_back(e1);
    obj.edges.push_back(e2);
    obj.edges.push_back(e3);
    obj.edges.push_back(e4);
    obj.edges.push_back(e5);
    obj.edges.push_back(e6);
    obj.edges.push_back(e7);
    obj.edges.push_back(e8);
    Face f1,f2,f3,f4,f5;
    f1.vertices.push_back(0);
    f1.vertices.push_back(1);
    f1.vertices.push_back(2);
    f2.vertices.push_back(0);
    f2.vertices.push_back(1);
    f2.vertices.push_back(3);
    f3.vertices.push_back(0);
    f3.vertices.push_back(3);
    f3.vertices.push_back(4);
    f4.vertices.push_back(0);
    f4.vertices.push_back(2);
    f4.vertices.push_back(4);
    f5.vertices.push_back(1);
    f5.vertices.push_back(2);
    f5.vertices.push_back(3);
    f5.vertices.push_back(4);
    obj.faces.push_back(f1);
    obj.faces.push_back(f2);
    obj.faces.push_back(f3);
    obj.faces.push_back(f4);
    obj.faces.push_back(f5);
    PlaneProjection* p = obj.project3D(thisarr);
    cout << "Projection: " << *p << endl;
    p->rotatePlane();
    cout << "Rotated Projection: " << *p << endl;
    return 0;
}

PlaneProjection* input3Dfile(string filename){
    ///
    /// Function to get input of the 3D Object from file
    ///
    ifstream inFile (filename);
    string output;
    Object3D obj;
    double planearr [4];
    if(!(inFile.is_open())){
        cout<< "not started" <<endl;
    }
    map<string, int> labeltoindex;
    if(inFile.is_open()){
        cout << "start file"<<endl;
        if(!inFile.eof()){
            inFile >> output;
            cout<< "getting vertices"<<endl;
            if(output=="Vertices"){
                // inFile>> output;
                int tempindex = 0;
                while(output!=";"){
                    inFile >> output;
                    double n1 = atof(output.c_str());
                    inFile >> output;
                    double n2 = atof(output.c_str());
                    inFile >> output;
                    double n3 = atof(output.c_str());
                    inFile >> output;
                    string label = output;
                    Point tempoint;
                    tempoint.setCoordinatesAndLabel(n1,n2,n3, label);
                    // cout << "point is "<< tempoint<< endl;
                    obj.vertices.push_back(tempoint);
                    labeltoindex[label] = tempindex;
                    inFile >> output;
                    tempindex++;
                }
            }
            cout << "vertices finished" <<endl;
            inFile >> output;
            cout << "edges begin "<< endl;
            if(output=="Edges"){
                while(output!=";"){
                    inFile >> output;
                    string label1 = output;
                    inFile >> output;
                    string label2 = output;
                    auto point1ptr = find_if(obj.vertices.begin(),obj.vertices.end(),[label1](Point p)->bool{
                        return(p.label == label1);
                    });
                    auto point2ptr = find_if(obj.vertices.begin(),obj.vertices.end(),[label2](Point p)->bool{
                        return(p.label == label2);
                    });
                    Edge tempedge;
                    tempedge.p1 = * point1ptr;
                    tempedge.p2 = * point2ptr;
                    obj.edges.push_back(tempedge);
                    inFile >> output;
                }
            }
            cout << "edges finished"<< endl;
            inFile >> output;
            cout << "faces starting" << endl;
            if(output=="Faces"){
                while(output!=";"){
                    inFile >> output;
                    // vector<string> labelvec;
                    Face tempface;
                    while(output!="," && output!=";"){
                        string tempstr = output;
                        // labelvec.push_back(tempstr);
                        // cout << "tempstr is " <<tempstr << endl;
                        inFile >> output;
                        tempface.vertices.push_back(labeltoindex[tempstr]);
                        
                    }
                    obj.faces.push_back(tempface);
                    // cout << "pushed face"<<endl;
                    // break;
                    // inFile >> output;
                }
            }
            cout << "faces finished" <<endl;
            inFile >> output;
            cout << "plane started "<< endl;
            if(output=="Plane"){
                inFile >> output;
                double n1 = atof(output.c_str());
                inFile >> output;
                double n2 = atof(output.c_str());
                inFile >> output;
                double n3 = atof(output.c_str());
                inFile >> output;
                double n4 = atof(output.c_str());
                // inFile >> output
                // planearr={n1,n2,n3,n4};
                planearr[0]=n1;
                planearr[1]=n2;
                planearr[2]=n3;
                planearr[3]=n4;
            }
            // cout << "plane finished" << endl;
        }
        cout << "file complete"<<endl;
        cout << "Object created from file: " << endl << obj << endl; 
        PlaneProjection* p = new PlaneProjection;
        p = obj.project3D(planearr);
        cout << "Projection: " << *p << endl;
        p->rotatePlane();
        cout << "Rotated Projection: " << *p << endl;
        return p;
    }
    return 0;
}

int check2D() {
    Point etop, atop, btop, ctop, dtop, afront,dfront, bfront,cfront, efront, eside, dside, cside, aside, bside;
    etop.setCoordinatesAndLabel(1.5,1.5,0,"e");
    atop.setCoordinatesAndLabel(1,1,0,"a");
    btop.setCoordinatesAndLabel(2,1,0,"b");
    ctop.setCoordinatesAndLabel(2,2,0,"c");
    dtop.setCoordinatesAndLabel(1,2,0,"d");
    efront.setCoordinatesAndLabel(1.5,0,2,"e");
    afront.setCoordinatesAndLabel(1,0,1,"a");
    bfront.setCoordinatesAndLabel(2,0,1,"b");
    cfront.setCoordinatesAndLabel(2,0,1,"c");
    dfront.setCoordinatesAndLabel(1,0,1,"d");
    eside.setCoordinatesAndLabel(0,1.5,2,"e");
    aside.setCoordinatesAndLabel(0,1,1,"a");
    bside.setCoordinatesAndLabel(0,1,1,"b");
    cside.setCoordinatesAndLabel(0,2,1,"c");
    dside.setCoordinatesAndLabel(0,2,1,"d");
    ClusteredPoint atopcl,btopcl, etopcl, dtopcl, ctopcl, efrontcl, adfrontcl,bcfrontcl,esidecl, dcsidecl, absidecl;
    atopcl.points.push_back(atop);
    btopcl.points.push_back(btop);
    dtopcl.points.push_back(dtop);
    etopcl.points.push_back(etop);
    ctopcl.points.push_back(ctop);
    efrontcl.points.push_back(efront);
    adfrontcl.points.push_back(afront);
    adfrontcl.points.push_back(dfront);
    bcfrontcl.points.push_back(bfront);
    bcfrontcl.points.push_back(cfront);
    esidecl.points.push_back(eside);
    dcsidecl.points.push_back(dside);
    dcsidecl.points.push_back(cside);
    absidecl.points.push_back(aside);
    absidecl.points.push_back(bside);
    OrthoProjection topview, frontview,sideview;
    ClusteredPoint topspoints[] = {atopcl,btopcl,dtopcl,etopcl,ctopcl};
    for(int i=0;i<5;i++){
        topview.vertices.push_back(topspoints[i]);
    }
    //ClusteredPoint temp =topview.vertices[2];
    //cout << topview.vertices[2].points[0].label << endl;
    ClusteredPoint frontspoints[] ={efrontcl,adfrontcl,bcfrontcl};
    for(int i=0;i<3;i++){
        frontview.vertices.push_back(frontspoints[i]);
    }
    ClusteredPoint sidespoints[] = {esidecl,dcsidecl,absidecl};
    for(int i=0;i<3;i++){
        sideview.vertices.push_back(sidespoints[i]);
    }
    Edge2D abtope,bctope,cdtope,adtope,aetope,betope,cetope,detope,actope,bdtope;
    abtope.cp1 = atopcl; abtope.cp2 = btopcl;
    bctope.cp1 = btopcl; bctope.cp2 = ctopcl;
    cdtope.cp1 = ctopcl; cdtope.cp2 = dtopcl;
    adtope.cp1 = atopcl; adtope.cp2 = dtopcl;
    aetope.cp1 = atopcl; aetope.cp2 = etopcl;
    betope.cp1 = btopcl; betope.cp2 = etopcl;
    cetope.cp1 = ctopcl; cetope.cp2 = etopcl;
    detope.cp1 = dtopcl; detope.cp2 = etopcl;
    actope.cp1 = atopcl; actope.cp2 = ctopcl;
    bdtope.cp1 = btopcl; bdtope.cp2 = dtopcl;
    Edge2D topsedges[] ={abtope,bctope,cdtope,adtope,aetope,betope,cetope,detope,actope,bdtope};
    //cout << sizeof(topsedges)/sizeof(Edge2D);
    for(int i=0;i<10;i++){
        topview.edges.push_back(topsedges[i]);
    }
    Edge2D ebcfronte, adbcfronte,eadfronte;
    ebcfronte.cp1=efrontcl; ebcfronte.cp2=bcfrontcl;
    adbcfronte.cp1=adfrontcl; adbcfronte.cp2=bcfrontcl;
    eadfronte.cp1=efrontcl; eadfronte.cp2=adfrontcl;
    Edge2D frontsedges[] = {ebcfronte, adbcfronte,eadfronte};
    for(int i=0;i<3;i++){
        frontview.edges.push_back(frontsedges[i]);
    }
    Edge2D eabsidee, dcabsidee, edcsidee;
    eabsidee.cp1=esidecl; eabsidee.cp2=absidecl;
    dcabsidee.cp1=dcsidecl; dcabsidee.cp2=absidecl;
    edcsidee.cp1=esidecl; edcsidee.cp2=dcsidecl;
    Edge2D sidesedges[] ={eabsidee, dcabsidee, edcsidee};
    for(int i=0;i<3;i++){
        sideview.edges.push_back(sidesedges[i]);
    }
    Projection2D myproj;
    myproj.frontview=frontview;
    myproj.sideview=sideview;
    myproj.topview =topview;
    myproj.create3D();
    return 0;
}

Wireframe* input2Dfile(string filename){
    ///
    /// Function to get input of 2D Projections from a file
    ///
    // ofstream inFile;
    cout <<"start" <<endl;
	// inFile.open("example.txt");
    ifstream inFile (filename);
    if(!(inFile.is_open())){
        cout<< "not started" <<endl;
    }

	//char output[100];
	OrthoProjection top,front,side;
	Point temp2dpoint;
	string output;
    cout<< "file started"<<endl;
    if(inFile.is_open()){
        if(!inFile.eof())
		{
			inFile >> output;
			//transform(output.begin(), output.end(), output.begin(), ::tolower);
            cout<<"begin" <<endl;
			if(output == "Top"){
                cout << "entered Top "<<endl;
                inFile >> output;
                map<string, ClusteredPoint> sampmap;
                if(output=="Vertices"){
                    cout << "entered Vertices" << endl;
                    inFile >> output;
                    while(output!=";"){
                        double n1 = atof(output.c_str());
                        // cout << n1 << endl;
                        inFile >> output;
                        double n2 = atof(output.c_str());
                        inFile >> output;
                        vector<string> thisstr;
                        inFile >> output;
                        while(output!="]"){
                            // inFile >> output;
                            thisstr.push_back(output);
                            inFile >> output;
                        }
                        ClusteredPoint tempcluster;
                        for(int i=0;i<thisstr.size();i++){
                            Point tempoint;
                            tempoint.x = n1;
                            tempoint.y = n2;
                            tempoint.z = 0 ;
                            tempoint.label = thisstr[i];
                            cout << tempoint.label << endl;
                            cout << tempoint << endl;
                            tempcluster.points.push_back(tempoint);
                        }
                        sampmap[tempcluster.points[0].label] = tempcluster;
                        top.vertices.push_back(tempcluster);
                        inFile >> output;
                    }

                    while(output!=";;"){
                        cout << "ended vertices" << endl;
                        inFile >> output;
                        if(output=="Edges"){
                            cout << "entered edges " <<endl;
                            
                            while(output!=";;"){
                                inFile >> output;
                                string a1 = output;
                                inFile >> output;
                                string a2 = output;
                                // cout << "a1 and a2 are " <<a1<<" "<<a2<<endl; 
                                ClusteredPoint c1 = sampmap[a1];
                                ClusteredPoint c2 = sampmap[a2];
                                Edge2D thisedge2d;
                                thisedge2d.cp1 = c1;
                                thisedge2d.cp2 = c2;
                                top.edges.push_back(thisedge2d);
                                inFile >> output;
                            }
                            cout << "edge size is " << top.edges.size() << endl;
                            // cout << "last edge is " << top.edges[top.edges.size()-1].cp1.points[0] << " : "<< top.edges[top.edges.size()-1].cp2.points[0] <<endl;
                        }
                    }
                    
                }

            }
            //yha se
            inFile >> output;
            if(output=="Front"){
                cout << "entered Front" <<endl;
                inFile >> output;

                map<string, ClusteredPoint> sampmap;
                if(output=="Vertices"){
                    cout << "entered Vertices" << endl;
                    inFile >> output;
                    while(output!=";"){
                        double n1 = atof(output.c_str());
                        // cout << n1 << endl;
                        inFile >> output;
                        double n2 = atof(output.c_str());
                        inFile >> output;
                        vector<string> thisstr;
                        inFile >> output;
                        while(output!="]"){
                            // inFile >> output;
                            thisstr.push_back(output);
                            inFile >> output;
                        }
                        ClusteredPoint tempcluster;
                        for(int i=0;i<thisstr.size();i++){
                            Point tempoint;
                            tempoint.x = n1;
                            tempoint.y = 0;
                            tempoint.z = n2 ;
                            tempoint.label = thisstr[i];
                            cout << tempoint.label << endl;
                            cout << tempoint << endl;
                            tempcluster.points.push_back(tempoint);
                        }
                        sampmap[tempcluster.points[0].label] = tempcluster;
                        front.vertices.push_back(tempcluster);
                        inFile >> output;
                    }

                    while(output!=";;"){
                        cout << "ended vertices" << endl;
                        inFile >> output;
                        if(output=="Edges"){
                            cout << "entered edges " <<endl;
                            
                            while(output!=";;"){
                                inFile >> output;
                                string a1 = output;
                                inFile >> output;
                                string a2 = output;
                                ClusteredPoint c1 = sampmap[a1];
                                ClusteredPoint c2 = sampmap[a2];
                                Edge2D thisedge2d;
                                thisedge2d.cp1 = c1;
                                thisedge2d.cp2 = c2;
                                front.edges.push_back(thisedge2d);
                                inFile >> output;
                            }
                            cout << "edge size is " << front.edges.size() << endl;
                        }
                    }   
                }
                //end doc
            }
            inFile >> output;
            if(output=="Side"){

                cout << "entered Side" <<endl;
                inFile >> output;

                map<string, ClusteredPoint> sampmap;
                if(output=="Vertices"){
                    cout << "entered Vertices" << endl;
                    inFile >> output;
                    while(output!=";"){
                        double n1 = atof(output.c_str());
                        // cout << n1 << endl;
                        inFile >> output;
                        double n2 = atof(output.c_str());
                        inFile >> output;
                        vector<string> thisstr;
                        inFile >> output;
                        while(output!="]"){
                            // inFile >> output;
                            thisstr.push_back(output);
                            inFile >> output;
                        }
                        ClusteredPoint tempcluster;
                        for(int i=0;i<thisstr.size();i++){
                            Point tempoint;
                            tempoint.x = 0;
                            tempoint.y = n1 ;
                            tempoint.z = n2 ;
                            tempoint.label = thisstr[i];
                            cout << tempoint.label << endl;
                            cout << tempoint << endl;
                            tempcluster.points.push_back(tempoint);
                        }
                        sampmap[tempcluster.points[0].label] = tempcluster;
                        side.vertices.push_back(tempcluster);
                        inFile >> output;
                    }

                    while(output!=";;"){
                        cout << "ended vertices" << endl;
                        inFile >> output;
                        if(output=="Edges"){
                            cout << "entered edges " <<endl;
                            
                            while(output!=";;"){
                                inFile >> output;
                                string a1 = output;
                                inFile >> output;
                                string a2 = output;
                                ClusteredPoint c1 = sampmap[a1];
                                ClusteredPoint c2 = sampmap[a2];
                                Edge2D thisedge2d;
                                thisedge2d.cp1 = c1;
                                thisedge2d.cp2 = c2;
                                side.edges.push_back(thisedge2d);
                                inFile >> output;
                            }
                            cout << "edge size is " << side.edges.size() << endl;
                            inFile >> output;
                        }
                    }   
                }
            //end doc
            }
		}
        cout << "lets start the computation now "<< endl;
        // we have top front side
        Wireframe frame;
        Projection2D myproj;
        myproj.frontview = front;
        myproj.sideview = side;
        myproj.topview = top;
        frame = myproj.create3D();
        Wireframe* retFrame;
        retFrame = new Wireframe;
        for(int i = 0; i < frame.vertices.size(); i++) {
            retFrame->vertices.push_back(frame.vertices[i]);
        }
        for(int i = 0; i < frame.edges.size(); i++) {
            Edge edge;
            edge.p1.setCoordinates(frame.edges[i].p1.x,frame.edges[i].p1.y,frame.edges[i].p1.z);
            edge.p2.setCoordinates(frame.edges[i].p2.x,frame.edges[i].p2.y,frame.edges[i].p2.z);        
            retFrame->edges.push_back(edge);
        }
        // cout << "retFrame: " << *retFrame << endl;
        retFrame->normalise();
        // cout << "retFrame after normalise: " << endl << *retFrame << endl;    
        return retFrame;
    }
    return 0;
}

PlaneProjection* createObject(Object3D* object, double plane[4]) {
    ///
    /// This function shall make use of the gtk library, to interactively take input from the user and returns the 3D object created from the user input
    ///
    cout << "In createObject" << endl; // ----------Remove
    Object3D temp_obj;
    for(int i = 0; i < object->vertices.size(); i++)
        temp_obj.vertices.push_back(object->vertices[i]);
    for(int i = 0; i < object->edges.size(); i++)
        temp_obj.edges.push_back(object->edges[i]);
    for(int i = 0; i < object->faces.size(); i++)
        temp_obj.faces.push_back(object->faces[i]);
    cout << "Input Object:" << endl << temp_obj;
    for(int i = 0; i < 4; i++)
        cout << plane[i];
    PlaneProjection* res = new PlaneProjection;
    res = temp_obj.project3D(plane);
    cout << "Object Returned: " << endl; // --------Remove
    cout << *res << endl; // --------Remove
    res->rotatePlane();
    cout << "Plane Rotated:" << endl; // ---------Remove
    cout << *res << endl; // ---------Remove
    return res;
}

Wireframe* createProjection(Projection2D* projection) {
    ///
    /// This function shall make use of the gtk library, to interactively take input from the user, to form a 2D projection and returns the Projection created from the user input
    ///
    cout << "In createProjection" << endl; // ----------Remove
    Wireframe newFrame;
    newFrame = projection->create3D();
    Wireframe* retFrame;
    retFrame = new Wireframe;
    for(int i = 0; i < newFrame.vertices.size(); i++) {
        retFrame->vertices.push_back(newFrame.vertices[i]);
    }
    for(int i = 0; i < newFrame.edges.size(); i++) {
        Edge edge;
        edge.p1.setCoordinates(newFrame.edges[i].p1.x,newFrame.edges[i].p1.y,newFrame.edges[i].p1.z);
        edge.p2.setCoordinates(newFrame.edges[i].p2.x,newFrame.edges[i].p2.y,newFrame.edges[i].p2.z);        
        retFrame->edges.push_back(edge);
    }
    // cout << "retFrame: " << *retFrame << endl;
    retFrame->normalise();
    // cout << "retFrame after normalise: " << endl << *retFrame << endl;
    return retFrame;
}