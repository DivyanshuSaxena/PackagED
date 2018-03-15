#include "gui.h"


PointWindow::PointWindow()
: m_submit("All Points Done"),
  m_add_point("Add more Points")
{
  obj = new Object3D;
  set_title("PackagED");
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
  m_grid.attach_next_to(m_submit, m_entry_x, Gtk::POS_BOTTOM, 1, 1);
  m_grid.attach_next_to(m_add_point, m_submit, Gtk::POS_RIGHT, 1, 1);
  // m_grid.attach_next_to(m_button_quit, m_button_2, Gtk::POS_BOTTOM, 1, 1);

  m_submit.signal_clicked().connect(sigc::mem_fun(*this,
      &PointWindow::on_button_submit) );
  m_add_point.signal_clicked().connect(sigc::mem_fun(*this,
      &PointWindow::on_button_addpoint) );
  cout << "Initialised PointWindow" << endl; // ------Remove
  show_all_children();
}

void PointWindow::on_button_submit()
{
  std::cout << "Entered text: " << m_entry_x.get_text() << m_entry_y.get_text() 
    << m_entry_z.get_text() << m_entry_label.get_text() << std::endl;
  this->hide();
}

void PointWindow::on_button_addpoint()
{
  std::cout << "Entered text: " << m_entry_x.get_text() << m_entry_y.get_text() 
    << m_entry_z.get_text() << m_entry_label.get_text() << std::endl;
  this->m_entry_x.set_text("x");
  this->m_entry_y.set_text("y");
  this->m_entry_z.set_text("z");
  this->m_entry_label.set_text("label");
}

void PointWindow::on_button_addlabel()
{
  std::cout << "Entered text: " <<  m_entry_label.get_text() << std::endl;
  this->m_entry_label.set_text("label");
}

PointWindow::~PointWindow()
{
}
