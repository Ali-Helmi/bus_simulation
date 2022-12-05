#pragma once

//Bus class that handles all bus-related information
class Bus {
private: //private variables to prevent misuse and unwanted changes
	char _name;
	int _max_capacity, _current_capacity;
	int _current_stop = 0;
	int _next_stop = 0;
	std::vector<int> _passengers;

	int _boarding_time = 10;
	int _travel_time = 300;

public: //include contructors, dconstructors, and needed functions
	Bus() {
		_name = 'Z';
		_max_capacity = 0;
		_current_capacity = 0;
	}
	Bus(char name) { _name = name; _max_capacity = 0; _current_capacity = 0; }
	Bus(char name, int stop, int cap) { 
		_name = name; 
		_current_stop = stop;
		_current_capacity = 0;
		_max_capacity = cap;
		if (_current_stop == 10) { 
			_next_stop = 1; 
		}
		else { 
			_next_stop = _current_stop + 1; 
		}
	}
	//Function to manipulate each instance of bus to suit the simulation uses
	void SetName(char name) { _name = name; }
	void SetMaxCapacity(int cap) { _max_capacity = cap; }
	void SetCurrentCapacity(int cap) { _current_capacity = cap; }
	void ResetTravelTime() { _travel_time = 300; }
	void ResetBoardingTime() { _travel_time = 10; }
	void SetTravelTime(int time) { _travel_time = time; }
	void SetBoardingTime(int time) { _travel_time = time; }
	
	void UpdateCurrentSop(int current) { _current_stop = current; }
	void UpdateNextStop() { if (_current_stop == 10) { _next_stop = 1; } else { _next_stop = _current_stop + 1; } }
	void AddPassenger(int destination) { _passengers.push_back(destination); }
	void UpdatePassengers(std::vector<int> passengers) { _passengers = passengers; }

	char GetName() { return _name; }
	int GetMaxCapacity() { return _max_capacity; }
	int GetCurrentCapacity() { return _current_capacity; }
	int GetCurrentStop() { return _current_stop; }
	int GetNextStop() { return _next_stop; }
	std::vector<int> GetPassengers() { return _passengers; }
	int GetTravelTime() { return _travel_time; }
	int GetBoardingTime() { return _travel_time; }

	bool operator== (char new_name) { return this->_name == new_name; } //Operator for comparing bus names

	~Bus() {}
};

//std::vector<int> stops = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int max_passengers_per_stop = 0; //vector 
int min_passengers_per_stop = 0; //random introduction at given point in time

std::vector<int> stops = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };



std::vector<std::vector<int>> stops_passengers(10, std::vector<int>(0));
//hash map will only have 10 keys which are the stops
//at each stop there is a number of people each represented in an index
//the value at that index will be their bus stop destination


std::unordered_map<int, char> stops_board {
	{stops[0], 'N'},
	{stops[1], 'N'},
	{stops[2], 'N'},
	{stops[3], 'N'},
	{stops[4], 'N'},
	{stops[5], 'N'},
	{stops[6], 'N'},
	{stops[7], 'N'},
	{stops[8], 'N'},
	{stops[9], 'N'}
};

//Manual's pre-defined parameters
int global_timer = 0;  //every iteration is one second.
int total_simulation_time = 28800;  //Equates to 8 hours
int passenger_boarding_time = 10;  //10 seconds
int bus_travel_time = 300;  //5 minutes

std::vector<char> bus_list = { 'A', 'B', 'C', 'D', 'E' }; //Bus names mereley for distinguishing
std::vector<int> initial_occupied_stops = { 1, 3, 5, 7, 9 }; //Initial positions for the buses respectively

// timers and state holders to be used during the mock simulation
std::vector<int> bus_timer = { 0, 0, 0, 0, 0 };
std::vector<int> bus_boarding_timer = { 0, 0, 0, 0, 0 };
std::vector<bool> movement_ready = { false, false, false, false, false };
std::vector<bool> boarding_status = { false, false, false, false, false };
std::vector<bool> bus_full = { false, false, false, false, false };

std::pair<int, int> empty_pair = { 0, 0 };
std::vector<std::vector<std::pair<int, int>>> results = { {empty_pair}, {empty_pair}, {empty_pair}, {empty_pair}, {empty_pair} };
