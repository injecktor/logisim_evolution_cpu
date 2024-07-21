#include "output.h"

output_t::output_t(std::string a_file_path)
	: m_file(a_file_path),
	m_max_line_count(1 << bits_in_address),
	m_line_count(0)
{
	if (!m_file.is_open()) {
		error("Output file wasn't open");
	}
	m_file << "v3.0 hex words addressed";
	m_file << "second line?";
}

output_t::~output_t()
{
}

void output_t::add_word(std::string a_word)
{
	m_line_count++;

}

void output_t::finish_file()
{
	m_file.close();
}
