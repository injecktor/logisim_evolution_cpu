#include "parser.h"

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
				error("Incorrect tokens count");
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
			if (tokens.size() != 3) {
				error("Incorrect tokens count");
			}
			if (tokens[1].type != token_type_t::token_register ||
				tokens[2].type != token_type_t::token_address) {
				error("Incorrect tokens. Must be \"lw {register token} {address token}\"");
			}
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
	unsigned int instr = bit_offset(op, 6, 26) + bit_offset(rs, 5, 21) + bit_offset(rt, 5, 16) +
		bit_offset(rd, 5, 11) + bit_offset(shamt, 5, 6) + bit_offset(funct, 6, 0);
	stringstream sstr;
	sstr << hex << instr;
	return sstr.str();
}

std::string parser_t::get_hex(int op, int rs, int rt, int address)
{
	using namespace std;
	unsigned int instr = bit_offset(op, 6, 26) + bit_offset(rs, 5, 21) + bit_offset(rt, 5, 16) +
		bit_offset(address, 16, 0);
	stringstream sstr;
	sstr << hex << instr;
	return sstr.str();
}

std::string parser_t::get_hex(int op, int address)
{
	using namespace std;
	unsigned int instr = bit_offset(op, 6, 26) + bit_offset(address, 26, 0);
	stringstream sstr;
	sstr << hex << instr;
	return sstr.str();
}

unsigned int parser_t::bit_offset(int number, int bits_count, int offset)
{
	return (number & (0xffffffff >> (32 - bits_count)) << offset);
}

