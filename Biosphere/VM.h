#pragma once

#include "Prelude.h"

#define MAX_SRC_SIZE 100

enum Opcode
{
	NOP,
	PUSH_CONSTANT,
	PUSH_INPUT,
	ADD,
	SUB,
	MUL,
	SET_OUTPUT
};

struct Command
{
	size_t idx;
};

using Source = Command[MAX_SRC_SIZE];

struct VM
{
	size_t src_idx = 0;
	Source src;
};