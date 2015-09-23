#include "mainwindow.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "Usage: ./DrawSource <source_socket_path>" << std::endl;
		return -1;
	}
	QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
