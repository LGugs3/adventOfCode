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

const std::regex target("(XMAS|SAMX)");
std::smatch match;
unsigned int numMatches = 0;

int main() {
    std::ifstream fin("input.txt");
    if(!fin.is_open())
        std::cerr << "Error opening file" << std::endl;

    //fill matrix for horizontal matches
    std::vector<std::vector<char>> hMatrix;
    std::string line;
    while (std::getline(fin, line))
    {
        auto& ref = hMatrix.emplace_back();
        for(auto ch : line)
            ref.push_back(ch);
    }
    fin.close();

    //horizontal matches
    match = std::smatch{};
    for(const auto& outIt : hMatrix)
    {
        line = "";
        for(auto inIt : outIt)
            line += inIt;

        while(regex_search(line, match, target))
        {
            numMatches++;
            line = match.suffix().str();
        }
    }

    //fill matrix for vertical matches
    std::vector<std::vector<char>> vMatrix;
    match = std::smatch{};
    fin.open("input.txt");
    if(!fin.is_open())
        std::cerr << "Error opening file" << std::endl;

    bool firstLoop = true;
    line="";
    while(getline(fin, line))
    {
        if(firstLoop)
        {
            firstLoop = false;
            for(auto ch : line)
            {
                auto& ref = vMatrix.emplace_back();
                ref.push_back(ch);
            }
        }
        else
        {
            for(int i = 0; i < line.size(); i++)
            {
                vMatrix[i].push_back(line[i]);
            }
        }
    }
    fin.close();

    //vertical matches
    for(const auto& outIt : vMatrix)
    {
        line = "";
        for(auto inIt : outIt)
            line += inIt;

        while(regex_search(line, match, target))
        {
            numMatches++;
            line = match.suffix().str();

        }
    }


    match = std::smatch{};
    //diagonal matches
    for(int ref = 0; ref < hMatrix.size(); ref++)
    {
        line = "";
        int tmpRef = ref;
        for(int inIt = 0; inIt < hMatrix[ref].size() && tmpRef < hMatrix.size(); inIt++, tmpRef++)
            line += hMatrix[tmpRef][inIt];

        while(regex_search(line, match, target))
        {
            numMatches++;
            line = match.suffix().str();
        }
    }

    match = std::smatch{};
    //more diag
    for(int ref = 0; ref < vMatrix.size(); ref++)
    {
        line = "";
        int tmpRef = ref;
        for(int inIt = 0; inIt < vMatrix[ref].size() && tmpRef < vMatrix.size(); inIt++, tmpRef++)
            line += vMatrix[tmpRef][inIt];

        while(regex_search(line, match, target))
        {
            numMatches++;
            line = match.suffix().str();
        }

    }

    std::cout << "num matches: " << numMatches << std::endl;
}
