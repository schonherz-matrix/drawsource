#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

//#include "array2D.h"
#include <vector>
#include <map>
#include "array2D.hpp"
#include "rgb.h"

struct DaemonConfiguration {
	unsigned short height; // pixel
	unsigned short width; // pixel
	unsigned short framerate; //
	int audio_latency; // micro sec, a videóhoz képest az audio időbeni eltolása
	unsigned char bit_depth; // a színmélység értéke (12 bit)
	std::map<int, std::string> sources; //
	int selected_source; // a kiválasztott forrás
};

struct SourceConfiguration {
	int id; // id
	std::string name; // alias
	unsigned short height; // pixel
	unsigned short width; // pixel
	unsigned short framerate; //
	int audio_latency; // micro sec, a videóhoz képest az audio időbeni eltolása
	unsigned char bit_depth; // a színmélység értéke (12 bit)
};

struct EmuConfiguration {
	unsigned short height; // pixel
	unsigned short width; // pixel
	unsigned short framerate; //
	int audio_latency; // micro sec, a videóhoz képest az audio időbeni eltolása
	unsigned char bit_depth; // a színmélység értéke (12 bit)
};

struct Frame { // A Daemon 2db Frame-et kap az RPC híváson keresztül
	int id;
	Array2D<RGB> pixels;
};

enum SourceEventType {
	SOURCE_EVENT_CONNECT = 1,
	SOURCE_EVENT_DISCONNECT
};

struct SourceEvent {
	int id;
	std::string name;
	enum SourceEventType type;
};

#endif
