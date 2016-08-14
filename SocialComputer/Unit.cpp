#include "Unit.h"

#include "Gene.h"
#include "Processor.h"
#include "Linker.h"


#define F_PI 3.14159265358979323846f




const double Unit::ENERGY_PER_MEMORY = 128.0;

//###########################################################################

Unit::Unit(const Gene& gene)
	: m_energy(0.0)
	, m_position(VectorF::Zero)
	, m_speed(VectorF::Zero)
	, m_radius(8.0f)
	, m_direction(1.0f, 0.0f)
	, m_angle(0.0f)
	, m_angleSpeed(0.0f)

	, m_gene(std::make_unique<Gene>(gene))

	, m_validMemSize(gene.getCode().size())
{
	m_energy = ENERGY_PER_MEMORY * gene.getCode().size();
	
	m_memory.resize(m_validMemSize);
	if (m_memory.size() < 1)
	{
		m_memory.resize(1);
		m_validMemSize = 1;
	}

	for (auto& mem : m_memory)
	{
		Linker* linker = mem.getLinker();
		linker->setOwner(this);
		linker->setPosition(m_position);

		m_newLinkerList.push_back(linker);
	}

	m_processor = std::make_unique<Processor>(*this,
		m_gene->getCode(),
		m_memory, m_validMemSize);
}


Unit::~Unit()
{

}

//###########################################################################

void Unit::updateState()
{
	m_speed -= m_speed / 128.0f;

	m_position += m_speed;


	setAngle(m_angle + m_angleSpeed);

	m_angleSpeed = 0.0f;
}


void Unit::updateProcessor()
{
	if (m_processor->isEnd() == false
		&& m_energy > 0.0)
	{
		m_processor->update();
	}
}


void Unit::updateMemory()
{
	if (m_processor->isEnd() == false)
	{
		m_processor->updateMemory();
	}
}

//###########################################################################

double Unit::getEnergy() const
{
	return m_energy;
}


void Unit::addEnergy(double energy)
{
	m_energy += energy;
	

	size_t nextSize = static_cast<size_t>(m_energy / ENERGY_PER_MEMORY);

	if (nextSize > m_memory.size())
	{
		size_t oldSize = m_memory.size();

		m_memory.resize(nextSize);

		for (size_t i = oldSize; i < nextSize; ++i)
		{
			Linker* linker = m_memory[i].getLinker();
			linker->setOwner(this);
			linker->setPosition(m_position);

			m_newLinkerList.push_back(linker);
		}
	}

	m_validMemSize = nextSize;
}


auto Unit::getPosition() const -> const VectorF&
{
	return m_position;
}


void Unit::setPosition(const VectorF& position)
{
	m_position = position;


	for (auto& linker : m_newLinkerList)
	{
		linker->setPosition(position);
	}
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


	for (auto& mem : m_memory)
	{
		Linker* linker = mem.getLinker();

		if (linker->hasConnection() == false)
		{
			linker->addSpeed(accelerate);
		}
	}
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


void Unit::setAngle(float degree)
{
	m_angle = degree;

	// NOTE: Angle 클래스의 operator* 사용을 피하기 위해 float에 대입.
	float angle = m_angle;
	float toRad = 180.0f / F_PI;
	m_direction.y = -std::sin(angle * toRad);
	m_direction.x = std::cos(angle * toRad);
}


void Unit::addAngleSpeed(float degreeSpeed)
{
	m_angleSpeed += degreeSpeed;
}

//###########################################################################

void Unit::pushMemory(size_t index, Memory::DataType data)
{
	if (index < m_validMemSize)
	{
		m_memory[index].writeData(data);
	}
	else
	{
		addEnergy(std::abs(data));
	}
}


Memory::DataType Unit::pullMemory(size_t index)
{
	if (index < m_validMemSize)
	{
		auto data = m_memory[index].getData();
		m_memory[index].writeData(0);


		return data;
	}
	else
	{
		const Memory::DataType pullEnergy = 1;

		addEnergy(-pullEnergy);


		return pullEnergy;
	}
}


size_t Unit::assignLinkerIndex(const Unit* user)
{
	auto it = m_linkerHub.find(user);

	if (it == m_linkerHub.end())
	{
		m_linkerHub.insert(std::make_pair(user, 1));


		return 0;
	}
	
	
	return it->second++;
}

//###########################################################################

const std::vector<Linker*>& Unit::getNewLinkerList() const
{
	return m_newLinkerList;
}


void Unit::clearNewLinkerList()
{
	m_newLinkerList.clear();
}

