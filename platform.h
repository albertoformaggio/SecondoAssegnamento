/* @author Michele Rieppi */

#ifndef platform_h
#define platform_h

#include "train.h"
#include "station.h"

class Platform{ //da rivedere i tipi bool

public:

	virtual int fixSpeed(Train& t) = 0;

	bool isEmpty() { return status == true; }	//ritorna true se il binario è libero false altrimenti
	void reserve() { occupied = true; }			//mette il binario occupato
	void free() { occupied = false; }			//libera il binario

	~Platform();

protected: 
	Platform(bool s) : status{ s } {}

	
	bool occupied;		//true occupato false libero
	
};

class transitPlatform : public Platform {
public:
	transitPlatform(bool s);

	int fixSpeed(Train& t) const override;

};

class standardPlatform : public Platform {
public:
	const int slowSpeed = 80;

	standardPlatform(bool s);

	int fixSpeed(Train& t) const override;
};

#endif
