class Station
{
public:
	const int kDistanceFromOrigin;

	Platform getStandardPlatform();
	Platform getTransitPlatform();
	Train getParkedTrain();
	bool hasStandardPlatform();
	bool hasTransitPlatform();
	bool hasParkedTrain();
	//3 tipi standard, transit, parcheggio

private:
	vector<Train> parked_;
};