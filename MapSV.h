#include "MAP.h"
#include <vector>
using namespace std;

class MapSV : public MAP{
	private:
		vector< pair<string,int> > vec;
		int busquedaBinaria(string key);
		
	public:
		void insert(pair<string,int> entry);
		void erase(string key);
		int at(string key);
		int size();
		bool empty();
		void print();
};