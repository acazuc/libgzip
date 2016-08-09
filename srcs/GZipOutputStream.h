#ifndef GZIP_OUTPUT_STREAM_H
# define GZIP_OUTPUT_STREAM_H

# include <cstdint>
# include <cstdio>
# include "zlib.h"

namespace sl_client
{

	class GZipOutputStream
	{

	private:
		unsigned char *buffer;
		bool opened;
		int bufferOff;
		int bufferLen;
		z_stream stream;
		FILE *file;

	public:
		GZipOutputStream();
		~GZipOutputStream();
		bool open(char *file);
		void close();
		ssize_t write(void *data, ssize_t len);
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
