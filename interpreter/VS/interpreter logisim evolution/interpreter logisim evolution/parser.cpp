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
	instr_type_t instr_type = none;
	int opcode = 0;
	int shamt = 0, funct = 0;
	switch (tokens[0].type) {
		case token_type_t::token_add: {
			instr_type = r_type;
			funct = 0b100000;
		} break;
		case token_type_t::token_sub: {
			instr_type = r_type;
			funct = 0b100010;
		} break;
		case token_type_t::token_and: {
			instr_type = r_type;
			funct = 0b100100;
		} break;
		case token_type_t::token_or: {
			instr_type = r_type;
			funct = 0b100101;
		} break;
		case token_type_t::token_slt: {
			instr_type = r_type;
			funct = 0b101010;
		} break;
		case token_type_t::token_beq: {
			opcode = 0b000100;
			instr_type = i_type_rrl;
		} break;
		case token_type_t::token_j: {
			opcode = 0b000010;
			instr_type = j_type;
		} break;
		case token_type_t::token_lw: {
			instr_type = i_type_ra;
			opcode = 0b100011;
		} break;
		case token_type_t::token_sw: {
			instr_type = i_type_ra;
			opcode = 0b101011;
		} break;
		case token_type_t::token_addi: {
			instr_type = i_type_rrl;
			opcode = 0b001000;
		} break;
		case token_type_t::token_subi: {
			instr_type = i_type_rrl;
			opcode = 0b001001;
		} break;
		default: {
			error("No token handle");
		} break;
	}
	switch (instr_type) {
		case r_type: {
			if (tokens.size() != 4) {
				error("Incorrect tokens count");
			}
			if (tokens[1].type != token_type_t::token_register ||
				tokens[2].type != token_type_t::token_register ||
				tokens[3].type != token_type_t::token_register) {
				error("Incorrect instruction");
			}
			instr = get_hex(opcode, tokens[2].value1, tokens[3].value1, tokens[1].value1, 0, funct);
		} break;
		case i_type_rrl: {
			if (tokens.size() != 4) {
				error("Incorrect tokens count");
			}
			if (tokens[1].type != token_type_t::token_register ||
				tokens[2].type != token_type_t::token_register ||
				tokens[3].type != token_type_t::token_literal) {
				error("Incorrect instruction");
			}
			instr = get_hex(opcode, tokens[2].value1, tokens[1].value1, tokens[3].value1);
		} break;
		case i_type_ra: {
			if (tokens.size() != 3) {
				error("Incorrect tokens count");
			}
			if (tokens[1].type != token_type_t::token_register ||
				tokens[2].type != token_type_t::token_address) {
				error("Incorrect instruction");
			}
			instr = get_hex(opcode, tokens[2].value2, tokens[1].value1, tokens[2].value1);
		} break;
		case j_type: {
			if (tokens.size() != 2) {
				error("Incorrect tokens count");
			}
			if (tokens[1].type != token_type_t::token_literal) {
				error("Incorrect instruction");
			}
			instr = get_hex(opcode, tokens[1].value1);
		} break;
		default: {

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

std::string parser_t::get_hex(int op, int rs, int rt, int immediate)
{
	using namespace std;
	unsigned int instr = bit_offset(op, 6, 26) + bit_offset(rs, 5, 21) + bit_offset(rt, 5, 16) +
		bit_offset(immediate, 16, 0);
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

