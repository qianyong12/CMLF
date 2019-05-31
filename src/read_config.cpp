

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "define.h"

#include "LocalTime.h"

class ReadConfig
{
public:
    ReadConfig();
    ~ReadConfig();
    std::vector<int> layer_node;
    std::vector<int> layer_mode;
    bool readFile(std::string filename);

private:
    std::vector<std::string> split(const std::string &str, const char charac);
    void set_mode(std::string mode);
    void set_node(std::string node);
};

ReadConfig::ReadConfig()
{
    ;
}

ReadConfig::~ReadConfig()
{
    ;
}

std::vector<std::string> ReadConfig::split(const std::string &str, const char charac)
{
    std::vector<std::string> vec;
    std::string tmpStr;
    for (auto c : str)
    {
        if (c == charac)
        {
            if (!tmpStr.empty())
            {
                vec.push_back(tmpStr);
                tmpStr.clear();
            }
        }
        else
        {
            tmpStr += c;
        }
    }
    if (!tmpStr.empty())
    {
        vec.push_back(tmpStr);
    }
    return vec;
}

bool ReadConfig::readFile(std::string filename)
{
    std::fstream file;

    file.open(filename);
    if (!file.is_open())
    {
        getTime();
        std::cout << "Cannot open the file! Please check the path!" << std::endl;
        return false;
    }
    else
    {
        getTime();
        std::cout << "Loading the network configuration ..." << std::endl;
        std::vector<std::string> cut;
        while (!file.eof())
        {
            std::string buffer;
            getline(file, buffer);

            cut = split(buffer, ' ');
            // std::cout << cut[0] << std::endl;
            set_mode(cut[0]);
            set_node(cut[1]);
        }
        int num;
        std::istringstream(cut[2]) >> num;
        layer_node.push_back(num);
        file.close();
        getTime();
        std::cout << "Config loading finished" << std::endl;
        return true;
    }
}

void ReadConfig::set_mode(std::string mode)
{
    if (mode.find("MLP") != -1)
        layer_mode.push_back(MLP);
    else if (mode.find("SIGMOID") != -1)
        layer_mode.push_back(SIGMOID);
    else if (mode.find("RELU") != -1)
        layer_mode.push_back(RELU);
    else
        ;
}

void ReadConfig::set_node(std::string node)
{
    int num;
    std::istringstream(node) >> num;
    layer_node.push_back(num);
}
