#ifndef CREDIT_H
#define CREDIT_H

#include <QMainWindow>

namespace Ui {
class Credit;
}

class Credit : public QMainWindow {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();
  int count = 1;
  QString conv_str(char *result);

 private slots:
  void on_Button_0_clicked();
  void on_Button_1_clicked();
  void on_Button_2_clicked();
  void on_Button_3_clicked();
  void on_Button_4_clicked();
  void on_Button_5_clicked();
  void on_Button_6_clicked();
  void on_Button_7_clicked();
  void on_Button_8_clicked();
  void on_Button_9_clicked();
  void on_Button_DOT_clicked();
  void on_Button_NEXT_clicked();
  void on_Button_PREV_clicked();
  void on_Button_AC_clicked();
  void on_Button_C_clicked();
  void on_Button_EQ_clicked();

 private:
  Ui::Credit *ui;
};

#endif  // CREDIT_H
