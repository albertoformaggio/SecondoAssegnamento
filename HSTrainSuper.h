/*
	@author Anna Scarpa Falce
*/


#ifndef HSTrainSuper_h
#define HSTrainSuper_h

#include "train.h"
class HSTrainSuper : public Train
{
public:
	const int v_max = 300;
	HSTrainSuper(int ID, bool d) : Train(ID, d, v_max) {}
	Platform& requirePlatform(Station* st) override;
};

#endif