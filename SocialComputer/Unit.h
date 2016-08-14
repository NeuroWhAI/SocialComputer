#pragma once


#include <memory>
#include <vector>
#include <unordered_map>

#include <CodeAdapter\EasyCA.h>

#include "Memory.h"




class Gene;
class Processor;
class Linker;


class Unit
{
private:
	USING_CA_DRAWING(VectorF);

	USING_CA_UTILITY(Angle);


public:
	static const double ENERGY_PER_MEMORY;


public:
	explicit Unit(const Gene& gene);
	virtual ~Unit();


protected:
	double m_energy;
	VectorF m_position;
	VectorF m_speed;
	float m_radius;
	VectorF m_direction;
	Angle m_angle;
	float m_angleSpeed;


protected:
	std::unique_ptr<Gene> m_gene;


protected:
	size_t m_validMemSize;
	std::vector<Memory> m_memory;
	std::vector<Linker*> m_newLinkerList;
	std::unique_ptr<Processor> m_processor;
	std::unordered_map<const Unit*, size_t> m_linkerHub;


public:
	void updateState();
	void updateProcessor();
	void updateMemory();


public:
	double getEnergy() const;
	void addEnergy(double energy);
	const VectorF& getPosition() const;
	void setPosition(const VectorF& position);
	void addPosition(const VectorF& move);
	const VectorF& getSpeed() const;
	void setSpeed(const VectorF& speed);
	void addSpeed(const VectorF& accelerate);
	float getRadius() const;
	const VectorF& getDirection() const;
	float getAngle() const;
	void setAngle(float degree);
	void addAngleSpeed(float degreeSpeed);


public:
	void pushMemory(size_t index, Memory::DataType data);
	Memory::DataType pullMemory(size_t index);
	size_t assignLinkerIndex(const Unit* user);


public:
	const std::vector<Linker*>& getNewLinkerList() const;
	void clearNewLinkerList();
};

