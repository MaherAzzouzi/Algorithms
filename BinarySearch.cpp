#include <iostream>
#include <stack>

using namespace std;

struct node {
	node* right;
	node* left;
	node* p;
	int key;	
};

class BinarySearchTree{
	public:
		node* root = NULL;

		BinarySearchTree();
		void insert(int value);

		void inorderShow(node* x, ostream &o = cout);
		void inorderShowStack(node* x);

		node* search(int value);

		node* maximum(node* x);
		node* minimum(node* x);

		node* successor(node* x);
		node* predecessor(node* x);

		void transplant(node* u, node* v);
		void treeDelete(node* x);

		void searchDelete(int key);

		friend ostream & operator<<(ostream & o, BinarySearchTree bs){
			bs.inorderShow(bs.root, o);
			return o;
		}
};

void BinarySearchTree::searchDelete(int key){
	node* x = search(key);
	if(x)
		treeDelete(x);
}

void BinarySearchTree::treeDelete(node* x){
	if(x->left == NULL)
			transplant(x, x->right);
	else if (x->right == NULL)
			transplant(x, x->left);
	else {
		node* y = minimum(x->right);

		if(y->p != x){
			transplant(y, y->right);
			y->right = x->right;
			y->right->p = y;
		}
		transplant(x, y);
		y->left = x->left;
		y->left->p = y;
	}
}

void BinarySearchTree::transplant(node* u, node* v){
	if(u->p == NULL)
		root = v;
	else if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;

	if(v != NULL)
		v->p = u->p;
}

node* BinarySearchTree::predecessor(node* x){
	if(x->left != NULL)
			return maximum(x->left);
	node* y = x->p;

	while(y != NULL && x == y->left){
		x = y;
		y = y->p;
	}
	
	return y;
}

node* BinarySearchTree::successor(node* x) {
	
		if(x->right != NULL)
				return minimum(x->right);
	
		node* y = x->p;
		while(y != NULL && x == y->right){
			x = y;
			y = y->p;
		}
		return y;
}

node* BinarySearchTree::maximum(node* x) {
	while(x->right != NULL)
			x = x->right;
	return x;
}

node* BinarySearchTree::minimum(node* x) {
	while(x->left != NULL)
			x = x->left;
	return x;
}

node* BinarySearchTree::search(int value) {
	node* x = root;
	while(x != NULL && value != x->key) {
		if(value < x->key)
			x = x->left;
		else
			x = x->right;
	}
	
	return x;
}

void BinarySearchTree::inorderShowStack(node *x){
	stack<node*> s;
	node* current = x;
	bool done=0;

	while(!done){
		if(current != NULL){
				s.push(current);
				current = current->left;
		}
		else
		{
			if(!s.empty()){
				current = s.top();
				s.pop();
				cout << current->key << " ";
				current = current->right;
			} else {
				done = 1;
			}
		}
	}
}

BinarySearchTree::BinarySearchTree(){
	cout << "Welcome to the Binary Search Tree!" << endl;
}

void BinarySearchTree::inorderShow(node* x, ostream & o){
	if(x != NULL){
		inorderShow(x->left);
		o << x->key << " ";
		inorderShow(x->right);
	}
}

void BinarySearchTree::insert(int value){
	node* z = new node();
	z->left = z->right = z->p = NULL;
	z->key = value;
	node* y = NULL;
	node* x = root;
	
	while(x != NULL){
		y = x;
		if(z->key < x->key)
				x = x->left;
		else
				x = x->right;
	}
	
	z->p = y;
	
	// Tree is empty
	if(y == NULL)
			this->root = z;
	else if (z->key < y->key)
			y->left = z;
	else
			y->right = z;
}

int main(){
	BinarySearchTree bs;
	bs.insert(10);
	bs.insert(5);
	bs.insert(4);
	bs.insert(17);
	bs.insert(21);
	bs.insert(16);

	bs.searchDelete(4);
	cout << bs << endl;

}
