/* @author Michele Rieppi*/

#ifndef parkPlatform_h
#define parkPlatform_h

#include "platform.h"

class parkPlatform : public Platform {
public:
	parkPlatform(bool s, bool d);
	int fixSpeed(const Train& t) const override;
};
#endif