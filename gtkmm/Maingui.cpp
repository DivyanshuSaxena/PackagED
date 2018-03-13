#include "gui.h"

MainWindow::MainWindow()
: m_button_1("Project 3D Object on a Plane"),
  m_button_2("Construct Wireframe Orthographic Views")
{
  set_title("PackagED");
  set_border_width(12);

  add(m_grid);

  m_grid.add(m_button_1);
  m_grid.attach_next_to(m_button_2, m_button_1, Gtk::POS_BOTTOM, 1, 1);
  // m_grid.attach_next_to(m_button_quit, m_button_2, Gtk::POS_BOTTOM, 1, 1);

  m_button_1.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this,
      &MainWindow::on_button_numbered), "1") );
  m_button_2.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this,
      &MainWindow::on_button_numbered), "2") );

  show_all_children();
}

void MainWindow::on_button_numbered(const Glib::ustring& data) 
{
  std::cout << data << " was pressed" << std::endl;
  if(data==std::string("1")){
    prwindow = new PointWindow;
    prwindow->show();
  }else{
    std::cout << "Under Construction";
  }
}

PointWindow::PointWindow()
: m_submit("All Points Done"),
  m_add_point("Add more Points"),
  m_label("Add more labels to this Point")
{
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
  m_grid.attach_next_to(m_label, m_add_point, Gtk::POS_RIGHT, 2, 1);
  // m_grid.attach_next_to(m_button_quit, m_button_2, Gtk::POS_BOTTOM, 1, 1);

  m_submit.signal_clicked().connect(sigc::mem_fun(*this,
      &PointWindow::on_button_submit) );
  m_add_point.signal_clicked().connect(sigc::mem_fun(*this,
      &PointWindow::on_button_addpoint) );
  m_label.signal_clicked().connect(sigc::mem_fun(*this,
      &PointWindow::on_button_addlabel) ); 

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

MainWindow::~MainWindow()
{
}

ConstructWindow::~ConstructWindow()
{
}

int main(int argc, char *argv[])
{
  auto app =
    Gtk::Application::create(argc, argv,
      "org.gtkmm.examples");

  MainWindow window;
  // window.set_default_size(600, 400);

  return app->run(window);
}