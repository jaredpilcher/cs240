#ifndef HISTORY_GUARD
#define HISTORY_GUARD

#include "Move.h"
#include <stack>
using namespace std;

class History{
	stack<Move> moves;
public:

	History();
	
	~History();
	
	void pushMove(Move move);
	
	Move popMove();
	
	bool isEmpty();
};

#endif
