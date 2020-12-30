class Controller
{
public:
	Controller(string line_descr, string timetable);


private:
	void getStations(string line_descr);
	void getTimetable(string timetable);

	vector<Station> stations_;
	vector<Train> trains_;
	priority_queue<Event> events_;
};

"line_description.txt"
"timetable.txt" ifstream

//treno orario stazione

struct Event 
{
	
};



//quando creo il controller ci saranno solo gli eventi di arrivo (conosco solo quelli grazie al file)
