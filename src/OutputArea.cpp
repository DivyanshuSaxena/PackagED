#include "gui.h"
#include <cairomm/context.h>

OutputArea::OutputArea(PlaneProjection &output)
{
  for (auto i = 0; i < output.vertices.size(); i++) {
      render->vertices.push_back(output.vertices[i]);
  }
  for (auto i = 0; i < output.visibleEdges.size(); i++) {
    Edge edge;
    edge.p1 = output.visibleEdges[i].p1;
    edge.p2 = output.visibleEdges[i].p2;
    render->visibleEdges.push_back(edge);
  }
  for (auto i = 0; i < output.hiddenEdges.size(); i++) {
    Edge edge;
    edge.p1 = output.hiddenEdges[i].p1;
    edge.p2 = output.hiddenEdges[i].p2;
    render->hiddenEdges.push_back(edge);
  }
  cout << "Constructor call" << endl; // -------Remove
}

OutputArea::~OutputArea()
{
}

bool OutputArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  // coordinates for the center of the window
  int xc, yc;
  xc = width / 2;
  yc = height / 2;

  cr->set_line_width(10.0);

  // draw red lines out from the center of the window
  cr->set_source_rgb(0.8, 0.0, 0.0);
  cr->move_to(0, 0);
  cr->line_to(xc, yc);
  cr->line_to(0, height);
  cr->move_to(xc, yc);
  cr->line_to(width, yc);
  cr->stroke();

  return true;
}