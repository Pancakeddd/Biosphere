#pragma once

#include "Prelude.h"

#include <stack>

#define MAX_SRC_SIZE 32
#define INPUTS 3
#define OUTPUTS 3

enum Opcode
{
	NOP,
	PUSH_CONSTANT,
	PUSH_INPUT,
	ADD,
	SUB,
	MUL,
	DIV,
	SET_OUTPUT,
	JUMP,
	OPSSIZE,
};

struct Command
{
	size_t idx;
	int arg1;

	Opcode type;
};

using Source = Command[MAX_SRC_SIZE];

struct VM
{
	size_t src_idx = 0;
	std::stack<double> stack;
	Source src;

	double input[INPUTS];
	double outputs[OUTPUTS];

	double eatStack();
	void runNextCommand();
};