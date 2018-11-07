#pragma once

#include "TreeNode.h"

class BinaryTree
{
	struct Node;

public:
	BinaryTree();
	~BinaryTree();

	bool isEmpty() const;
	void insert(int a_nValue);
	void remove(int a_nValue);
	TreeNode* find(int a_nValue);
	void draw(aie::Renderer2D* renderer, aie::Font *g_systemFont, TreeNode* selected = nullptr);

private:
	bool findNode(int a_nSearchValue, TreeNode** ppOutNode, TreeNode** ppOutParent);

	void draw(aie::Renderer2D* renderer, TreeNode*, int x, int y, int horizontalSpacing, aie::Font *g_systemFont,TreeNode* selected = nullptr);

	TreeNode* m_pRoot;

};

