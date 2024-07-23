#include "output.h"

output_t::output_t(std::string a_file_path, bool a_is_word_addressing)
	: m_file(a_file_path),
	m_word_count(0),
	m_max_word_count(1 << bits_in_address),
	m_is_word_addressing(a_is_word_addressing)
{
	if (!m_file.is_open()) {
		error("Output file wasn't open");
	}
	m_file << "v3.0 hex words addressed";
	if (m_is_word_addressing) {
		addresses_in_line = addresses_in_line_word_addressing;
		addresses_by_instr = addresses_by_instr_word_addressing;
	}
	else {
		addresses_in_line = addresses_in_line_byte_addressing;
		addresses_by_instr = addresses_by_instr_byte_addressing;
	}
}

output_t::~output_t()
{
}

void output_t::add_word(std::string a_instr)
{
	if (m_word_count % addresses_in_line == 0) {
		std::string tmp_string;
		std::stringstream hex_word_count;
		hex_word_count << std::hex << m_word_count;
		while (hex_word_count.str().length() + tmp_string.length() != (bits_in_address - 1) / 4 + 1) {
			tmp_string += '0';
		}
		m_file << '\n' << tmp_string << std::hex << hex_word_count.str() << ':';
	}
	m_file << ' ';
	for (size_t i = 0; i < instr_length - a_instr.length(); i++)
	{
		m_file << '0';
	}
	if (m_is_word_addressing) {
		m_file << a_instr;
	}
	else {
		m_file << a_instr.substr(instr_length - 2, 2) << ' ' << a_instr.substr(instr_length - 4, 2) << ' ' <<
			a_instr.substr(instr_length - 6, 2) << ' ' << a_instr.substr(instr_length - 8, 2);
	}
	m_word_count += addresses_by_instr;
}

void output_t::finish_file()
{
	while (m_word_count != m_max_word_count) {
		add_word("00000000");
	}
	m_file.close();
}

void output_t::add_word_to_word_address(std::string a_word)
{

}

void output_t::add_word_to_byte_address(std::string a_word)
{

}
