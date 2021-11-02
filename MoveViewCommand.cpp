#include "MoveViewCommand.h"

MoveViewCommand::MoveViewCommand(ScreenScroller::ViewMovmentDirection initDir, ScreenScroller& initScroller) :
	scroller{ initScroller },
	dirToMoveScreen{ initDir }
{}

void MoveViewCommand::execute()
{
	scroller.addMoveOrderForUpdate(dirToMoveScreen);
}