#pragma once


#include <vector>
#include <array>

#include "Memory.h"
#include "Gene.h"




class Unit;


class Processor
{
public:
	explicit Processor(Unit& owner,
		const std::vector<char>& code,
		std::vector<Memory>& memory,
		const size_t& validMemSize);


protected:
	Unit& m_owner;


protected:
	bool m_isEnd;
	const std::vector<char>& m_code;
	const size_t m_codeLength;
	std::vector<Memory>& m_memory;
	const size_t& m_validMemSize;
	Memory::DataType m_register;
	size_t m_ptr;
	size_t m_head;
	std::vector<size_t> m_getBeginBracket;
	std::vector<size_t> m_getEndBracket;


protected:
	std::array<bool (Processor::*)(), Gene::CMD_COUNT> m_cmdSet;


public:
	bool isEnd() const;
	void update();
	void updateMemory();


protected:
	bool readyCode(const std::vector<char>& code);


protected:
	bool increasePtr();
	bool decreasePtr();
	bool increaseData();
	bool decreaseData();
	bool pushData();
	bool pullData();
	bool jumpIfZero();
	bool jumpIfNotZero();
	bool getDirection();
	bool grow();
	bool writeRegister();
	bool readRegister();
	bool getLength();
};

