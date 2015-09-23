#ifndef DRAW_SENDER_H_INCLUDED
#define DRAW_SENDER_H_INCLUDED

#include "timer.h"
#include "interface/frame.h"
#include "interface/sourceconfiguration.h"
#include "interface/sourceinterface.h"
#include "interface/daemonsourceinterface.h"
#include "stub/sourcedaemon.hpp"
#include "ipc-rpc/localsocket.h"
#include "ipc-rpc/pipeinterpreter.hpp"
#include "ipc-rpc/pipeinterpreterbase.hpp"
#include "core/color.h"
#include <string>
#include <mutex>
#include <memory>
#include <QObject>
#include <QColor>


class DrawSender: public QObject, public SourceInterface {
	Q_OBJECT
	private:
		std::unique_ptr<LocalSocket> socket_;
		std::unique_ptr<PipeInterpreter<DrawSender, DaemonSourceInterface>> pipe_;
		SourceConfiguration config_;
		int id_;
		QColor color_;
		Frame frame_;
		std::mutex m_;
		std::unique_ptr<Timer> timer_;
		void packetCallback();
	public:
		DrawSender(const std::string& socket_name);
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
