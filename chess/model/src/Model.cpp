#include "Model.h"
#include "Piece.h"

Model::Model(){
	
}

Model::~Model(){
	
}

void Model::pushMove(Move move){
	history.pushMove(move);
}

Move Model::popMove(){
	return history.popMove();
}

bool Model::isHistoryEmpty(){
	return history.isEmpty();
}

void Model::clearHistory(){
		history.clearMoves();
}

bool Model::saveFile(string filename, stack<PieceStruct> pieces){
	xml.saveChessGame(history.getMoves(),pieces,filename);
}

//loads the file into board and history
//Returnts a list of piece structs that is the current board setup
stack<PieceStruct> Model::loadFile(string filename){
	stack<PieceStruct> current_board;
	current_board.push((PieceStruct){-1,-1,false,false,0,NO_IMAGE});
	return current_board;
}


//Returns whether or not it is Player 1's turn when loading a file
bool Model::isWhiteTurn(){
	
}
