
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

        bool hasValue() const noexcept { return !parseError; }
        explicit operator bool () const noexcept { return hasValue(); }
    };

    /**
     * Constructor
     * 
     * @param argc Argument count, size of argv
     * @param argv Pointer to arguments array
    **/
    ArgParse(int argc, char** argv);
    ~ArgParse();

    /**
     * Tells if the given short_arg or long_arg can be found among the arguments
     * 
     * @param short_arg Short version of the argument, example: -f
     * @param short_arg Long version of the argument, example: --flag
     * @return True is returned if such an argument is present
    **/
    bool hasFlag(const std::string& short_arg, const std::string& long_arg) const;
    //std::pair<bool, int64_t> getArg(const std::string& short_arg, const std::string& long_arg);

    /**
     * Get an integer from given short_arg or long_arg argument
     * 
     * @param short_arg Short version of the argument, example: -t
     * @param short_arg Long version of the argument, example: --tries
     * @return Argument struct which evaluates to true if the given argument is present and has a value
    **/
    Argument<int64_t> getInt(const std::string& short_arg, const std::string& long_arg) const;

    /**
     * Get an double from given short_arg or long_arg argument
     * 
     * @param short_arg Short version of the argument, example: -p
     * @param short_arg Long version of the argument, example: --percent
     * @return Argument struct which evaluates to true if the given argument is present and has a value
    **/
    Argument<double> getDouble(const std::string& short_arg, const std::string& long_arg) const;

    /**
     * Get a string from given short_arg or long_arg argument
     * 
     * @param short_arg Short version of the argument, example: -n
     * @param short_arg Long version of the argument, example: --name
     * @return String if the given argument is present and has a value, otherwise empty string is returned
    **/
    std::string getStr(const std::string& short_arg, const std::string& long_arg) const;

    /**
     * Get the given name of the program
    **/
    std::string getName() const;

    /**
     * Get the amount of arguments passed to the program
    **/
    size_t count() const;

private:
    std::string findArgumentValue(const std::string& short_arg, const std::string& long_arg) const;

    std::string mName;
    std::vector<std::string> mArgs;

};

#endif