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
	std::string get_hex(int op, int rs, int rt, int rd, int shamt, int funct);
	std::string get_hex(int op, int rs, int rt, int address);
	std::string get_hex(int op, int address);
};

