#pragma once
#include "Node.h"

//use of template means this binary tree can store any datatypes (including user defined classes)
template <class T>
class BinaryTree
{
public:

	//constructor
	BinaryTree(void)
	{
		_root = NULL;
	}


	//destructor
	~BinaryTree(void)
	{
		delete _root;
	}


	//remove (this calls _remove)
	void remove(T key)
	{
		_remove(key);
	}


	//insert - this insert only checks root, if empty it fills it else it directs to _insert() (it check all other roots as it iterates through the tree)
	void insert(T* key)
	{
		//check if root is not null
		if(_root != NULL)
		{
			//if it isn't that means the tree is populated with existing nodes, hence recursion ...
			_insert(key, _root);
		}
		else
		{
			try
			{
				//if the tree is empty then go ahead make a new node in root 
				_root = new Node<T>;
				_root->setKey(key);
				_root->setNodeLeft(NULL);
				_root->setNodeRight(NULL);
			}
			catch ( exception excp)
			{
				throw excp;
			}
		}
	}


	//search
	T *search(T key)
	{
		return _search(key, _root)->getKey();
	}


	//destroy tree!
	void destroy()
	{
		try
		{
			_destroy();
		}
		catch(exception excp)
		{
			throw excp;
		}
	}

	//convert tree to vector
	vector<T*> BinaryTree<T>::vectorConversion()
	{
		if(_root != NULL)
		{
			return _root->getSuccessors();
		}
		/*else
		{
			throw exception(NO_AIRCRAFT);
		}*/
	}

private:

	//make root
	Node<T> *_root;


	//gets to this insert when root is not empty
	void _insert(T* key, Node<T>* node)
	{
		//if less than then go left apply reccursion until space is found ... if space is found fill it!
		if(*key < *node->getKey())
		{
			if(node->getNodeLeft() != NULL)
			{
				_insert(key, node->getNodeLeft());
			}
			else
			{
				try
				{
					node->setNodeLeft(new Node<T>);
					node->getNodeLeft()->setKey(key);
					node->getNodeLeft()->setNodeLeft(NULL);	//Sets the left child of the child node to null
					node->getNodeLeft()->setNodeRight(NULL);	//Sets the right child of the child node to null
				}
				catch(exception excp)
				{
					throw excp;
				}
			}
		}

		//if greater than go right and apply reccursion until space is found ... if space is found fill it!
		else if (*key > *node->getKey())
		{
			if(node->getNodeRight() != NULL)
			{
				_insert(key, node->getNodeRight());
			}
			else
			{
				try
				{
					node->setNodeRight(new Node<T>);
					node->getNodeRight()->setKey(key);
					node->getNodeRight()->setNodeLeft(NULL); //Sets the left child of the child node to null
					node->getNodeRight()->setNodeRight(NULL);  //Sets the right child of the child node to null
				}
				catch(exception excp)
				{
					throw excp;
				}
			}		
		}

		//call signs matches
		else 
		{
			throw exception(DUPLICATE_CALLSIGN);
		}
	}


	//binary search
	Node<T> *_search(T key, Node<T>* node)
	{
		//checks left, checks right and applies recursion if value not found ... and if found it just returns the node 
		if(node != NULL)
		{
			if(key == *node->getKey())
			{
				return node;
			}
			if(key < *node->getKey())
			{
				return _search(key, node->getNodeLeft());
			}
			else
			{
				return _search(key, node->getNodeRight());
			}
		}
		else 
		{
			//aircraft not found 
			throw exception(AIRCRAFT_NOT_FOUND);
		}
	}


	//_destroy
	void _destroy()
	{
		//if root is not null then destroy tree
		if(_root != NULL)
		{
			_root->destroy();
			_root = NULL;
		}
	}


	//_remove
	void _remove(T key)
	{
		//searches to see if node exists based on key passed in 
		try
		{
			search(key);
		}
		catch(exception excp)
		{
			throw excp;
		}

		//if root is empty that means nothing to delete hence throw exception 
		if (_root == NULL)
		{
			throw exception (NO_AIRCRAFT);
		}
		else 
		{
			//if it is only the root (i.e. no left and no right) then just destroy it
			if (_root->getNodeLeft() == NULL && _root->getNodeRight() == NULL)
			{
				_root->destroy();
				_root = NULL;
			}
			//if root has children then it goes here
			else if(key == *_root->getKey())
			{
				//finds node to remove by going to node's remove function
				Node<T>* nodeToRemove = _root->remove(key, _root);
				try
				{
					//removes node
					if(nodeToRemove != NULL)
					{
						nodeToRemove = NULL;
					}
				}
				catch (exception excp)
				{
					throw excp;
				}
			}
			else
			{
				//for every other cases it is the same, go to node's remove function find it and then return to this function and finally just delete the particular node
				//node's remove function takes care of rearranging the binary tree 
				Node<T>* nodeToRemove = _root->remove(key, NULL);
				try
				{
					if(nodeToRemove != NULL)
					{
						nodeToRemove = NULL;
					}
				}
				catch (exception excp)
				{
					throw excp;
				}
			}
		}
	}
};