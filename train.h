class Train
{
public:
	void setSpeed();
	void editDelay();
	Platform requirePlatform(Station st);
	void leaving(Platform pl);	//Quando parte semplicemente setta pl a libero 
};
