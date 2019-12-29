#ifndef GRID_DRAWER_H
#define GRID_DRAWER_H

#include <QBrush>
#include <QImage>
#include <QMouseEvent>
#include <QPen>
#include <QPixmap>
#include <QWidget>

class GridDrawer : public QWidget {
  Q_OBJECT

 public:
  explicit GridDrawer(QWidget* parent = nullptr);
  void setFrame(QImage* frame);

  // QWidget interface
  QSize sizeHint() const override;

 protected:
  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;

 signals:
  void clickEvent(const QPoint&);

 private:
  QImage* m_frame{nullptr};
  int m_windowSize = 20;

  QPoint screenToGrid(const QPoint&);
};

#endif
