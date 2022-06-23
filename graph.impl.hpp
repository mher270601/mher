#ifndef __GRAPH__IMPL__HPP__
#define __GRAPH__IMPL__HPP__

#include <algorithm>
#include <utility>
#include <cstring>
#include <sstream>
#include <fstream>
#include <string>
#include <limits>
#include <thread>

template <typename T>
inline size_t Graph<T>::maxPath() const noexcept{
	return maximumPath;
} // maxPath

template <typename T>
void Graph<T>::checkSimplicity(){
	vecType tempGraph = m_graphVec;
	while(tempGraph.size() != 1){
		for(size_t i = 0; i < tempGraph.size()-1; ++i){
			if(tempGraph[i].second == tempGraph[tempGraph.size()-1].second){
				std::cerr << "Graph is not simple !!!" << std::endl;
				throw('g');
			}
		}
		tempGraph.pop_back();	
	}
	std::cout << "Graph is simple" << std::endl;
	std::this_thread::sleep_for (std::chrono::seconds(1));
} // checkSimplicity

template <typename T>
void Graph<T>::SepRepeaters(){
	m_unRepeated = m_graphVec;
	for(size_t i = 0; i < m_graphVec.size()-1; ++i){
		bool cur = false;
		for(size_t j = i+1; j < m_graphVec.size(); ++j){
			if(m_graphVec[i].first == m_graphVec[j].first){
				cur = true;
				std::cout << m_graphVec[i].first << " " << m_graphVec[i].second << " Matched " << std::endl;
				std::cout << m_graphVec[j].first << " " << m_graphVec[j].second << " has repeated" << std::endl;
	
				m_repeated.push_back(m_graphVec[j]);
				
				for(size_t k = j; k < m_graphVec.size()-1; ++k){
					m_graphVec[k].swap(m_graphVec[k+1]);
				}
				m_graphVec.pop_back();
			}	
		}
		if(cur){
			m_repeated.push_back(m_graphVec[i]);
			for(size_t k = i; k < m_graphVec.size()-1; ++k){
				m_graphVec[k].swap(m_graphVec[k+1]);
			}
			m_graphVec.pop_back();
		}
	}
	std::cout << "__ REPEATED __  ճյուղավորվողներ" << std::endl;
	for(const auto& elem : m_repeated){
		std::cout << elem.first << " " << elem.second << std::endl;
	}
	m_unRepeated.swap(m_graphVec);
	std::cout << "__ VECTOR __  ընդհանուր" << std::endl;
	for(const auto& elem : m_graphVec){
		std::cout << elem.first << " " << elem.second << std::endl;
	}

	std::cout << "__ UNREPEATED __  չճյուղավորվողներ" << std::endl;
	for(const auto& elem : m_unRepeated){
		std::cout << elem.first << " " << elem.second << std::endl;
	}
	filterRepeats();
} // SepRepeaters

template <typename T>
size_t Graph<T>::currentCount(valueType numb, size_t count){
	for(size_t i = 0; i < m_unRepeated.size(); ++i){
		if(numb == m_unRepeated[i].first){
			++count;
			currentCount(m_unRepeated[i].second, count);
		}
	}
	return count;
} // currentCount

template <typename T>
void Graph<T>::m_reverse(std::vector<std::vector<valueType>>& _roads){
	for(size_t i = 0; i < _roads.size(); ++i){
		std::reverse(_roads[i].begin(), _roads[i].end());
	}	
} // m_reverse

template <typename T>
void Graph<T>::Print(){
	size_t count{0};
	m_reverse(roads);
	for(size_t i = 0; i < roads.size()-1; ++i){
		if(roads[i+1].size() > roads[i].size()){
			count = i + 1;
		}
	}
	std::cout << "__ ANSWER __  առավելագույն երկարությունը" << std::endl;
	for(size_t i = 0; i < roads[count].size(); ++i){
		std::cout << roads[count][i] << " ";
	}
	std::cout << "\n" << "Size = " << roads[count].size() - 1 << std::endl;

} // Print

template <typename T>
void Graph<T>::buildRoads(repType longPath){
	renderStrings(longPath);
	valueType startPoint = m_graphVec[0].first;
	while(longPath.size() != 0){
		std::vector<valueType> road;
		road.push_back(longPath[0].first.first);
		road.push_back(longPath[0].first.second);
		size_t bindCounts{longPath[0].second-1};
		size_t binds{longPath[0].second};
		while(bindCounts != 0){
			for(size_t i = 0; i < m_unRepeated.size(); ++i){
				if(m_unRepeated[i].first == road[road.size()-1]){
					road.push_back(m_unRepeated[i].second);
					//break;
				}
			}
			--bindCounts;
			std::reverse(road.begin(), road.end());
		}
		valueType cur; 
		if(cur == startPoint){
			++cur;
		}
		while(cur != startPoint && road[road.size()-1] != startPoint){
			for(size_t i = 0; i < m_graphVec.size(); ++i){
				if(m_graphVec[i].second == road[road.size()-1]){
					road.push_back(m_graphVec[i].first);
					cur = m_graphVec[i].first;
					break;
				}
			}
		}
		roads.push_back(road);
		for(size_t i = 0; i < longPath.size()-1; ++i){
			longPath[i].swap(longPath[i+1]);
		}
		longPath.pop_back();
	}
	std::cout << "__ ROADS __  ամենաերկար ճյուղավորվողների երկարությունները" << std::endl;
	for(size_t i = 0; i < roads.size(); ++i){
		for(size_t j = 0; j < roads[i].size(); ++j){
			std::cout << roads[i][j] << " ";
		}
		std::cout << std::endl;
	}
	Print();

} // buildRoads

template <typename T>
void Graph<T>::renderStrings(repType& longPath){
	valueType val = longPath[0].first.first;
	std::string expr = std::to_string(val);
	for(size_t i = 0; i < m_unRepeated.size(); ++i){
		if(m_unRepeated[i].first == longPath[0].first.second){
			valueType m_first = m_unRepeated[i].first;
			valueType m_second = m_unRepeated[i].second;
			expr = expr + " " + std::to_string(m_first) + " " + std::to_string(m_second);
		}
	}
} // renderStrings

template <typename T>
void Graph<T>::filterRepeats(){
	repType length; // not long repeats / in the end
	repType longPath; // long repeats
	repType tempLength; // full repeats
	while(m_repeated.size() != 0){
		valueType repNumber = m_repeated[m_repeated.size()-1].first;
		std::vector<valueType> curSize;
		size_t stepCounts{0};
		while(m_repeated[m_repeated.size()-1].first == repNumber){
			//std::cout << "WHILED" << std::endl;
			++stepCounts;
			size_t curr = currentCount(m_repeated[m_repeated.size()-1].second);
			//std::cout << "cur = " << curr << ", stepCounts = " << stepCounts << std::endl;
			length.push_back(std::make_pair(m_repeated[m_repeated.size()-1], stepCounts + curr));
			tempLength.push_back(std::make_pair(m_repeated[m_repeated.size()-1], stepCounts + curr));
			m_repeated.pop_back();
			stepCounts = 0;
		}
		size_t maxIndx{0};
		for(size_t i = 1; i < length.size(); ++i){
			if(length[i].second > length[maxIndx].second){
				maxIndx = i;
			}
		}
		longPath.push_back(length[maxIndx]);
		length.clear();
	}
	std::cout << "__ Rep length count __  ճյուղավորվողները ըստ իրենց երկարության" << std::endl;
	for(const auto& elem : tempLength){
		std::cout << elem.first.first << " " << elem.first.second << " = " << elem.second << std::endl;
	}
	std::cout << "__ Long length count __ ամենաերկար ճյուղավորվածները" << std::endl;
	for(const auto& elem : longPath){
		std::cout << elem.first.first << " " << elem.first.second << " = " << elem.second << std::endl;
	}
	buildRoads(longPath);
} // filterRepeats

template <typename T>
void Graph<T>::checkFile(){
	m_file.open(m_filePath);
	if(!m_file){
		std::cerr << "Can't open the file" << std::endl;
		throw('g');
	}
} // checkFile

template <typename T>
std::pair<T, T> Graph<T>::ReadFile(){
	valueType temp1{0};
	valueType temp2{0};
	std::string lineExpr;
	std::getline(m_file, lineExpr);
	std::istringstream lStream(lineExpr);
	std::string cur = "0";
	
	lStream >> cur;
	int curVal1 = std::stoi(cur);
	temp1 = curVal1;
	
	lStream >> cur;
	int curVal2 = std::stoi(cur);
	temp2 = curVal2;
	
	return std::make_pair(temp1, temp2);
} // ReadFile

template <typename T>
void Graph<T>::Render() noexcept{
	std::string curExpr;
	checkFile();
	while(!m_file.eof()){
		std::pair<valueType, valueType> curPair = ReadFile();
		if(!m_file.eof()){
			m_graphVec.push_back(curPair);
		}
	}
	checkSimplicity();
	std::cout << "__ VECTOR __" << std::endl;
	for(const auto& elem : m_graphVec){
		std::cout << elem.first << " " << elem.second << std::endl;
	}
	SepRepeaters();
} // Render

template <typename T>
Graph<T>::~Graph(){}

#endif // __GRAPH__IMPL__HPP__
