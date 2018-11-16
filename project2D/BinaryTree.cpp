#include "BinaryTree.h"


//default constructor, setting root of tree to null
BinaryTree::BinaryTree()
{
	m_pRoot = nullptr;
}


BinaryTree::~BinaryTree()
{
}

//bool check to see if tree is empty
bool BinaryTree::isEmpty() const
{
	return (m_pRoot == nullptr) ? true : false;
}

//inserts an entirely new node into the tree into the correct position
//via iterating over the existing tree branches to find the proper place
void BinaryTree::insert(int a_nValue)
{
	TreeNode* current = m_pRoot;
	TreeNode* parent = m_pRoot; 
	
	

	if (isEmpty())
	{
		m_pRoot = new TreeNode(a_nValue);
		m_pRoot->setLeft(nullptr);
		m_pRoot->setRight(nullptr);
	}
	else
	{
		while (current != nullptr)
		{
			if (a_nValue < current->getData())
			{
				parent = current;
				current = current->getLeft();
			}
			else if (a_nValue > current->getData())
			{
				parent = current;
				current = current->getRight();
			}
			else
			{
				break;
			}
		}

		TreeNode** ptrCurrent = &current;
		TreeNode** ptrParent = &parent;

		if (!findNode(a_nValue, ptrCurrent, ptrParent))
		{
			if (a_nValue < parent->getData())
			{
				parent->setLeft(new TreeNode(a_nValue));
			}
			else if (a_nValue > parent->getData())
			{
				parent->setRight(new TreeNode(a_nValue));
			}
		}
		
	}

}

//removes the node in the tree with the matching value passed in
void BinaryTree::remove(int a_nValue)
{
	TreeNode* current;
	TreeNode* parent;

	TreeNode** ppOutNode = &current;
	TreeNode** ppOutParent = &parent;
	findNode(a_nValue, ppOutNode, ppOutParent);

	current = *ppOutNode;
	parent = *ppOutParent;

	//if current node has a right branch
	//obtain smallest node on right side of current
	if (current->hasRight())
	{
		TreeNode* small;
		TreeNode* smallParent = current;
		small = current->getRight();

		while (small->hasLeft())
		{
			smallParent = small;
			small = small->getLeft();
		}

		current->setData(small->getData());

		if (smallParent->getLeft() == small)
		{
			if (small->hasRight())
			{
				smallParent->setLeft(small->getRight());
			}
			else
			{
				smallParent->setLeft(nullptr);
			}
		}
		else if (smallParent->getRight() == small)
		{
			if (small->hasRight())
			{
				smallParent->setRight(small->getRight());
			}
			else
			{
				smallParent->setRight(nullptr);
			}
		}

		delete small;
	}
	else //if current node has no right branch
	{
		if (parent->getLeft() == current)
		{
			if (current->hasLeft())
			{
				parent->setLeft(current->getLeft());
			}
			else
			{
				parent->setLeft(nullptr);
			}
		}
		if (parent->getRight() == current)
		{
			if (current->hasLeft())
			{
				parent->setRight(current->getLeft());
			}
			else
			{
				parent->setRight(nullptr);
			}
		}
		else if (current == m_pRoot)
		{
			if (current->hasLeft())
			{
				m_pRoot = current->getLeft();
			}
			else
			{
				m_pRoot = nullptr;
			}
		}

		delete current;
	}

}

//find node, when FIND button pressed, highlights that node 
TreeNode * BinaryTree::find(int a_nValue)
{
	TreeNode* current = m_pRoot;

	while (current != nullptr)
	{
		if (a_nValue == current->getData())
		{
			return current;
		}
		else if (a_nValue < current->getData())
		{
			current = current->getLeft();
		}
		else
		{
			current = current->getRight();
		}
	}

	return current;
}

//shorthand draw function to be called elsewhere
void BinaryTree::draw(aie::Renderer2D * renderer, aie::Font *g_systemFont, TreeNode * selected)
{
	draw(renderer, m_pRoot, 640, 680, 640, g_systemFont, selected);
}

//finds a node by the given searchValue, returns bool on if found, also returns searched for node and its parent 
bool BinaryTree::findNode(int a_nSearchValue, TreeNode ** ppOutNode, TreeNode ** ppOutParent)
{
	TreeNode* current = m_pRoot;
	TreeNode* parent = m_pRoot;

	while (current != nullptr)
	{
		if (a_nSearchValue == current->getData())
		{
			*ppOutParent = parent;
			*ppOutNode = current;
			return true;
		}
		else if (a_nSearchValue < current->getData())
		{
			parent = current;
			current = current->getLeft();
		}
		else
		{
			parent = current;
			current = current->getRight();
		}
	}
	return false;
}

//draws tree to window
void BinaryTree::draw(aie::Renderer2D * renderer, TreeNode *pNode, int x, int y, int horizontalSpacing, aie::Font *g_systemFont, TreeNode * selected)
{
	horizontalSpacing /= 2;

	if (pNode) 
	{
		if (pNode->hasLeft())
		{
			renderer->setRenderColour(1, 0, 0);
			renderer->drawLine(x, y, x - horizontalSpacing, y - 80);
			draw(renderer, pNode->getLeft(), x - horizontalSpacing, y - 80, horizontalSpacing, g_systemFont,selected);
		}
		if (pNode->hasRight())
		{
			renderer->setRenderColour(1, 0, 0);
			renderer->drawLine(x, y, x + horizontalSpacing, y - 80);
			draw(renderer, pNode->getRight(), x + horizontalSpacing, y - 80, horizontalSpacing, g_systemFont, selected);
		}

		pNode->draw(renderer, x, y, g_systemFont, (selected == pNode));
	}
}
