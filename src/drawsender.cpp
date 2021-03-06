#include "drawsender.h"

#include "ui_drawsender.h"

DrawSender::DrawSender(QWidget* parent)
    : QWidget(parent),
      transmitter_(libmueb::MuebTransmitter::Instance()),
      ui(new Ui::DrawSender) {
  m_frame = transmitter_.frame();
  setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint |
                 Qt::MSWindowsFixedSizeDialogHint);
  m_frame.fill(Qt::black);

  ui->setupUi(this);
  ui->grid->setFrame(&m_frame);
  ui->colorDialog->setWindowFlags(Qt::Widget);
  ui->colorDialog->setOptions(QColorDialog::DontUseNativeDialog |
                              QColorDialog::NoButtons);

  adjustSize();
  setFixedSize(size());

  connect(ui->colorDialog, &QColorDialog::currentColorChanged, this,
          &DrawSender::setColor);
  connect(ui->grid, &GridDrawer::clickEvent, this, &DrawSender::changeCell);
}

DrawSender::~DrawSender() { delete ui; }

void DrawSender::setColor(const QColor& color) { m_color = color; }

void DrawSender::changeCell(const QPoint& cell) {
  m_frame.setPixelColor(cell.x(), cell.y(), m_color);
  transmitter_.SendFrame(m_frame);

  ui->grid->update();
}

void DrawSender::fillFrame() {
  m_frame.fill(m_color);
  transmitter_.SendFrame(m_frame);
  ui->grid->update();
}
