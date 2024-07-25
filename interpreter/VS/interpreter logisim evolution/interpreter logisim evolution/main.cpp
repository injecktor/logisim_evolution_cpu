#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

#include "parser.h"
#include "output.h"

using namespace std;

size_t line_count = 0;

const string src = "../../../../asm/asm_example.txt";
const string dst = "../../../../asm_output/example.da";

int main() {
	ifstream src_f(src);

	assert(src_f.is_open(), "Src file wasn't open.");

	char line[256]{ 0 };

	tokenizer_t tokenizer;
	parser_t parser;
	output_t output(dst);

	while (src_f.getline(line, sizeof(line))) {
		vector<token_t> tokens = tokenizer.tokenize(line);
		if (tokens.size()) {
			string hex_instr = parser.parse(tokens);
			output.add_word(hex_instr);
		}
		line_count++;
	}
	output.finish_file();

	return 0;
}

void error(string msg) {
	string error_msg = to_string(line_count) + ": " + msg;
	cerr << error_msg;
	abort();
}