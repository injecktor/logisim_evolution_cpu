#include "output.h"

output_t::output_t(std::string a_file_path)
	: m_file(a_file_path),
	m_word_count(0),
	m_max_word_count(1 << bits_in_address)
{
	if (!m_file.is_open()) {
		error("Output file wasn't open");
	}
	m_file << "v3.0 hex words addressed";
}

output_t::~output_t()
{
}

void output_t::add_word(std::string a_word)
{
	if (m_word_count % 8 == 0) {
		std::string tmp_string;
		std::stringstream hex_word_count;
		hex_word_count << std::hex << m_word_count;
		while (hex_word_count.str().length() + tmp_string.length() != (bits_in_address - 1) / 4 + 1) {
			tmp_string += '0';
		}
		m_file << '\n' << tmp_string << std::hex << hex_word_count.str() << ':';
	}
	m_file << ' ' << a_word;
	m_word_count++;
}

void output_t::finish_file()
{
	m_file.close();
}
