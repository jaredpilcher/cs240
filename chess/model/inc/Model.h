#ifndef MODEL_GUARD
#define MODEL_GUARD

#include "History.h"
#include "XMLIO.h"

class Model{
	History history;
public:

	Model();
	
	~Model();
	
	void pushMove(Move move);
	
	Move popMove();
	
	bool isHistoryEmpty();
	
};

#endif
