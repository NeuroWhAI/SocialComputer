#include "Board.h"

#include "Tile.h"
#include "Unit.h"
#include "Linker.h"
#include "Gene.h"




Board::Board(std::mt19937& randEngine)
	: m_rand(randEngine)
	
	, m_boardSize(0)
	, m_tileSize(1.0f)
{

}


Board::~Board()
{

}

//###########################################################################

void Board::initialize(int boardSize, float tileSize)
{
	m_boardSize = boardSize;
	m_tileSize = tileSize;


	// 타일 생성
	m_board.resize(boardSize);

	for (auto& horizon : m_board)
	{
		horizon.resize(boardSize);

		for (auto& tile : horizon)
		{
			tile = std::make_unique<Tile>(m_rand);
		}
	}


	// 타일 초기화 및 연결
	for (int y = 0; y < boardSize; ++y)
	{
		for (int x = 0; x < boardSize; ++x)
		{
			auto& tile = m_board[y][x];


			// 타일 초기화
			tile->initialize({ x * tileSize, y * tileSize }, tileSize);


			// 타일 연결
			int Y[8] = {
				y - 1, y - 1, y - 1, y, y + 1, y + 1, y + 1, y
			};

			int X[8] = {
				x - 1, x, x + 1, x + 1, x + 1, x, x - 1, x - 1
			};

			for (size_t i = 0; i < 8; ++i)
			{
				int linkY = Y[i];
				int linkX = X[i];

				if (linkY >= 0 && linkY < m_boardSize
					&& linkX >= 0 && linkX < m_boardSize)
				{
					tile->linkTile(m_board[linkY][linkX].get(), i);
				}
				else
				{
					tile->linkTile(nullptr, i);
				}
			}
		}
	}
}


void Board::update()
{
	for (auto& horizon : m_board)
	{
		for (auto& tile : horizon)
		{
			tile->update();


			// 새로 탄생한 유전자 목록에 저장.
			auto& newUnitList = tile->getNewUnitList();
			for (auto& unit : newUnitList)
			{
				m_newUnitList.emplace_back(std::move(unit));
			}

			tile->clearNewUnitList();
		}
	}
}

//###########################################################################

int Board::getBoardSize() const
{
	return m_boardSize;
}


float Board::getTileSize() const
{
	return m_tileSize;
}

//###########################################################################

void Board::addUnit(Unit* unit)
{
	auto position = unit->getPosition();
	Vector index = static_cast<Vector>(position / m_tileSize);

	if (index.x < 0)
	{
		position.x = 0;
		index.x = 0;
	}
	else if (index.x >= m_boardSize)
	{
		position.x = m_boardSize * m_tileSize - 1;
		index.x = m_boardSize - 1;
	}

	if (index.y < 0)
	{
		position.y = 0;
		index.y = 0;
	}
	else if (index.y >= m_boardSize)
	{
		position.y = m_boardSize * m_tileSize - 1;
		index.y = m_boardSize - 1;
	}

	unit->setPosition(position);
	m_board[index.y][index.x]->addUnit(unit);
}


void Board::removeUnit(const Unit* unit)
{
	const auto& position = unit->getPosition();
	Vector index = static_cast<Vector>(position / m_tileSize);

	if (index.x >= 0 && index.x < m_boardSize
		&& index.y >= 0 && index.y < m_boardSize)
	{
		m_board[index.y][index.x]->removeUnit(unit);
	}
	else
	{
		throw std::invalid_argument("Unit\'s position is not valid.");
	}
}


void Board::addLinker(Linker* linker)
{
	auto position = linker->getPosition();
	Vector index = static_cast<Vector>(position / m_tileSize);

	if (index.x < 0)
	{
		position.x = 0;
		index.x = 0;
	}
	else if (index.x >= m_boardSize)
	{
		position.x = m_boardSize * m_tileSize - 1;
		index.x = m_boardSize - 1;
	}

	if (index.y < 0)
	{
		position.y = 0;
		index.y = 0;
	}
	else if (index.y >= m_boardSize)
	{
		position.y = m_boardSize * m_tileSize - 1;
		index.y = m_boardSize - 1;
	}

	linker->setPosition(position);
	m_board[index.y][index.x]->addLinker(linker);
}


void Board::removeLinker(const Linker* linker)
{
	const auto& position = linker->getPosition();
	Vector index = static_cast<Vector>(position / m_tileSize);

	if (index.x >= 0 && index.x < m_boardSize
		&& index.y >= 0 && index.y < m_boardSize)
	{
		m_board[index.y][index.x]->removeLinker(linker);
	}
	else
	{
		throw std::invalid_argument("Linker\'s position is not valid.");
	}
}

//###########################################################################

std::vector<std::unique_ptr<Unit>>& Board::getNewUnitList()
{
	return m_newUnitList;
}


void Board::clearNewUnitList()
{
	m_newUnitList.clear();
}

