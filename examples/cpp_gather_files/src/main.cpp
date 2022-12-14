#include <cstdio>
#include <filesystem>
#include <vector>
#include <string>
#include "file_gatherer.h"
#include "argparse.h"

void parse_entry( std::vector<std::filesystem::directory_entry>& files
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
            if(extension == extension_filter)
            {
                files.emplace_back();
            }
        }

    }
}

std::vector<std::filesystem::directory_entry> gather_files(std::filesystem::path path, std::string extension_filter="", bool recursive = false)
{
    using recursive_dir_iterator = std::filesystem::recursive_directory_iterator;
    using dir_iterator = std::filesystem::directory_iterator;

    std::vector<std::filesystem::directory_entry> files;

    if(std::filesystem::exists(path))
    {   
        if(recursive)
        {
            for (auto const& dir_entry : recursive_dir_iterator(path))
            {
                parse_entry(files, extension_filter, dir_entry);
            }
        }
        else
        {
            for (auto const& dir_entry : dir_iterator(path))
            {
                parse_entry(files, extension_filter, dir_entry);
            }
        }
    }

    return files;
}


int main(int argc, char** argv)
{

    ArgParse parser(argc, argv);

    if(parser.count() == 0 || parser.hasFlag("-h", "--help"))
    {
        printf("Usage: %s [OPTIONS] <DIRPATH>\n", parser.getName().c_str());
        printf("Options:\n");
        printf("    -r, --recursive - Lists files recursively\n");
        printf("    -f, --filter <file_extension> - Filters files by the given file extension, example: -f \"cpp\" - should list all *.cpp files\n");
        printf("    -s, --size - Prints out the total size of the filtered files\n");
        printf("    -n, --new_line - Print file entries on a new line\n");
        return 0;
    }

    // Args
    bool recursive = parser.hasFlag("-r", "--recursive");
    bool print_size = parser.hasFlag("-s", "--size");
    bool new_line = parser.hasFlag("-n", "--new_line");
    std::string extension_filter = parser.getStr("-f", "--filter");

    std::string path(argv[argc-1]);

    FileGatherer gatherer(path);
    std::vector<std::string> files = gatherer.listFiles(extension_filter, recursive);

    if(print_size)
    {
        printf("Total file size: %li\n", gatherer.totalFileSize(extension_filter, recursive));
    }

    printf("Found files:\n");
    for(const auto& path : files)
    {
        printf("%s", path.c_str());
        if(new_line)
        {
            printf("\n");
        }
        else
        {
            printf(" ");
        }
        

    }
    if(!new_line)
    {
        printf("\n");
    }

    return 0;
}