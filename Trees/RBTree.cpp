#include <iostream>
using namespace std;

#define RED 0x0
#define BLACK 0x1

struct node {
	node* left;
	node* right;
	node* p;
	int c;
	int key;
};

class RBTree{
	public:
		node* nil;
		node* root = NULL;

		RBTree(){
		   	nil = new node;
			nil->c = BLACK;
		}

		void left_rotate(node* x);
		void right_rotate(node* x);
		void insert(int);
		void insert_fixup(node*);
		void delete_node(node *);
		void delete_fixup(node*);
		void transplant(node*, node*);
		node* minimum(node*);
		node* maximum(node*);
		node* search(int key);
		void inorder_print(node* x);

};

void RBTree::inorder_print(node* x){
	if(x!=nil){
		inorder_print(x->left);
		cout << x->key << " ";
		inorder_print(x->right);
	}
}

node* RBTree::search(int key){
	node* x = root;
	while ( x != nil && x->key != key ) {
		if(x->key < key)
			x = x->right;
		else
			x = x->left;
	}

	return x;

}

node* RBTree::maximum(node* x){
	while(x!= NULL && x->right != nil){
		x = x->right;	
	}
	return x;
}

node* RBTree::minimum(node* x){
	while(x != NULL && x->left != nil){
		cout << x-> key << endl;
		x = x->left;	
	}
	return x;
}


// The running time is O(lgn)
// Case 2 is the only case when we will repeat the loop.
void RBTree::delete_fixup(node* x){
	if(x->p == nil){
		return;
	}
	while(x != root && x->c == BLACK){
		// Here we check if x is a left or right child
		// of its parent.
		if(x == x->p->left){
			// The sibling can never be nil
			node* sibling = x->p->right;
			// This is case 1, when the sibling is red
			// the children of the sibling must be red
			// so we can switch colors and perform left rotation
			// on the parent of x.
			// Now we converted this case to into case 2,3 or 4.
			// 2,3 and 4 cases occur when the sibling is black, but we
			// can differentiate them upon the color of the sibling's
			// children.
			if (sibling->c == RED){
				sibling->c = BLACK;
				x->p->c = RED;
				left_rotate(x->p);
				sibling = x->p->right;
			}
			// This is case 2.
			// The sibling along with all its childrens are black.
			// We just colot the sibling red, and iterate for the parent.
			if (sibling->left->c == BLACK && 
				sibling->right->c == BLACK)
			{
				sibling->c = RED;
				x = x->p;
			}

			else {
					// Case 3.
					// sibling is black, sibling->right is also black
					// but sibling->left is red.
					// We switch the colors of the sibling and it's left child
					// and we peform a right rotation on the sibling.
					// We now transformed this case into case 4.
					if (sibling->right->c == BLACK){
					sibling->left->c = BLACK;
					sibling->c = RED;
					right_rotate(sibling);
					sibling = x->p->right;
				
			}
				// Case 4.
				// sibling is black but sibling->right is red.
				// sibling will take the color of its parent
				// parent will become black long with the sibling right child.
				// we perform rotation on the sibling parent.
				// and as this is a terminating case we make x = root
				// just to get out the loop.
				sibling->c = x->p->c;
				x->p->c = BLACK;
				sibling->right->c = BLACK;
				left_rotate(x->p);
				x = root;
			}

		} else {
			// Here we just left to tighr, and right to left (in rotations too).
			if(x == x->p->right){

				node* sibling = x->p->left;
				if(sibling->c == RED){
					// case 1
					sibling->c = BLACK;
					x->p->c = RED;
					right_rotate(x->p);
					sibling = x->p->left;
				}
				if (sibling->left->c == BLACK && 
					sibling->right->c == BLACK)
				{
					// case 2
					sibling->c = RED;
					x = x->p;
				}
					
				else{
					if (sibling->left->c == BLACK)
					{
						// case 3
						sibling->right->c = BLACK;
						sibling->c = RED;
						left_rotate(sibling);
						sibling = x->p->left;
					}
					
				// case 4
				sibling->c = x->p->c;
				x->p->c = BLACK;
				sibling->left->c = BLACK;
				right_rotate(x->p);
				x = root;
			}
				
			}
		}
	}
	// The loop will terminate here. (or not even start is some situations)
	// The the node that will replace the inorder successor is either red
	// or it's the root itself, we remove the extra-blackness by coloring it
	// black only.	
	x->c = BLACK;
}

void RBTree::transplant(node* u, node* v){
	if(u->p == nil)
			root = v;
	else if (u == u->p->left) {
		u->p->left = v;
	} else {
		u->p->right = v;
	}

	v->p = u->p;
}


void RBTree::delete_node(node* z){
	node* x;
	node* y = z;
	int y_original_color = y->c;

	if(z->left == nil){
		x = z->right;
		transplant(z, z->right);
	} else if (z->right == nil) {
		x = z->left;
		transplant(z, z->left);
	} else {
		y = minimum(z->right);
		y_original_color = y->c;
		x = y->right;

		if(y->p == z){
			x->p = y;
		} else {
			transplant(y, y->right);
			y->right = z->right;
			y->right->p = y;
		}

		transplant(z, y);
		y->left = z->left;
		y->left->p = y;
		y->c = z->c;
	}
	
	if(y_original_color == BLACK){
		delete_fixup(x);	
	}

}

void RBTree::insert_fixup(node* z){	
	node* y;

	while(z->p->c == RED){
		if(z->p == z->p->p->left){
			y = z->p->p->right;
			if(y->c == RED){
				// case 1
				z->p->c = BLACK;
				y->c = BLACK;
				z->p->p->c = RED;
				z = z->p->p;
			} else {
				if (z == z->p->right){
				// case 2
				z = z->p;
				left_rotate(z);
				}
			
				// case 3
				z->p->c = BLACK;
				z->p->p->c = RED;
				right_rotate(z->p->p);
		}
	}
	else
	{
		if(z->p == z->p->p->right){
			y = z->p->p->left;
			if(y->c == RED){
				z->p->c = BLACK;
				y->c = BLACK;
				z->p->p->c = RED;
				z = z->p->p;
			} else {
				if (z == z->p->left){
					z = z->p;
					right_rotate(z);
				}
				
				z->p->c = BLACK;
				z->p->p->c = RED;
				left_rotate(z->p->p);
				}
			}	
		}
	}

	root->c = BLACK;
}

void RBTree::insert(int key){
	node* z = new node;
	z->key = key;

	node* y = nil;
	node* x = root;
	while(x && x != nil){
		y = x;
		if(z->key < x->key)	{
			x = x->left;
		} else {
			x = x->right;
		}
	}

	z->p = y;
	if(y == nil){
		root = z;
	}
	else if (z->key < y->key){
		y->left = z;
	} else {
		y->right = z;
	}

	z->left = nil;
	z->right = nil;
	z->c = RED;
	insert_fixup(z);
}

void RBTree::left_rotate(node* x){
	node* y = x->right;
	x->right = y->left;
	if(y->left != nil){
		y->left->p = x;
	}

	y->p = x->p;

	if(x->p == nil){
		root = y;
	} else if (x == x->p->left) {
		x->p->left = y;
	} else {
		x->p->right = y;
	}
	y->left = x;
	x->p = y;
}

void RBTree::right_rotate(node* y){
	node* x = y->left;
	y->left = x->right;

	if(x->right != nil){
		x->right->p = y;
	}

	x->p = y->p;
	
	if(y->p == nil)
		root = x;
	else if (y->p->left == y){
		y->p->left = x;
	} else {
		y->p->right = x;
	}

	x->right = y;
	y->p = x;
}

int main(){
	RBTree rb;
	for(int i=1; i<=100; i++){
		rb.insert(i);
		cout << i << " inserted!" << endl;
	}
	
	node* k;
	k = rb.search(59);
	rb.delete_node(k);
	rb.inorder_print(rb.root);
	cout << "The root " << rb.root->key << endl;
	return 0;
}
