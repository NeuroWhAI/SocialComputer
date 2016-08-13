#pragma once


#include <memory>

#include <CodeAdapter\EasyCA.h>




class Linker;


class Memory
{
private:
	USING_CA_DRAWING(VectorF);


public:
	using DataType = int;


public:
	Memory();


public:
	static const DataType MAX_DATA = 128;
	static const DataType MIN_DATA = -MAX_DATA;


protected:
	DataType m_data;
	std::unique_ptr<Linker> m_linker;


protected:
	void (Memory::*m_willExecuted)();
	void (Memory::*m_willExecutedWithData)(DataType);
	DataType m_reservedData;


public:
	void update();
	void reserve(void (Memory::*willExecuted)());
	void reserveData(void (Memory::*willExecuted)(DataType), DataType data);


public:
	Linker* getLinker() const;
	const VectorF& getLinkerPosition() const;


public:
	DataType getData() const;
	void writeData(DataType data);
	void increase();
	void decrease();
	void push();
	void pull();
	void grow();
};

