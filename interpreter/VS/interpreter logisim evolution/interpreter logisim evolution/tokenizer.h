#pragma once

#include <string>
#include <vector>
#include <cassert>

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
	token_address
};

struct token_t {
	token_type_t type;
	signed int value1; // -1 = unused
	signed int value2;
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
};

