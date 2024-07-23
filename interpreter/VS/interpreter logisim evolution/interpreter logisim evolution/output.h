#pragma once

#include <string>
#include <fstream>
#include <cassert>
#include <sstream>

extern void error(std::string msg);

class output_t
{
public:
	output_t(std::string a_file_path, bool a_is_word_addressing = false);
	~output_t();

	void add_word(std::string a_word);
	void finish_file();

private:
	size_t m_word_count;
	const size_t m_max_word_count;
	std::ofstream m_file;
	bool m_is_word_addressing;
	size_t addresses_in_line;
	size_t addresses_by_instr;

	enum output_stats_t {
		bits_in_address = 16,
		instr_length = 8,
		addresses_in_line_word_addressing = 8,
		addresses_in_line_byte_addressing = 16,
		addresses_by_instr_word_addressing = 1,
		addresses_by_instr_byte_addressing = 4,
	};

	void add_word_to_word_address(std::string a_word);
	void add_word_to_byte_address(std::string a_word);
};

