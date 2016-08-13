#include "World.h"

#include <ctime>

#include "Gene.h"

#include "Board.h"
#include "Unit.h"
#include "Linker.h"




World::World()
	: m_rand(static_cast<unsigned int>(time(nullptr)))
	
	, m_board(std::make_unique<Board>())
{

}


World::~World()
{

}

//###########################################################################

void World::initialize(int mapSize)
{
	m_board->initialize(mapSize, 128.0f);

	
	std::uniform_int_distribution<> degreeDist{ 0, 360 };

	float tileSize = m_board->getTileSize();

	for (float y = 0; y < mapSize; y += 1.0f)
	{
		for (float x = 0; x < mapSize; x += 1.0f)
		{
			Gene gene;
			gene.initializeRandomly(m_rand);

			auto unit = std::make_unique<Unit>(gene);
			unit->setPosition({ x * tileSize, y * tileSize });
			unit->setAngle(static_cast<float>(degreeDist(m_rand)));

			addUnit(std::move(unit));
		}
	}
}


void World::update()
{
	// ���� ����(��ġ, �ӵ�, ���� ��) ����
	for (auto& unit : m_unitList)
	{
		unit->updateState();
	}


	// ��Ŀ ��ġ, �ӵ� ����
	for (auto& linker : m_linkerList)
	{
		linker->update();
	}


	m_board->update();


	// ���� ���μ��� �۵� �� �ൿ ����
	for (auto& unit : m_unitList)
	{
		unit->updateProcessor();
	}


	// ���� �ൿ �� ���ο� ��Ŀ �ޱ�
	for (auto& unit : m_unitList)
	{
		unit->updateMemory();


		const auto& newLinkerList = unit->getNewLinkerList();

		for (auto& linker : newLinkerList)
		{
			addLinker(linker);
		}

		unit->clearNewLinkerList();
	}
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


void World::addLinker(Linker* linker)
{
	m_board->addLinker(linker);

	m_linkerList.push_back(linker);
}


void World::removeLinkerAt(size_t index)
{
	m_board->removeLinker(m_linkerList[index]);

	m_linkerList.erase(m_linkerList.begin() + index);
}

