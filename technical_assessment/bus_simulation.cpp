#include "libraries.h"
#include "initial_quantities.h"
#include "bus_simulation_functions.h"



int main() {
	std::vector<Bus> buses; 
	Print("Enter Bus Capacity: ");
	int bus_capacity = 1;
	bus_capacity << std::cin.get(); //Users input

	BusesStarter(buses, stops_board, bus_list, initial_occupied_stops, bus_capacity); //Creates bus instances
	AssignStops(stops_passengers, stops, bus_capacity); //Fills the bus stops with passengers who have random destinations


	while (global_timer <= total_simulation_time) { //Simulation Environment
		/*
		for (auto elem : buses) {
			Print("Bus: ", elem.GetName());
		}
		*/
		for (int bus_identifier = 0; bus_identifier < 5; bus_identifier++) {

			// First Bus
			if ((bus_timer[bus_identifier] == 0) && (movement_ready[bus_identifier])) {
				// Only moves when the timer is up and all passengers have boarded and dropped off
				results[bus_identifier].push_back(std::make_pair(buses[bus_identifier].GetCurrentStop(), global_timer));
				MoveBus(buses, bus_list[bus_identifier], stops_board, stops);
				bus_timer[bus_identifier] = bus_travel_time;
			}
			else if (bus_timer[bus_identifier] > 0) {
				//if not decrease the timer and check for passengers
				bus_timer[bus_identifier] --;
			}
			int current_stop = buses[bus_identifier].GetCurrentStop() - 1;

			//drop off
			if ((bus_boarding_timer[bus_identifier] == 0) && (!IsBusEmpty(buses[bus_identifier]))) {
				//each passengers need 10 seconds
				//if bus is not empty and passenger timer is up dropoff next passenger
				DroppingOff(buses[bus_identifier]);
				boarding_status[bus_identifier] = false;
				bus_boarding_timer[bus_identifier] = passenger_boarding_time;
			}
			if ((IsBusEmpty(buses[bus_identifier]) && (stops_passengers[current_stop].empty() || bus_full[bus_identifier]) && (bus_boarding_timer[bus_identifier] == 0))) {
				//if no passengers left to dropoff and bus stop is empty or bus is full proceed to next stop
				//cannot move until passenger boarding time is up
				movement_ready[bus_identifier] = true;
			}

			if (IsBusEmpty(buses[bus_identifier])) {
				//signaling that all passengers are dropped off
				boarding_status[bus_identifier] = true;
			}

			//boarding
			if ((bus_boarding_timer[bus_identifier] == 0) && (!stops_passengers[current_stop].empty()) && (boarding_status[bus_identifier])) {
				//checking if passenger boarding time is up and there are passengers to board
				boarding_status[bus_identifier] = Boarding(buses[bus_identifier], stops, stops_passengers);
				bus_boarding_timer[bus_identifier] = passenger_boarding_time;
				if (!boarding_status[bus_identifier]) {
					bus_full[bus_identifier] = true;
					movement_ready[bus_identifier] = true;
				}
			}

			if (bus_boarding_timer[bus_identifier] > 0) {
				//in contrast with bus timer passenger's is determined by both boarding and dropping off so it cannot be tied to one if-statement
				bus_boarding_timer[bus_identifier] --;
			}
		}


		// Second Bus

		// Third Bus

		// Fourth Bus

		// Fifth Bus

		RandomCrowding(stops_passengers, stops); // adding random passengers at one random bus stop
		global_timer++;
	}

	//opneing/creating file to output results
	std::ofstream result_file;
	result_file.open("results.csv");
	std::vector<int> result_sizes = { int(results[0].size()), int(results[1].size()), int(results[2].size()), int(results[3].size()), int(results[4].size())};

	int result_length = FindMin(result_sizes); // finding the smallest list of entries to avoid accessing unwanted memory

	for (int result_entry = 0; result_entry < result_length; result_entry++) { //writing results to csv file
		for (int bus_entry = 0; bus_entry < 5; bus_entry++) {
			result_file << results[bus_entry][result_entry].first << "," << results[bus_entry][result_entry].second << ",";
		}
		result_file << std::endl;
	}
	result_file.close();

	return 0;
}