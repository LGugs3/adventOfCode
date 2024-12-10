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

#define OBSTACLE '#'
#define SPACE_TRAVELED 'X'

void changeGuardDir(char& currDir);
std::pair<int, int> findGuardPos(const std::vector<std::vector<char>>& map);
size_t countUniqueSpacesTraveled(const std::vector<std::vector<char>>& map);

std::pair<int, int> operator+(const std::pair<int, int>& leftPos, const std::pair<int, int>& rightPos);

int main() {
    std::ifstream fin("input.txt");
    if(!fin.is_open())
        std::cerr << "Error opening file" << std::endl;

    std::vector<std::vector<char>> map;

    std::string line;
    while(std::getline(fin, line))
    {
        auto& rowRef = map.emplace_back();
        for(auto ch : line)
            rowRef.push_back(ch);
    }
    fin.close();

    auto moveDir = [&map](const std::pair<int, int>& guardPos, const char guardFace)
    {
        std::pair dir(0,0);
        switch (guardFace)
        {
            case '^':
                dir.second = -1;
                return dir;
            case '>':
                dir.first = 1;
                return dir;
            case 'v':
                dir.second = 1;
                return dir;
            case '<':
                dir.first = -1;
                return dir;
            default:
                throw std::invalid_argument("Invalid guard face");
        }
    };

    std::function<void(std::pair<int, int>&, char)> moveGuard = [&map, &moveDir, &moveGuard](std::pair<int, int>& guardPos, char guardFace) -> void
    {
        std::pair<int, int> dirToMove = moveDir(guardPos, guardFace);
        std::pair<int, int> nextPos = guardPos + dirToMove;

        //position out of map
        if(nextPos.second >= map.size() || nextPos.first >= map[nextPos.second].size() || nextPos.first < 0 || nextPos.second < 0)
        {
            map[guardPos.second][guardPos.first] = SPACE_TRAVELED;
            return;
        }

        auto nextSpace = map[nextPos.second][nextPos.first];
        if(nextSpace == OBSTACLE)
            changeGuardDir(guardFace);
        else
        {
            //move guard
            auto prevSpace = guardPos;
            guardPos = nextPos;
            map[prevSpace.second][prevSpace.first] = SPACE_TRAVELED;//replace last space as traveled
        }
        moveGuard(guardPos, guardFace);
    };

    std::pair<int, int> pos = findGuardPos(map);

    moveGuard(pos, '^');

    std::cout << countUniqueSpacesTraveled(map) << std::endl;
}

void changeGuardDir(char& currDir)
{
    switch (currDir)
    {
        case '^':
            currDir = '>';
            break;
        case '>':
            currDir = 'v';
            break;
        case 'v':
            currDir = '<';
            break;
        case '<':
            currDir = '^';
            break;
        default:
            throw std::invalid_argument("Invalid Guard Direction");
    }
}

std::pair<int, int> findGuardPos(const std::vector<std::vector<char> > &map)
{
    for(auto y : map)
    {
        for(auto x = y.begin(); x != y.end(); ++x)
        {
            if(*x == '^')
            {
                auto yInt = std::distance(map.begin(), std::find(map.begin(), map.end(), y));
                auto xInt = std::distance(y.begin(), x);

                return std::make_pair(xInt, yInt);
            }
        }
    }
    throw std::invalid_argument("Guard Position not found");
}

std::pair<int, int> operator+(const std::pair<int, int> &leftPos, const std::pair<int, int> &rightPos)
{
    int leftNum = leftPos.first - rightPos.first;
    int rightNum = leftPos.second - rightPos.second;
    std::pair pos(leftNum, rightNum);

    return pos;
}

size_t countUniqueSpacesTraveled(const std::vector<std::vector<char>>& map)
{
    size_t count = 0;
    for(const auto& y : map)
        for(const auto x : y)
            if(x == SPACE_TRAVELED)
                ++count;

    return count;
}
