#include "Computer.h"
#include "Board.h"

/**
* Constructor
*/
Computer::Computer(){
	
}

/**
* Destructor
*/
Computer::~Computer(){
	
}

/**
* Indicate to the player that the user clicked on the given
* row and column with the mouse.
*/
void Computer::on_CellSelected(int row, int col, int button){
	
}

/**
* Instructs player to make a move 
*/
int Computer::makeMove(Move& move){
  int row = 0;
  int col = 0;
  int select_return = NO_MOVE;
  while(select_return==NO_MOVE){
	  row = (rand() % 8);
	  col = (rand() % 8);
	  if(board->checkEOG()){
		break;
	   }
	   select_return = board->handleSelect(row,col,move);
  }
  return select_return;
}



/**
* Handle when the timeout duration has passed.
*/
void Computer::on_TimerEvent(){
	
}
