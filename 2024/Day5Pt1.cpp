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

    //testing cases
    unsigned int orderSum = 0;
    bool testPassed;
    for(const auto& testCase : testContainer)
    {
        testPassed = true;
        for(auto currNum = testCase.begin(); currNum != testCase.end(); ++currNum)
        {
            std::vector<int> rulesList = updateReqs[*currNum];

            // std::cout << "Left number: " << *currNum << std::endl;
            // for(auto tmp : rulesList)
            //     std::cout << tmp << std::endl;
            // std::cout << std::endl;

            for(auto currRuleNum : rulesList)
            {
                if (std::find(testCase.begin(), currNum, currRuleNum) != currNum)
                {
                    //std::cout << "Wrong number: " << *currNum << std::endl;
                    testPassed = false;
                }
            }

            //std::cout << std::endl;
        }
        if (testPassed)
            orderSum += testCase[(testCase.size() - 1) / 2];
    }

    std::cout << orderSum << std::endl;
}
