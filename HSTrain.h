/*
	@author Anna Scarpa Falce
*/

#ifndef HSTrain_h
#define HSTrain_h

#include "train.h"

class HSTrain : public Train
{
public:
	//const int v_max = 240;
	HSTrain(int ID, bool d) : Train(ID, d, 240) {}
	Platform& requirePlatform(Station* st) override;
};

#endif
