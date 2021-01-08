/* @author Michele Rieppi */

#include "platform.h"

class standardPlatform : public Platform {
public:
	const int slowSpeed = 80;		//DA CONTROLLARE ED IN CASO INSERIRE IN STATION PER AVERCI ACCESSO DAI METODI TRAIN

	standardPlatform(bool s, bool d);

	int fixSpeed(const Train& t) const override;
};
