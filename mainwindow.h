#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "drawsender.h"
#include "griddrawer.h"
#include <memory>
#include <QMainWindow>
#include <QColorDialog>
#include <QHBoxLayout>
#include <QGraphicsView>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
	QGraphicsView* centralWidget;
	QHBoxLayout* layout;
	QColorDialog* colorDialog;
	GridDrawer* gridDrawer;
    DrawSender* drawSender;
};

#endif // MAINWINDOW_H
