#include "drawsender.h"
#include "core/array2D.hpp"
#include <thread>
#include <cmath>
#include <QPoint>
#include <QDebug>

DrawSender::DrawSender(const std::string& socket_name): id_{0}, color_{QColor{0,0,0}} {
	socket_ = std::unique_ptr<LocalSocket>{LocalSocket::create()};
	socket_->connectToServer(socket_name.c_str(), 1000);
	socket_->readTimeout(1000);
	socket_->writeTimeout(1000);
	pipe_ = std::unique_ptr<PipeInterpreter<DrawSender, DaemonSourceInterface>>{new PipeInterpreter<DrawSender, DaemonSourceInterface>{this, socket_.release()}};
	config_ = pipe_->getSourceConfiguration("Draw source");
	frame_.pixels = Array2D<Color>{config_.width, config_.height};
	for (int x = 0; x < config_.width; x++) {
		for (int y = 0; y < config_.height; y++) {
			frame_.pixels(x,y) = Color{0,0,0};
		}
	}
	timer_ = std::unique_ptr<Timer>{new Timer(std::bind(&DrawSender::packetCallback, this), std::chrono::milliseconds((int) ceil(2000.0 / config_.framerate)))};
	timer_->start();
}

DrawSender::~DrawSender() {
	timer_->stop();
	pipe_->disconnect();
}

const SourceConfiguration& DrawSender::getSourceConfiguration() const {
	return config_;
}

void DrawSender::setColor(const QColor& color) {
	m_.lock();
	color_= color;
	m_.unlock();
}

void DrawSender::changeCell(const QPoint& cell) {
	m_.lock();
	frame_.pixels(cell.x(), cell.y()) = Color{color_.red(), color_.green(), color_.blue()};
	m_.unlock();
	emit frameChanged(frame_);
}

void DrawSender::fillFrame() {
	m_.lock();
	Color rgb = Color{color_.red(), color_.green(), color_.blue()};
	for (int x = 0; x < config_.width; x++) {
		for (int y = 0; y < config_.height; y++) {
			frame_.pixels(x,y) = rgb;
		}
	}
	m_.unlock();
	emit frameChanged(frame_);
}

void DrawSender::packetCallback() {
	m_.lock();
	Frame frame = frame_;
	frame_.id = id_++;
	m_.unlock();
	pipe_->sendFrame(frame, frame);
}


