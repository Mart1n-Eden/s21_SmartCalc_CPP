#include <QApplication>

#include "View/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  s21::Economy economy;
  s21::Controller controller(model, economy);
  MainWindow w(controller);
  w.show();
  return a.exec();
}
