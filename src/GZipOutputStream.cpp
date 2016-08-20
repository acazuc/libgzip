#include "GZipOutputStream.h"
#include <cstring>

#define CHUNK 16384

namespace libgzip
{

	GZipOutputStream::GZipOutputStream()
	{
		this->buffer = new unsigned char[CHUNK];
		this->bufferOff = 0;
		this->bufferLen = 0;
		this->file = NULL;
		this->opened = false;
	}

	GZipOutputStream::~GZipOutputStream()
	{
		if (this->buffer)
			delete[] this->buffer;
		close();
	}

	bool GZipOutputStream::open(std::string filename)
	{
		if (this->file || this->opened)
			return (false);
		memset(&this->stream, 0, sizeof(this->stream));
		if (deflateInit2(&this->stream, 1, Z_DEFLATED, 16 | 15, 8, Z_DEFAULT_STRATEGY) != Z_OK)
			return (false);
		if (!(this->file = fopen(filename.c_str(), "wb")))
			return (false);
		this->opened = true;
		return (true);
	}

	void GZipOutputStream::close()
	{
		if (this->opened)
		{
			int ret;
			ssize_t tmp;
			do
			{
				this->stream.avail_in = 0;
				this->stream.next_in = (Bytef*)0;
				this->stream.avail_out = CHUNK;
				this->stream.next_out = this->buffer;
				if ((ret = deflate(&this->stream, Z_FULL_FLUSH)) != Z_OK && ret != Z_FINISH)
					break;
				this->bufferLen = CHUNK - this->stream.avail_out;
				if ((tmp = fwrite(this->buffer, 1, this->bufferLen, this->file)) != this->bufferLen)
					break;
				if (ret == Z_FINISH)
					break;
			} while (1);
			deflateEnd(&this->stream);
			this->opened = false;
		}
		if (this->file)
		{
			fclose(this->file);
			this->file = NULL;
		}
	}

	ssize_t GZipOutputStream::write(void *data, ssize_t len)
	{
		ssize_t written;
		ssize_t tmp;
		int ret;

		if (!this->opened || !this->file)
			return (-1);
		written = 0;
		do {
			this->stream.avail_in = len - written;
			this->stream.next_in = (Bytef*)data + written;
			this->stream.avail_out = CHUNK;
			this->stream.next_out = this->buffer;
			if ((ret = deflate(&this->stream, Z_NO_FLUSH)) != Z_OK && ret != Z_FINISH)
			{
				written = -1;
				break;
			}
			this->bufferLen = CHUNK - this->stream.avail_out;
			if ((tmp = fwrite(this->buffer, 1, this->bufferLen, this->file)) != this->bufferLen)
			{
				written = -1;
				break;
			}
			written += len - written - this->stream.avail_in;
		} while (written != len);
		return (written);
	}

	bool GZipOutputStream::writeInt8(int8_t val)
	{
		return (write(&val, 1) == 1);
	}

	bool GZipOutputStream::writeUInt8(uint8_t val)
	{
		return (write(&val, 1) == 1);
	}

	bool GZipOutputStream::writeInt16(int16_t val)
	{
		return (write(&val, 2) == 2);
	}

	bool GZipOutputStream::writeUInt16(uint16_t val)
	{
		return (write(&val, 2) == 2);
	}

	bool GZipOutputStream::writeInt32(int32_t val)
	{
		return (write(&val, 4) == 4);
	}

	bool GZipOutputStream::writeUInt32(uint32_t val)
	{
		return (write(&val, 4) == 4);
	}

	bool GZipOutputStream::writeInt64(int64_t val)
	{
		return (write(&val, 8) == 8);
	}

	bool GZipOutputStream::writeUInt64(uint64_t val)
	{
		return (write(&val, 8) == 8);
	}

}
