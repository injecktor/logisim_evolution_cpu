#include "output.h"

output_t::output_t(std::string a_file_path)
	: m_file(a_file_path),
	m_line_count(0)
{
	if (!m_file.is_open()) {
		error("Output file wasn't open");
	}
	m_file << "v3.0 hex words addressed";
}

output_t::~output_t()
{
}
