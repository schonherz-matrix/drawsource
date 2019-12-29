#ifndef DRAW_SENDER_H
#define DRAW_SENDER_H

#include <QWidget>
#include <memory>
#include "muebtransmitter.h"

namespace Ui {
class DrawSender;
}

class DrawSender : public QWidget {
  Q_OBJECT

 public:
  explicit DrawSender(QWidget* parent = nullptr,
                      std::shared_ptr<MuebTransmitter> transmitter = nullptr);

 public slots:
  void setColor(const QColor& color);
  void changeCell(const QPoint& cell);
  void fillFrame();

 private:
  QImage m_frame{libmueb::defaults::frame};
  QColor m_color{Qt::black};
  std::shared_ptr<MuebTransmitter> m_transmitter{nullptr};
  Ui::DrawSender* ui{nullptr};
};

#endif
