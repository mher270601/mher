#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <vector>

#include "graph.hpp"

//enum EFInput{
//	Console,
//	Default
//};

void getFilePath(int argc, char** argv, std::string& filePath){
	//EFInput fInput;
	std::string FToken;
	switch(argc){
		case 1:
			//fInput = Default;
		break;
		case 3:
			FToken = static_cast<std::string>(argv[1]);
			if(FToken == "-f"){
				filePath = static_cast<std::string>(argv[2]);
			}
			else{
				throw('f');
				//fInput = Console;
			}
		break;
		default:
			throw ('f');
		break;
	}
}

int main(const int argc, char** argv){
	
	std::string filePath = "graph.txt";
	try{
		getFilePath(argc, argv, filePath);
	}catch(char error){
		std::cout << error << " ERROR: Inavlid file path arguments" << std::endl;
		return 0;
	}
	std::ifstream file;
	file.open(filePath);
	//checkFile(file);
	//std::vector<std::pair<unsigned int, unsigned int>> graphs;
	Graph<unsigned int> myGraph(filePath);
	myGraph.Render();
	return 0;
}
