#pragma once
#include <SFML/Graphics.hpp>
#include "ICommand.h"
#include "ScreenScroller.h"

class MoveViewCommand : public ICommand
{
public:
	MoveViewCommand(ScreenScroller::ViewMovmentDirection initDir, ScreenScroller& initScroller);
	void execute() override;

private:
	ScreenScroller& scroller;
	ScreenScroller::ViewMovmentDirection dirToMoveScreen;
};

