#include "argparse.h"

ArgParse::ArgParse(int argc, char** argv)
    : mName(argv[0])
    , mArgs()
{
    mArgs.reserve(argc - 1);
    for (int i = 1; i < argc; ++i)
    {
        mArgs.emplace_back(argv[i]);
    }
}

ArgParse::~ArgParse()
{

}

bool ArgParse::hasFlag(const std::string& short_arg, const std::string& long_arg) const
{
    for (const auto& val : mArgs)
    {
        if ( (val == short_arg) || (val == long_arg) ) 
        { return true; }
    }
    return false;
}
//std::pair<bool, int64_t> getArg(const std::string& short_arg, const std::string& long_arg);
ArgParse::Argument<int64_t> ArgParse::getInt(const std::string& short_arg, const std::string& long_arg) const
{
    Argument<int64_t> retval;
    std::string value = findArgumentValue(short_arg, long_arg);
    if(!value.empty())
    {
        retval.value = std::strtoll(value.c_str(), nullptr, 10);
        retval.parseError = false;
    }

    return retval;
}
ArgParse::Argument<double> ArgParse::getDouble(const std::string& short_arg, const std::string& long_arg) const
{
    Argument<double> retval;
    std::string value = findArgumentValue(short_arg, long_arg);
    if(!value.empty())
    {
        retval.value = std::strtod(value.c_str(), nullptr);
        retval.parseError = false;
    }

    return retval;
}
std::string ArgParse::getStr(const std::string& short_arg, const std::string& long_arg) const
{
    return findArgumentValue(short_arg, long_arg);

}
std::string ArgParse::getName() const
{
    return mName;
}

std::string ArgParse::findArgumentValue(const std::string& short_arg, const std::string& long_arg) const
{   
    std::string value;
    size_t idx = mArgs.size();

    for(size_t i = 0; i < mArgs.size(); ++i)
    {   
        if ( (mArgs[i].find(short_arg) == 0) || (mArgs[i].find(long_arg) == 0) ) 
        { 
            idx = i;
            break; 
        }
    }

    if(idx < mArgs.size())
    {   
        const auto& arg = mArgs[idx];
        size_t pos = arg.find("=");

        if (pos != std::string::npos)
        {   
            value = arg.substr(pos+1);
        }
        else if((idx + 1) < mArgs.size())
        {
            value = mArgs[idx + 1];
        }
    }

    return value;
}

size_t ArgParse::count() const
{
    return mArgs.size();
}