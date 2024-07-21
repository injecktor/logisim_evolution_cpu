#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

#include "parser.h"
#include "output.h"

using namespace std;

size_t line_count = 0;

const string src = "../../../../asm/asm.txt";
const string dst = "../../../../machine_code/binary_code.txt";

int main() {
	ifstream src_f(src);
	ofstream dst_f(dst);

	assert(src_f.is_open(), "Src file wasn't open.");
	assert(dst_f.is_open(), "Dst file wasn't open.");

	char line[256]{ 0 };

	tokenizer_t tokenizer;
	parser_t parser;
	output_t output(dst);

	while (src_f.getline(line, sizeof(line))) {
		vector<token_t> tokens = tokenizer.tokenize(line);
		if (tokens.size()) {
			string hex_instr = parser.parse(tokens);
		}
		line_count++;
	}

	return 0;
}

void error(string msg) {
	assert(false, line_count + ": " + msg);
}