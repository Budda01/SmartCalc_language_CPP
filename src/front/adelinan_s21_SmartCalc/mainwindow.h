#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "credit.h"
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  int check_calc = 0;
  QString for_x_calc;

 private:
  Ui::MainWindow *ui;
  Graph *graph;
  Credit *credit;

 private slots:
  void openGraph();
  void closeGraph();
  void openCredit();
  void closeCredit();
  void on_pushButton_DOT_clicked();
  void on_pushButton_0_clicked();
  void on_pushButton_1_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_3_clicked();
  void on_pushButton_4_clicked();
  void on_pushButton_5_clicked();
  void on_pushButton_6_clicked();
  void on_pushButton_7_clicked();
  void on_pushButton_8_clicked();
  void on_pushButton_9_clicked();

  void on_pushButton_PLUS_clicked();
  void on_pushButton_OP_Bracket_clicked();
  void on_pushButton_CL_Bracket_clicked();
  void on_pushButton_Pow_clicked();
  void on_pushButton_MINUS_clicked();
  void on_pushButton_DIV_clicked();
  void on_pushButton_MUL_clicked();
  void on_pushButton_C_clicked();
  void on_pushButton_AC_clicked();
  void on_pushButton_ASIN_clicked();
  void on_pushButton_ACOS_clicked();
  void on_pushButton_ATAN_clicked();
  void on_pushButton_SIN_clicked();
  void on_pushButton_COS_clicked();
  void on_pushButton_TAN_clicked();
  void on_pushButton_LOG_clicked();
  void on_pushButton_LN_clicked();
  void on_pushButton_SQRT_clicked();
  void on_pushButton_MOD_clicked();
  void on_pushButton_EQ_clicked();
  void simple_exp();
  int calc_values();
  void on_pushButton_X_clicked();
  void on_pushButton_CREDIT_clicked();
  void calc_one_value(QString for_x_calc);
  void Output_and_err(char *setingtxt, int err, int check_gr);
};
#endif  // MAINWINDOW_H
