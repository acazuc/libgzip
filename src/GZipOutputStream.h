#ifndef LIBGZIP_OUTPUT_STREAM_H
# define LIBGZIP_OUTPUT_STREAM_H

# include <cstdint>
# include <cstdio>
# include <string>
# include <zlib.h>

namespace libgzip
{

	class GZipOutputStream
	{

	private:
		uint32_t bufferOff;
		uint32_t bufferLen;
		uint8_t *buffer;
		bool openedFile;
		bool opened;
		z_stream stream;
		FILE *file;

	public:
		GZipOutputStream();
		~GZipOutputStream();
		bool open(std::string filename);
		bool open(FILE *file);
		void close();
		ssize_t write(const void *data, ssize_t len);
		bool writeInt8(int8_t val);
		bool writeUInt8(uint8_t val);
		bool writeInt16(int16_t val);
		bool writeUInt16(uint16_t val);
		bool writeInt32(int32_t val);
		bool writeUInt32(uint32_t val);
		bool writeInt64(int64_t val);
		bool writeUInt64(uint64_t val);

	};

}

#endif
