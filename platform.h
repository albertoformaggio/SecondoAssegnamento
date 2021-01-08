/* @author Michele Rieppi */

#include "train.h"

#ifndef platform_h
#define platform_h



class Platform{ //da rivedere i tipi bool

public:

	virtual int fixSpeed(const Train& t) const = 0;

	bool isEmpty() { return occupied == true; }	//ritorna true se il binario è libero false altrimenti
	void reserve() { occupied = true; }			//mette il binario occupato
	void free() { occupied = false; }			//libera il binario

	~Platform();

protected: 
	Platform(bool s) : occupied{ s } {}

	
	bool occupied;		//true occupato false libero
	
};

class transitPlatform : public Platform {
public:
	transitPlatform(bool s);

	int fixSpeed(const Train& t) const override;

};

class standardPlatform : public Platform {
public:
	const int slowSpeed = 80;		//DA CONTROLLARE ED IN CASO INSERIRE IN STATION PER AVERCI ACCESSO DAI METODI TRAIN

	standardPlatform(bool s);

	int fixSpeed(const Train& t) const override;
};

#endif
