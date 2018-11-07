#include "TreeNode.h"
#include <imgui.h>
#include <iostream>

TreeNode::TreeNode(int value)
{
	m_value = value;

	m_left = nullptr;
	m_right = nullptr;
}


TreeNode::~TreeNode()
{
}

void TreeNode::draw(aie::Renderer2D *renderer, int x, int y, aie::Font *g_systemFont, bool selected)
{
	static char buffer[10];

	sprintf(buffer, "%d", m_value);

	renderer->setRenderColour(1, 1, 0);
	renderer->drawCircle(x, y, 30);

	if (selected == true)
	{
		renderer->setRenderColour(.5, .5, 0);
	}
	else
	{
		renderer->setRenderColour(0, 0, 0);
	}
	renderer->drawCircle(x, y, 28);

	renderer->setRenderColour(1, 1, 1);
	renderer->drawText(g_systemFont, buffer, x - 12, y - 10);

}

