#ifndef DRAW_SENDER_H
#define DRAW_SENDER_H

#include <QWidget>

#include "muebtransmitter.h"

namespace Ui {
class DrawSender;
}

class DrawSender : public QWidget {
  Q_OBJECT

 public:
  explicit DrawSender(QWidget* parent = nullptr);
  ~DrawSender();

 public slots:
  void setColor(const QColor& color);
  void changeCell(const QPoint& cell);
  void fillFrame();

 private:
  QImage m_frame{libmueb::defaults::frame};
  QColor m_color{Qt::black};
  MuebTransmitter& m_transmitter;
  Ui::DrawSender* ui{nullptr};
};

#endif
