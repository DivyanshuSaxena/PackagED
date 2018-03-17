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
    createObject();
  }else{
    createProjection();
  }
}

MainWindow::~MainWindow()
{
}