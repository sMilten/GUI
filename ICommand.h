#pragma once
class ICommand
{
public:
	virtual void execute() {}
	virtual ~ICommand();
};

