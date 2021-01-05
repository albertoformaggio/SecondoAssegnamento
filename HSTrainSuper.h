
#include "train.h"

class HSTrainSuper : public train
{
private:

public:
	void setSpeed() override;
	void editDelay() override;
	Platform requirePlatform(Station st) override;
	void leaving(Platform pl) override;
};

