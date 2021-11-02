#pragma once
#include "ICommand.h"

class DoNothingCommand : public ICommand
{
public:
	DoNothingCommand() = default;
	void execute() override {}
};

