#include "file_gatherer.h"


FileGatherer::FileGatherer(const std::string& path_name)
    : mPath(path_name)
{}

FileGatherer::~FileGatherer(){}

std::vector<std::string> FileGatherer::listFiles(const std::string& extension_filter,  bool recursive)
{
    std::vector<std::string> paths;
    std::vector<std::filesystem::directory_entry> files = gatherFiles(extension_filter, recursive);

    if(!files.empty())
    {
        for(auto& entry : files)
        {   
            if(entry.is_symlink())
            {
                paths.emplace_back(std::filesystem::read_symlink(entry.path()));
            }
            else
            {
                paths.emplace_back(entry.path().string());
            }
        }
    }

    return paths;
}

size_t FileGatherer::totalFileSize(const std::string& extension_filter, bool recursive)
{
    size_t totalSize = 0;
    std::vector<std::filesystem::directory_entry> files = gatherFiles(extension_filter, recursive);

    if(!files.empty())
    {
        for(auto& entry : files)
        {
            totalSize += entry.file_size();
        }
    }

    return totalSize;
}

std::vector<std::filesystem::directory_entry> FileGatherer::gatherFiles(const std::string& extension_filter, bool recursive)
{
    std::vector<std::filesystem::directory_entry> files;

    if(std::filesystem::exists(mPath))
    {
        if(recursive)
        {
            for (auto const& dir_entry : recursive_dir_iterator(mPath))
            {
                parse_entry(files, extension_filter, dir_entry);
            }    
        }
        else
        {
            for (auto const& dir_entry : dir_iterator(mPath))
            {
                parse_entry(files, extension_filter, dir_entry);
            }    
        }
    }

    return files;
}

void FileGatherer::parse_entry( std::vector<std::filesystem::directory_entry>& files
                              , const std::string& extension_filter
                              , const std::filesystem::directory_entry& entry)
{
    const std::string& extension = entry.path().extension();

    if(!entry.is_directory())
    {   
        if(extension_filter.empty())
        {
            files.emplace_back(entry);
        }
        else
        {
            if(extension.find(extension_filter) != std::string::npos)
            {
                files.emplace_back(entry);
            }
        }
    }
}