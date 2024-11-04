#include "credit.h"

#include "ui_credit.h"

extern "C" {
#include "../../s21_SmartCalc.h"
}

Credit::Credit(QWidget *parent) : QMainWindow(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
}

Credit::~Credit() { delete ui; }

void Credit::on_Button_0_clicked() {
  if (count == 1) ui->Sum->setText(ui->Sum->text() + "0");
  if (count == 2) ui->Time->setText(ui->Time->text() + "0");
  if (count == 3) ui->Rate->setText(ui->Rate->text() + "0");
}
void Credit::on_Button_1_clicked() {
  if (count == 1) ui->Sum->setText(ui->Sum->text() + "1");
  if (count == 2) ui->Time->setText(ui->Time->text() + "1");
  if (count == 3) ui->Rate->setText(ui->Rate->text() + "1");
}
void Credit::on_Button_2_clicked() {
  if (count == 1) ui->Sum->setText(ui->Sum->text() + "2");
  if (count == 2) ui->Time->setText(ui->Time->text() + "2");
  if (count == 3) ui->Rate->setText(ui->Rate->text() + "2");
}
void Credit::on_Button_3_clicked() {
  if (count == 1) ui->Sum->setText(ui->Sum->text() + "3");
  if (count == 2) ui->Time->setText(ui->Time->text() + "3");
  if (count == 3) ui->Rate->setText(ui->Rate->text() + "3");
}
void Credit::on_Button_4_clicked() {
  if (count == 1) ui->Sum->setText(ui->Sum->text() + "4");
  if (count == 2) ui->Time->setText(ui->Time->text() + "4");
  if (count == 3) ui->Rate->setText(ui->Rate->text() + "4");
}
void Credit::on_Button_5_clicked() {
  if (count == 1) ui->Sum->setText(ui->Sum->text() + "5");
  if (count == 2) ui->Time->setText(ui->Time->text() + "5");
  if (count == 3) ui->Rate->setText(ui->Rate->text() + "5");
}
void Credit::on_Button_6_clicked() {
  if (count == 1) ui->Sum->setText(ui->Sum->text() + "6");
  if (count == 2) ui->Time->setText(ui->Time->text() + "6");
  if (count == 3) ui->Rate->setText(ui->Rate->text() + "6");
}
void Credit::on_Button_7_clicked() {
  if (count == 1) ui->Sum->setText(ui->Sum->text() + "7");
  if (count == 2) ui->Time->setText(ui->Time->text() + "7");
  if (count == 3) ui->Rate->setText(ui->Rate->text() + "7");
}
void Credit::on_Button_8_clicked() {
  if (count == 1) ui->Sum->setText(ui->Sum->text() + "8");
  if (count == 2) ui->Time->setText(ui->Time->text() + "8");
  if (count == 3) ui->Rate->setText(ui->Rate->text() + "8");
}
void Credit::on_Button_9_clicked() {
  if (count == 1) ui->Sum->setText(ui->Sum->text() + "9");
  if (count == 2) ui->Time->setText(ui->Time->text() + "9");
  if (count == 3) ui->Rate->setText(ui->Rate->text() + "9");
}
void Credit::on_Button_DOT_clicked() {
  if (count == 1 && !ui->Sum->text().contains("."))
    ui->Sum->setText(ui->Sum->text() + ".");
  if (count == 2 && !ui->Time->text().contains("."))
    ui->Time->setText(ui->Time->text() + ".");
  if (count == 3 && !ui->Rate->text().contains("."))
    ui->Rate->setText(ui->Rate->text() + ".");
}
void Credit::on_Button_NEXT_clicked() {
  if (count < 3)
    count++;
  else
    count = 1;
}

void Credit::on_Button_PREV_clicked() {
  if (count == 1)
    count = 3;
  else
    count--;
}
void Credit::on_Button_AC_clicked() {
  ui->Sum->setText("");
  ui->Time->setText("");
  ui->Rate->setText("");
  ui->Res->setText("");
  count = 1;
}
void Credit::on_Button_C_clicked() {
  if (count == 1) ui->Sum->setText("");
  if (count == 2) ui->Time->setText("");
  if (count == 3) ui->Rate->setText("");
}

QString Credit::conv_str(char *result) {
  std::string output;
  output = result;
  QString qOutput = QString::fromStdString(output);
  qOutput.replace(",", ".");

  qOutput = qOutput.trimmed();
  if (qOutput.contains('.')) {
    while (qOutput.endsWith('0')) {
      qOutput.chop(1);
    }
    if (qOutput.endsWith('.')) {
      qOutput.chop(1);
    }
  }
  return qOutput;
}
void Credit::on_Button_EQ_clicked() {
  char out[256];
  int err = 0;
  QString input_sum = ui->Sum->text();
  QByteArray byteArrayS = input_sum.toUtf8();
  const char *Sum_c = byteArrayS.constData();
  QString input_time = ui->Time->text();
  QByteArray byteArrayT = input_time.toUtf8();
  const char *Time_c = byteArrayT.constData();
  QString input_rate = ui->Rate->text();
  QByteArray byteArrayR = input_rate.toUtf8();
  const char *Rate_c = byteArrayR.constData();
  if (ui->annuit->isChecked()) {
    err = ann_credit_calc(Sum_c, Time_c, Rate_c, out);
    if (!err) {
      QString qOutput = conv_str(out);
      ui->Res->setText(qOutput);
    }
  } else if (ui->diff->isChecked()) {
    err = diff_credit_calc(Sum_c, Time_c, Rate_c, out);
    if (!err) {
      QString qOutput = conv_str(out);
      ui->Res->setText(qOutput);
    }
  } else
    ui->Res->setText("INCORRECT INPUT");
}
