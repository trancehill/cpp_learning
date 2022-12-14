#include <vector>
#include <string>
#include <filesystem>

class FileGatherer
{
using recursive_dir_iterator = std::filesystem::recursive_directory_iterator;
using dir_iterator = std::filesystem::directory_iterator;

public:

    /**
     * Constructor
     * 
     * @param path_name Directory to list files from
    **/
    FileGatherer(const std::string& path_name);
    ~FileGatherer();

    /**
     * List all the files in the directory, can be recursive and can be filtered by extension
     * 
     * @param extension_filter Filter files by extension for example: .cpp, cpp
     * @param recursive If set list files from subdirectories
    **/
    std::vector<std::string> listFiles(const std::string& extension_filter="", bool recursive = false);

    /***
     * Count the total size of all the files in the directory, can be recursive and can be filtered by extension
     * 
     * @param extension_filter Filter counted files by extension for example: .cpp, cpp
     * @param recursive If set count file sizes from subdirectories
    **/
    size_t totalFileSize(const std::string& extension_filter="", bool recursive = false);
    
private:
    std::vector<std::filesystem::directory_entry> gatherFiles(const std::string& extension_filter="", bool recursive = false);
    std::filesystem::path mPath;

    void parse_entry(std::vector<std::filesystem::directory_entry>& files
                    , const std::string& extension_filter
                    , const std::filesystem::directory_entry& entry);
};



