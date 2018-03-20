#ifndef GTKMM_PROJWINDOW_H
#define GTKMM_PROJWINDOW_H

#include <gtkmm.h>
#include <iostream>
#include <vector>
#include <string>
#include "Classes.h"
using namespace std;

class ProjectionWindow : public Gtk::Window
{
public:
  ProjectionWindow();
  virtual ~ProjectionWindow();
  Object3D* obj;
  PlaneProjection* output;
  double plane[4];
  bool create;

private:
  // Signal handlers:
  void on_button_submit();
  void on_button_addpoint();
  void on_button_addedge();
  void on_button_addface();
  void on_button_created();
  void on_file_button();
  bool on_custom_draw(const Cairo::RefPtr<Cairo::Context>& cr);
  
  // Signals
  bool pointsDone, init;

  // Child widgets:
  Gtk::Box m_Box;
  Gtk::Frame m_point_frame, m_edge_frame, m_face_frame;
  Gtk::Frame m_plane_frame, m_draw_frame, m_file_frame;
  Gtk::Grid m_point_grid, m_edge_grid, m_face_grid, m_plane_grid, m_file_grid;
  Gtk::Entry m_entry_x, m_entry_y, m_entry_z, m_entry_label;
  Gtk::Entry m_entry_a, m_entry_b, m_entry_c, m_entry_d;
  Gtk::Entry m_edge_p1, m_edge_p2, m_entry_file;
  Gtk::Button m_submit, m_add_point, m_add_file;
  Gtk::Button m_add_edge, m_add_face, m_create;
  Gtk::CheckButton** m_face_point;
  Gtk::DrawingArea m_area;
};

class ConstructWindow : public Gtk::Window
{
public:
  ConstructWindow();
  virtual ~ConstructWindow();
  Projection2D* proj;
  Wireframe* object;
  
private:
  // Signal handlers:
  // void on_button_quit();
  void on_button_submit();
  void on_button_addpoint();
  void on_button_addlabel();
  void on_button_addedge();
  void on_button_created();
  bool on_custom_draw(const Cairo::RefPtr<Cairo::Context>& cr);  
  void on_button_rotate(int type);
  void on_file_button();

  int projection, create;
  OrthoProjection* front, * top, * side;
  ClusteredPoint* cp;
  double factor;

  // Child widgets:
  Gtk::Box m_Box;
  Gtk::Frame m_point_frame, m_edge_frame, m_draw_frame;
  Gtk::Frame m_rotate_frame, m_file_frame;
  Gtk::Grid m_point_grid, m_edge_grid, m_draw_grid, m_rotate_grid, m_file_grid;
  Gtk::Entry m_entry_x, m_entry_y, m_entry_z, m_entry_label;
  Gtk::Entry m_edge_p1, m_edge_p2, m_entry_file;
  Gtk::Button m_submit, m_add_point, m_add_label;
  Gtk::Button m_add_edge, m_create, m_add_file;
  Gtk::Button m_top_rotate, m_bottom_rotate, m_left_rotate, m_right_rotate;
  Gtk::DrawingArea m_area;
};

class MainWindow : public Gtk::Window
{
public:
  MainWindow();
  virtual ~MainWindow();

private:
  // Signal handlers:
  void on_button_numbered(const Glib::ustring& data);

  // Child widgets:
  Gtk::Grid m_grid;
  Gtk::Button m_button_1, m_button_2;
};

PlaneProjection* createObject(Object3D*,double[4]);
Wireframe* createProjection(Projection2D*);

#endif /* GTKMM_PROJWINDOW_H */
