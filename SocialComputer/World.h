#pragma once


#include <memory>
#include <vector>




class Board;
class Unit;


class World
{
public:
	World();
	virtual ~World();


protected:
	std::unique_ptr<Board> m_board;
	std::vector<std::unique_ptr<Unit>> m_unitList;


public:
	void initialize(int mapSize);
	void update();


protected:
	void addUnit(std::unique_ptr<Unit>&& unit);
	void removeUnitAt(size_t index);
};

