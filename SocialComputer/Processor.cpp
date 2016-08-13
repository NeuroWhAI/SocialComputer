#include "Processor.h"

#include "Unit.h"




Processor::Processor(Unit& owner,
	const std::vector<char>& code,
	std::vector<Memory>& memory,
	const size_t& validMemSize)
	: m_owner(owner)

	, m_isEnd(false)
	, m_code(code)
	, m_codeLength(code.size())
	, m_memory(memory)
	, m_validMemSize(validMemSize)
	, m_register(0)
	, m_ptr(0)
	, m_head(0)
{
	m_isEnd = !readyCode(code);


	// 명령어 셋 초기화
	m_cmdSet[0] = &Processor::increasePtr;
	m_cmdSet[1] = &Processor::decreasePtr;
	m_cmdSet[2] = &Processor::increaseData;
	m_cmdSet[3] = &Processor::decreaseData;
	m_cmdSet[4] = &Processor::pushData;
	m_cmdSet[5] = &Processor::pullData;
	m_cmdSet[6] = &Processor::jumpIfZero;
	m_cmdSet[7] = &Processor::jumpIfNotZero;
	m_cmdSet[8] = &Processor::getDirection;
	m_cmdSet[9] = &Processor::grow;
	m_cmdSet[10] = &Processor::writeRegister;
	m_cmdSet[11] = &Processor::readRegister;
	m_cmdSet[12] = &Processor::getLength;
}

//###########################################################################

bool Processor::isEnd() const
{
	return ((m_head >= m_codeLength) || m_isEnd);
}


void Processor::update()
{
	m_isEnd = !(this->*m_cmdSet[m_code[m_head]])();


	m_owner.addAngleSpeed(static_cast<float>(m_register) / Memory::MAX_DATA);
}


void Processor::updateMemory()
{
	if (m_ptr < m_validMemSize)
	{
		m_memory[m_ptr].update();
	}
}

//###########################################################################

bool Processor::readyCode(const std::vector<char>& code)
{
	/// 코드 길이
	const size_t codeLength = code.size();


	// 메모리 포인터를 첫부분으로 옮긴다.
	m_ptr = 0;

	// 코드 헤더를 첫부분으로 옮긴다.
	m_head = 0;


	// 괄호 짝의 위치를 미리 계산해둔다.
	m_getBeginBracket.clear();
	m_getBeginBracket.resize(codeLength, 0);

	m_getEndBracket.clear();
	m_getEndBracket.resize(codeLength, 0);


	/// 괄호 짝을 찾기위한 스택
	std::stack<size_t> beginBracket;

	// 괄호 짝을 찾는다.
	for (size_t i = 0; i < codeLength; ++i)
	{
		// 괄호 짝 찾기.
		if (code[i] == 6)
		{
			beginBracket.push(i);
		}
		else if (code[i] == 7)
		{
			if (beginBracket.empty())
			{
				// 괄호의 짝이 맞지 않으므로 실패.
				return false;
			}
			else
			{
				// 짝을 찾았음.

				size_t beginIndex = beginBracket.top();
				beginBracket.pop();

				m_getBeginBracket[i] = beginIndex;
				m_getEndBracket[beginIndex] = i;
			}
		}
	}


	return true;
}

//###########################################################################

bool Processor::increasePtr()
{
	++m_head;

	if (m_ptr < m_validMemSize - 1)
	{
		++m_ptr;
	}
	else
	{
		m_ptr = 0;
	}


	return true;
}


bool Processor::decreasePtr()
{
	++m_head;

	if (m_ptr > 0)
	{
		--m_ptr;
	}
	else
	{
		m_ptr = m_validMemSize - 1;
	}


	return true;
}


bool Processor::increaseData()
{
	++m_head;

	if (m_ptr < m_validMemSize)
	{
		m_memory[m_ptr].reserve(&Memory::increase);

		auto oldData = m_memory[m_ptr].getData();
		if (oldData < 0)
		{
			m_owner.addEnergy(1);
		}
		else
		{
			m_owner.addEnergy(-1);
		}
	}


	return true;
}


bool Processor::decreaseData()
{
	++m_head;

	if (m_ptr < m_validMemSize)
	{
		m_memory[m_ptr].reserve(&Memory::decrease);

		auto oldData = m_memory[m_ptr].getData();
		if (oldData > 0)
		{
			m_owner.addEnergy(1);
		}
		else
		{
			m_owner.addEnergy(-1);
		}
	}


	return true;
}


bool Processor::pushData()
{
	++m_head;

	if (m_ptr < m_validMemSize)
	{
		m_memory[m_ptr].reserve(&Memory::push);
	}


	return true;
}


bool Processor::pullData()
{
	++m_head;

	if (m_ptr < m_validMemSize)
	{
		m_memory[m_ptr].reserve(&Memory::pull);
	}


	return true;
}


bool Processor::jumpIfZero()
{
	if (m_ptr >= m_validMemSize
		|| m_memory[m_ptr].getData() == 0)
	{
		m_head = m_getEndBracket[m_head];
	}
	else
	{
		++m_head;
	}


	return true;
}


bool Processor::jumpIfNotZero()
{
	if (m_ptr < m_validMemSize
		&& m_memory[m_ptr].getData() != 0)
	{
		m_head = m_getBeginBracket[m_head];
	}
	else
	{
		++m_head;
	}


	return true;
}


bool Processor::getDirection()
{
	++m_head;

	if (m_ptr < m_validMemSize)
	{
		const auto& linkerPosition = m_memory[m_ptr].getLinkerPosition();
		const auto& unitPosition = m_owner.getPosition();
		const auto& unitSpeed = m_owner.getSpeed();

		auto dirVec = linkerPosition - unitPosition;

		auto dot = dirVec.dotProduct(unitSpeed);

		m_memory[m_ptr].reserveData(&Memory::writeData,
			static_cast<Memory::DataType>(dot));
	}


	return true;
}


bool Processor::grow()
{
	++m_head;

	if (m_ptr < m_validMemSize)
	{
		m_memory[m_ptr].reserve(&Memory::grow);

		float speed = static_cast<float>(m_memory[m_ptr].getData()) / Memory::MAX_DATA;
		m_owner.addSpeed(m_owner.getDirection() * speed);
	}


	return true;
}


bool Processor::writeRegister()
{
	++m_head;

	if (m_ptr < m_validMemSize)
	{
		m_register = m_memory[m_ptr].getData();
	}


	return true;
}


bool Processor::readRegister()
{
	++m_head;

	if (m_ptr < m_validMemSize)
	{
		m_memory[m_ptr].reserveData(&Memory::writeData, m_register);
	}


	return true;
}


bool Processor::getLength()
{
	++m_head;

	if (m_ptr < m_validMemSize)
	{
		const auto& linkerPosition = m_memory[m_ptr].getLinkerPosition();
		const auto& unitPosition = m_owner.getPosition();

		auto subVec = linkerPosition - unitPosition;

		m_memory[m_ptr].reserveData(&Memory::writeData,
			static_cast<Memory::DataType>(subVec.getLength()));
	}


	return true;
}

