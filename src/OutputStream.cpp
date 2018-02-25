#include "OutputStream.h"
#include <cstring>

#define CHUNK 16384

namespace gz
{

	OutputStream::OutputStream()
	: bufferOff(0)
	, bufferLen(0)
	{
		this->buffer = new uint8_t[CHUNK];
	}

	OutputStream::~OutputStream()
	{
		delete[] (this->buffer);
	}

	ssize_t OutputStream::write(const void *data, size_t len)
	{
		ssize_t written = 0;
		do
		{
			this->stream.avail_in = len - written;
			this->stream.next_in = (Bytef*)data + written;
			this->stream.avail_out = CHUNK;
			this->stream.next_out = this->buffer;
			int ret = deflate(&this->stream, Z_NO_FLUSH);
			if (ret != Z_OK && ret != Z_FINISH)
			{
				written = -1;
				break;
			}
			this->bufferLen = CHUNK - this->stream.avail_out;
			ssize_t tmp = writeBytes(this->buffer, this->bufferLen);
			if (tmp != this->bufferLen)
			{
				written = -1;
				break;
			}
			written += len - written - this->stream.avail_in;
		} while (written != len);
		return (written);
	}

	bool OutputStream::writeInt8(int8_t val)
	{
		return (write(&val, 1) == 1);
	}

	bool OutputStream::writeUInt8(uint8_t val)
	{
		return (write(&val, 1) == 1);
	}

	bool OutputStream::writeInt16(int16_t val)
	{
		return (write(&val, 2) == 2);
	}

	bool OutputStream::writeUInt16(uint16_t val)
	{
		return (write(&val, 2) == 2);
	}

	bool OutputStream::writeInt32(int32_t val)
	{
		return (write(&val, 4) == 4);
	}

	bool OutputStream::writeUInt32(uint32_t val)
	{
		return (write(&val, 4) == 4);
	}

	bool OutputStream::writeInt64(int64_t val)
	{
		return (write(&val, 8) == 8);
	}

	bool OutputStream::writeUInt64(uint64_t val)
	{
		return (write(&val, 8) == 8);
	}

}
