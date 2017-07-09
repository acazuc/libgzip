#include "GZipInputStream.h"
#include <cstring>

#define CHUNK 16384

namespace libgzip
{

	GZipInputStream::GZipInputStream()
	: bufferOff(0)
	, bufferLen(0)
	, openedFile(false)
	, opened(false)
	, file(NULL)
	{
		this->buffer = new uint8_t[CHUNK];
	}

	GZipInputStream::~GZipInputStream()
	{
		if (this->buffer)
			delete[] (this->buffer);
		close();
	}

	bool GZipInputStream::open(std::string filename)
	{
		if (this->opened || this->file)
			return (false);
		std::memset(&this->stream, 0, sizeof(this->stream));
		if (inflateInit2(&this->stream, 16 + MAX_WBITS) != Z_OK)
			return (false);
		if (!(this->file = std::fopen(filename.c_str(), "rb")))
		{
			inflateEnd(&this->stream);
			return (false);
		}
		this->opened = true;
		this->openedFile = true;
		return (true);
	}

	bool GZipInputStream::open(FILE *file)
	{
		if (this->opened || this->file)
			return (false);
		std::memset(&this->stream, 0, sizeof(this->stream));
		if (inflateInit2(&this->stream, 16 + MAX_WBITS) != Z_OK)
			return (false);
		this->file = file;
		this->opened = true;
		this->openedFile = true;
		return (true);
	}

	void GZipInputStream::close()
	{
		if (this->openedFile && this->file)
		{
			std::fclose(this->file);
			this->openedFile = false;
			this->file = NULL;
		}
		if (this->opened)
		{
			inflateEnd(&this->stream);
			this->opened = false;
		}
	}

	ssize_t GZipInputStream::read(void *data, size_t len)
	{
		size_t written = 0;
		size_t readed = 0;
		int ret;

		if (!this->opened || !this->file)
			return (-1);
		do
		{
			if (this->bufferLen > 0 && this->bufferOff > 0)
			{
				std::memmove(this->buffer, this->buffer + this->bufferOff, this->bufferLen);
				this->bufferOff = 0;
			}
			readed = std::fread(this->buffer + this->bufferLen, 1, CHUNK - this->bufferLen, this->file);
			if (readed == (size_t)-1 && std::feof(this->file))
			{
				break;
			}
			this->bufferLen += readed;
			this->stream.avail_in = this->bufferLen;
			if (std::ferror(this->file))
			{
				written = -1;
				break;
			}
			if (this->stream.avail_in == 0)
				break;
			this->stream.next_in = this->buffer;
			this->stream.avail_out = len - written;
			this->stream.next_out = (Bytef*)data + written;
			if ((ret = inflate(&this->stream, Z_NO_FLUSH)) != Z_OK && ret != Z_FINISH)
			{
				written = -1;
				break;
			}
			this->bufferOff = this->bufferLen - this->stream.avail_in;
			written = len - this->stream.avail_out;
			this->bufferLen = this->stream.avail_in;
		} while (written < len);
		return (written);
	}

	bool GZipInputStream::readInt8(int8_t *val)
	{
		return (read(val, 1) == 1);
	}

	bool GZipInputStream::readUInt8(uint8_t *val)
	{
		return (read(val, 1) == 1);
	}

	bool GZipInputStream::readInt16(int16_t *val)
	{
		return (read(val, 2) == 2);
	}

	bool GZipInputStream::readUInt16(uint16_t *val)
	{
		return (read(val, 2) == 2);
	}

	bool GZipInputStream::readInt32(int32_t *val)
	{
		return (read(val, 4) == 4);
	}

	bool GZipInputStream::readUInt32(uint32_t *val)
	{
		return (read(val, 4) == 4);
	}

	bool GZipInputStream::readInt64(int64_t *val)
	{
		return (read(val, 8) == 8);
	}

	bool GZipInputStream::readUInt64(uint64_t *val)
	{
		return (read(val, 8) == 8);
	}

}
