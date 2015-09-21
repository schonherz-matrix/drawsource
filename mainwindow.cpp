#include "mainwindow.h"
#include <QMainWindow>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent): QMainWindow{parent} {

	/* Initalize members */
	drawSender = new DrawSender{};
	
	centralWidget = new QGraphicsView{this};
	
	layout = new QHBoxLayout{centralWidget};
	
	colorDialog = new QColorDialog{centralWidget};
	/* Act as widget, not as a dialog */
    colorDialog->setWindowFlags(Qt::Widget);
    colorDialog->setOptions(
		  QColorDialog::DontUseNativeDialog
		| QColorDialog::NoButtons
    );
	layout->addWidget(colorDialog);
	
	gridDrawer = new GridDrawer{centralWidget, drawSender->getSourceConfiguration().width, drawSender->getSourceConfiguration().height, 20};
	layout->addWidget(gridDrawer);

	/* Setting layout */
	centralWidget->setLayout(layout);
	setCentralWidget(centralWidget);
	setGeometry(250, 250, layout->sizeHint().width(), layout->sizeHint().height());

	/* View -> Controller signals */
    connect(colorDialog, &QColorDialog::currentColorChanged, drawSender, &DrawSender::setColor);
	connect(gridDrawer, &GridDrawer::clickEvent, drawSender, &DrawSender::changeCell);
	
	/* Controller -> View signals */
	qRegisterMetaType<Frame>("Frame");
	connect(drawSender, &DrawSender::frameChanged, gridDrawer, &GridDrawer::setFrame);
}

MainWindow::~MainWindow(){

}
