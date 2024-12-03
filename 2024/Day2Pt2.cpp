#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
//#include <set>
//#include <algorithm>
#include <fstream>
#include <string>
//#include <queue>
//#include <utility>
//#include <utility>
#include <vector>
#include <iterator>

void removeLevel(std::vector<int>& vec, std::vector<int>::iterator& it)
{
    it = std::prev(vec.erase(std::next(it)),2);
}

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
        bool levelRemoved = false;
        //need to use reg for loop for iterator
        for(auto inIt = outIt.begin(); std::next(inIt) != outIt.end() && safeReport; ++inIt)
        {
            int next = *std::next(inIt);
            //checks if rest of numbers are following increase/decrease standard
            if ((*inIt > next && expectIncreasingNums) || (*inIt < next && !expectIncreasingNums))
            {
                if (!levelRemoved)
                {
                    levelRemoved = true;
                    removeLevel(outIt, inIt);
                }
                else
                    safeReport = false;
            }
            else
            {
                //check difference
                unsigned int diff = abs(*inIt - next);
                if(!(diff <= 3 && diff > 0))
                {
                    if (!levelRemoved)
                    {
                        levelRemoved = true;
                        removeLevel(outIt, inIt);
                    }
                    else
                        safeReport = false;
                }
            }
        }
        if (safeReport) numSafeReports++;
    }

    std::cout << numSafeReports << std::endl;
}
