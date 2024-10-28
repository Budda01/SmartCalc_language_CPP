#ifndef GRAPH_H
#define GRAPH_H

#include <QMainWindow>
#include <QVector>

namespace Ui {
class Graph;
}

class Graph : public QMainWindow {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();
  void drawPlot(double Y[100]);

 private:
  Ui::Graph *ui;
  double max_x, min_x, max_y, min_y, h, X;
  int n;
  QVector<double> x, y;
 private slots:
};

#endif  // GRAPH_H
