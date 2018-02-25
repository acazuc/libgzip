#include "MemoryOutputStream.h"
#include <cstring>

#define CHUNK 16384

namespace gz
{

	MemoryOutputStream::MemoryOutputStream()
	{
		//Empty
	}

	MemoryOutputStream::~MemoryOutputStream()
	{
		//Empty
	}

	ssize_t MemoryOutputStream::writeBytes(const void *data, ssize_t len)
	{
		this->data.resize(this->data.size() + len);
		std::memmove(this->data.data() + this->data.size(), data, len);
		return (len);
	}

}
