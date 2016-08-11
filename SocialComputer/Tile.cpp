#include "Tile.h"

#include "Unit.h"




Tile::Tile()
	: m_position(VectorF::Zero)
	, m_tileSize(1.0f)
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
}


void Tile::update()
{
	size_t unitCount = m_unitList.size();

	for (size_t u = 0; u < unitCount; ++u)
	{
		auto& unit = m_unitList[u];
		const auto& position = unit->getPosition();


		// 鸥老阑 哈绢车促搁 贸府
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
				pOutTile->addUnit(m_unitList[u]);

				m_unitList.erase(m_unitList.begin() + u);
				--u;
				--unitCount;
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


bool Tile::hasUnit() const
{
	return !m_unitList.empty();
}

