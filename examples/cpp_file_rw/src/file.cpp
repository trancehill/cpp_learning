#include "file.h"
#include <string_view>
#include <fcntl.h>
#include <cstring>
#include <sys/stat.h>

namespace io
{

File::File(const std::string& pathname, const std::string& mode)
    : mFile(nullptr)
    , mLastError(0)
    , mPathName(pathname)
    , mCache(4*1024)
{
    mFile = fopen(pathname.c_str(), mode.c_str());
    if(!mFile)
    {
        mLastError = errno;
    }
}

File::~File()
{
    close();
}

std::vector<uint8_t> File::read(size_t max_size)
{
    std::vector<uint8_t> result;

    if(mFile)
    {
        result.resize( (max_size == 0) ? getFileSize() : max_size );
        if(result.size() > 0)
        {
            size_t read_bytes = fread(result.data(), 1, result.size(), mFile);
            if(read_bytes > 0)
            {
                result.resize(read_bytes);
            }
            else
            {
                mLastError = errno;
                result.resize(0);
            }
        }
    }

    return result;
}

std::string File::readLine()
{
    bool foundLine = false;
    std::string result;

    if(mFile)
    {
        while(!foundLine)
        {
            if(mCache.readBytes == 0)
            {
                mCache.readBytes = fread(mCache.buffer.data(), 1, mCache.buffer.size(), mFile);
                if(mCache.readBytes == 0)
                {
                    mLastError = errno;
                    break;
                }
            }

            std::string_view sv(reinterpret_cast<char*>(mCache.buffer.data() + mCache.cursor), mCache.readBytes);

            size_t pos = sv.find('\n'); // THIS IS FUCKED
            if(pos != std::string_view::npos)
            {
                result += std::string(sv.substr(mCache.cursor, pos));
                mCache.cursor = pos+1;
                mCache.readBytes -= pos;
                foundLine = true;
            }
            else
            {
                result += std::string(reinterpret_cast<char*>(mCache.buffer.data() + mCache.cursor), mCache.readBytes);
                mCache.readBytes = 0;
                mCache.cursor = 0;
            }
        }
    }
    return result;
}

bool File::seek(size_t offset, File::Whence whence)
{
    bool result = false;

    if(mFile)
    {   
        if(fseek(mFile, offset, (int)whence) > 0)
        {
            mLastError = errno;
        }
        else
        {
            result = true;
        }
    }
    return result;
}

ssize_t File::tell()
{   
    ssize_t result = -1;
    if(mFile)
    {
        result = ftell(mFile);
        if(result == -1)
        {
            mLastError = errno;
        }
    }
    return result;
}

size_t File::write(const std::vector<uint8_t>& data)
{   
    size_t result = 0;
    if(mFile && !data.empty())
    {   
        result = fwrite(data.data(), 1, data.size(), mFile);
        if(result != data.size())
        {
            mLastError = errno;
        }
    }
    return result;
}

size_t File::write(const std::string& str)
{
    size_t result = 0;
    if(mFile && !str.empty())
    {  
        result = fwrite(str.c_str(), 1, str.size(), mFile);
        if(result != str.size())
        {
            mLastError = errno;
        }
    }
    return result;
}

size_t File::write(const uint8_t* data, size_t size)
{   
    size_t result = 0;
    if(mFile && (size > 0))
    {
        result = fwrite(data, 1, size, mFile);
        if(result != size)
        {
            mLastError = errno;
        }
    }
    return result;
}
void File::close()
{   
    if(mFile)
    {
        fclose(mFile);
        mFile = nullptr;
    }
}

bool File::eof() const
{
    if(mFile)
    {
        return feof(mFile);
    }
    return false;
}

error_t File::error() const
{
    return mLastError;
}

size_t File::getFileSize()
{
    struct stat st;
    if(stat(mPathName.c_str(), &st) == 0)
    {
        return st.st_size;
    }
    return 0;
}

}
