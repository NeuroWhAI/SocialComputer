#pragma once


#include <vector>
#include <array>

#include <CodeAdapter\EasyCA.h>




class Unit;
class Linker;


class Tile
{
private:
	USING_CA_DRAWING(VectorF);


public:
	Tile();
	virtual ~Tile();


protected:
	VectorF m_position;
	float m_tileSize;
	std::array<Tile*, 8> m_linkedTiles;


protected:
	std::vector<Unit*> m_unitList;
	std::vector<Linker*> m_linkerList;


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
};

