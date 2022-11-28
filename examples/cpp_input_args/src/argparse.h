
#ifndef ARGPARSE_H
#define ARGPARSE_H

#include <string>
#include <cstdlib>
#include <vector>
#include <utility>
#include <stdint.h>

class ArgParse
{
public:
    template<class T>
    struct Argument
    {
        bool parseError;
        T value;

        Argument(bool parse_error = true, T _value = T())
            : parseError(parse_error)
            , value(_value)
        {}

        explicit operator bool () const noexcept
        {
            return !parseError;
        }
    };

    ArgParse(int argc, char** argv);
    ~ArgParse();
    bool hasFlag(const std::string& short_arg, const std::string& long_arg) const;
    //std::pair<bool, int64_t> getArg(const std::string& short_arg, const std::string& long_arg);
    Argument<int64_t> getInt(const std::string& short_arg, const std::string& long_arg) const;
    Argument<double> getDouble(const std::string& short_arg, const std::string& long_arg) const;
    std::string getStr(const std::string& short_arg, const std::string& long_arg) const;
    std::string getName() const;
    size_t count() const;

private:
    std::string findArgumentValue(const std::string& short_arg, const std::string& long_arg) const;

    std::string mName;
    std::vector<std::string> mArgs;

};

#endif