#pragma once

#include <string>
#include <vector>
#include <cassert>
#include <sstream>
#include <bitset>

extern void error(std::string msg);

enum class token_type_t {
	token_add,
	token_sub,
	token_and,
	token_or,
	token_slt,
	token_beq,
	token_j,
	token_lw,
	token_sw,
	token_register,
	token_address,
	token_addi,
	token_subi,
	token_literal
};

struct token_t {
	token_type_t type;
	int value1; // -1 = unused
	int value2;
	token_t(token_type_t a_type, signed int a_value1 = -1, signed int a_value2 = -1)
		: type(a_type),
		value1(a_value1),
		value2(a_value2) {}
};

class tokenizer_t
{
public:
	tokenizer_t();
	~tokenizer_t();

	std::vector<token_t> tokenize(char a_line[256]);
private:
	std::string m_line;

	token_t ident_token(std::string a_token_str);
};

