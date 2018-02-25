#include "FileOutputStream.h"
#include <cstring>

#define CHUNK 16384

namespace gz
{

	FileOutputStream::FileOutputStream()
	: file(NULL)
	, openedFile(false)
	, opened(false)
	{
		//Empty
	}

	FileOutputStream::~FileOutputStream()
	{
		close();
	}

	bool FileOutputStream::open(std::string filename, uint8_t level)
	{
		if (this->file || this->opened)
			return (false);
		std::memset(&this->stream, 0, sizeof(this->stream));
		if (deflateInit(&this->stream, level) != Z_OK)
			return (false);
		if (!(this->file = std::fopen(filename.c_str(), "wb")))
		{
			deflateEnd(&this->stream);
			return (false);
		}
		this->opened = true;
		this->openedFile = true;
		return (true);
	}

	bool FileOutputStream::open(FILE *file, uint8_t level)
	{
		if (this->file || this->opened)
			return (false);
		std::memset(&this->stream, 0, sizeof(this->stream));
		if (deflateInit(&this->stream, level) != Z_OK)
			return (false);
		this->file = file;
		this->opened = true;
		return (true);
	}

	void FileOutputStream::close()
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
				if ((tmp = std::fwrite(this->buffer, 1, this->bufferLen, this->file)) != this->bufferLen)
					break;
				if (ret == Z_FINISH)
					break;
			} while (1);
			deflateEnd(&this->stream);
			this->opened = false;
		}
		if (this->openedFile && this->file)
		{
			std::fclose(this->file);
			this->file = NULL;
		}
	}

	ssize_t FileOutputStream::writeBytes(const void *data, size_t len)
	{
		if (!this->opened || !this->file)
			return (-1);
		return (std::fwrite(data, 1, len, this->file));
	}

}
