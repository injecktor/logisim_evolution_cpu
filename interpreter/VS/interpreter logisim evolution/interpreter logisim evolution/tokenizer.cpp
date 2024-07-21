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
			if (token_str == "add") {
				tokens.push_back({ token_type_t::token_add });
			}
			else if (token_str == "sub") {
				tokens.push_back({ token_type_t::token_sub });
			}
			else if (token_str == "and") {
				tokens.push_back({ token_type_t::token_and });
			}
			else if (token_str == "or") {
				tokens.push_back({ token_type_t::token_or });
			}
			else if (token_str == "slt") {
				tokens.push_back({ token_type_t::token_slt });
			}
			else if (token_str == "beq") {
				tokens.push_back({ token_type_t::token_beq });
			}
			else if (token_str == "lw") {
				tokens.push_back({ token_type_t::token_lw });
			}
			else if (token_str == "sw") {
				tokens.push_back({ token_type_t::token_sw });
			}
			else if (token_str[0] == 'r') {
				int number = stoi(token_str.substr(1, token_str.length() - 1));
				if (number >= 0 && number <= 31) {
					tokens.push_back({ token_type_t::token_beq, number });
				}
				else {
					error("Incorrect register number");
				}
			}
			else if (isdigit(token_str[0])) {
				if (int index = token_str.find('(') != -1) {
					int number1 = stoi(token_str.substr(0, index));
					int number2 = stoi(token_str.substr(index + 2, token_str.find(')')));
					tokens.push_back({ token_type_t::token_address, number1, number2 });
				}
			}
			else {
				error("Unknown instruction");
			}
			token_str = "";
		}
		if (token_started) {
			token_str += m_line[i];
		}
		i++;
	}
	return tokens;
}
