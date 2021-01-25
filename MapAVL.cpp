#include "MapAVL.h"
#include <iostream>
#include <algorithm>
using namespace std;

MapAVL::MapAVL(){
	root = NULL; //vacio arbol
	cantNodos = 0; //ningun nodo al comienzo(arbol vacio)
}

MapAVL::~MapAVL(){
	postOrderDeleteNode(root);
}

//elimina el nodo pasado por referencia
void MapAVL::deleteNode(TreeNode* node){
	node->left = NULL;
	node->right = NULL;
	delete node;
}

//recorre el avl en postOrder mientras elimina todos los nodos
void MapAVL::postOrderDeleteNode(TreeNode* root){
	if(root == NULL) return;
	postOrderDeleteNode(root->left);
	postOrderDeleteNode(root->right);
	deleteNode(root);
}


//hallar el nodo con clave minima a partir de un nodo dado
TreeNode* MapAVL::findMin(TreeNode* node){
	while(node->left!= NULL){
		node = node->left;
	}
	return node;																			
}


//calcula la altura del nodo que se pasa por referencia
int MapAVL::calcularAltura(TreeNode* node){
	if(node == NULL) return 0;
	return 1 + max(getHeight(node->left) , getHeight(node->right));
}

//obtiene el campo "height" del nodo pasado por referencia
int MapAVL::getHeight(TreeNode* node){
	if(node != NULL) return node->height;
	return 0;
}

//obtiene el factor de balance del nodo pasado por referencia
int MapAVL::getBalance(TreeNode* node){
	if(node == NULL) return 0;
	return (getHeight(node->left) - getHeight(node->right));
}

//elimina un nodo de forma recursiva bajando por el arbol
TreeNode* MapAVL::eraseNode(TreeNode* node , string key){
	//caso base
	if(node==NULL) return node;
	string keyRoot = node->data.first;
	if(key < keyRoot) node->left = eraseNode(node->left , key);
	else if(key > keyRoot) node->right = eraseNode(node->right , key);
	else{
		//se encontro la clave a borrar
		//caso 1 : no tiene hijos
		if(node->left == NULL && node->right == NULL){
			node = NULL;
			delete node;
			return node;
		}
		//caso
		else if(node->left == NULL){
			TreeNode* aux = node;
			node = node->right;
			aux = NULL;
			delete aux;
			return node;
		}
		else if(node->right == NULL){
			TreeNode* aux = node;
			node = node->left;
			aux = NULL;
			delete aux;
			return node;
		}
		//caso 3 : tiene 2 hijos
		else{
			TreeNode* aux = findMin(node->right);
			node->data = aux->data;
			node->right = eraseNode(node->right , aux->data.first);
		}
	}
	node->height = calcularAltura(node);
	node->factorBalance = getBalance(node);
	node = Balancear(node);
	return node;
}


//buscar y retorna un nodo
TreeNode* MapAVL::search(TreeNode* root , string key){
	//caso base
	if(root == NULL) return NULL;
	string keyRoot = root->data.first;
	if(keyRoot == key) return root;
	else{
		if(key < keyRoot){
			return search(root->left , key);
		}
		else{
			return search(root->right , key);
		}
	} 
}

//recorrido en inorder del AVL, para mostrar info
void MapAVL::inorder(TreeNode* root){
	if(root != NULL){
		inorder(root->left);
		cout << root->data.first << "--> " << root->data.second;
		cout <<"  -altura: "<< root->height<<"  -balance: "<<root->factorBalance<<endl;
		inorder(root->right); 
	}
}

//verifica si una clave existe en el AVL
bool MapAVL::existe(TreeNode* root,string key){
	//casos base
	if(root == NULL) return false;
	if(root->data.first == key) return true;
	string keyRoot = root->data.first;
	if(key < keyRoot){
		return existe(root->left , key);
	}else{
		return existe(root->right , key);
	}
}

//crea y retorna un nodo
TreeNode* MapAVL::createNode(pair<string,int> entry){
	TreeNode* newNode = new TreeNode();
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->data = entry;
	newNode->height = 1;
	return newNode;
}

//inserta un nodo de forma recursiva , bajando por el arbol
TreeNode* MapAVL::insertNode(TreeNode* root , pair<string,int> entry){
	//caso base
	if(!root){
		return createNode(entry);
		}else{
			//verificar si es mayor o menor a la raiz o si ya existe en el arbol
			string keyRoot = root->data.first;
			if(entry.first < keyRoot){
				root->left = insertNode(root->left,entry);
			}else if(entry.first > keyRoot){
				root->right = insertNode(root->right,entry);
			}else return root;
		}

	root->height = calcularAltura(root);
	root->factorBalance = getBalance(root);
	root = Balancear(root);

	return root;
}


//balancear los nodos , si su factor de balance esta fuera de [-1,1]
TreeNode* MapAVL::Balancear(TreeNode*& node){
	if(node != NULL){
		int balance = node->factorBalance;
		if(balance > 1){
			int balanceLeft = getBalance(node->left); 
			if(balanceLeft > 0){
				node = rotarLeftLeft(node);
			}else{
				node = rotarLeftRight(node);
			}
		}else if(balance < -1){
			int balanceRight = getBalance(node->right);
			if(balanceRight > 0){
				node = rotarRightLeft(node);
			}else{
				node = rotarRightRight(node);
			}
		}	
	}
	return node;
}

//rotacion left-left
TreeNode* MapAVL::rotarLeftLeft(TreeNode* node){
	TreeNode* aux = node->left;
	node->left = aux->right;
	aux->right = node;

	node->height = calcularAltura(node);
	aux->height = calcularAltura(aux);

	node->factorBalance = getBalance(node);
	aux->factorBalance = getBalance(node);

	return aux;
}

//rotacion right-right
TreeNode* MapAVL::rotarRightRight(TreeNode* node){
	TreeNode* aux = node->right;
	node->right = aux->left;
	aux->left = node;

	node->height = calcularAltura(node);
	aux->height = calcularAltura(aux);

	node->factorBalance = getBalance(node);
	aux->factorBalance = getBalance(aux);

	return aux;
}

//rotacion left-right
TreeNode* MapAVL::rotarLeftRight(TreeNode* node){
	TreeNode* aux = node->left;
	node->left = aux->right;
	aux->right = aux->right->left;
	node->left->left = aux;
	aux->height = calcularAltura(aux);
	aux->factorBalance = getBalance(aux);
	return rotarLeftLeft(node);
}

//rotacion right-left
TreeNode* MapAVL::rotarRightLeft(TreeNode* node){
	TreeNode* aux = node->right;
	node->right = aux->left;
	aux->left = aux->left->right;
	node->right->right = aux;
	aux->height = calcularAltura(aux);
	aux->factorBalance = getBalance(aux);
	return rotarRightRight(node);
}

//insertar entrada
void MapAVL::insert(pair<string,int> entry){
	root = insertNode(root,entry);
	cantNodos++;
}

//devuelve tam del AVL
int MapAVL::size(){
	return cantNodos;
}

//devuelve true o false si el arbol esta vacio o no
bool MapAVL::empty(){
	if(cantNodos) return false;
	return true;
}

//elimina una clave del AVL
void MapAVL::erase(string key){
	if(existe(root,key)){
		root = eraseNode(root,key);	
		cantNodos--;
	}
}

//retorna valor asociado a una clave
int MapAVL::at(string key){
	TreeNode* node = search(root,key);
	if(!node) return -1;
	return node->data.second;
}

//muestra la info del AVL en orden ascendente
void MapAVL::print(){
	inorder(root);
}

