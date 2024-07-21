#include "parser.h"

parser_t::parser_t()
{
}

parser_t::~parser_t()
{
}

std::string parser_t::parse(std::vector<token_t> tokens)
{
	std::string instr;
	switch (tokens[0].type) {
		case token_type_t::token_add: {
			if (tokens.size() != 4) {
				error("Incorrect registers count");
			}
			if (tokens[1].type != token_type_t::token_register ||
				tokens[2].type != token_type_t::token_register ||
				tokens[3].type != token_type_t::token_register) {
				error("Registers must be specified");
			}
			instr = get_hex(0, tokens[2].value1, tokens[3].value1, tokens[1].value1, 0, 0b100000);
		};
		case token_type_t::token_sub: {

		};
		case token_type_t::token_lw: {
			instr = get_hex(0b100011, tokens[2].value2, tokens[1].value1, tokens[2].value1);
		};
		case token_type_t::token_sw: {

		};
		default: {
			error("No token handle");
		}
	}
	return instr;
}

std::string parser_t::get_hex(int op, int rs, int rt, int rd, int shamt, int funct)
{
	using namespace std;
	string str_binary = bitset<6>(op).to_string() + bitset<5>(rs).to_string() + bitset<5>(rt).to_string() +
		bitset<5>(rd).to_string() + bitset<5>(shamt).to_string() + bitset<6>(funct).to_string();
	stringstream sstr;
	sstr << hex << stoi(str_binary);
	return sstr.str();
}

std::string parser_t::get_hex(int op, int rs, int rt, int address)
{
	using namespace std;
	string str_binary = bitset<6>(op).to_string() + bitset<5>(rs).to_string() + bitset<5>(rt).to_string() +
		bitset<16>(address).to_string();
	stringstream sstr;
	sstr << hex << stoi(str_binary);
	return sstr.str();
}

std::string parser_t::get_hex(int op, int address)
{
	using namespace std;
	string str_binary = bitset<6>(op).to_string() + bitset<26>(address).to_string();
	stringstream sstr;
	sstr << hex << stoi(str_binary);
	return sstr.str();
}

