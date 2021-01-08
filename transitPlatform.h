/* @author Michele Rieppi */

#ifndef transitPlatform_h
#define transitPlatform_h

#include "platform.h"

class transitPlatform : public Platform {
public:
	transitPlatform(bool s, bool d);

	int fixSpeed(const Train& t) const override;

};
#endif