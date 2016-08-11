#pragma once


#include <vector>

#include <CodeAdapter\EasyCA.h>




class Unit
{
private:
	USING_CA_DRAWING(VectorF);


public:
	Unit();
	virtual ~Unit();


protected:
	VectorF m_position;
	VectorF m_speed;


public:
	void updatePosition();


public:
	const VectorF& getPosition() const;
	void setPosition(const VectorF& position);
	void addPosition(const VectorF& move);
	const VectorF& getSpeed() const;
	void setSpeed(const VectorF& speed);
	void addSpeed(const VectorF& accelerate);
};

