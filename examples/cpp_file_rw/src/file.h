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

        /**
         * Constructor, if the file cannot be opened mLastError error is set
         * 
         * @param pathname File path to be opened
         * @param mode Specify file access mode: 
         * - "r" Can only read from the file and it must exist
         * - "w" Can only write into a file, if it does not exist an empty file is created, if it exists its contents are deleted!
         * - "a" Append to the end of a file, if it does not exist an empty file is created
         * - "r+" Can read and write the file and it must exist
         * - "w+" Can read and write the file, if it does not exist an empty file is created, if it exists its contents are deleted!
         * - "a+" Can read and write the file but all write operations write to the end of the file, if it does not exist an empty file is created
        **/
        File(const std::string& pathname, const std::string& mode = "r");
        ~File();
        
        /**
         *  Read bytes from the file
         * 
         * @param max_size How many bytes to read, if set to 0 read the entire file
         * @return std::vector<uint8_t> containing the read data, if there is an error returns an empty vector and mLastError is set
        **/
        std::vector<uint8_t> read(size_t max_size = 0);

        /**
         * Read a line from the file, if the file does not contain any '\n' than the entire file is read
         * 
         * @return Line string that was read, if there is an error returns an empty string and mLastError is set
        **/
        std::string readLine();

        /**
         * Seek to a specific position in the file from different positions, set mLastError if seek fails
         * 
         * @param offset Position where to seek
         * @param whence Specifies which position to seek from
         * - Whence::SeekBegin Seek from the beginning of the file
         * - Whence::SeekCurrent Seek from the current position in the file, default
         * - Whence::SeekBegin Seek from the end of the file
         * 
         * @return True if seek succeded
        **/
        bool seek(size_t offset, Whence whence = Whence::SeekCurrent);

        /**
         * Seek to a specific position in the file from the beginning, set mLastError if seek fails
         * 
         * @param offset Position where to seek
         * @return True if seek succeded
        **/
        inline bool seekFromBegin(size_t offset) { return seek(offset, Whence::SeekBegin); }

        /**
         * Seek to a specific position in the file from the end, set mLastError if seek fails
         * 
         * @param offset Position where to seek
         * @return True if seek succeded
        **/
        inline bool seekFromEnd(size_t offset) { return seek(offset, Whence::SeekEnd); }

        /**
         * Get the current file position, set mLastError if tell fails
         * 
         * @return The current file position if succeded, -1 if failed
        **/
        ssize_t tell();

        /**
         * Write bytes into the file, if the write fails mLastError is set
         * 
         * @param data The vector uint8_t data to write
         * @return The amount of bytes that were written into the file, if it does not equal with the size of the vector the write failed
        **/
        size_t write(const std::vector<uint8_t>& data);

        /**
         * Write string into the file, if the write fails mLastError is set
         * 
         * @param str The string to write
         * @return The amount of characters that were written into the file, if it does not equal with the size of the string the write failed
        **/
        size_t write(const std::string& str);

        /**
         * Write a specific amount of bytes into the file starting from a pointer, if the write fails mLastError is set
         * 
         * @param data Pointer to the start of the data
         * @param size How many bytes to write
         * @return The amount of bytes that were written into the file, if it does not equal with the given size the write failed
        **/
        size_t write(const uint8_t* data, size_t size);

        /**
         * Close the opened file
        **/
        void close();

        /**
         * Check that the current file position is at the end of the file
         * 
         * @return True if the current position is at the end of the file
        **/
        bool eof() const;

        /**
         * Returns a positive integer if an error occured during any file operations
         * 
         * @return 0 if no errors occured, otherwise returns a positive integer
        **/
        error_t error() const;

        /**
         * Check that the specified file has been opened
         * 
         * @return True if the file was opened
        **/
        bool isOpen() const noexcept { return (mFile != nullptr); }
        explicit operator bool() const noexcept { return isOpen(); }

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
