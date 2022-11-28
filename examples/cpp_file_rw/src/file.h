#include <vector>
#include <string>
#include <stdio.h>
#include <stdint.h>
#include <error.h>

namespace io
{
    class File
    {
    public:

        enum class Whence
        {
            SeekBegin = SEEK_SET,
            SeekCurrent = SEEK_CUR,
            SeekEnd = SEEK_END,
        };

        File(const std::string& pathname, const std::string& mode = "r");
        ~File();
        
        std::vector<uint8_t> read(size_t max_size = 0);
        std::string readLine();

        bool seek(size_t offset, Whence whence = Whence::SeekCurrent);
        inline bool seekFromBegin(size_t offset) { return seek(offset, Whence::SeekBegin); }
        inline bool seekFromEnd(size_t offset) { return seek(offset, Whence::SeekEnd); }
        ssize_t tell();

        size_t write(const std::vector<uint8_t>& data);
        size_t write(const std::string& str);
        size_t write(const uint8_t* data, size_t size);

        void close();

        bool eof() const;
        error_t error() const;

        explicit operator bool() const noexcept { return (mFile && (error() == 0)); }

    private:

        struct LineCache
        {
            std::vector<uint8_t> buffer;
            size_t cursor;
            size_t readBytes;

            LineCache(size_t size) : buffer(size), cursor(0), readBytes(0)
            {
            }
        };

        size_t getFileSize();

        FILE * mFile;
        error_t mLastError;
        std::string mPathName;
        LineCache mCache;        
    };
}
