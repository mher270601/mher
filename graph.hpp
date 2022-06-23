#ifndef __GRAPH__HPP__
#define __GRAPH__HPP__

#include <iostream>
#include <vector>
#include <utility>
#include <cassert>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <fstream>

template<typename T>
class Graph{
	public:
		Graph(std::string_view filePath) : m_filePath(filePath){};
		//Graph(std::ifstream& graphFile) : m_file(graphFile){};
		Graph() =delete;
		~Graph();
		size_t maxPath() const noexcept;
		void Render() noexcept;
	private:
		using valueType = T;
		using vecType = std::vector<std::pair<valueType, valueType>>;
		using repType = std::vector<std::pair<std::pair<valueType, valueType>, valueType>>;
	
		vecType m_graphVec;
		vecType m_unRepeated;
		vecType m_repeated;
	
		std::string m_filePath;
		std::ifstream m_file;
		size_t maximumPath{0};
	private: // HELPERS
		//std::pair<std::pair<>> longLength();
		std::vector<std::vector<valueType>> roads;
		repType m_repeats;
		void checkSimplicity();
		void m_reverse(std::vector<std::vector<valueType>>& _roads);
		void Print();
		void buildRoads(repType longPath);
		void renderStrings(repType& longPaths);
		size_t currentCount(valueType numb, size_t count = 0);
		void filterRepeats();
		void SepRepeaters();
		std::pair<valueType, valueType> ReadFile();
		void checkFile(/*std::ifstream& file*/);
};  // class Graph

#include "graph.impl.hpp"

#endif // __GRAPH__HPP__
