#ifndef RPC_H_INCLUDED
#define RPC_H_INCLUDED

#include <exception>
#include "matrix.h"

class PipeException: public std::exception
{
	private:
		std::string what_;
	public:
		PipeException(std::string what);
		const char* what() const noexcept override;
};

SourceConfiguration getConfiguration(std::string name);
void sendFrame(Frame, Frame);

#endif
