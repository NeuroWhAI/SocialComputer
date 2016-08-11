#pragma once


#include <vector>
#include <array>

#include <CodeAdapter\EasyCA.h>




class Unit;


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


public:
	void initialize(const VectorF& position, float tileSize);
	void update();


public:
	void linkTile(Tile* tile, size_t index);


public:
	void addUnit(Unit* unit);
	void removeUnit(const Unit* unit);
	bool hasUnit() const;
};
