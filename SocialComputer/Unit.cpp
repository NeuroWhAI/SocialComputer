#include "Unit.h"

#include "Gene.h"




Unit::Unit(const Gene& gene)
	: ENERGY_PER_MEMORY(16.0)
	
	, m_energy(0.0)
	, m_position(VectorF::Zero)
	, m_speed(VectorF::Zero)
	, m_radius(16.0f)
	, m_direction(1.0f, 0.0f)
	, m_angle(0.0f)

	, m_gene(std::make_unique<Gene>(gene))
{
	m_energy = ENERGY_PER_MEMORY * gene.getCode().size();
}


Unit::~Unit()
{

}

//###########################################################################

void Unit::updatePosition()
{
	m_position += m_speed;
}

//###########################################################################

auto Unit::getPosition() const -> const VectorF&
{
	return m_position;
}


void Unit::setPosition(const VectorF& position)
{
	m_position = position;
}


void Unit::addPosition(const VectorF& move)
{
	m_position += move;
}


auto Unit::getSpeed() const -> const VectorF&
{
	return m_speed;
}


void Unit::setSpeed(const VectorF& speed)
{
	m_speed = speed;
}


void Unit::addSpeed(const VectorF& accelerate)
{
	m_speed += accelerate;
}


float Unit::getRadius() const
{
	return m_radius;
}


auto Unit::getDirection() const -> const VectorF&
{
	return m_direction;
}


float Unit::getAngle() const
{
	return m_angle;
}

