#include <QApplication>
#include <iostream>
#include "drawsender.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  DrawSender w;
  w.show();

  return a.exec();
}
