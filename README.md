# MU0ARM Assembler
This is a simple one-pass assembler for MU0ARM CPU Project @ Imperial

**NOTE:** ALU instructions are all floating point

# Features
- Comments within assembly code
- Customizable opcodes for your own instruction set

# How to Use
1. Download assembler binary and place in any directory.
2. Run the executable and it will generate a file named `config.txt` and one named `input.txt` in the same directory as `Assembler.exe`.
3. Type your assembly code into the `input.txt` and run the executable `Assembler.exe` again to generate the ouputfile.

**Examples**
*input.txt*

    LDR R1 R0 +15 wp; this is a comment
    ADD R1 R0 LSL3
    SUB R0 R1
    STP; stops the program

*output.txt*

    Binary Format:
    0b0000011111111100
    0b1000010000110000
    0b1001010000000000
    0b0111000000000000
     
    Hex Format:
    0x07FC
    0x8430
    0x9400
    0x7000

# Assembly Code Formatting
1. **Load Store Instructions** *(default opcode: 0000)*
	\<OP\> \<Rd\> \<Rm\> \<n\> \<flags\>; \<comment\>
	
	*Mandatory Fields: OP, Rd, Rm
	Optional: n (default 0), flags (default 00), comment*

	Examples:
	- `LDR R1 R0 +15 wp`
		- R1 := [R0 + 15] with post-increment (**p** flag) 
		- R0 := R0 + 15 write-back (**w** flag)
	
	-  `STR R1 R0 -3 w`
		- mem[R0 - 3] := R1
		- R0 := R0 - 3 write-back (**w** flag)

2. **Program Counter Instructions** *(default opcodes: 0XXX, except 0000)*
	\<OP\> \<N\>; \<comment\>
	
	*Mandatory Fields: OP
	Optional: n (default 0), comment*

	Examples:
	- `JMP 12` 
		- Jump to location 12
	- `STP`
		- Stops the programs

3. **Data Processing Instructions** *(default opcodes: 1XXX)*
	\<OP\> \<Rd\> \<Rm\> \<sh\>; \<comment\>
	*Mandatory Fields: OP, Rd, Rm
	Optional: shift n (default to LS0), comment*

	Examples:
	- `ADD R1 R0 LS2`
		- R1 := R1 + R0 * 4
	- `SUB R1 R0 RS2`
		- R1 := R1 - R0 / 4

# Planned Features
- Error Detection
	- Register or immediate number must be within bounds
	- Opcode typos