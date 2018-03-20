#include "gui.h"
#include <Eigen/Dense>

using namespace Eigen;

ProjectionWindow::ProjectionWindow()
: m_Box(Gtk::ORIENTATION_VERTICAL),
  m_point_frame("Points"),
  m_edge_frame("Edges"),
  m_face_frame("Faces"),
  m_plane_frame("Projection Plane"),
  m_draw_frame("Rendered Projection"),
  m_file_frame("Enter from file"),
  m_submit("All Points Done"),
  m_add_point("Add More Points"),
  m_add_edge("Add Edge"),
  m_add_face("Add Face"),
  m_create("Create Projection"),
  m_add_file("Create Projection")
{
  obj = new Object3D;
  pointsDone = false;
  create = false;
  init = true;
  set_title("Project 3D Object on a plane");
  set_border_width(12);

  add(m_Box);
  m_Box.pack_start(m_point_frame, Gtk::PACK_EXPAND_WIDGET, 10);

  // Add Points
  m_point_frame.add(m_point_grid);

  m_entry_x.set_max_length(5);
  m_entry_x.set_text("x");
  m_entry_x.select_region(0, m_entry_x.get_text_length());

  m_entry_y.set_max_length(5);
  m_entry_y.set_text("y");
  m_entry_y.select_region(0, m_entry_y.get_text_length()); 

  m_entry_z.set_max_length(5);
  m_entry_z.set_text("z");
  m_entry_z.select_region(0, m_entry_z.get_text_length());  

  m_entry_label.set_max_length(10);
  m_entry_label.set_text("label");
  m_entry_label.select_region(0, m_entry_label.get_text_length());

  m_point_grid.add(m_entry_x);
  m_point_grid.attach_next_to(m_entry_y, m_entry_x, Gtk::POS_RIGHT, 1, 1);
  m_point_grid.attach_next_to(m_entry_z, m_entry_y, Gtk::POS_RIGHT, 1, 1);
  m_point_grid.attach_next_to(m_entry_label, m_entry_z, Gtk::POS_RIGHT, 1, 1);
  m_point_grid.attach_next_to(m_submit, m_entry_x, Gtk::POS_BOTTOM, 2, 1);
  m_point_grid.attach_next_to(m_add_point, m_submit, Gtk::POS_RIGHT, 2, 1);

  // Add Edges
  m_Box.pack_start(m_edge_frame, Gtk::PACK_EXPAND_WIDGET, 10);

  m_edge_p1.set_max_length(30);
  m_edge_p1.set_text("Label of First Point");
  m_edge_p1.select_region(0, m_edge_p1.get_text_length());

  m_edge_p2.set_max_length(30);
  m_edge_p2.set_text("Label of Second Point");
  m_edge_p2.select_region(0, m_edge_p1.get_text_length());

  m_edge_frame.add(m_edge_grid);
  m_edge_grid.add(m_edge_p1);
  m_edge_grid.attach_next_to(m_edge_p2, m_edge_p1, Gtk::POS_RIGHT, 1, 1);
  m_edge_grid.attach_next_to(m_add_edge, m_edge_p1, Gtk::POS_BOTTOM, 2, 1);
  // m_edge_grid.attach_next_to(m_add_edge, m_edge_submit, Gtk::POS_RIGHT, 1, 1);

  m_add_edge.set_sensitive(false);

  // Add Faces
  m_Box.pack_start(m_face_frame, Gtk::PACK_EXPAND_WIDGET, 10);

  m_face_frame.add(m_face_grid);
  m_face_grid.add(m_add_face);

  m_add_face.set_sensitive(false);

  // Add Projection Plane
  m_Box.pack_start(m_plane_frame, Gtk::PACK_EXPAND_WIDGET, 10);
  m_plane_frame.add(m_plane_grid);

  m_entry_a.set_max_length(10);
  m_entry_a.set_text("a");
  m_entry_a.select_region(0, m_entry_a.get_text_length());

  m_entry_b.set_max_length(10);
  m_entry_b.set_text("b");
  m_entry_b.select_region(0, m_entry_b.get_text_length()); 

  m_entry_c.set_max_length(10);
  m_entry_c.set_text("c");
  m_entry_c.select_region(0, m_entry_c.get_text_length());  

  m_entry_d.set_max_length(10);
  m_entry_d.set_text("d");
  m_entry_d.select_region(0, m_entry_d.get_text_length());

  m_plane_grid.add(m_entry_a);
  m_plane_grid.attach_next_to(m_entry_b, m_entry_a, Gtk::POS_RIGHT, 1, 1);
  m_plane_grid.attach_next_to(m_entry_c, m_entry_b, Gtk::POS_RIGHT, 1, 1);
  m_plane_grid.attach_next_to(m_entry_d, m_entry_c, Gtk::POS_RIGHT, 1, 1);
  m_plane_grid.attach_next_to(m_create, m_entry_b, Gtk::POS_BOTTOM, 2, 1);

  // Add Choose from File
  m_Box.pack_start(m_file_frame, Gtk::PACK_EXPAND_WIDGET, 10);
  m_file_frame.add(m_file_grid);

  m_entry_file.set_max_length(30);
  m_entry_file.set_text("Name of file");
  m_entry_file.select_region(0, m_entry_file.get_text_length());

  m_file_grid.add(m_entry_file);
  m_file_grid.attach_next_to(m_add_file, m_entry_file, Gtk::POS_RIGHT, 1, 1);

  // Add Drawing Area
  m_Box.pack_start(m_draw_frame, Gtk::PACK_EXPAND_WIDGET, 10);
  m_area.set_size_request(600,500);
  m_draw_frame.add(m_area);

  // Signal Handlers
  m_submit.signal_clicked().connect(sigc::mem_fun(*this,
      &ProjectionWindow::on_button_submit) );
  m_add_point.signal_clicked().connect(sigc::mem_fun(*this,
      &ProjectionWindow::on_button_addpoint) );
  m_add_edge.signal_clicked().connect(sigc::mem_fun(*this,
      &ProjectionWindow::on_button_addedge) );
  m_add_face.signal_clicked().connect(sigc::mem_fun(*this,
      &ProjectionWindow::on_button_addface) );
  m_create.signal_clicked().connect(sigc::mem_fun(*this,
    &ProjectionWindow::on_button_created) );
  m_area.signal_draw().connect(
    sigc::mem_fun(*this, &ProjectionWindow::on_custom_draw));
  m_add_file.signal_clicked().connect(sigc::mem_fun(*this,
      &ProjectionWindow::on_file_button) );
  show_all_children();
}

void ProjectionWindow::on_button_submit()
{
  std::cout << "Entered text: " << m_entry_x.get_text() << m_entry_y.get_text() 
    << m_entry_z.get_text() << m_entry_label.get_text() << std::endl;
  Point p;
  double x = atof(m_entry_x.get_text().c_str());
  double y = atof(m_entry_y.get_text().c_str());
  double z = atof(m_entry_z.get_text().c_str());
  string label = std::string(m_entry_label.get_text());
  p.setCoordinatesAndLabel(x,y,z,label);
  obj->vertices.push_back(p);
  this->pointsDone = true;
  m_face_point = new Gtk::CheckButton*[obj->vertices.size()];
  m_add_edge.set_sensitive(true);
  m_add_face.set_sensitive(true);
}

void ProjectionWindow::on_button_addpoint()
{
  std::cout << "Entered text: " << m_entry_x.get_text() << m_entry_y.get_text() 
    << m_entry_z.get_text() << m_entry_label.get_text() << std::endl;
  Point p;
  double x = atof(m_entry_x.get_text().c_str());
  double y = atof(m_entry_y.get_text().c_str());
  double z = atof(m_entry_z.get_text().c_str());
  string label = std::string(m_entry_label.get_text());
  p.setCoordinatesAndLabel(x,y,z,label);
  obj->vertices.push_back(p);
  this->m_entry_x.set_text("x");
  this->m_entry_y.set_text("y");
  this->m_entry_z.set_text("z");
  this->m_entry_label.set_text("label");
}

void ProjectionWindow::on_button_addedge()
{
  string label1 = std::string(m_edge_p1.get_text());
  string label2 = std::string(m_edge_p2.get_text());
  auto it1 = find_if(obj->vertices.begin(),obj->vertices.end(),
                    [label1] (Point p) -> bool {return (p.label==label1);});
  auto it2 = find_if(obj->vertices.begin(),obj->vertices.end(),
                    [label2] (Point p) -> bool {return (p.label==label2);});
  if(it1!=obj->vertices.end() && it2!=obj->vertices.end()) {
    Edge edge;
    edge.p1 = *it1;
    edge.p2 = *it2;
    obj->edges.push_back(edge);
  }
  m_edge_p1.set_text("Label of First Point");
  m_edge_p2.set_text("Label of Second Point");
}

void ProjectionWindow::on_button_addface()
{
  int len = obj->vertices.size();
  Face face;
  if(this->init) {
    for(int i = 0; i < len; i++) {
      m_face_point[i] = new Gtk::CheckButton(obj->vertices[i].label);
      m_face_grid.add(*m_face_point[i]);
      init = false;
      // cb.signal_clicked().connect(sigc::bind<int>( sigc::mem_fun(face,
      // &on_button_facepoint), i) );
    }
    show_all_children();
  }else{
    for(int i = 0; i < len; i++) {
      if(m_face_point[i]->get_active()) {
        face.vertices.push_back(i);
      }
      m_face_point[i]->set_active(false);
    }
    obj->faces.push_back(face); 
  }
}

void ProjectionWindow::on_button_created()
{
  plane[0] = atof(m_entry_a.get_text().c_str());
  plane[1] = atof(m_entry_b.get_text().c_str());
  plane[2] = atof(m_entry_c.get_text().c_str());
  plane[3] = atof(m_entry_d.get_text().c_str());
  this->create = true;
  output = new PlaneProjection;
  output = createObject(obj,plane);
  cout << "Object Returned" << endl;
  // OutputArea area;
  m_area.queue_draw();
  // m_Box.add(area);
}

void ProjectionWindow::on_file_button()
{
  cout << "File Name: " << m_entry_file.get_text() << endl;
  std::string str = m_entry_file.get_text();
  output = new PlaneProjection;
  output = input3Dfile(str);
  cout << "File output object" << endl << *output << endl;
  this->create = true;
  m_area.queue_draw();
}

bool ProjectionWindow::on_custom_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  int width = m_area.get_allocated_width();  
  int height = m_area.get_allocated_height();  
  std::cout << "In oncdraw" << std::endl;
  // std::cout << width << " " << height << std::endl;
  // coordinates for the center of the window
  int xc, yc;
  xc = width / 2;
  yc = height / 2;

  if(this->create)
    cr->set_line_width(2.0);
  else
    cr->set_line_width(15.0);
  // draw red lines out from the center of the window
  cr->set_source_rgb(0.0, 0.0, 0.0);

  if(this->create) {
    double sumx = 0.0;
    double sumy = 0.0;
    int len = output->visibleEdges.size() + output->hiddenEdges.size();
    for(int i = 0; i < len; i++) {
      if(i < output->visibleEdges.size()) {
        sumx += output->visibleEdges[i].p1.x;
        sumx += output->visibleEdges[i].p2.x;
        sumy += output->visibleEdges[i].p1.y;
        sumy += output->visibleEdges[i].p2.y;
      } else {
        sumx += output->hiddenEdges[i].p1.x;
        sumx += output->hiddenEdges[i].p1.x;
        sumx += output->hiddenEdges[i].p1.x;
        sumx += output->hiddenEdges[i].p1.x;        
      }
    }
    sumx = sumx/(len);
    sumy = sumy/(len);
    cout << sumx << " " << sumy << endl;
    Vector3d p1(output->visibleEdges[0].p1.x,output->visibleEdges[0].p1.y,output->visibleEdges[0].p1.z);
    Vector3d p2(output->visibleEdges[0].p2.x,output->visibleEdges[0].p2.y,output->visibleEdges[0].p2.z);
    double dist = (p1-p2).norm();
    double factor = (width/dist)/5;  
    std::vector<double> vec;
    vec.push_back(10.0);
    vec.push_back(5.0);
    cr->set_dash(vec,0);
    for(int i = 0; i < output->hiddenEdges.size(); i++) {
      cr->move_to((output->hiddenEdges[i].p1.x)*factor + xc - sumx, (output->hiddenEdges[i].p1.y)*factor + yc - sumy);
      cr->line_to((output->hiddenEdges[i].p2.x)*factor + xc - sumx, (output->hiddenEdges[i].p2.y)*factor + yc - sumy);
    }
    cr->stroke();
    cr->restore();
    for(int i = 0; i < output->visibleEdges.size(); i++) {
      cr->move_to((output->visibleEdges[i].p1.x)*factor + xc, (output->visibleEdges[i].p1.y)*factor + yc);
      cr->line_to((output->visibleEdges[i].p2.x)*factor + xc, (output->visibleEdges[i].p2.y)*factor + yc);
    }
    cr->stroke();
  } else {
    cr->move_to(xc-25,yc-25);
    cr->line_to(xc-25,yc+25);
    cr->move_to(xc+25,yc-25);
    cr->line_to(xc+25,yc+25);
    cr->stroke();
  }
  return true;
}

ProjectionWindow::~ProjectionWindow()
{
}