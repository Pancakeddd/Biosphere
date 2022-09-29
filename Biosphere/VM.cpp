#include "VM.h"

#include <math.h>

double VM::eatStack()
{
	if (stack.size() <= 0)
	{
		return 0.0;
	}
	else {
		auto t = stack.top();
		stack.pop();
		return t;
	}
}

void VM::runNextCommand()
{
	auto current_command = src[src_idx];

	src_idx++;

	switch (current_command.type)
	{
	case NOP:
		break;

	case PUSH_CONSTANT:
		stack.push(current_command.arg1);
		break;

	case PUSH_INPUT:
		stack.push(input[current_command.idx]);
		break;

	case ADD:
		stack.push(eatStack() + eatStack());
		break;

	case SUB:
		stack.push(eatStack() - eatStack());
		break;

	case MUL:
	{
		auto a1 = eatStack();
		auto a2 = eatStack();

		if (_finite(a2) && _finite(a1))
		{
			stack.push(a1 * a2);
		}
		else {
			stack.push(0.0);
		}

		break;
	}

	case DIV:
	{
		auto a1 = eatStack();
		auto a2 = eatStack();

		if (_finite(a2) && _finite(a1) && a1 > 0.0)
		{
			stack.push(a1 / a2);
		}
		else {
			stack.push(0.0);
		}

		break;
	}

	case SET_OUTPUT:
	{
		outputs[current_command.idx] = eatStack();
		break;
	}

	case JUMP:
	{
		src_idx += eatStack();
		break;
	}
	}

	src_idx %= MAX_SRC_SIZE;
}
