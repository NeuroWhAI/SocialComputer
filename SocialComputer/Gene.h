#pragma once


#include <vector>
#include <random>




class Gene
{
public:
	Gene();


protected:
	const char CMD_COUNT;
	std::vector<char> m_code;


public:
	void initializeRandomly(std::mt19937& engine);


public:
	const std::vector<char>& getCode() const;


public:
	void combine(const Gene& other, std::mt19937& engine);
	void mutate(std::mt19937& engine);
};

