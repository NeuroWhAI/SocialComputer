#include "Linker.h"

#include "Unit.h"




Linker::Linker()
	: m_position(VectorF::Zero)
	, m_speed(VectorF::Zero)

	, m_owner(nullptr)

	, m_connectedUnit(nullptr)
	, m_connectedIndex(0)
{

}

//###########################################################################

void Linker::update()
{
	if (m_connectedUnit == nullptr)
	{
		m_speed -= m_speed / 128.0f;

		m_position += m_speed;
	}
	else
	{
		m_position = m_connectedUnit->getPosition();

		m_connectedUnit->addSpeed(m_speed);

		m_speed = VectorF::Zero;
	}
}

//###########################################################################

auto Linker::getPosition() const -> const VectorF&
{
	return m_position;
}


void Linker::setPosition(const VectorF& position)
{
	m_position = position;
}


void Linker::addPosition(const VectorF& move)
{
	m_position += move;
}


auto Linker::getSpeed() const -> const VectorF&
{
	return m_speed;
}


void Linker::setSpeed(const VectorF& speed)
{
	m_speed = speed;
}


void Linker::addSpeed(const VectorF& accelerate)
{
	m_speed += accelerate;
}

//###########################################################################

const Unit* Linker::getOwner() const
{
	return m_owner;
}


void Linker::setOwner(Unit* owner)
{
	m_owner = owner;
}

//###########################################################################

void Linker::connect(Unit* target, size_t index)
{
	m_connectedUnit = target;
	m_connectedIndex = index;
}


Unit* Linker::getConnectedUnit() const
{
	return m_connectedUnit;
}


bool Linker::hasConnection() const
{
	return (m_connectedUnit != nullptr);
}

//###########################################################################

void Linker::push(Memory::DataType data)
{
	if (m_connectedUnit != nullptr)
	{
		m_connectedUnit->pushMemory(m_connectedIndex, data);
	}
}


Memory::DataType Linker::pull()
{
	if (m_connectedUnit == nullptr)
	{
		return 0;
	}


	return m_connectedUnit->pullMemory(m_connectedIndex);
}


void Linker::grow(Memory::DataType data)
{
	if (m_owner != nullptr)
	{
		const float rate = static_cast<float>(data) / Memory::MAX_DATA;

		m_speed += m_owner->getDirection() * rate;
	}
}

