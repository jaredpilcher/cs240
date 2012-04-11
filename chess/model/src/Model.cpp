#include "Model.h"

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
