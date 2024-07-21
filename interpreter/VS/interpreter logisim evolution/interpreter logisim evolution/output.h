#pragma once

#include <string>
#include <fstream>
#include <cassert>

extern void error(std::string msg);

class output_t
{
public:
	output_t(std::string a_file_path);
	~output_t();

private:
	size_t m_line_count;

	std::ofstream m_file;
};

