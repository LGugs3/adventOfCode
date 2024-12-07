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
#include <unordered_map>

int main() {
    std::ifstream fin("input.txt");
    if(!fin.is_open())
        std::cerr << "Error opening file" << std::endl;

    std::unordered_map<int, std::vector<int>> updateReqs = std::unordered_map<int, std::vector<int>>();
    std::vector<std::vector<int>> updateOrder;

    const char reqsDel = '|';
    const char orderDel = ',';

    //filling map and vector
    //requirment
    std::string line;
    for(std::getline(fin, line); !line.empty(); std::getline(fin, line))
    {
        std::istringstream iss(line);
        std::string first, second;
        std::getline(iss, first, reqsDel);
        std::getline(iss, second, reqsDel);

        updateReqs[std::stoi(first)].push_back(std::stoi(second));
    }

    //order
    while(getline(fin, line))
    {
        auto& ref = updateOrder.emplace_back();
        std::istringstream iss(line);
        std::string part;
        while(std::getline(iss, part, orderDel))
            ref.push_back(stoi(part));
    }

    //testing cases
    unsigned int orderSum = 0;
    bool goodOrder = true;
    for(const auto& outIt : updateOrder)
    {
        for(auto inIt = outIt.begin(); inIt != outIt.end(); ++inIt)
        {
            auto arr = updateReqs[*inIt];
            for(auto reqsIt : arr)
            {
                if (std::find(outIt.begin(), inIt, reqsIt) == outIt.end())
                    goodOrder = false;
            }
        }
        if (goodOrder)
            orderSum += outIt[outIt.size() / 2];
    }

    std::cout << orderSum << std::endl;
}
