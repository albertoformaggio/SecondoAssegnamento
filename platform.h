/* @author Michele Rieppi */
#ifndef PLATFORM_H
#define PLATFORM_H

#include "train.h"

class Platform
{
public:
	void fixSpeed(Train t);
	bool isEmpty();
	void reserve();
	void free();

	Platform(bool t, bool s);
	~Platform();

private:
	const bool type;	//0 standard 1 transit
	bool status;		//0 free 1 occupato
};

#endif
