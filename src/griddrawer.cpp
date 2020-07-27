#include "griddrawer.h"

#include <QPainter>

#include "libmueb_global.h"

GridDrawer::GridDrawer(QWidget* parent) : QWidget{parent} {
  setMouseTracking(true);

  setFixedSize(libmueb::defaults::width * m_windowSize + 1,
               libmueb::defaults::height * m_windowSize + 1);
}

QSize GridDrawer::sizeHint() const { return size(); }

void GridDrawer::setFrame(QImage* frame) {
  m_frame = frame;
  update();
}

void GridDrawer::paintEvent(QPaintEvent*) {
  QPainter painter{this};

  if (m_frame) {
    painter.setPen(QPen(Qt::lightGray, 0));

    for (int y = 0; y < m_frame->height(); y++) {
      for (int x = 0; x < m_frame->width(); x++) {
        painter.setBrush(m_frame->pixelColor(x, y));
        painter.drawRect(m_windowSize * x, m_windowSize * y, m_windowSize,
                         m_windowSize);
      }
    }
  }
}

QPoint GridDrawer::screenToGrid(const QPoint& p) {
  return QPoint{p.x() / m_windowSize, p.y() / m_windowSize};
}

void GridDrawer::mousePressEvent(QMouseEvent* event) {
  QWidget::mousePressEvent(event);
  auto pos = event->pos();

  if (event->buttons() & Qt::LeftButton && rect().contains(pos, true)) {
    emit clickEvent(screenToGrid(pos));
  }
}

void GridDrawer::mouseMoveEvent(QMouseEvent* event) {
  QWidget::mouseMoveEvent(event);
  mousePressEvent(event);
}
