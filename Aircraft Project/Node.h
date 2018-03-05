#pragma once
#include "Main.h"

template <class T>
struct Node
{
public:
	
	//setters and getters

	//set _keyValue
	void setKey(T* key)
	{
		_keyValue = key;
	}

	//returns _keyValue
	T* getKey()
	{
		return _keyValue;
	}

	//set left node 
	void setNodeLeft(Node<T> *left)
	{
		_left = left;
	}

	//get left node
	Node<T>* getNodeLeft()
	{
		return _left;
	}

	//set right node
	void setNodeRight(Node<T> *right)
	{
		_right = right;
	}

	//get right node
	Node<T>* getNodeRight()
	{
		return _right;
	}


	//other functions

	//delete a particular node
	Node<T>* remove(T key, Node<T>* parent)
	{
		if (key < *this->_keyValue)
		{
			//recursion occurs till the corrent node is identified (left)- this run's node's version of remove
			if (_left != NULL)
			{
				_left->remove(key, this);
			}
		}
		else if (key > *this->_keyValue)
		{
			//recursion occurs till the corrent node is identified (right) - this run's node's version of remove
			if (_right != NULL)
			{
				_right->remove(key, this);
			}
		}
		else //aircraft to delete has been found
		{
			// node to delete has two children
			if (_left != NULL && _right != NULL)
			{
				this->_keyValue = _left->minValue();
				return _left->remove(*this->_keyValue, this);
			}
			//check if this is left
			else if (parent->_left == this)
			{
				parent->_left = (_left != NULL) ? _left : _right;
				return this;
			}
			//check if this is right
			else if ( parent->_right == this)
			{
				parent->_right = (_left != NULL) ? _left : _right;
				return this;
			}
			//check if left is NULL and right is not NULL
			else if(_left == NULL && _right != NULL)
			{
				this->_keyValue = _right->minValue();
				return _right->remove(*this->_keyValue, this);
			}
			//check if left is not NULL and right NULL
			else if(_left != NULL && _right == NULL)
			{
				this->_keyValue = _left->minValue();
				return _left->remove(*this->_keyValue, this);
			}
		}
	}

	//gets the min value in tree
	T* minValue()
	{
		return _minValue();
	}

	//destroy node
	void destroy()
	{
		//calls private _destroy
		_destroy();
	}

	//returns all successors
	vector<T*> Node<T>::getSuccessors()
	{
		vector<T*> successors;
		vector<T*> rightSuccessors;
		vector<T*> leftSuccessors;

		successors.push_back(_keyValue);
		
		//check left
		if(_left != NULL)
		{
			leftSuccessors = _left->getSuccessors();
			successors.insert(successors.end(), leftSuccessors.begin(), leftSuccessors.end());
		}

		//check right
		if(_right != NULL)
		{
			rightSuccessors = _right->getSuccessors();
			successors.insert(successors.end(), rightSuccessors.begin(), rightSuccessors.end());
		}

		return successors;
	}

private:
	//stores T pointer variable ... _keyValue
	T* _keyValue;
	Node<T> *_left;
	Node<T> *_right;

	void _destroy()
	{
		//check left
		if (_left != NULL)
		{
			_left->destroy();
		}

		//check right
		if (_right != NULL)
		{
			_right->destroy();
		}

		//delete the node (this happens for every node since this is recursive)
		delete this;
	}

	T* _minValue()
	{
		if(_left == NULL)
		{
			return _keyValue;
		}
		else 
		{
			//recursion occurs until min value is found
			return _left->minValue();
		}
	}
};

