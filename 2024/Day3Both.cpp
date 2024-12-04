#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <set>
#include <algorithm>
#include <fstream>
#include <string>
#include <queue>
#include <utility>
#include <utility>
#include <vector>
#include <iterator>
#include <regex>

int main() {
    std::ifstream fin("input.txt");

    std::vector<std::string> vec;
    std::regex combinedCmd(R"(do\(\)|don't\(\)|mul\((\d{1,3}),(\d{1,3})\))");
    unsigned int total = 0;
    bool mulAble = true;

    //populate vector
    std::string line;
    while (std::getline(fin, line))
        vec.push_back(line);

    //find matches
    std::smatch match;
    for(const auto & i : vec)
    {
        std::string subj = i;
        while(regex_search(subj, match, combinedCmd))
        {
            std::string substr = match.str(0);
            if(substr.find("don't()") != std::string::npos)
            {
                mulAble = false;
            }
            else if(substr.find("do()") != std::string::npos)
            {
                mulAble = true;
            }
            else if (substr.find("mul(") != std::string::npos)
            {
                if(mulAble)
                {
                    int leftInt = std::stoi(match.str(1));
                    int rightInt = std::stoi(match.str(2));
                    total += (leftInt * rightInt);
                }
            }
            subj = match.suffix().str();
        }
    }
    std::cout << total << std::endl;
}
