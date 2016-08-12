#pragma once


#include <memory>
#include <vector>

#include <CodeAdapter\EasyCA.h>




class Gene;


class Unit
{
private:
	USING_CA_DRAWING(VectorF);


public:
	explicit Unit(const Gene& gene);
	virtual ~Unit();


protected:
	const double ENERGY_PER_MEMORY;


protected:
	double m_energy;
	VectorF m_position;
	VectorF m_speed;
	float m_radius;
	VectorF m_direction;
	float m_angle;


protected:
	std::unique_ptr<Gene> m_gene;


public:
	void updatePosition();


public:
	const VectorF& getPosition() const;
	void setPosition(const VectorF& position);
	void addPosition(const VectorF& move);
	const VectorF& getSpeed() const;
	void setSpeed(const VectorF& speed);
	void addSpeed(const VectorF& accelerate);
	float getRadius() const;
	const VectorF& getDirection() const;
	float getAngle() const;
};

