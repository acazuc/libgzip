#include "MemoryOutputStream.h"
#include <cstring>

#define CHUNK 16384

namespace gz
{

	MemoryOutputStream::MemoryOutputStream()
	{
		std::memset(&this->stream, 0, sizeof(this->stream));
		if (deflateInit2(&this->stream, 1, Z_DEFLATED, 16 | 15, 9, Z_DEFAULT_STRATEGY) != Z_OK)
			throw std::exception();
	}

	MemoryOutputStream::~MemoryOutputStream()
	{
		deflateEnd(&this->stream);
	}

	ssize_t MemoryOutputStream::writeBytes(const void *data, size_t len)
	{
		this->data.resize(this->data.size() + len);
		std::memmove(this->data.data() + this->data.size() - len, data, len);
		return (len);
	}

}
