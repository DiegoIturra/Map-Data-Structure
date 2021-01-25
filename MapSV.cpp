#include "MapSV.h"
#include <iostream>
#include <iterator>
using namespace std;

void MapSV::insert(pair<string,int> entry){
	//si el vec esta vacio
	if(vec.empty()){
		vec.push_back(entry);
		return;
	}
	//si no esta vacia , buscar si existe el elemento en el vec
	else if(busquedaBinaria(entry.first) == -1){
		int it = 0;
		int posAinsertar = 0;
		while(posAinsertar <= vec.size()-1 && vec[it].first < entry.first){
			posAinsertar++;
			it++;
		}
		vec.insert(vec.begin() + posAinsertar , entry);
	}
}
	


int MapSV::busquedaBinaria(string key){
	int mitad;
	int limInf = 0;
	int limSup = vec.size()-1;
	bool encontrado = false;
	while(limInf <= limSup && (!encontrado)){
		mitad = (limInf + limSup) / 2;
		if(vec[mitad].first == key ) encontrado = true;
		else if(vec[mitad].first < key ){
			limInf = mitad + 1;
		}
		else{
			limSup = mitad - 1;
		}
	}
	if(encontrado)
		return mitad;
	else
		return -1;
}

void MapSV::erase(string key){
	int pos = busquedaBinaria(key);
	//si no hay elementos o no esta el elemento
	if(vec.empty() || pos == -1) return;
	//si el elemento existe
	vec.erase(vec.begin()+ pos);
}

int MapSV::at(string key){
	int pos = busquedaBinaria(key);
	if(pos == -1) return -1;
	return vec[pos].second;
}

int MapSV::size(){
	return vec.size();
}

bool MapSV::empty(){
	return vec.empty();
}

void MapSV::print(){
	for(int i=0 ; i<vec.size() ; i++) cout << vec[i].first << "-->" << vec[i].second << endl;
}