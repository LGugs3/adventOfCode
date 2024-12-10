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
    std::vector<std::vector<int>> testContainer;

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
        auto& vecRef = testContainer.emplace_back();
        std::istringstream iss(line);
        std::string part;
        while(std::getline(iss, part, orderDel))
            vecRef.push_back(stoi(part));
    }
    fin.close();

    std::function<void(std::vector<int>&, int)> reorderCase = [&updateReqs, &reorderCase](std::vector<int>& testCase, const int indexToOrder) -> void
    {
        if(indexToOrder == testCase.size())
            return;

        bool swapped;
        for(auto testNum = testCase.begin() + indexToOrder + 1; testNum != testCase.end(); ++testNum)
        {
            swapped = false;
            for(auto reqsNum = updateReqs[*testNum].begin(); reqsNum != updateReqs[*testNum].end() && !swapped; ++reqsNum)
            {
                if(*reqsNum == testCase[indexToOrder])
                {
                    swapped = true;
                    auto orderIt = testCase.begin() + indexToOrder;
                    std::iter_swap(orderIt, testNum);
                }
            }
        }

        reorderCase(testCase, indexToOrder + 1);
    };


    //testing cases
    unsigned int orderSum = 0;
    bool numsReordered;
    for(auto& testCase : testContainer)
    {
        numsReordered = false;
        for(auto currNum = testCase.begin(); currNum != testCase.end() && !numsReordered; ++currNum)
        {
            std::vector<int> rulesList = updateReqs[*currNum];

            for(auto currRuleNum : rulesList)
            {
                if (std::find(testCase.begin(), currNum, currRuleNum) != currNum)
                {
                    numsReordered = true;
                    reorderCase(testCase, 0);
                }
            }
        }
        if(numsReordered)
            orderSum += testCase[(testCase.size() - 1) / 2];
    }
    std::cout << orderSum << std::endl;
}
