#ifndef GTKMM_PROJWINDOW_H
#define GTKMM_PROJWINDOW_H

#include <gtkmm.h>
#include <iostream>
#include <vector>
#include <string>
#include "Classes.h"
using namespace std;

class PointWindow;

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
  std::vector<Point> projectPoints;
  std::vector<ClusteredPoint> constructPoints;
  std::vector<Edge> projectEdges;
  std::vector<Edge2D> constructEdges;
  std::vector<Face> projectFaces;
  int predicate;
private:
  // Signal handlers:
  void on_button_numbered(const Glib::ustring& data);

  // Child widgets:
  Gtk::Grid m_grid;
  Gtk::Button m_button_1, m_button_2;
  PointWindow* prwindow;
  ConstructWindow* crwindow;
};

class PointWindow : public Gtk::Window
{
public:
  PointWindow(MainWindow*);
  virtual ~PointWindow();

private:
  // Signal handlers:
  void on_button_submit();
  void on_button_addpoint();
  void on_button_addlabel();
  ClusteredPoint* cp;
  MainWindow* parent;

  // Child widgets:
  Gtk::Grid m_grid;
  Gtk::Entry m_entry_x, m_entry_y, m_entry_z, m_entry_label;
  Gtk::Button m_submit, m_add_point, m_label;
  std::vector<std::string> labels;
};

#endif /* GTKMM_PROJWINDOW_H */