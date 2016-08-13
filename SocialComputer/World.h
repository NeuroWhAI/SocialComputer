#pragma once


#include <memory>
#include <vector>
#include <random>




class Board;
class Unit;
class Linker;


class World
{
public:
	World();
	virtual ~World();


protected:
	std::mt19937 m_rand;


protected:
	std::unique_ptr<Board> m_board;
	std::vector<std::unique_ptr<Unit>> m_unitList;
	std::vector<Linker*> m_linkerList;


public:
	void initialize(int mapSize);
	void update();


protected:
	void addUnit(std::unique_ptr<Unit>&& unit);
	void removeUnitAt(size_t index);
	void addLinker(Linker* linker);
	void removeLinkerAt(size_t index);
};

