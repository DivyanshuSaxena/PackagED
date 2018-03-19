#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <Eigen/Dense>
#include <gtkmm.h>
#include "gui.h"
#include <fstream>

using namespace std;
using Eigen::MatrixXd;
int check2D();
int check3D();
int check2Dfile();

int main(int argc, char *argv[]) {
    /// 
    /// The main function shall be responsible for calling various other functions and instantiating the classes for using their functions cop290
    ///
        
    // ---------To Be Used Later---------
    check2Dfile();  
    // auto app =
    //     Gtk::Application::create(argc, argv,
    //     "org.gtkmm.examples");
    // MainWindow window;
    // return app->run(window);
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
    //cout <<atop<<endl;
    myproj.create3D();
    return 0;
}
int check2Dfile(){
    // ofstream inFile;
    cout <<"start" <<endl;
	// inFile.open("example.txt");
    ifstream inFile ("inp2.txt");
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
        Projection2D myproj;
        myproj.frontview = front;
        myproj.sideview = side;
        myproj.topview = top;
        myproj.create3D();
        
    }
    return 0;
}

PlaneProjection* createObject(Object3D* object, double plane[4]) {
    ///
    /// This function shall make use of the gtk library, to interactively take input from the user and returns the 3D object created from the user input
    ///
    cout << "In createObject" << endl; // ----------Remove
    // cout << "Input Object:" << endl << object;
    PlaneProjection* res = object->project3D(plane);
    cout << "Object Returned";
    res->rotatePlane();
    return res;
}

int createProjection(Projection2D* projection) {
    ///
    /// This function shall make use of the gtk library, to interactively take input from the user, to form a 2D projection and returns the Projection created from the user input
    ///
    cout << "In createObject" << endl; // ----------Remove
}
int renderObject(Wireframe frame) {
    ///
    /// This function shall make use of opengl library to render the object, from the Wireframe instance passed in parameter.
    ///
}

int renderProjection(OrthoProjection projection) {
    ///
    /// This function shall make use of opengl library to render the object, from the OrthoProjection instance passed in parameter.
    ///
}
