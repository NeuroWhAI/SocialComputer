#pragma once


#include <memory>
#include <vector>
#include <random>

#include <CodeAdapter\EasyCA.h>




class Tile;
class Unit;
class Linker;


class Board
{
private:
	USING_CA_DRAWING(Vector);
	USING_CA_DRAWING(VectorF);


public:
	explicit Board(std::mt19937& randEngine);
	virtual ~Board();


protected:
	std::mt19937& m_rand;


protected:
	int m_boardSize;
	float m_tileSize;
	std::vector<std::vector<std::unique_ptr<Tile>>> m_board;


protected:
	std::vector<std::unique_ptr<Unit>> m_newUnitList;


public:
	void initialize(int boardSize, float tileSize);
	void update();


public:
	int getBoardSize() const;
	float getTileSize() const;


public:
	void addUnit(Unit* unit);
	void removeUnit(const Unit* unit);
	void addLinker(Linker* linker);
	void removeLinker(const Linker* linker);


public:
	std::vector<std::unique_ptr<Unit>>& getNewUnitList();
	void clearNewUnitList();
};

