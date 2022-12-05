#pragma once //Header Gaurd

int PassengerRandomizer(int bus_capacity) { //Return an arbitrary number of passenger to fill a bus stop
	return (rand() % bus_capacity);
}

int StopRandomizer(std::vector<int> stops, int current_stop) { //Picks a random bus stop from our list of stops
	//The stop picked will be assigned as a destination to a passenger
	
	int random_stop = rand() % stops.size();

	while (stops[random_stop] == current_stop) {// avoid picking the current stop
		random_stop = rand() % stops.size();
	}
	return random_stop;
}


//Initialize Bus stops with random number of passengers each having random distenation
void AssignStops(std::vector<std::vector<int>> &stops_passengers, std::vector<int> stops, int passenger_limit) {
	int current_stop;
	//srand(time(0));
	int waiting_passengers;

	for (int stops_iterator = 0; stops_iterator < stops_passengers.size(); stops_iterator++) {
		waiting_passengers = PassengerRandomizer(passenger_limit);
		current_stop = stops[stops_iterator];
		
		for (int passenger_filler = 0; passenger_filler < waiting_passengers; passenger_filler++) {
			stops_passengers[stops_iterator].push_back(StopRandomizer(stops, current_stop));
		}
	}
}


//Used to randomly add one passenger to a random bus stop at a given point in time
void RandomCrowding(std::vector<std::vector<int>>& stops_passengers, std::vector<int> stops) {
	int random_stop = rand() % stops.size();
	std::vector<int>::iterator stop_finder = find(stops.begin(), stops.end(), random_stop);
	int stops_index = std::distance(stops.begin(), stop_finder);
	stops_passengers[stops_index].push_back(StopRandomizer(stops, random_stop));
}


//Marks a bus stop is currently occupied by a bus and updates the stop board
void SpotFiller(std::unordered_map<int, char>& stops_board, int target_stop) {
	std::unordered_map<int, char>::iterator stop_finder = stops_board.find(target_stop);
	if (stop_finder == stops_board.end()) {
		Print("Stop: ", target_stop, " Not found.");
		return;
	}
	stop_finder->second = 'Y';
}


//Marks a bus stop is currently freed by a bus and updates the stop board
void SpotFreer(std::unordered_map<int, char>& stops_board, int target_stop) {
	std::unordered_map<int, char>::iterator stop_finder = stops_board.find(target_stop);
	if (stop_finder == stops_board.end()) {
		Print("Stop: ", target_stop, " Not found.");
		return;
	}
	stop_finder->second = 'N';
}


//Initialize the buses, create instances with appropraie parametes, and group them in a vector.
void BusesStarter(std::vector<Bus>& buses, std::unordered_map<int, char>& stops_board, std::vector<char> bus_list, std::vector<int> initial_occupied_stops, int bus_capacity) {
	
	for (unsigned int bus_list_iterator = 0; bus_list_iterator < bus_list.size(); bus_list_iterator++) {
		std::vector<Bus>::iterator bus_addition = buses.emplace(buses.end(), Bus(bus_list[bus_list_iterator], initial_occupied_stops[bus_list_iterator], bus_capacity));
		SpotFiller(stops_board, initial_occupied_stops[bus_list_iterator]);
	}
}

//Looks up the stops board and check if is currently occupied
bool CheckIfOccupied(char is_occupied) {
	return (is_occupied == 'Y');
}

//Used by MoveBus() to check if the next stop is available to proceed
bool IsLocationAvailable(std::unordered_map<int, char> stops_board, int target_stop) {
	std::unordered_map<int, char>::iterator stops_tracker = stops_board.begin();

	while (stops_tracker != stops_board.end()) {

		if (stops_tracker->first == target_stop && CheckIfOccupied(stops_tracker->second)) {
			return false;
		}
		stops_tracker++;
	}
	return true;
}


//Handles all buses movements and adjusts all parameter according to this movement.
bool MoveBus(std::vector<Bus>& buses, char target_bus, std::unordered_map<int, char>& stops_board, std::vector<int> stops) {
	std::vector<Bus>::iterator bus_finder = buses.begin();
	while (bus_finder != buses.end()) {
		if ((*bus_finder).GetName() == target_bus) {
			break;
		}
		else {
			bus_finder++;
		}
	}
	if (bus_finder == buses.end())
	{
		Print("Bus: ", target_bus, " Not Found.\n");
		return false;
	}
	//Bus current_bus = *bus_finder;

	int current_stop = bus_finder->GetCurrentStop();
	std::vector<int>::iterator stops_iterator = find(stops.begin(), stops.end(), current_stop);
	std::vector<int>::iterator stops_checker = next(stops_iterator);

	if (stops_checker == stops.end()) {
		stops_checker = stops.begin();
	}
	// after finding the bus and the current stop we dereference next stop to check if it is occupied or available
	int next_stop = *(stops_checker);
	
	if (IsLocationAvailable(stops_board, next_stop)) {
		
		SpotFreer(stops_board, current_stop);
		//std::this_thread::sleep_for(std::chrono::seconds(5));
		SpotFiller(stops_board, next_stop);

		bus_finder->UpdateCurrentSop(next_stop);
		bus_finder->UpdateNextStop();
		return true;
	}
	return false;	
}

//Drops off a passenger from a particular bus at their desired destination
void DroppingOff(Bus& target_bus) {
	//used to drop off all passengers at once but then readjusted to only drop off one at a time
	std::vector<int> current_boarded_passengers = target_bus.GetPassengers();
	int current_stop = target_bus.GetCurrentStop();
	std::vector<int>::iterator passenger_dropoff = find(current_boarded_passengers.begin(), current_boarded_passengers.end(), current_stop);
	current_boarded_passengers.erase(passenger_dropoff);
	target_bus.UpdatePassengers(current_boarded_passengers);
	target_bus.SetCurrentCapacity(current_boarded_passengers.size());
}

//Board passengers one at a time and checks the bus maximum capacity
bool Boarding(Bus& target_bus, std::vector<int> stops, std::vector<std::vector<int>>& stops_passengers) {
	//similarly made to board one passenger at a time
	int bus_current_capacity = target_bus.GetCurrentCapacity();
	int bus_max_capacity = target_bus.GetMaxCapacity();
	int current_stop = target_bus.GetCurrentStop();

	std::vector<int>::iterator stop_finder = find(stops.begin(), stops.end(), current_stop);
	int stops_index = std::distance(stops.begin(), stop_finder);

	if (bus_current_capacity == bus_max_capacity) {
		Print("Bus: ", target_bus.GetName(), " is full.\n");
		return false;
	}
	target_bus.AddPassenger(stops_passengers[stops_index].back());
	stops_passengers[stops_index].pop_back();
	target_bus.SetCurrentCapacity(target_bus.GetCurrentCapacity() + 1);
	return true;
}

//check if bus is empty of passengers
bool IsBusEmpty(Bus target_bus) {
	return (target_bus.GetPassengers().empty());
}

//find the minimum number in a given vector
int FindMin(std::vector<int> array) {
	int min = array[0];
	for (auto size : array) {
		if (size < min) {
			min = size;
		}
	}
	return min;
}