#pragma once

#include <string>
#include <fstream>
#include <cassert>
#include <sstream>

extern void error(std::string msg);

class output_t
{
public:
	output_t(std::string a_file_path);
	~output_t();

	void add_word(std::string a_word);
	void finish_file();

private:
	size_t m_line_count;
	size_t m_max_line_count;
	std::ofstream m_file;

	enum output_stats_t {
		words_in_line = 8,
		bits_in_address = 16
	};
};

