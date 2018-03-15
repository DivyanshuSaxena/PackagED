#include "gui.h"


ProjectionWindow::ProjectionWindow()
: m_Box(Gtk::ORIENTATION_VERTICAL),
  m_point_frame("Points"),
  m_edge_frame("Edges"),
  m_face_frame("Faces"),
  m_submit("All Points Done"),
  m_add_point("Add More Points"),
  m_edge_submit("All Edges Done"),
  m_add_edge("Add More Edges")
{
  obj = new Object3D;
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
  m_edge_grid.attach_next_to(m_edge_submit, m_edge_p1, Gtk::POS_BOTTOM, 1, 1);
  m_edge_grid.attach_next_to(m_add_edge, m_edge_submit, Gtk::POS_RIGHT, 1, 1);


  m_Box.pack_start(m_face_frame, Gtk::PACK_EXPAND_WIDGET, 10);

  m_submit.signal_clicked().connect(sigc::mem_fun(*this,
      &ProjectionWindow::on_button_submit) );
  m_add_point.signal_clicked().connect(sigc::mem_fun(*this,
      &ProjectionWindow::on_button_addpoint) );
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
  this->hide();
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

// void ProjectionWindow::on_button_addlabel()
// {
//   std::cout << "Entered text: " <<  m_entry_label.get_text() << std::endl;
//   this->m_entry_label.set_text("label");
// }

ProjectionWindow::~ProjectionWindow()
{
}
