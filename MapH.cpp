#include "MapH.h"
#include <iostream>
#include <iterator>

#define AVAILABLE "AVAILABLE"
#define FREE "FREE"

using namespace std;


MapH::MapH(){
	indicePrimos = 0; //se posiciona en el primer tam
	tamTabla = primos[indicePrimos];
	tabla = reservarMemoria(tamTabla); //asignamos memoria
	tablaPtr = tabla;
	//incializar 
	for(int i=0  ; i<tamTabla ; i++){
		tabla[i].first = FREE;
	}
	cantElementos = 0;
	tablaAux = NULL;
}

MapH::~MapH(){
	delete[] tablaPtr;
}

unsigned int MapH::hash1(string key , int tam){
	unsigned int sum = 0;
	for(int i=0 ; i<key.length() ; i++){
		sum = sum*33 + int(key[i]);
	}
	unsigned int hash = sum % tam;
	return hash;
}

unsigned int MapH::hash2(string k){
	unsigned int hash = 7 - (int(k[0]) % 7);
	return hash;
}

void MapH::insert(pair<string,int> entry){
	unsigned int hash = hash1(entry.first , tamTabla);
	unsigned int hash_2 = hash2(entry.first);
	if(cantElementos < tamTabla){
		int it = 0;
		while(true){
			unsigned int newIndex = (hash + it*hash_2) % tamTabla; //en it=0 solo evalua hash1
			if(tablaPtr[newIndex].first == entry.first) return;
			if(tablaPtr[newIndex].first == FREE || tablaPtr[newIndex].first == AVAILABLE){ 
				tablaPtr[newIndex] = entry;
				break;
			}
			it++;
		}
	}else{
		indicePrimos++;
		int newTam = primos[indicePrimos];
		//hacer rehash
		tablaAux = reservarMemoria(newTam);
		//inicializar la nueva tabla
		for(int i=0 ; i<newTam ;i++){
			tablaAux[i].first = FREE;
		}
		//insertar nuevo elemento
		hash = hash1(entry.first , newTam);
		tablaAux[hash] = entry;
		//para cada elemento de la tabla anterior, hacer rehash
		for(int i=0 ; i<tamTabla ; i++){
			hash = hash1(tablaPtr[i].first , newTam);
			hash_2 = hash2(tablaPtr[i].first);
			int it = 0;
			while(true){
				unsigned int newIndex = (hash + it*hash_2) % newTam; //en it=0 solo evalua hash1
				if(tablaAux[newIndex].first == FREE){
					tablaAux[newIndex] = tablaPtr[i]; //inserta
					break;
				}
				it++;
			}
		}
		//suponiendo que ya se hizo rehash a la nueva tabla
		delete[] tablaPtr;
		tablaPtr = tablaAux;
		tamTabla = newTam;
	}
	cantElementos++;
}
	
void MapH::erase(string key){
	//si esta vacio
	if(cantElementos==0) return;
	else{
		unsigned int hash = hash1(key,tamTabla);
		unsigned int hash_2 = hash2(key);
		int it = 0;
		while(true){
			unsigned int newIndex = (hash + it*hash_2) % tamTabla; //en it=0 solo evalúa hash1
			if(tablaPtr[newIndex].first == key){
				tablaPtr[newIndex].first = AVAILABLE;
				tablaPtr[newIndex].second = 0;
				return;
			}
			if(tablaPtr[newIndex].first == FREE) return;
			it++;
		}
	}
}

int MapH::at(string key){
	//si la tabla esta vacia
	if(cantElementos == 0) return -1;
	//si no esta vacia
	else{
		unsigned int hash = hash1(key,tamTabla);
		unsigned int hash_2 = hash2(key);
		int it = 0;
		while(true){
			unsigned int newIndex = (hash + it*hash_2) %  tamTabla; //en it=0 solo evalúa hash1
			if(tablaPtr[newIndex].first == key) return tablaPtr[newIndex].second;
			if(tablaPtr[newIndex].first == FREE) return -1;
			it++;
		}		
	}
}

int MapH::size(){
	return cantElementos;
}

bool MapH::empty(){
	if(cantElementos > 0) return false;
	return true;
}

pair<string,int>* MapH::reservarMemoria(int tam){
	pair<string,int>* tabla = new pair<string,int>[tam];
	return tabla;
}

void MapH::print(){
	for(int i=0 ; i<tamTabla ; i++){
		cout<<tablaPtr[i].first<< "--->"<<tablaPtr[i].second <<endl;
	}
}