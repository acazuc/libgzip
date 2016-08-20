#ifndef LIBGZIP_INPUT_STREAM
# define LIBGZIP_INPUT_STREAM

# include <cstdint>
# include <cstdio>
# include <string>
# include <zlib.h>

namespace libgzip
{

	class GZipInputStream
	{

	private:
		unsigned char *buffer;
		bool opened;
		int bufferOff;
		int bufferLen;
		z_stream stream;
		FILE *file;

	public:
		GZipInputStream();
		~GZipInputStream();
		bool open(std::string filename);
		void close();
		ssize_t read(void *data, size_t len);
		bool readInt8(int8_t *val);
		bool readUInt8(uint8_t *val);
		bool readInt16(int16_t *val);
		bool readUInt16(uint16_t *val);
		bool readInt32(int32_t *val);
		bool readUInt32(uint32_t *val);
		bool readInt64(int64_t *val);
		bool readUInt64(uint64_t *val);

	};

}

#endif
