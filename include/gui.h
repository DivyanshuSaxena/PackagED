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
  double plane[4];

private:
  // Signal handlers:
  void on_button_submit();
  void on_button_addpoint();
  void on_button_addedge();
  void on_button_addface();
  void on_button_created();

  // Signals
  bool pointsDone, create, init;

  // Child widgets:
  Gtk::Box m_Box;
  Gtk::Frame m_point_frame, m_edge_frame, m_face_frame, m_plane_frame;
  Gtk::Grid m_point_grid, m_edge_grid, m_face_grid, m_plane_grid;
  Gtk::Entry m_entry_x, m_entry_y, m_entry_z, m_entry_label;
  Gtk::Entry m_entry_a, m_entry_b, m_entry_c, m_entry_d;
  Gtk::Entry m_edge_p1, m_edge_p2;
  Gtk::Button m_submit, m_add_point;
  Gtk::Button m_add_edge, m_add_face, m_create;
  Gtk::CheckButton** m_face_point;
};

class ConstructWindow : public Gtk::Window
{
public:
  ConstructWindow();
  virtual ~ConstructWindow();

private:
  // Signal handlers:
  // void on_button_quit();
  void on_button_numbered(const Glib::ustring& data);

  // Child widgets:
  Gtk::Grid m_grid;
  Gtk::Button m_button_1, m_button_2;
};

class MainWindow : public Gtk::Window
{
public:
  MainWindow();
  virtual ~MainWindow();
  Object3D* obj;
  Projection2D* proj;

private:
  // Signal handlers:
  void on_button_numbered(const Glib::ustring& data);

  // Child widgets:
  Gtk::Grid m_grid;
  Gtk::Button m_button_1, m_button_2;
  // ProjectionWindow* prwindow;
  // ConstructWindow* crwindow;
};

#endif /* GTKMM_PROJWINDOW_H */
