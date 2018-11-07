#include "CDDS_BinaryTreesApp.h"



CDDS_BinaryTreesApp::CDDS_BinaryTreesApp()
{
}


CDDS_BinaryTreesApp::~CDDS_BinaryTreesApp()
{
}

bool CDDS_BinaryTreesApp::startup()
{
	m_2dRenderer = new aie::Renderer2D();
	g_systemFont = new aie::Font("./font/consolas.ttf", 32);
	return true;
}

void CDDS_BinaryTreesApp::shutdown()
{
	delete m_selectedNode;
	delete g_systemFont;
	delete m_2dRenderer;
}

void CDDS_BinaryTreesApp::update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	static int value = 0;
	ImGui::InputInt("Value", &value);

	if (ImGui::Button("Insert", ImVec2(50, 0)))
	{
		m_binaryTree.insert(value);
		m_selectedNode = m_binaryTree.find(value);
	}

	if (ImGui::Button("Remove", ImVec2(50, 0)))
	{
		m_binaryTree.remove(value);
	}

	if (ImGui::Button("Find", ImVec2(50, 0)))
	{
		m_selectedNode = m_binaryTree.find(value);
	}

	//exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		quit();
	}
}

void CDDS_BinaryTreesApp::draw()
{
	clearScreen();

	m_2dRenderer->begin();

	m_binaryTree.draw(m_2dRenderer, g_systemFont, m_selectedNode);

	m_2dRenderer->drawText(g_systemFont, "Press ESC to quit", 0, 0);

	m_2dRenderer->end();
}
