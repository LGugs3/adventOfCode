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

unsigned int getCount(const std::vector<std::pair<int, int>>& vec, int target)
{
    unsigned int count = 0;
    for (auto it : vec)
    {
        if (target == it.first) count++;
    }
    return count;
}

int main() {
    std::ifstream fin("input.txt");

    std::vector<std::pair<int, int>> vec;

    //fill barVec
    std::string line;
    int leftItem, rightItem;
    std::stringstream ss;
    while (std::getline(fin, line))
    {
        ss.clear();
        ss << line;
        ss >> leftItem >> rightItem;

        vec.emplace_back(leftItem, rightItem);
    }
    fin.close();

    unsigned int acc = 0;
    //accumulate similarity
    for(auto it : vec)
    {
        unsigned int count = getCount(vec, it.second);

        acc += count * it.second;
    }

    std::cout << acc << std::endl;


}
