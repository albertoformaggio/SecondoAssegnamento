/* @author Michele Rieppi */
#ifndef platform_h
#define platform_h

#include "station.h"

class Platform //da rivedere i tipi bool
{
public:

	const bool type;	//0 standard 1 transit


	bool isEmpty();
	void reserve();
	void free();

	~Platform();

protected: 
	Platform(bool t, bool s) : type{ t }, status{ s } {}
	bool status;		//0 free 1 occupato
	
};

class transitPlatform : public Platform {
public:
	transitPlatform(bool t, bool s);
};

class standardPlatform : public Platform {
public:
	standardPlatform(bool t, bool s);

	void fixSpeed(Train t);
};

#endif
