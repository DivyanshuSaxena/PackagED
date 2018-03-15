#ifndef GTKMM_PROJWINDOW_H
#define GTKMM_PROJWINDOW_H

#include <gtkmm.h>
#include <iostream>
#include <vector>
#include <string>
#include "Classes.h"
using namespace std;

class PointWindow : public Gtk::Window
{
public:
  PointWindow();
  virtual ~PointWindow();
  Object3D* obj;

private:
  // Signal handlers:
  void on_button_submit();
  void on_button_addpoint();
  void on_button_addlabel();

  // Child widgets:
  Gtk::Grid m_grid;
  Gtk::Entry m_entry_x, m_entry_y, m_entry_z, m_entry_label;
  Gtk::Button m_submit, m_add_point;
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
  // PointWindow* prwindow;
  // ConstructWindow* crwindow;
};

#endif /* GTKMM_PROJWINDOW_H */
