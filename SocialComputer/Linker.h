#pragma once


#include <CodeAdapter\EasyCA.h>

#include "Memory.h"




class Unit;


class Linker
{
private:
	USING_CA_DRAWING(VectorF);


public:
	Linker();


protected:
	VectorF m_position;
	VectorF m_speed;


protected:
	const Unit* m_owner;


protected:
	Unit* m_connectedUnit;
	size_t m_connectedIndex;


public:
	void update();


public:
	const VectorF& getPosition() const;
	void setPosition(const VectorF& position);
	void addPosition(const VectorF& move);
	const VectorF& getSpeed() const;
	void setSpeed(const VectorF& speed);
	void addSpeed(const VectorF& accelerate);


public:
	const Unit* getOwner() const;
	void setOwner(const Unit* owner);


public:
	void connect(Unit* target, size_t index);
	Unit* getConnectedUnit() const;
	bool hasConnection() const;


public:
	void push(Memory::DataType data);
	Memory::DataType pull();
	void grow(Memory::DataType data);
};

