#ifndef _COMMAND_ARGS_H
#define _COMMAND_ARGS_H

#include <string>
#include <set>
#include <map>
#include <vector>

class CommandArgs
{
    public:
        CommandArgs();
        CommandArgs(int argc, char *argv[]);
        void process(int argc, char *argv[]);

        // Testing if a flag or an option is present
        bool hasFlag(std::string flag);
        bool hasFlag(char flag);
        bool hasOption(std::string option);

        // Getting a n option
        std::string getOption(std::string name, std::string fallback="");
        int getOptionInt(std::string name, int fallback=0);
        double getOptionDouble(std::string name, double fallback=0);
        float getOptionFloat(std::string name, float fallback=0);
        
        // Getting parts
        std::vector<std::string> getParts();

    protected:
        std::set<std::string> flags;
        std::map<std::string, std::string> options;
        std::vector<std::string> parts;
};

#endif 
