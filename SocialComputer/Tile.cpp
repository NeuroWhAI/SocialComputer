#include "Tile.h"

#include "Unit.h"
#include "Linker.h"




Tile::Tile()
	: m_position(VectorF::Zero)
	, m_tileSize(1.0f)

	, m_maxSpeedSq(1.0f)
{
	m_linkedTiles.fill(nullptr);
}


Tile::~Tile()
{

}

//###########################################################################

void Tile::initialize(const VectorF& position, float tileSize)
{
	m_position = position;
	m_tileSize = tileSize;

	m_maxSpeedSq = tileSize / 2;
	m_maxSpeedSq *= m_maxSpeedSq;
}


void Tile::update()
{
	size_t unitCount = m_unitList.size();

	for (size_t u = 0; u < unitCount; ++u)
	{
		Unit* const unit = m_unitList[u];
		const auto& position = unit->getPosition();
		const float radius = unit->getRadius();


		// 유닛간 충돌처리
		std::vector<Unit*>* currentUnitList = nullptr;

		for (int tileIndex = -1; tileIndex < 8; ++tileIndex)
		{
			if (tileIndex < 0)
			{
				currentUnitList = &m_unitList;
			}
			else
			{
				if (m_linkedTiles[tileIndex] == nullptr)
					continue;
				else
					currentUnitList = &m_linkedTiles[tileIndex]->m_unitList;
			}

			for (auto otherUnit : *currentUnitList)
			{
				if (otherUnit == unit)
					continue;


				auto subVec = otherUnit->getPosition() - position;
				const float minDistance = otherUnit->getRadius() + radius;

				const float distanceSq = subVec.getLengthSq();

				// 충돌했음.
				if (distanceSq < minDistance * minDistance)
				{
					// 튕겨져 나감.
					if (distanceSq > 0.0f)
					{
						auto pushVec = subVec / (distanceSq * 4.0f);
						if (pushVec.getLengthSq() > 1.0f)
							pushVec.normalize();

						otherUnit->addSpeed(pushVec);
						unit->addSpeed(-pushVec);

						if (otherUnit->getSpeed().getLengthSq() > m_maxSpeedSq)
							otherUnit->addSpeed(-pushVec);

						if (unit->getSpeed().getLengthSq() > m_maxSpeedSq)
							unit->addSpeed(pushVec);
					}
				}
			}
		}


		// 타일을 벗어났다면 처리
		int outTile = checkOutTile(position);

		if (outTile >= 0)
		{
			Tile* const pOutTile = m_linkedTiles[outTile];

			if (pOutTile == nullptr)
			{
				unit->addPosition(-unit->getSpeed());
				unit->setSpeed(VectorF::Zero);
			}
			else
			{
				pOutTile->addUnit(unit);

				m_unitList.erase(m_unitList.begin() + u);
				--u;
				--unitCount;
			}
		}
	}


	size_t linkerCount = m_linkerList.size();

	for (size_t l = 0; l < linkerCount; ++l)
	{
		auto linker = m_linkerList[l];
		const auto& position = linker->getPosition();
		auto owner = linker->getOwner();


		if (linker->hasConnection() == false)
		{
			// 링커-유닛 충돌처리
			std::vector<Unit*>* currentUnitList = nullptr;

			for (int tileIndex = -1; tileIndex < 8; ++tileIndex)
			{
				if (tileIndex < 0)
				{
					currentUnitList = &m_unitList;
				}
				else
				{
					if (m_linkedTiles[tileIndex] == nullptr)
						continue;
					else
						currentUnitList = &m_linkedTiles[tileIndex]->m_unitList;
				}

				bool isConnected = false;

				auto& otherUnitList = *currentUnitList;
				for (auto otherUnit : otherUnitList)
				{
					if (otherUnit == owner)
						continue;


					auto subVec = otherUnit->getPosition() - position;
					const float minDistance = otherUnit->getRadius();

					const float distanceSq = subVec.getLengthSq();

					// 충돌했음.
					if (distanceSq < minDistance * minDistance)
					{
						// 연결
						size_t linkIndex = otherUnit->assignLinkerIndex(owner);
						linker->connect(otherUnit, linkIndex);

						isConnected = true;

						break;
					}
				}

				if (isConnected)
				{
					break;
				}
			}
		}


		// 타일을 벗어났다면 처리
		int outTile = checkOutTile(position);

		if (outTile >= 0)
		{
			Tile* const pOutTile = m_linkedTiles[outTile];

			if (pOutTile == nullptr)
			{
				linker->addPosition(-linker->getSpeed());
				linker->setSpeed(VectorF::Zero);
			}
			else
			{
				pOutTile->addLinker(linker);

				m_linkerList.erase(m_linkerList.begin() + l);
				--l;
				--linkerCount;
			}
		}
	}
}

//###########################################################################

void Tile::linkTile(Tile* tile, size_t index)
{
	m_linkedTiles[index] = tile;
}

//###########################################################################

int Tile::checkOutTile(const VectorF& position)
{
	int outTile = -1;

	if (position.x < m_position.x)
	{
		if (position.y < m_position.y)
		{
			outTile = 0;
		}
		else if (position.y >= m_position.y + m_tileSize)
		{
			outTile = 6;
		}
		else
		{
			outTile = 7;
		}
	}
	else if (position.x >= m_position.x + m_tileSize)
	{
		if (position.y < m_position.y)
		{
			outTile = 2;
		}
		else if (position.y >= m_position.y + m_tileSize)
		{
			outTile = 4;
		}
		else
		{
			outTile = 3;
		}
	}
	else
	{
		if (position.y < m_position.y)
		{
			outTile = 1;
		}
		else if (position.y >= m_position.y + m_tileSize)
		{
			outTile = 5;
		}
	}


	return outTile;
}

//###########################################################################

void Tile::addUnit(Unit* unit)
{
	m_unitList.emplace_back(unit);
}


void Tile::removeUnit(const Unit* unit)
{
	const size_t unitCount = m_unitList.size();

	for (size_t i = 0; i < unitCount; ++i)
	{
		if (m_unitList[i] == unit)
		{
			m_unitList.erase(m_unitList.begin() + i);

			return;
		}
	}


	throw std::invalid_argument("No matching unit.");
}


void Tile::addLinker(Linker* linker)
{
	m_linkerList.emplace_back(linker);
}


void Tile::removeLinker(const Linker* linker)
{
	const size_t linkerCount = m_linkerList.size();

	for (size_t i = 0; i < linkerCount; ++i)
	{
		if (m_linkerList[i] == linker)
		{
			m_linkerList.erase(m_linkerList.begin() + i);

			return;
		}
	}


	throw std::invalid_argument("No matching linker.");
}

