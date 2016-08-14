#pragma once


#include <vector>
#include <array>
#include <random>

#include <CodeAdapter\EasyCA.h>




class Unit;
class Linker;


class Tile
{
private:
	USING_CA_DRAWING(VectorF);


public:
	explicit Tile(std::mt19937& randEngine);
	virtual ~Tile();


protected:
	std::mt19937& m_rand;
	std::uniform_int_distribution<> m_mutationDist;


protected:
	VectorF m_position;
	float m_tileSize;
	std::array<Tile*, 8> m_linkedTiles;


protected:
	float m_maxSpeedSq;
	std::vector<Unit*> m_unitList;
	std::vector<Linker*> m_linkerList;


protected:
	std::vector<std::unique_ptr<Unit>> m_newUnitList;


public:
	void initialize(const VectorF& position, float tileSize);
	void update();


public:
	void linkTile(Tile* tile, size_t index);


protected:
	int checkOutTile(const VectorF& position);


public:
	void addUnit(Unit* unit);
	void removeUnit(const Unit* unit);
	void addLinker(Linker* linker);
	void removeLinker(const Linker* linker);


public:
	std::vector<std::unique_ptr<Unit>>& getNewUnitList();
	void clearNewUnitList();
};

