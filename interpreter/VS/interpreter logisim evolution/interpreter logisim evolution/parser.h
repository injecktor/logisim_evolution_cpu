#pragma once

#include <string>
#include <vector>
#include <array>
#include <cassert>
#include <bitset>
#include "sstream"

#include "tokenizer.h"

extern void error(std::string msg);

class parser_t
{
public:
	parser_t();
	~parser_t();

	std::string parse(std::vector<token_t> tokens);
private:
	enum instr_type_t : uint8_t {
		none,
		r_type,
		//i_type_register_register_literal
		i_type_rrl,
		//i_type_register_address
		i_type_ra,
		j_type
	};

	std::string get_hex(int op, int rs, int rt, int rd, int shamt, int funct);
	std::string get_hex(int op, int rs, int rt, int address);
	std::string get_hex(int op, int address);

	unsigned int bit_offset(int number, int bits_count, int offset);
};

