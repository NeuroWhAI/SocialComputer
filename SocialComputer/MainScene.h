#pragma once


#include <memory>

#include <CodeAdapter\EasyCA.h>




class World;


class MainScene : public caUtil::Scene
{
public:
	MainScene();
	virtual ~MainScene();


protected:
	std::shared_ptr<caDraw::Panel> m_panel;
	std::shared_ptr<caDraw::Font> m_font;


protected:
	std::unique_ptr<World> m_world;


public:
	virtual void onInitialize(caDraw::Window& owner) override;
	virtual void onRelease() override;
	virtual void onUpdate(caDraw::Window& owner) override;
	virtual void onDrawBack(caDraw::Graphics& g) override;
	virtual void onDrawFront(caDraw::Graphics& g) override;
};

