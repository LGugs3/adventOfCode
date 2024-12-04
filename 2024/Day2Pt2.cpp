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

void removeLevel(std::vector<int>& vec, std::vector<int>::iterator& it, bool removeFirst = false)
{
    removeFirst ? vec.erase(vec.begin()) : vec.erase(std::next(it));
    if(removeFirst) it = vec.begin();
}

bool retestExpectedNums(const std::vector<int>& vec)
{
    int startIndex = 0;
    while (vec[startIndex] == vec[startIndex + 1])
        startIndex++;
    return vec[startIndex] < vec[startIndex + 1] ? true : false;
}

void printVector(const std::vector<int>& vec)
{
    for(auto it: vec)
        std::cout << it << " ";
    std::cout << std::endl;
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
        bool firstIndexRemoved = false;
        bool attemptedFirstRemoval = false;
        int firstIndex = *outIt.begin();
        //need to use reg loop for iterator
        for(auto inIt = outIt.begin(); std::next(inIt) != outIt.end() && inIt != outIt.end() && safeReport; ++inIt)
        {
            int next = *std::next(inIt);
            //checks if rest of numbers are following increase/decrease standard
            if ((*inIt > next && expectIncreasingNums) || (*inIt < next && !expectIncreasingNums))
            {

                if (!levelRemoved)
                {
                    //assume begin index is wrong
                    if(!firstIndexRemoved && !attemptedFirstRemoval)
                    {
                        removeLevel(outIt, inIt, true);
                        firstIndexRemoved = true;
                        expectIncreasingNums = retestExpectedNums(outIt);
                        attemptedFirstRemoval = true;
                    }
                    else
                    {
                        outIt.insert(outIt.begin(), firstIndex);
                        firstIndexRemoved = false;
                        levelRemoved = true;
                        removeLevel(outIt, inIt);
                        expectIncreasingNums = retestExpectedNums(outIt);
                    }
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
                        //assume begin index is wrong
                        if(!firstIndexRemoved && !attemptedFirstRemoval)
                        {
                            removeLevel(outIt, inIt, true);
                            firstIndexRemoved = true;
                            expectIncreasingNums = retestExpectedNums(outIt);
                            attemptedFirstRemoval = true;
                        }
                        else
                        {
                            outIt.insert(outIt.begin(), firstIndex);
                            firstIndexRemoved = false;
                            levelRemoved = true;
                            removeLevel(outIt, inIt);
                            expectIncreasingNums = retestExpectedNums(outIt);
                        }
                    }
                    else
                        safeReport = false;
                }
            }
        }
        if (safeReport) numSafeReports++;
        printVector(outIt);
    }

    std::cout << numSafeReports << std::endl;
}
