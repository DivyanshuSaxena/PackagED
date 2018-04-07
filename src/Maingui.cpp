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
  m_VBox.pack_start(m_button_1);
  m_VBox.pack_start(m_button_2);

  m_button_1.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this,
      &MainWindow::on_button_numbered), "1") );
  m_button_2.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this,
      &MainWindow::on_button_numbered), "2") );

  // Fill Buffers
  m_TextBuffer = Gtk::TextBuffer::create();
  m_TextBuffer->set_text(
          "Welcome to PackagED.\nThis software is developed to cater to the following needs for Engineering \nDrawing:\n1. Get 2D Projection from a 3D Object Input :- \n\tThe user can either input the 3D Object, manually by inputting the points, \n\ttheir labels and subsequently, the edges of the object (as pairs of the endpoints). \n\tThe user is also supposed to enter the faces in the Object (as collection \n\tof Points that form the face).\n\tAlternatively, the user may also enter the 3D Object from a file.\n2. Get Wireframe Model from three 2D Projections of an Object :- \n\tThere are again two options for the user to enter the Projections. \n\tFirst, the user can enter the Projection by inputting the 3D coordinates \n\tof a point and the labels of the points at this coordinate, in the projection. \n\tNext, the user can enter the edges, consisting of the endpoints.\n\tAlternatively, the user may also enter the 2D Projections from a file.\nThe output of 3D to 2D results in the rendered projection being shown in\n the Drawing Area.\nAs for the 2D to 3D reconstruction, the output is first rendered in OpenScad and\n later, the Wireframe Model is visible in the Drawing Area which can be verified\n to be the same as the one rendered in OpenScad.");
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