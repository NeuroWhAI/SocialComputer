#include "Memory.h"

#include "Linker.h"




Memory::Memory()
	: m_data(0)
	, m_linker(std::make_unique<Linker>())

	, m_willExecuted(nullptr)
	, m_willExecutedWithData(nullptr)
	, m_reservedData(0)
{

}

//###########################################################################

void Memory::update()
{
	if (m_willExecuted != nullptr)
	{
		(this->*m_willExecuted)();

		m_willExecuted = nullptr;
	}

	if (m_willExecutedWithData != nullptr)
	{
		(this->*m_willExecutedWithData)(m_reservedData);

		m_willExecutedWithData = nullptr;
	}
}


void Memory::reserve(void (Memory::*willExecuted)())
{
	m_willExecuted = willExecuted;
}


void Memory::reserveData(void (Memory::*willExecuted)(DataType), DataType data)
{
	m_willExecutedWithData = willExecuted;
	m_reservedData = data;
}

//###########################################################################

Linker* Memory::getLinker() const
{
	return m_linker.get();
}


auto Memory::getLinkerPosition() const -> const VectorF&
{
	return m_linker->getPosition();
}

//###########################################################################

auto Memory::getData() const -> DataType
{
	return m_data;
}


void Memory::writeData(DataType data)
{
	if (data < MIN_DATA)
		data = MIN_DATA;
	else if (data > MAX_DATA)
		data = MAX_DATA;

	m_data = data;
}


void Memory::increase()
{
	++m_data;

	// 오버플로
	if (m_data > MAX_DATA)
	{
		m_data = MIN_DATA;
	}
}


void Memory::decrease()
{
	--m_data;

	// 언더플로
	if (m_data < MIN_DATA)
	{
		m_data = MAX_DATA;
	}
}


void Memory::push()
{
	m_linker->push(m_data);
}


void Memory::pull()
{
	m_data = m_linker->pull();
}


void Memory::grow()
{
	m_linker->grow(m_data);
}

