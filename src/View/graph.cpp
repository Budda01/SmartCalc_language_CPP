#include "graph.h"

#include "ui_graph.h"

Graph::Graph(QWidget *parent) : QMainWindow(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
  h = 0.1;
  max_x = 5;
  min_x = -5;
  max_y = 5;
  min_y = -5;

  ui->widget->xAxis->setRange(-4, 4);
  ui->widget->yAxis->setRange(-4, 4);
}

Graph::~Graph() { delete ui; }

void Graph::drawPlot(double Y[100]) {
  int j = 0;
  for (double i = -5; i < max_x; i += h) {
    x.push_back(i);
    y.push_back(Y[j]);
    j++;
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
}
