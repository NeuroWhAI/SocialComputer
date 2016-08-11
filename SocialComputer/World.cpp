#include "World.h"

#include "Board.h"
#include "Unit.h"




World::World()
	: m_board(std::unique_ptr<Board>())
{

}


World::~World()
{

}

//###########################################################################

void World::initialize(int mapSize)
{
	m_board->initialize(mapSize, 128.0f);
}


void World::update()
{
	// 유닛 위치 갱신(속도 적용)
	for (auto& unit : m_unitList)
	{
		unit->updatePosition();
	}


	m_board->update();
}

//###########################################################################

void World::addUnit(std::unique_ptr<Unit>&& unit)
{
	Unit* const unitPtr = unit.get();


	m_board->addUnit(unitPtr);

	m_unitList.emplace_back(std::move(unit));
}


void World::removeUnitAt(size_t index)
{
	Unit* const unitPtr = m_unitList[index].get();


	m_board->removeUnit(unitPtr);

	m_unitList.erase(m_unitList.begin() + index);
}

