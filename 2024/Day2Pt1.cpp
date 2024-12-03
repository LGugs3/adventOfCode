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

int main() {
    std::ifstream fin("input.txt");

    std::vector<std::vector<int>> matrix;
    std::string line;
    std::stringstream ss;
    int index;
    //fill matrix
    for(index = 0; std::getline(fin, line); index++)
    {
        ss.clear();
        ss << line;

        matrix.emplace_back();
        int val;
        while(ss >> val)
            matrix[index].push_back(val);
    }

    unsigned int numSafeReports = 0;
    bool expectIncreasingNums = false;
    for(auto outIt : matrix)
    {
        //get increasing or decreasing
        int startIndex = 0;
        while (outIt[startIndex] == outIt[startIndex + 1])
            startIndex++;
        outIt[startIndex] < outIt[startIndex + 1] ? expectIncreasingNums = true : expectIncreasingNums = false;

        bool safeReport = true;
        for(auto inIt = outIt.begin(); std::next(inIt, 1) != outIt.end() && safeReport; ++inIt)//need to use reg for loop for iterator
        {
            int next = *std::next(inIt, 1);
            //checks if rest of numbers are following standard
            if ((*inIt > next && expectIncreasingNums) || (*inIt < next && !expectIncreasingNums)) safeReport = false;
            else
            {
                unsigned int diff = abs(*inIt - next);
                if(!(diff <= 3 && diff > 0)) safeReport = false;
            }
        }
        if (safeReport) numSafeReports++;
    }

    std::cout << numSafeReports << std::endl;
}
