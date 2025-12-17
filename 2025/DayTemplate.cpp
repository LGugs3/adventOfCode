#include <string>


class DayTemplate
{
protected:
	std::string m_filename;

public:
	explicit DayTemplate(std::string fname) : m_filename(fname) {}

	virtual std::string getSolution(int part = 1) = 0;
};