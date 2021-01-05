/*
	@author Anna Scarpa Falce
*/

#include "train.h"

class RegionalTrain : public train
{
private:
	const int v_max = 160;
	int speed;
	int delay;
	const Station origin;
	const int identifying_number;
public:
	void setSpeed() override;
	void editDelay() override;
	Platform requirePlatform(Station st) override;
	void leaving(Platform pl) override;
};
