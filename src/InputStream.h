#ifndef GZ_INPUT_STREAM
# define GZ_INPUT_STREAM

# include <cstdint>
# include <cstdio>
# include <zlib.h>

namespace gz
{

	class InputStream
	{

	protected:
		uint32_t bufferOff;
		uint32_t bufferLen;
		uint8_t *buffer;
		z_stream stream;
		virtual ssize_t readBytes(void *data, size_t len) {(void)data;(void)len;return (0);};

	public:
		InputStream();
		~InputStream();
		ssize_t read(void *data, size_t len);
		bool readInt8(int8_t *val);
		bool readUInt8(uint8_t *val);
		bool readInt16(int16_t *val);
		bool readUInt16(uint16_t *val);
		bool readInt32(int32_t *val);
		bool readUInt32(uint32_t *val);
		bool readInt64(int64_t *val);
		bool readUInt64(uint64_t *val);
		virtual bool eof() {return (true);};

	};

}

#endif
