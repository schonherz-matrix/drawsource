#ifndef DRAW_SENDER_H_INCLUDED
#define DRAW_SENDER_H_INCLUDED

#include "timer.h"
#include <mutex>
#include <memory>
#include <QObject>
#include <QColor>

#include "rpc.h"
#include "matrix.h"

class DrawSender: public QObject {
	Q_OBJECT
	private:
		SourceConfiguration config_;
		int id_;
		QColor color_;
		Frame frame_;
		std::mutex m_;
		std::unique_ptr<Timer> timer_;
		void packetCallback();
	public:
		DrawSender();
		virtual ~DrawSender();
		const SourceConfiguration& getSourceConfiguration() const;
	public slots:
		void setColor(const QColor& color);
		void changeCell(const QPoint& cell);
		void fillFrame();
	signals:
		void frameChanged(Frame frame);
};

#endif
