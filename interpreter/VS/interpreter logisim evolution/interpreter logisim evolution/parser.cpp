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
				error("Incorrect tokens count");
			}
			if (tokens[1].type != token_type_t::token_register ||
				tokens[2].type != token_type_t::token_register ||
				tokens[3].type != token_type_t::token_register) {
				error("Registers must be specified");
			}
			instr = get_hex(0, tokens[2].value1, tokens[3].value1, tokens[1].value1, 0, 0b100000);
		} break;
		case token_type_t::token_sub: {
			if (tokens.size() != 4) {
				error("Incorrect tokens count");
			}
			if (tokens[1].type != token_type_t::token_register ||
				tokens[2].type != token_type_t::token_register ||
				tokens[3].type != token_type_t::token_register) {
				error("Registers must be specified");
			}
			instr = get_hex(0, tokens[2].value1, tokens[3].value1, tokens[1].value1, 0, 0b100010);
		} break;
		case token_type_t::token_and: {
			if (tokens.size() != 4) {
				error("Incorrect tokens count");
			}
			if (tokens[1].type != token_type_t::token_register ||
				tokens[2].type != token_type_t::token_register ||
				tokens[3].type != token_type_t::token_register) {
				error("Registers must be specified");
			}
			instr = get_hex(0, tokens[2].value1, tokens[3].value1, tokens[1].value1, 0, 0b100100);
		} break;
		case token_type_t::token_or: {
			if (tokens.size() != 4) {
				error("Incorrect tokens count");
			}
			if (tokens[1].type != token_type_t::token_register ||
				tokens[2].type != token_type_t::token_register ||
				tokens[3].type != token_type_t::token_register) {
				error("Registers must be specified");
			}
			instr = get_hex(0, tokens[2].value1, tokens[3].value1, tokens[1].value1, 0, 0b100101);
		} break;
		case token_type_t::token_slt: {
			if (tokens.size() != 4) {
				error("Incorrect tokens count");
			}
			if (tokens[1].type != token_type_t::token_register ||
				tokens[2].type != token_type_t::token_register ||
				tokens[3].type != token_type_t::token_register) {
				error("Registers must be specified");
			}
			instr = get_hex(0, tokens[2].value1, tokens[3].value1, tokens[1].value1, 0, 0b101010);
		} break;
		case token_type_t::token_lw: {
			if (tokens.size() != 3) {
				error("Incorrect tokens count");
			}
			if (tokens[1].type != token_type_t::token_register ||
				tokens[2].type != token_type_t::token_address) {
				error("Incorrect tokens. Must be \"lw {register token} {address token}\"");
			}
			instr = get_hex(0b100011, tokens[2].value2, tokens[1].value1, tokens[2].value1);
		} break;
		case token_type_t::token_sw: {
			if (tokens.size() != 3) {
				error("Incorrect tokens count");
			}
			if (tokens[1].type != token_type_t::token_register ||
				tokens[2].type != token_type_t::token_address) {
				error("Incorrect tokens. Must be \"lw {register token} {address token}\"");
			}
			instr = get_hex(0b101011, tokens[2].value2, tokens[1].value1, tokens[2].value1);
		} break;
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
	return (number & (0xffffffff >> (32 - bits_count))) << offset;
}

