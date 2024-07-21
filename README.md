# Logisim evolution cpu

### Main Decoder

|Command|Opcode|RegWrite|RegDst|ALUSrc|Branch|MemWrite|MemtoReg|ALUOp|
|-|-|-|-|-|-|-|-|-|
|R-type|000000|1|1|0|0|0|0|10|
|lw|100011|1|0|1|0|0|1|00|
|sw|101011|0|X|1|0|1|X|00|
|beq|000100|0|X|0|1|0|X|01|
|addi|001000|1|0|1|0|0|0|00|
|subi|001001|1|0|1|0|0|0|01|

### ALU Decoder

|ALUOp|funct|ALUControl|
|-|-|-|
|00|X|010|
|X1|X|110|
|10|100000|010|
|10|100010|110|
|10|100100|000|
|10|100101|001|
|10|101010|111|

|ALUControl|Action|
|-|-|
|000|logical and|
|001|logical or|
|010|add|
|011||
|100||
|101||
|110|sub|
|111|slt|