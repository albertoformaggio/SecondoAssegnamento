/* @author Michele Rieppi*/

class mainStation : public Station {
public:
	mainStation(int distance, std::string name);
	transitPlatform getTransitPlatform(bool direction) override { throw std::exception(); }
};