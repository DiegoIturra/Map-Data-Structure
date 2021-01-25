#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <time.h>
#include <string>
#include "MapSV.h"
#include "MapH.h"
#include "MapAVL.h"
using namespace std;

int main(){
	MapSV map1; //map con vector
	MapH map2; //map con tabla hash y usando soble hashing
	MapAVL tree; //map con un AVL tree

	int cantDatos,cantDatos2;
	vector< pair<string,int> > datos;
	vector<pair<string,int>> datosAbuscar;
	string clave;
	int valor;

	cin >> cantDatos;
	for(int i=0 ; i<cantDatos ; i++){
		cin >> clave >> valor;
		datos.push_back(make_pair(clave,valor));
	}

	cin >> cantDatos2;
	for(int i=0 ; i<cantDatos2 ; i++){
		cin >> clave >> valor;
		datosAbuscar.push_back(make_pair(clave,valor));
	}

	//tam del vector de datos
	int lenDatos = datos.size();
	double tiempo;
	clock_t start,stop;

	cout << "METODOS DE INSERCION" << endl;

	//timepo insert MapSV
	start = clock();
	for(int i=0 ; i<lenDatos ; i++){
		map1.insert(datos[i]);
	}
	stop = clock();
	tiempo = (double)(stop-start)/CLOCKS_PER_SEC/lenDatos;
	printf("tiempo insert MapSV: %.10f \n",tiempo);

	//tiempo insert MapH
	start = clock();
	for(int i=0 ; i<lenDatos ; i++){
		map2.insert(datos[i]);
	}
	stop = clock();
	tiempo = (double)(stop-start)/CLOCKS_PER_SEC/lenDatos;
	printf("tiempo insert MapH: %.10f \n",tiempo);

	//tiempo insert MapAVL
	start = clock();
	for(int i=0 ; i<lenDatos ; i++){
		tree.insert(datos[i]);
	}
	stop = clock();
	tiempo = (double)(stop-start)/CLOCKS_PER_SEC/lenDatos;
	printf("tiempo insert MapAVL: %.10f \n",tiempo);
	
	cout << "METODOS AT() , PARA CLAVES EXISTENTES" << endl;

	start = clock();
	for(int i=0 ; i<lenDatos; i++){
		map1.at(datos[i].first);
	}
	stop = clock();
	tiempo = (double)(stop-start)/CLOCKS_PER_SEC/lenDatos;
	printf("tiempo at MapSV: %.10f \n",tiempo);

	start = clock();
	for(int i=0 ; i<lenDatos ; i++){
		map2.at(datos[i].first);
	}
	stop = clock();
	tiempo = (double)(stop-start)/CLOCKS_PER_SEC/lenDatos;
	printf("tiempo at MapH: %.10f \n",tiempo);

	start = clock();
	for(int i=0 ; i<lenDatos ; i++){
		tree.at(datos[i].first);
	}
	stop = clock();
	tiempo = (double)(stop-start)/CLOCKS_PER_SEC/lenDatos;
	printf("tiempo at MapAVL: %.10f \n",tiempo);


	cout << "METODOS AT() , PARA CLAVES NO EXISTENTES" << endl;

	int len = datosAbuscar.size();
	start = clock();
	for(int i=0 ; i<len; i++){
		map1.at(datosAbuscar[i].first);
	}
	stop = clock();
	tiempo = (double)(stop-start)/CLOCKS_PER_SEC/len;
	printf("tiempo at MapSV: %.10f \n",tiempo);

	start = clock();
	for(int i=0 ; i<len ; i++){
		map2.at(datosAbuscar[i].first);
	}
	stop = clock();
	tiempo = (double)(stop-start)/CLOCKS_PER_SEC/len;
	printf("tiempo at MapH: %.10f \n",tiempo);

	start = clock();
	for(int i=0 ; i<len ; i++){
		tree.at(datosAbuscar[i].first);
	}
	stop = clock();
	tiempo = (double)(stop-start)/CLOCKS_PER_SEC/len;
	printf("tiempo at MapAVL: %.10f \n",tiempo);

	//tree.print();


	return 0;
}