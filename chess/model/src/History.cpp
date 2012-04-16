#include "History.h"

History::History(){
	
}

History::~History(){
	
}

void History::pushMove(Move move){
	if(move.isValidMove()) moves.push(move);
}

Move History::popMove(){
	Move move = moves.top();
	moves.pop();
	return move;
}

bool History::isEmpty(){
	return moves.empty();
}

void History::clearMoves(){
	while(!moves.empty()){
		moves.pop();
	}
}

stack<Move> History::getMoves(){
	return moves;
}
