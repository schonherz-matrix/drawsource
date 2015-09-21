#include "drawsender.h"
#include <thread>
#include <cmath>
#include <QPoint>
#include <QDebug>

#include "rpc.h"
#include "matrix.h"
#include "array2D.hpp"

#include <iostream>

DrawSender::DrawSender(): id_{0}, color_{QColor{0,0,0}} {
	config_ = getConfiguration("Draw source");
	frame_.pixels = Array2D<RGB>{config_.width, config_.height};
	for (int x = 0; x < config_.width; x++) {
		for (int y = 0; y < config_.height; y++) {
			frame_.pixels(x,y) = RGB{0,0,0};
		}
	}
	timer_ = std::unique_ptr<Timer>{new Timer(std::bind(&DrawSender::packetCallback, this), std::chrono::milliseconds((int) ceil(2000.0 / config_.framerate)))};
	timer_->start();
}

DrawSender::~DrawSender() {
	timer_->stop();
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
	frame_.pixels(cell.x(), cell.y()) = RGB{color_.red(), color_.green(), color_.blue()};
	m_.unlock();
	emit frameChanged(frame_);
}

void DrawSender::fillFrame() {
	m_.lock();
	RGB rgb = RGB{color_.red(), color_.green(), color_.blue()};
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
	sendFrame(frame, frame);
}


