/*
	@author Anna Scarpa Falce
*/
#include "train.h"

class HSTrain : public train
{
private:

public:
	void setSpeed() override;
	void editDelay() override;
	Platform requirePlatform(Station st) override;
	void leaving(Platform pl) override;
};

