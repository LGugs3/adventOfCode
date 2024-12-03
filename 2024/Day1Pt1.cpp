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

    std::priority_queue<int, std::vector<int>, std::greater<int>> leftPQ;
    std::priority_queue<int, std::vector<int>, std::greater<int>> rightPQ;

    //fill barVec
    std::string line;
    int leftItem, rightItem;
    std::stringstream ss;
    while (std::getline(fin, line))
    {
        ss.clear();
        ss << line;
        ss >> leftItem >> rightItem;

        leftPQ.push(leftItem);
        rightPQ.push(rightItem);
    }
    fin.close();

    //accumulate distance
    unsigned long long int acc = 0;
    int leftTop, rightTop;
    while (!(leftPQ.empty() && rightPQ.empty()))
    {
        leftTop = leftPQ.top();
        rightTop = rightPQ.top();
        leftPQ.pop();
        rightPQ.pop();
        acc += abs(leftTop - rightTop);
    }

    std::cout << acc << std::endl;
}
