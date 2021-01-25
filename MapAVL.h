#include "MAP.h"

using namespace std;

struct TreeNode{
	pair<string,int> data;
	TreeNode* left;
	TreeNode* right;
	int height; 
	int factorBalance;
};

class MapAVL : public MAP{
	private:
		int cantNodos;
		TreeNode* root;
		TreeNode* findMin(TreeNode*);
		TreeNode* eraseNode(TreeNode* , string);
		TreeNode* insertNode(TreeNode* root , pair<string,int>);
		TreeNode* search(TreeNode* root, string);
		void deleteNode(TreeNode*); //borra un solo nodo
		void postOrderDeleteNode(TreeNode* root); //recorrido en post Order para eliminar el arbol
		TreeNode* createNode(pair<string,int>);
		void inorder(TreeNode* root);
		bool existe(TreeNode* root,string);
		int calcularAltura(TreeNode*);
		int getHeight(TreeNode*);
		int getBalance(TreeNode*);
		TreeNode* Balancear(TreeNode*&);
		TreeNode* rotarLeftLeft(TreeNode*);
		TreeNode* rotarLeftRight(TreeNode*);
		TreeNode* rotarRightRight(TreeNode*);
		TreeNode* rotarRightLeft(TreeNode*);

	public:
		MapAVL();
		~MapAVL();
		void insert(pair<string,int>);
		void erase(string); //generico
		int at(string key);
		int size();
		bool empty();
		void print();
};
