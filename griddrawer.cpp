#include "griddrawer.h"
#include <QPainter>
#include <QDebug>

#include "rgb.h"

GridDrawer::GridDrawer(QWidget* parent, int x, int y, int windowSize): QWidget{parent}, x_{x}, y_{y}, windowSize_{windowSize} {
	frame_.pixels = Array2D<RGB>{x_, y_};
	for (int x = 0; x < frame_.pixels.getWidth(); x++) {
		for (int y = 0; y < frame_.pixels.getHeight(); y++) {
			frame_.pixels(x,y) = RGB{0, 0, 0};
		}
	}
	setMouseTracking(true);
}

QSize GridDrawer::minimumSizeHint() const {
    return QSize{x_*windowSize_, y_*windowSize_};
}

QSize GridDrawer::sizeHint() const {
    return QSize{x_*windowSize_, y_*windowSize_};
}

void GridDrawer::setFrame(Frame frame) {
	frame_ = frame;
	update();
}

void GridDrawer::paintEvent(QPaintEvent*) {
	QPainter painter{this};
	for (int x = 0; x < frame_.pixels.getWidth(); x++) {
		for (int y = 0; y < frame_.pixels.getHeight(); y++) {
			painter.setBrush(QBrush{QColor{frame_.pixels(x,y).r, frame_.pixels(x,y).g, frame_.pixels(x,y).b}});
			painter.drawRect(windowSize_*x, windowSize_*y, windowSize_, windowSize_);
		}
	}
}

QPoint GridDrawer::screenToGrid(const QPoint& p) {
	return QPoint{p.x() / windowSize_, p.y() / windowSize_};
}

void GridDrawer::mouseMoveEvent(QMouseEvent* event) {
	if (event->buttons() & Qt::LeftButton) {
		emit clickEvent(screenToGrid(event->pos()));
	}
}