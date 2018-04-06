#include "gui.h"
#include <Eigen/Dense>

using namespace Eigen;

ConstructWindow::ConstructWindow()
: m_Box(Gtk::ORIENTATION_VERTICAL),
  m_point_frame("Points"),
  m_edge_frame("Edges"),
  m_draw_frame("Rendered Object"),
  m_file_frame("Enter from File"),  
  m_rotate_frame("Rotate Object"),  
  m_submit("All Points Done"),
  m_add_point("Add More Points"),
  m_add_label("Add Label to this Point"),
  m_add_edge("Add Edge"),
  m_create("Front View Done"),
  m_top_rotate("Rotate Bottom"),
  m_bottom_rotate("Rotate Top"),
  m_left_rotate("Rotate Left"),
  m_right_rotate("Rotate Right"),
  m_add_file("Choose Input File")
{
  ///
  /// The constructor for ConstructorWindow
  ///
  front = new OrthoProjection;
  top = new OrthoProjection;
  side = new OrthoProjection;
  cp = new ClusteredPoint;
  proj = new Projection2D;
  object = new Wireframe;
  this->projection = 0;

  set_title("Front View");
  set_border_width(12);

  add(m_Box);
  m_Box.pack_start(m_point_frame, Gtk::PACK_EXPAND_WIDGET, 10);

  // Add Points
  m_point_frame.add(m_point_grid);

  m_entry_x.set_max_length(10);
  m_entry_x.set_text("x");
  m_entry_x.select_region(0, m_entry_x.get_text_length());

  m_entry_y.set_max_length(10);
  m_entry_y.set_text("y");
  m_entry_y.select_region(0, m_entry_y.get_text_length()); 

  m_entry_z.set_max_length(10);
  m_entry_z.set_text("z");
  m_entry_z.select_region(0, m_entry_z.get_text_length());  

  m_entry_label.set_max_length(10);
  m_entry_label.set_text("label");
  m_entry_label.select_region(0, m_entry_label.get_text_length());

  m_point_grid.add(m_entry_x);
  m_point_grid.attach_next_to(m_entry_y, m_entry_x, Gtk::POS_RIGHT, 1, 1);
  m_point_grid.attach_next_to(m_entry_z, m_entry_y, Gtk::POS_RIGHT, 1, 1);
  m_point_grid.attach_next_to(m_entry_label, m_entry_z, Gtk::POS_RIGHT, 1, 1);
  m_point_grid.attach_next_to(m_submit, m_entry_x, Gtk::POS_BOTTOM, 1, 1);
  m_point_grid.attach_next_to(m_add_point, m_submit, Gtk::POS_RIGHT, 1, 1);
  m_point_grid.attach_next_to(m_add_label, m_add_point, Gtk::POS_RIGHT, 2, 1);

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
  m_edge_grid.attach_next_to(m_add_edge, m_edge_p2, Gtk::POS_RIGHT, 2, 1);
  // m_edge_grid.attach_next_to(m_add_edge, m_edge_submit, Gtk::POS_RIGHT, 1, 1);

  m_add_edge.set_sensitive(false);
  m_create.set_sensitive(false);

  // Create Button
  m_Box.pack_start(m_create, Gtk::PACK_EXPAND_WIDGET, 10);

  // Add File Input
  m_Box.pack_start(m_file_frame, Gtk::PACK_EXPAND_WIDGET, 10);
  m_file_frame.add(m_file_grid);

  m_file_grid.add(m_add_file);

  // Add Drawing Area
  m_Box.pack_start(m_draw_frame, Gtk::PACK_EXPAND_WIDGET, 10);
  m_draw_frame.add(m_draw_grid);  
  m_area.set_size_request(600,500);
  m_draw_grid.add(m_area);
  m_area.show();

  // Add Rotate Buttons
  m_Box.pack_start(m_rotate_frame, Gtk::PACK_EXPAND_WIDGET, 10);
  m_rotate_frame.add(m_rotate_grid);
  m_rotate_grid.attach(m_top_rotate, 1, 1, 2, 1);
  m_rotate_grid.attach_next_to(m_left_rotate, m_top_rotate, Gtk::POS_RIGHT, 1, 1);
  m_rotate_grid.attach_next_to(m_bottom_rotate, m_left_rotate, Gtk::POS_RIGHT, 1, 1);
  m_rotate_grid.attach_next_to(m_right_rotate, m_bottom_rotate, Gtk::POS_RIGHT, 1, 1);  

  m_area.signal_draw().connect(
  sigc::mem_fun(*this, &ConstructWindow::on_custom_draw));

  // Signal Handlers
  m_submit.signal_clicked().connect(sigc::mem_fun(*this,
      &ConstructWindow::on_button_submit) );
  m_add_point.signal_clicked().connect(sigc::mem_fun(*this,
      &ConstructWindow::on_button_addpoint) );
  m_add_label.signal_clicked().connect(sigc::mem_fun(*this,
      &ConstructWindow::on_button_addlabel) );
  m_add_edge.signal_clicked().connect(sigc::mem_fun(*this,
      &ConstructWindow::on_button_addedge) );
  m_create.signal_clicked().connect(sigc::mem_fun(*this,
      &ConstructWindow::on_button_created) );
  m_top_rotate.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,
      &ConstructWindow::on_button_rotate), 1) );
  m_left_rotate.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,
      &ConstructWindow::on_button_rotate), 2) );
  m_bottom_rotate.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,
      &ConstructWindow::on_button_rotate), 3) );
  m_right_rotate.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,
      &ConstructWindow::on_button_rotate), 4) );
  m_add_file.signal_clicked().connect(sigc::mem_fun(*this,
      &ConstructWindow::on_button_file_clicked) );
  show_all_children();
}

void ConstructWindow::on_button_submit()
{
  ///
  /// Function to submit ClusteredPoint, so as to enter the next point 
  ///
  std::cout << "Entered text: " << m_entry_x.get_text() << m_entry_y.get_text() 
    << m_entry_z.get_text() << m_entry_label.get_text() << std::endl;
  Point p;
  double x = atof(m_entry_x.get_text().c_str());
  double y = atof(m_entry_y.get_text().c_str());
  double z = atof(m_entry_z.get_text().c_str());
  string label = std::string(m_entry_label.get_text());
  p.setCoordinatesAndLabel(x,y,z,label);
  cp->points.push_back(p);
  if(this->projection==0)
    front->vertices.push_back(*cp);
  else if(this->projection==1)
    top->vertices.push_back(*cp);
  else
    side->vertices.push_back(*cp);
  m_add_edge.set_sensitive(true);
  m_create.set_sensitive(true);
  this->m_entry_x.set_text("x");
  this->m_entry_y.set_text("y");
  this->m_entry_z.set_text("z");
  this->m_entry_label.set_text("label");
}

void ConstructWindow::on_button_addpoint()
{
  ///
  /// Function to add a point to the previous ClusteredPoint
  ///
  std::cout << "Entered text: " << m_entry_x.get_text() << m_entry_y.get_text() 
    << m_entry_z.get_text() << m_entry_label.get_text() << std::endl;
  Point p;
  double x = atof(m_entry_x.get_text().c_str());
  double y = atof(m_entry_y.get_text().c_str());
  double z = atof(m_entry_z.get_text().c_str());
  string label = std::string(m_entry_label.get_text());
  p.setCoordinatesAndLabel(x,y,z,label);
  cp->points.push_back(p);
  if(this->projection==0)
    front->vertices.push_back(*cp);
  else if(this->projection==1)
    top->vertices.push_back(*cp);
  else
    side->vertices.push_back(*cp);
  cp = new ClusteredPoint;
  this->m_entry_x.set_text("x");
  this->m_entry_y.set_text("y");
  this->m_entry_z.set_text("z");
  this->m_entry_label.set_text("label");
}

void ConstructWindow::on_button_addlabel()
{
  ///
  /// Function to add label to the ClusteredPoint
  ///
  std::cout << "Entered text: " << m_entry_x.get_text() << m_entry_y.get_text() 
    << m_entry_z.get_text() << m_entry_label.get_text() << std::endl;
  // this->m_entry_label.set_text("label");
  Point p;
  double x = atof(m_entry_x.get_text().c_str());
  double y = atof(m_entry_y.get_text().c_str());
  double z = atof(m_entry_z.get_text().c_str());
  string label = std::string(m_entry_label.get_text());
  p.setCoordinatesAndLabel(x,y,z,label);
  cp->points.push_back(p);
  this->m_entry_label.set_text("label");  
}

void ConstructWindow::on_button_addedge()
{
  ///
  /// Function to add a new edge to the projection
  ///
  string label1 = std::string(m_edge_p1.get_text());
  string label2 = std::string(m_edge_p2.get_text());\
  OrthoProjection* currProjection;
  if(this->projection==0) 
    currProjection = this->front;
  else if(this->projection==1) 
    currProjection = this->top;
  else
    currProjection = this->side;
  auto it1 = find_if(currProjection->vertices.begin(),currProjection->vertices.end(),
            [label1] (ClusteredPoint cp) -> bool {
                        int flag = 0;
                        for(int i = 0; i < cp.points.size(); i++) {
                            if(cp.points[i].label==label1)
                                return true;
                        }
                        return false;});
  auto it2 = find_if(currProjection->vertices.begin(),currProjection->vertices.end(),
            [label2] (ClusteredPoint cp) -> bool {
                        int flag = 0;
                        for(int i = 0; i < cp.points.size(); i++) {
                            if(cp.points[i].label==label2)
                                return true;
                        }
                        return false;});
  if(it1!=currProjection->vertices.end() && it2!=currProjection->vertices.end()) {
    Edge2D edge;
    edge.cp1 = *it1;
    edge.cp2 = *it2;
    currProjection->edges.push_back(edge);
  }
  this->m_edge_p1.set_text("Label of First Point");
  this->m_edge_p2.set_text("Label of Second Point");
}

void ConstructWindow::on_button_created()
{
  ///
  /// Create 3D Object
  ///
  projection++;
  m_add_edge.set_sensitive(false);
  m_create.set_sensitive(false);
  this->m_entry_x.set_text("x");
  this->m_entry_y.set_text("y");
  this->m_entry_z.set_text("z");
  this->m_entry_label.set_text("label");
  this->m_edge_p1.set_text("Label of First Point");
  this->m_edge_p2.set_text("Label of Second Point");
  cp = new ClusteredPoint;
  if(projection==1) {
    m_create.set_label("Top View Done");
    cout << "Front View: " << *(this->front) << endl;
    this->set_title("Top View");
  }
  else if(projection==2) {
    m_create.set_label("Side View Done");
    this->set_title("Top View");
    cout << "Top View: " << *(this->top) << endl;    
    this->set_title("Side View");
  }
  else {
    this->create = true;
    cout << "Side View: " << *(this->side) << endl;        
    proj->frontview = *(this->front);
    proj->topview = *(this->top);
    proj->sideview = *(this->side);
    object = createProjection(proj);
    cout << object->vertices.size() << endl;
    m_area.queue_draw();
  }
}

void ConstructWindow::on_button_file_clicked()
{
  ///
  /// Function to take in file input from dialog box from user
  ///
  Gtk::FileChooserDialog dialog("Please choose a file",
          Gtk::FILE_CHOOSER_ACTION_OPEN);
  dialog.set_transient_for(*this);

  //Add response buttons the the dialog:
  dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
  dialog.add_button("_Open", Gtk::RESPONSE_OK);

  //Add filters, so that only certain file types can be selected:

  auto filter_text = Gtk::FileFilter::create();
  filter_text->set_name("Text files");
  filter_text->add_mime_type("text/plain");
  dialog.add_filter(filter_text);

  auto filter_cpp = Gtk::FileFilter::create();
  filter_cpp->set_name("C/C++ files");
  filter_cpp->add_mime_type("text/x-c");
  filter_cpp->add_mime_type("text/x-c++");
  filter_cpp->add_mime_type("text/x-c-header");
  dialog.add_filter(filter_cpp);

  auto filter_any = Gtk::FileFilter::create();
  filter_any->set_name("Any files");
  filter_any->add_pattern("*");
  dialog.add_filter(filter_any);

  //Show the dialog and wait for a user response:
  int result = dialog.run();

  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {
      std::cout << "Open clicked." << std::endl;

      //Notice that this is a std::string, not a Glib::ustring.
      std::string filename = dialog.get_filename();
      std::cout << "File selected: " <<  filename << std::endl;
      object = input2Dfile(filename);
      this->create = true;
      m_area.queue_draw();
      break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
  }
}

// void ConstructWindow::on_file_button()
// {
//   ///
//   /// Add file name for input
//   ///
//   cout << "Input Name" << m_entry_file.get_text() << endl;
//   std::string str = m_entry_file.get_text();
//   object = input2Dfile(str);
//   this->create = true;
//   m_area.queue_draw();
// }

bool ConstructWindow::on_custom_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  ///
  /// Function to draw the Wireframe Model
  ///
  int width = m_area.get_allocated_width();  
  int height = m_area.get_allocated_height();  
  std::cout << "In oncdraw" << std::endl;
  // std::cout << width << " " << height << std::endl;
  // coordinates for the center of the window
  int xc, yc;
  xc = width / 2;
  yc = height / 2;

  Wireframe* obj;
  obj = object->projectFrame();

  // cout << "Frame passed in custom_draw: " << *object << endl;
  cout << "Projected Frame drawn" << endl;
  // cout << "Projected Frame: " << *obj << endl;

  if(this->create)
    cr->set_line_width(2.0);
  else
    cr->set_line_width(15.0);
  cr->set_source_rgb(0.1, 0.1, 0.6);

  if(this->create) {
    Vector3d p1(obj->edges[0].p1.x,obj->edges[0].p1.y,obj->edges[0].p1.z);
    Vector3d p2(obj->edges[0].p2.x,obj->edges[0].p2.y,obj->edges[0].p2.z);
    double dist = (p1-p2).norm();
    if(factor==0)
      factor = (width/dist)/5;  
    for(int i = 0; i < obj->edges.size(); i++) {
      // cout << obj->edges[i].p1.x << " " << obj->edges[i].p1.y << endl;
      cr->move_to((obj->edges[i].p1.x)*factor + xc, (obj->edges[i].p1.y)*factor + yc);
      cr->line_to((obj->edges[i].p2.x)*factor + xc, (obj->edges[i].p2.y)*factor + yc);
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

void ConstructWindow::on_button_rotate(int type)
{
  ///
  /// Rotate object based on the type passed aas parameter
  ///
  object->rotateFrame(type);
  m_area.queue_draw();
}

ConstructWindow::~ConstructWindow()
{
}
