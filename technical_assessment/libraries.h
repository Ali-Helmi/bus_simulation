#pragma once //Header Gaurd

//This file includes all necessary libraries and helper functions
#ifdef _WIN32 //check operating system
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdlib>
#include <initializer_list>
#include <ctime>
#include <chrono>
#include <thread>
#include <dos.h>
#include <fstream>
#include <conio.h>
#include <algorithm>

namespace ali {  //my standard library of helper function
	template <class T>
	void Print(T message) { //Different instances of the same function to utilize the ability to change arguments for the same function
		std::cout << message;
	}
	template<typename T, typename... Args>
	void Print(T message, Args... args) { //This function is called recursively for variable number of arguments
		std::cout << message;
		Print(args...);
	}
	template <class T>
	void PrintLine(T message) { //all others are just replicas tailored for different purposes
		std::cout << message << std::endl;
	}
	template<typename T, typename... Args>
	void PrintLine(T message, Args... args) {//I am able to print any type and for any given number of arguments
		std::cout << message << std::endl;
		PrintLine(args...);
	}
	template <typename T>
	void PrintList(std::initializer_list<T> list) {
		for (auto elem : list) {
			std::cout << elem << ", ";
		}
	}
	template <typename T>
	void PrintList(std::vector<T> list) {
		for (auto elem : list) {
			std::cout << elem << ", ";
		}
	}
	//template <typename T>
	void PrintMap(std::unordered_map<int, char> list) {
		for (auto elem : list) {
			std::cout << "(" << elem.first << ", " << elem.second << ")" << std::endl;
		}
	}

	float UnitTime(float time, char from_unit, char to_unit) { //Helps unifying time units

		switch (from_unit) {
		case 'h':
			switch (to_unit) {
			case 's':
				return time * 3600;
			case 'm':
				return time * 60;
			default:
				return 0;
			}
		case 's':
			switch (to_unit) {
			case 'h':
				return time / 3600;
			case 'm':
				return time / 60;
			default:
				return 0;
			}
		case 'm':
			switch (to_unit) {
			case 's':
				return time * 60;
			case 'h':
				return time / 60;
			default:
				return 0;
			}
		default:
			return 0;
		}
	}
}

//In order to be able to use my helper functions
//I like to avoid using generic "using namespaces std;"
using ali::Print;
using ali::PrintLine;
using ali::PrintList;
using ali::PrintMap;
using ali::UnitTime;
