#ifdef _RBTREE_H_
#include "rbtree.h"
#include <iostream>

using namespace std;


template <typename T>
RBTree<T>::RBTree() {
	size = 0;
	root = NULL;
}

template <typename T>
RBTree<T>::RBTree(const RBTree<T>& rbtree) {
	size = 0;
	root = NULL;
	CopyTree(rbtree.root, NULL);
}

template <typename T>
RBTree<T>::~RBTree() {
	RemoveAll();
}

template <typename T>
RBTree<T>& RBTree<T>::operator=(const RBTree<T>& rbtree) {
	if (this != &rbtree) {
		RemoveAll();
		size = 0;
		root = NULL;
		CopyTree(rbtree.root, NULL);
	}
	
	return *this;
}

// Calls BSTInsert and then performs any necessary tree fixing.
// If item already exists, do not insert and return false.
// Otherwise, insert, increment size, and return true.
template <typename T>
bool RBTree<T>::Insert(T item) {
	if (Find(item) != NULL) {
		return false;
	}

	else {
		Node<T>* newNode = BSTInsert(item);
		size++;
		newNode->is_black = false;

		while (newNode != root && newNode->p->is_black == false) {
			if (newNode->p == newNode->p->p->left) {
				Node<T>* uncle = newNode->p->p->right;
				if (uncle != NULL) {
					if (uncle->is_black == false) {
						newNode->p->is_black = true;
						uncle->is_black = true;
						newNode->p->p->is_black = false;
						newNode = newNode->p->p;
					}

					else {
						if (newNode == newNode->p->right) {
							newNode = newNode->p;
							RotateLeft(newNode);
						}

						newNode->p->is_black = true;
						newNode->p->p->is_black = false;
						RotateRight(newNode->p->p);
						}
				}

				// a bit repetitive but needed if uncle is NULL
				else {
					if (newNode == newNode->p->right) {
							newNode = newNode->p;
							RotateLeft(newNode);
						}

					newNode->p->is_black = true;
					newNode->p->p->is_black = false;
					RotateRight(newNode->p->p);
				}
			}

			else {
				Node<T>* y = newNode->p->p->left;
				if (y != NULL) {
					if (y->is_black == false) {
						newNode->p->is_black = true;
						y->is_black = true;
						newNode->p->p->is_black = false;
						newNode = newNode->p->p;
					}

					else {
						if (newNode == newNode->p->left) {
							newNode = newNode->p;
							RotateRight(newNode);
						}

					newNode->p->is_black = true;
					newNode->p->p->is_black = false;
					RotateLeft(newNode->p->p);
					}
				}

				else {
					if (newNode == newNode->p->left) {
							newNode = newNode->p;
							RotateRight(newNode);
						}

					newNode->p->is_black = true;
					newNode->p->p->is_black = false;
					RotateLeft(newNode->p->p);
					}
				}
			}

		root->is_black = true;
		return true;
	}
}


template <typename T>
bool RBTree<T>::Remove(T item) {
	Node<T>* z = Find(item);
	Node<T>* y = NULL;
	Node<T>* x = NULL;
	Node<T>* parent = NULL;
	bool isLeft;

	if (z == NULL) { // z was not found, return false
		return false;
	}

	else { 
		if (z->left == NULL || z->right == NULL) { // z has at most one child, set y to z, determine if y is left or right child
			y = z;
			parent = y->p;

		}

		else { // z has two children, find the predecessor
			y = Predecessor(z);
			parent = y->p;
		}

		if (y->left != NULL) { // determine x from y's children
			x = y->left;
		}

		if (x != NULL) { // x has a value, set it's parent to y's parent
			x->p = y->p;
		}

		if (y->p == NULL) { // if y's parent is null, y must be the root, so x becomes root
			root = x;
		}

		else { // 
			if (y == y->p->left) {
				y->p->left = x;
				isLeft = true;
			}

			else {
				 y->p->right = x;
				 isLeft = false;
			}
		}

			if (y != z) {
				z->data = y->data;
			}	
		}

		if (y->is_black == true) {
			RBRemoveFixUp(x, parent, isLeft);
		}

		delete y;
		size--;
		return true;
	}


template <typename T>
void RBTree<T>::RBRemoveFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild) {
	Node<T>* y;
	bool xcolor;
	bool yleftcolor;
	bool yrightcolor;
	if (x != NULL) {
		xcolor = x->is_black;
	}

	else {
		xcolor = true;
	}

	while (x != root && xcolor) { // entering for a value of X, need while loop
		if (!xisleftchild) {
			y = xparent->left;
			if (y != NULL) {
				if (!y->is_black) {
					y->is_black = true;
					xparent->is_black = false;
					RotateRight(xparent);
					y = xparent->left;
				}

				if (y->left != NULL) {
					yleftcolor = y->left->is_black;
				}

				else {
					yleftcolor = true;
				}

				if (y->right != NULL) {
					yrightcolor = y->right->is_black;
				}

				else {
					yrightcolor = true;
				}

				if (yleftcolor && yrightcolor) {
					y->is_black = false;
					x = xparent;
					xcolor = x->is_black;
					xparent = xparent->p;
					if (xparent->left == x) {
						xisleftchild = true;
					}

					else {
						xisleftchild = false;
					}
				}

				else {
					if (yleftcolor) {
						y->right->is_black = true; // this may cause problems
						y->is_black = false;
						RotateLeft(y);
						y = xparent->left;
					}

					y->is_black = xparent->is_black;
					xparent->is_black = true;
					if (y->left != NULL) {
						y->left->is_black = true;
					}
					RotateRight(xparent);
					x = root;
					return;
				}
			}
		}

		else {
			y = xparent->right;
			if (y != NULL) {
				if (!y->is_black) {
					y->is_black = true;
					xparent->is_black = false;
					RotateLeft(xparent);
					y = xparent->right;
				}
			}

			if (y->left != NULL) {
					yleftcolor = y->left->is_black;
				}

			else {
				yleftcolor = true;
			}

			if (y->right != NULL) {
				yrightcolor = y->right->is_black;
			}

			else {
				yrightcolor = true;
			}

			if (yleftcolor && yrightcolor) {
				y->is_black = false;
				x = xparent;
				xcolor = x->is_black;
				xparent = xparent->p;
				if (xparent->left == x) {
					xisleftchild = true;
				}

				else {
					xisleftchild = false;
				}
			}

			else {
				if (yrightcolor) {
					y->left->is_black = true; // this may cause problems
					y->is_black = false;
					RotateRight(y);
					y = xparent->right;
				}

				y->is_black = xparent->is_black;
				xparent->is_black = true;
				if (y->right != NULL) {
					y->right->is_black = true;
				}
				RotateLeft(xparent);
				x = root;
				return;
			}
		}
	}

	if (x != NULL) {
		x->is_black = true;
	}
}


template <typename T>
void RBTree<T>::RemoveAll(Node<T>* node) {
	if (node == NULL) {
		return;
	}

	if (node->left != NULL) {
		RemoveAll(node->left);
	}

	if (node->right != NULL) {
		RemoveAll(node->right);
	}

	if (node != root) {
		if (node->p->left == node) {
		node->p->left = NULL;
	}

		if (node->p->right == node) {
		node->p->right = NULL;
	}		
}

	else {
		node->left = NULL;
		node->right = NULL;
		delete node;
		root = NULL;
		return;
	}

	node->p = NULL;
	delete node;
}

template <typename T>
void RBTree<T>::RemoveAll() {
	RemoveAll(root);
}


template <typename T>
Node<T>* RBTree<T>::CopyTree(Node<T>* sourcenode, Node<T>* parentnode) {
	if (size <= 0) {
		Node<T>* refNode;
		root = new Node<T>(sourcenode->data);
		refNode = root;
		size++;
		refNode->is_black = sourcenode->is_black;
		if (sourcenode->left != NULL) {
			refNode->left = CopyTree(sourcenode->left, refNode);
		}

		if (sourcenode->right != NULL) {
			refNode->right = CopyTree(sourcenode->right, refNode);
		} 

		return refNode;
	}

	else {
		Node<T>* next = new Node<T>(sourcenode->data);
		size++;
		next->p = parentnode;
		next->is_black = sourcenode->is_black;
		if (sourcenode->left != NULL) {
			next->left = CopyTree(sourcenode->left, next);
		}

		if (sourcenode->right != NULL) {
			next->right = CopyTree(sourcenode->right, next);
		}

		return next;
	}
}

template <typename T>
int RBTree<T>::Size() const {
	return size;
}

template <typename T>
int RBTree<T>::ComputeHeight(Node<T>* node) const {
	if (!node) {
		return 0;
	}

	 else {
	 	int left = ComputeHeight(node->left);
	 	int right = ComputeHeight(node->right);

	 	if (left > right) {
	 		return left + 1;
	 	}

	 	else {
	 		return right + 1;
	 	}
	 }
}

template <typename T>
int RBTree<T>::Height() const {
	return ComputeHeight(root);
}


#endif