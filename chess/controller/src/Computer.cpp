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
void Computer::makeMove(){
  //~ std::cout << "Making a move!!!!" << std::endl;
  int row = 0;
  int col = 0;
  //~ Piece* piece;
  //~ while(row<=0 || row >=7 || col>=7 || col<=0){
	//~ piece = board->getRandomPiece();
	//~ std::cout << "piece row:" << piece->getRow() << " col: " << piece->getCol() << std::endl;
	//~ //Start here next. WHen the king has only a few moves left, all of the returned moves are -1 -1 for almost all pieces. Why?
	//~ piece->getRandomMove(row, col);
  //~ std::cout << "move row: " << row << " col: " << col << std::endl;
	//~ if(board->checkEOG()){
		//~ std::cout << "Game Over!" << std::endl;
		//~ break;
	//~ }
  //~ }
	//~ std::cout << "after while loop" << std::endl;
  //~ 
	//~ board->handleSelect(piece->getRow(),piece->getCol());
  //~ std::cout << "row: " << row << " col: " << col << std::endl;
  //~ board->handleSelect(row,col);
  while(!(board->handleSelect(row,col))){
		//std::cout << "move row: " << row << " col: " << col << std::endl;
		//std::cout << "rand:" << (rand() % 8) << std::endl;
	  row = (rand() % 8);
	  col = (rand() % 8);
	  if(board->checkEOG()){
		std::cout << "Game Over!" << std::endl;
		break;
	}
		//std::cout << "make move row:" << row << std::endl;
	};
  
}



/**
* Handle when the timeout duration has passed.
*/
void Computer::on_TimerEvent(){
	
}
