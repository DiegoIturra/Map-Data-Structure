#include "MAP.h"
using namespace std;

static int primos[] = {53,97,193,389,769,1543,3079,6151,12289,24593,49157,98317,196613,393241,786433,1572869,3145739,6291469};

class MapH : public MAP{
	private:
		pair<string,int>* tabla; //tabla original
		pair<string,int>* tablaPtr; //referencia a la tabla actual
		pair<string,int>* tablaAux; //tabla actual al momento de hacer rehashing
		int cantElementos;
		int indicePrimos;
		int tamTabla;
		pair<string,int>* reservarMemoria(int);
		unsigned int hash1(string, int);
		unsigned int hash2(string);
		
	public:
		MapH();
		~MapH();
		void insert(pair<string,int>);
		void erase(string);
		int at(string);
		int size();
		bool empty();
		void print();
};