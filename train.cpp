class Train
{
public:
	void setSpeed();
	void editDelay();
	Platform requirePlatform(Station st);
	void leaving(Platform platform);	//Quando parte semplicemente setta pl a libero 
};