#include "MemoryInputStream.h"
#include <cstring>

namespace gz
{

	MemoryInputStream::MemoryInputStream(void *data, size_t len)
	: len(len)
	, pos(0)
	, data(data)
	{
		//Empty
	}

	MemoryInputStream::~MemoryInputStream()
	{
		//Empty
	}

	ssize_t MemoryInputStream::readBytes(void *data, size_t len)
	{
		ssize_t readed = std::min(this->len - this->pos, len);
		std::memmove(data, (uint8_t*)this->data + this->pos, readed);
		return (readed);
	}

	bool MemoryInputStream::eof()
	{
		return (this->pos == this->len);
	}

}
