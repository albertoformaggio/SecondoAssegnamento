/* @author Michele Rieppi */
#ifndef PLATFORM_H
#define PLATFORM_H

#include "train.h"

class Platform
{
public:

	const bool type;	//0 standard 1 transit


	bool isEmpty();
	void reserve();
	void free();

	~Platform();

protected: 
	Platform(bool t, bool s);

private:
	bool status;		//0 free 1 occupato
};

class transitPlatform : public Platform {

};

class standardPlatform : public Platform {
	void fixSpeed(Train t);
};

#endif
