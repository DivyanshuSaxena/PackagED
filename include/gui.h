#ifndef GTKMM_PROJWINDOW_H
#define GTKMM_PROJWINDOW_H

#include <vector>
#include <string>
#include "Classes.h"
using namespace std;

class MainWindow : public Gtk::Window
{
public:
  MainWindow();
  virtual ~MainWindow();
  int predicate;
  Object3D obj;
  Projection2D proj;
private:
  // Signal handlers:
  void on_button_numbered(const Glib::ustring& data);

  // Child widgets:
  Gtk::Grid m_grid;
  Gtk::Button m_button_1, m_button_2;
};

class PointWindow : public Gtk::Window
{
public:
  PointWindow();
  virtual ~PointWindow();
  Object3D obj;

private:
  // Signal handlers:
  void on_button_submit();
  void on_button_addpoint();
  // void on_button_addlabel();

  // Child widgets:
  Gtk::Grid m_grid;
  Gtk::Entry m_entry_x, m_entry_y, m_entry_z, m_entry_label;
  Gtk::Button m_submit, m_add_point;
  // std::vector<std::string> labels;
};

#endif /* GTKMM_PROJWINDOW_H */