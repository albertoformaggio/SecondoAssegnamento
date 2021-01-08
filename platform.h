/* @author Michele Rieppi */

#include "train.h"

#ifndef platform_h
#define platform_h



class Platform{ //da rivedere i tipi bool

public:

	const bool startFromOrigin; //direzione del binario true parte dall'origine false parte dalla destinazione

	virtual int fixSpeed(const Train& t) const = 0;

	bool isEmpty() { return occupied == true; }	//ritorna true se il binario � libero false altrimenti
	void reserve() { occupied = true; }			//mette il binario occupato
	void free() { occupied = false; }			//libera il binario

	~Platform();

protected: 
	Platform(bool s, bool d) : occupied{ s }, startFromOrigin{ d } {}

	
	bool occupied;		//true occupato false libero
	
	
};

class transitPlatform : public Platform {
public:
	transitPlatform(bool s, bool d);

	int fixSpeed(const Train& t) const override;

};

class standardPlatform : public Platform {
public:
	const int slowSpeed = 80;		//DA CONTROLLARE ED IN CASO INSERIRE IN STATION PER AVERCI ACCESSO DAI METODI TRAIN

	standardPlatform(bool s, bool d);

	int fixSpeed(const Train& t) const override;
};

#endif
