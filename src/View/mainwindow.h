#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QVector>

#include "../Controller/Controller.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(s21::Controller &c, QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  s21::Controller controller;

 private slots:
  void button_push();
  void on_pushButton_EQ_clicked();
  void on_pushButton_10_clicked();
  void on_pushButton_backspace_clicked();
  void on_pushButton_Grafic_clicked();
  void on_pushButton_Clear_Graf_clicked();
  void on_pushButton_calculateCredit_clicked();
  void on_pushButton_calculateDeposit_clicked();
};
#endif  // MAINWINDOW_H
