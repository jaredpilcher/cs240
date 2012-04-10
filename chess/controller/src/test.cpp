#include "UnitTest.h"
#include "Pawn.h"
#include "Board.h"
#include "ChessGuiDefines.h"
#include <iostream>

using namespace std;

int main(){
	Board board(NULL);
	Pawn pawn(0,0,WHITE, NULL, &board, W_PAWN);
	pawn.test(cout);
}
