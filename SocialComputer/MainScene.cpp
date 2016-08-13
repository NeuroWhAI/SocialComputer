#include "MainScene.h"

#include "DrawableWorld.h"




MainScene::MainScene()
	: m_camera(PointF::Zero)
	, m_world(std::make_shared<DrawableWorld>())
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


	m_world->initialize(6);
}


void MainScene::onRelease()
{

}


void MainScene::onUpdate(caDraw::Window& owner)
{
	m_beginTime = system_clock::now();


	if (caKeyboard->isKeyDown(caSys::Keys::Escape))
	{
		reserveNextScene(nullptr);
	}
	
	if (caKeyboard->isKeyPressed(caSys::Keys::Up))
	{
		m_camera.move(0, 8);
	}
	else if (caKeyboard->isKeyPressed(caSys::Keys::Down))
	{
		m_camera.move(0, -8);
	}

	if (caKeyboard->isKeyPressed(caSys::Keys::Left))
	{
		m_camera.move(8, 0);
	}
	else if (caKeyboard->isKeyPressed(caSys::Keys::Right))
	{
		m_camera.move(-8, 0);
	}


	m_world->update();
}


void MainScene::onDrawBack(caDraw::Graphics& g)
{
	auto cam = m_panel->transform;
	cam.position += m_camera;


	m_world->draw(g, cam);
}


void MainScene::onDrawFront(caDraw::Graphics& g)
{
	auto endTime = system_clock::now();
	std::chrono::duration<double> duration = endTime - m_beginTime;

	double fps = 1.0 / duration.count();


	auto& textArtist = g.textArtist;


	textArtist->beginDrawString(*m_font);

	textArtist->drawString(std::to_string(fps) + "fps",
		8, 8, caDraw::Color::Red);

	textArtist->endDrawString();
}

