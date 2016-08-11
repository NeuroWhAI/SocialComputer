#pragma once


#include <memory>
#include <vector>

#include <CodeAdapter\EasyCA.h>




class Tile;
class Unit;


class Board
{
private:
	USING_CA_DRAWING(Vector);
	USING_CA_DRAWING(VectorF);


public:
	Board();
	virtual ~Board();


protected:
	int m_boardSize;
	float m_tileSize;
	std::vector<std::vector<std::unique_ptr<Tile>>> m_board;


public:
	void initialize(int boardSize, float tileSize);
	void update();


public:
	int getBoardSize() const;
	float getTileSize() const;


public:
	void addUnit(Unit* unit);
	void removeUnit(const Unit* unit);
};

