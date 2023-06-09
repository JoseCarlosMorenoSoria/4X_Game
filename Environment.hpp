#ifndef Environment_hpp
#define Environment_hpp
#include <string>
#include <iostream>
#include <vector>



class Environment {
public:
	Environment();
	~Environment();


	static const int columns = 47; //x value
	static const int rows = 26; //y value
	void LoadMap(int arr[rows][columns]);
	void setMap();//for loading a map defined by the function rather than copying an existing map preset

	int map[rows][columns]; //map[y][x] where 0,0 is the top left corner


};

#endif