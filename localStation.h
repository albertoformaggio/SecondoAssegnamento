/* @author Michele Rieppi*/

class localStation : public Station {
public:
	localStation(int distance, std::string name);

	void addTransitPlatform(const transitPlatform track) { transitPlatforms.push_back(track); }

	transitPlatform getTransitPlatform(bool direction) override;
};