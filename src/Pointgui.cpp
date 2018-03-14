#include "gui.h"

PointWindow::PointWindow()
: m_submit("All Points Done"),
  m_add_point("Add more Points")
{
  set_title("3D Object");
  set_border_width(12);

  add(m_grid);

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

  m_grid.add(m_entry_x);
  m_grid.attach_next_to(m_entry_y, m_entry_x, Gtk::POS_RIGHT, 1, 1);
  m_grid.attach_next_to(m_entry_z, m_entry_y, Gtk::POS_RIGHT, 1, 1);
  m_grid.attach_next_to(m_entry_label, m_entry_z, Gtk::POS_RIGHT, 1, 1);
  m_grid.attach_next_to(m_submit, m_entry_x, Gtk::POS_BOTTOM, 2, 1);
  m_grid.attach_next_to(m_add_point, m_submit, Gtk::POS_RIGHT, 2, 1);
  // m_grid.attach_next_to(m_label, m_add_point, Gtk::POS_RIGHT, 2, 1);
  // m_grid.attach_next_to(m_button_quit, m_button_2, Gtk::POS_BOTTOM, 1, 1);

  m_submit.signal_clicked().connect(sigc::mem_fun(*this,
      &PointWindow::on_button_submit) );
  m_add_point.signal_clicked().connect(sigc::mem_fun(*this,
      &PointWindow::on_button_addpoint) );
  // m_label.signal_clicked().connect(sigc::mem_fun(*this,
  //     &PointWindow::on_button_addlabel) ); 

  show_all_children();
}

void PointWindow::on_button_submit()
{
  std::cout << "Entered text: " << m_entry_x.get_text() << m_entry_y.get_text() 
    << m_entry_z.get_text() << m_entry_label.get_text() << std::endl;
  Point p;
  p.setCoordinatesAndLabel(stod(m_entry_x.get_text()),stod(m_entry_y.get_text()),
                            stod(m_entry_z.get_text()),std::string(m_entry_label.get_text()));
  obj.vertices.push_back(p);    
  // if(parent->predicate==1){
    
  // }else{ 
  //   Point point;
  //   point.setCoordinatesAndLabel(stod(m_entry_x.get_text()),stod(m_entry_y.get_text()),
  //                             stod(m_entry_z.get_text()),std::string(m_entry_label.get_text()));
  //   cp->points.push_back(point);
  //   ClusteredPoint newcp;
  //   for(int i = 0; i < cp->points.size(); i++)
  //     newcp.points.push_back(cp->points[i]);
  //   parent->constructPoints.push_back(newcp);
  // }
  this->hide();
}

void PointWindow::on_button_addpoint()
{
  std::cout << "Entered text: " << m_entry_x.get_text() << m_entry_y.get_text() 
    << m_entry_z.get_text() << m_entry_label.get_text() << std::endl;
  Point p;
  p.setCoordinatesAndLabel(stod(m_entry_x.get_text()),stod(m_entry_y.get_text()),
                            stod(m_entry_z.get_text()),std::string(m_entry_label.get_text()));
  obj.vertices.push_back(p);
  // if(parent->predicate==1)
  // {
    
  // }else{
  //   Point point;
  //   point.setCoordinatesAndLabel(stod(m_entry_x.get_text()),stod(m_entry_y.get_text()),
  //                             stod(m_entry_z.get_text()),std::string(m_entry_label.get_text()));
  //   cp->points.push_back(point);
  //   ClusteredPoint newcp;
  //   for(int i = 0; i < cp->points.size(); i++)
  //     newcp.points.push_back(cp->points[i]);
  //   parent->constructPoints.push_back(newcp);
  //   cp = new ClusteredPoint;
  // }
  this->m_entry_x.set_text("x");
  this->m_entry_y.set_text("y");
  this->m_entry_z.set_text("z");
  this->m_entry_label.set_text("label");
}

// void PointWindow::on_button_addlabel()
// {
//   std::cout << "Entered text: " <<  m_entry_label.get_text() << std::endl;
//   Point point;
//   point.setCoordinatesAndLabel(stod(m_entry_x.get_text()),stod(m_entry_y.get_text()),
//                             stod(m_entry_z.get_text()),std::string(m_entry_label.get_text()));
//   cp->points.push_back(point);
//   this->m_entry_label.set_text("label");
// }
