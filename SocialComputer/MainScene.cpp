#include "MainScene.h"

#include "World.h"




MainScene::MainScene()
{

}


MainScene::~MainScene()
{

}

//###########################################################################

void MainScene::onInitialize(caDraw::Window& owner)
{
	auto winSize = owner.getSize();


	m_panel = caFactory->createPanel();
	m_panel->transform.position = { 0, 0 };
	m_panel->size = static_cast<caDraw::SizeF>(winSize);
	addPanel(m_panel);

	m_font = caFactory->createFont();
	m_font->loadFromFile("SC Resources/NanumGothic.ttf");
	m_font->setCharacterSize(32);
	m_font->setStyle(caDraw::FontStyles::Bold);


	m_world->initialize(32);
}


void MainScene::onRelease()
{

}


void MainScene::onUpdate(caDraw::Window& owner)
{
	if (caKeyboard->isKeyDown(caSys::Keys::Escape))
	{
		reserveNextScene(nullptr);
	}


	m_world->update();
}


void MainScene::onDrawBack(caDraw::Graphics& g)
{

}


void MainScene::onDrawFront(caDraw::Graphics& g)
{

}

