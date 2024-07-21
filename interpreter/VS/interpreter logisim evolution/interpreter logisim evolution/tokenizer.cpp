#include "tokenizer.h"

tokenizer_t::tokenizer_t()
	: m_line()
{

}

tokenizer_t::~tokenizer_t()
{
}

std::vector<token_t> tokenizer_t::tokenize(char a_line[256])
{
	std::vector<token_t> tokens;
	m_line = a_line;
	size_t i = 0;
	std::string token_str;
	int token_start_pos = 0;
	bool token_started = false;
	bool token_ended = false;
	while (m_line[i] != '\0') {
		if (m_line[i] != ' ' && !token_started) {
			token_started = true;
			token_start_pos = i;
		}
		else if (m_line[i] == ' ' && token_started) {
			token_started = false;
			tokens.push_back(ident_token(token_str));
			token_str = "";
		}
		if (token_started) {
			token_str += m_line[i];
		}
		i++;
	}
	if (token_started) {
		tokens.push_back(ident_token(token_str));
	}
	return tokens;
}

token_t tokenizer_t::ident_token(std::string a_token_str)
{
	if (a_token_str == "add") {
		return{ token_type_t::token_add };
	}
	else if (a_token_str == "sub") {
		return{ token_type_t::token_sub };
	}
	else if (a_token_str == "and") {
		return{ token_type_t::token_and };
	}
	else if (a_token_str == "or") {
		return{ token_type_t::token_or };
	}
	else if (a_token_str == "slt") {
		return{ token_type_t::token_slt };
	}
	else if (a_token_str == "beq") {
		return{ token_type_t::token_beq };
	}
	else if (a_token_str == "lw") {
		return{ token_type_t::token_lw };
	}
	else if (a_token_str == "sw") {
		return{ token_type_t::token_sw };
	}
	else if (a_token_str[0] == 'r') {
		int number = stoi(a_token_str.substr(1, a_token_str.length() - 1));
		if (number >= 0 && number <= 31) {
			return{ token_type_t::token_register, number };
		}
		else {
			error("Incorrect register");
		}
	}
	else if (isdigit(a_token_str[0])) {
		if (int index = a_token_str.find('(') != -1) {
			int number1 = stoi(a_token_str.substr(0, index));
			int number2 = stoi(a_token_str.substr(index + 2, a_token_str.find(')')));
			return{ token_type_t::token_address, number1, number2 };
		}
	}
	else {
		error("Unknown instruction");
	}
}
