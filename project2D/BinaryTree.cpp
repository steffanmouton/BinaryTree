#include "BinaryTree.h"



BinaryTree::BinaryTree()
{
	m_pRoot = nullptr;
}


BinaryTree::~BinaryTree()
{
}

bool BinaryTree::isEmpty() const
{
	return (m_pRoot == nullptr) ? true : false;
}

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

void BinaryTree::remove(int a_nValue)
{
	TreeNode* current;
	TreeNode* parent;

	TreeNode** ppOutNode = &current;
	TreeNode** ppOutParent = &parent;
	findNode(a_nValue, ppOutNode, ppOutParent);

	current = *ppOutNode;
	parent = *ppOutParent;

	//deleting a leaf
	if (current->getLeft() == nullptr && current->getRight() == nullptr)
	{
		delete current;
		parent->setLeft(nullptr);
		parent->setRight(nullptr);
		return;
	}
	//deleting node with two children
	if (current->getLeft() != nullptr && current->getRight() != nullptr)
	{
		TreeNode* smallest = current->getRight();
		TreeNode* smallParent = parent->getRight();


	
		while (smallest->getLeft() != nullptr)
		{
			smallParent = smallest;
			smallest = smallest->getLeft();
		}

		current->setData(smallest->getData());

		//deleting smallest node if leaf
		if (smallest->getRight() == nullptr)
		{
			delete smallest;
			smallParent->setLeft(nullptr);
		}

		//deleting smallest node if one child
		else if (smallest->getRight() != nullptr)
		{
			smallParent->setRight(smallest->getRight());
			delete smallest;
		}

		//
		return;
	}
	//deleting node with one child
	if (current->getLeft() != nullptr || current->getRight() != nullptr)
	{
		enum Side { Left, Right };

		//determine side of parent
		Side parentSide;

		if (parent->getLeft() != nullptr)
		{
			if (parent->getLeft()->getData() == a_nValue)
			{
				parentSide = Left;
			}
		}

		if (parent->getRight() != nullptr)
		{
			if (parent->getRight()->getData() == a_nValue)
			{
				parentSide = Right;
			}
		}

		//determine side of current
		Side curSide;

		if (current->getLeft() != nullptr)
		{
			curSide = Left;
		}
		else
		{
			curSide = Right;
		}
		//
		switch (curSide)
		{
		case Left:
			if (parentSide == Left)
			{
				parent->setLeft(current->getLeft());
			}
			else
			{
				parent->setRight(current->getLeft());
			}

			delete current;
			break;

		case Right:
			if (parentSide == Left)
			{
				parent->setLeft(current->getRight());
			}
			else
			{
				parent->setRight(current->getRight());
			}
			
			delete current;
			break;
		}

		return;
	}

}

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

void BinaryTree::draw(aie::Renderer2D * renderer, aie::Font *g_systemFont, TreeNode * selected)
{
	draw(renderer, m_pRoot, 640, 680, 640, g_systemFont, selected);
}

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
