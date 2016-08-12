#include "DrawableWorld.h"

#include "Board.h"
#include "Unit.h"




DrawableWorld::DrawableWorld()
{

}


DrawableWorld::~DrawableWorld()
{

}

//###########################################################################

void DrawableWorld::onDraw(Graphics& g, const Transform& parentTransform)
{
	auto& rectArtist = g.rectangleArtist;
	auto& ellipseArtist = g.ellipseArtist;
	auto& lineArtist = g.lineArtist;


	float boardSize = m_board->getBoardSize() * m_board->getTileSize();

	rectArtist->beginDrawRectangle(4.0f);
	rectArtist->drawRectangle(0.0f, 0.0f, boardSize, boardSize,
		caDraw::Color::Gray);
	rectArtist->endDrawRectangle();


	ellipseArtist->beginFillEllipse();

	for (auto& unit : m_unitList)
	{
		const auto& position = unit->getPosition();
		float radius = unit->getRadius();


		ellipseArtist->fillEllipse(position.x - radius,
			position.y - radius,
			radius * 2, radius * 2,
			caDraw::Color(34, 177, 76));
	}

	ellipseArtist->endFillEllipse();


	lineArtist->beginDrawLine(2.0f);

	for (auto& unit : m_unitList)
	{
		const auto& position = unit->getPosition();
		float radius = unit->getRadius();

		auto dir = unit->getDirection();
		dir *= radius;
		dir += position;

		lineArtist->drawLine(position.x, position.y,
			dir.x, dir.y,
			caDraw::Color(181, 230, 29));
	}

	lineArtist->endDrawLine();
}

