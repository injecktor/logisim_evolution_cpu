#pragma once

#include "tokenizer.h"
#include <string>
#include <vector>
#include <array>
#include <cassert>
#include <bitset>
#include "sstream"

extern void error(std::string msg);

std::array<token_type_t, 9> instructions = {
	token_type_t::token_add,
	token_type_t::token_sub,
	token_type_t::token_and,
	token_type_t::token_or,
	token_type_t::token_slt,
	token_type_t::token_beq,
	token_type_t::token_j,
	token_type_t::token_lw,
	token_type_t::token_sw
};

class parser_t
{
public:
	parser_t();
	~parser_t();

	std::string parse(std::vector<token_t> tokens);
private:
	std::string get_hex(int op, int rs, int rt, int rd, int shamt, int funct);
	std::string get_hex(int op, int rs, int rt, int address);
	std::string get_hex(int op, int address);
};

