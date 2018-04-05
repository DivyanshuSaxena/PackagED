#include "gui.h"

MainWindow::MainWindow()
: m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_button_1("Project 3D Object on a Plane"),
  m_button_2("Construct Wireframe Orthographic Views")
{
  ///
  /// Constructor for MainWindow
  ///
  set_title("PackagED");
  set_border_width(12);

  add(m_VBox);

  m_VBox.pack_start(m_TextView);
  m_TextView.set_editable(false);
  m_VBox.pack_start(m_grid, Gtk::PACK_SHRINK);

  m_grid.add(m_button_1);
  m_grid.attach_next_to(m_button_2, m_button_1, Gtk::POS_RIGHT, 1, 1);
  // m_grid.attach_next_to(m_button_quit, m_button_2, Gtk::POS_BOTTOM, 1, 1);

  m_button_1.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this,
      &MainWindow::on_button_numbered), "1") );
  m_button_2.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this,
      &MainWindow::on_button_numbered), "2") );

  // Fill Buffers
  m_TextBuffer = Gtk::TextBuffer::create();
  m_TextBuffer->set_text(
          "Welcome to PackagED.\nThis software is developed to cater to the following needs for Engineering Drawing:\n1. Get 2D Projection from a 3D Object Input :- \n\tThe user can either input the 3D Object, manually by inputting the points, \n\ttheir labels and subsequently, the edges of the object (as pairs of the endpoints). \n\tThe user is also supposed to enter the faces in the Object (as collection of Points that form the face).\n\tAlternatively, the user may also enter the 3D Object from a file.\n2. Get Wireframe Model from three 2D Projections of an Object :- \n\tThere are again two options for the user to enter the Projections. \n\tFirst, the user can enter the Projection by inputting the 3D coordinates of a point and \n\tthe labels of the points at this coordinate, in the projection. \n\tNext, the user can enter the edges, consisting of the endpoints.\n\tAlternatively, the user may also enter the 2D Projections from a file.");
  m_TextView.set_buffer(m_TextBuffer);
  show_all_children();
}

void MainWindow::on_button_numbered(const Glib::ustring& data) 
{
  ///
  /// Function to call respective functions based on input by user
  ///
  std::cout << data << " was pressed" << std::endl;
  if(data==std::string("1")){
    ProjectionWindow* pinput = new ProjectionWindow;
    pinput->show();
  }else{
    ConstructWindow* cinput = new ConstructWindow;
    cinput->show();
  }
}

MainWindow::~MainWindow()
{
}