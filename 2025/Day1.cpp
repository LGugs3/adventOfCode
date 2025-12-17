#include <fstream>
#include <iostream>
#include "DayTemplate.cpp"
using namespace std;


class Day1 : public DayTemplate
{
private:

	int turnDial(ifstream& fin, int position)
	{
		if (!fin.good())
		{
			cout << "file " << m_filename << " failed to open." << endl;
			exit(EXIT_FAILURE);
		}

		string instruction, intermid;
		char direction;
		int magnitude, acc = 0, lastPos = 50;
		while (getline(fin, instruction))
		{
			//get info
			direction = instruction[0];
			magnitude = stoi(instruction.substr(1));

			position += direction == 'R' ? magnitude : magnitude * -1;

			if (position % 100 == 0 || abs(position) > 100 || position * lastPos < 0) acc++;
			lastPos = position;
		}
		return acc;
	}

	int solve(int part)
	{
		ifstream fin("Inputs/Day1.txt");

		switch (part)
		{
			case 1:
				int position = 50;
				return turnDial(fin, position);

		}


	}

public:
	explicit Day1(string fname) : DayTemplate(fname) {}

	string getSolution(int part = 1) override
	{
		return to_string(solve(part));
	}
};
