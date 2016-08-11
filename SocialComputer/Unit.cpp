#include "Unit.h"




Unit::Unit()
	: m_position(VectorF::Zero)
	, m_speed(VectorF::Zero)
{

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

