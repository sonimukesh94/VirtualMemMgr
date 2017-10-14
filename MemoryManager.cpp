/*
 * MemoryManager.cpp
 *
 *  Created on: 08-Oct-2017
 *      Author: hp
 */

#include "MemoryManager.h"
#include "MainMemory.h"
#include <iostream>
#include <iomanip>

//#define KB 1024
//#define MB 1024 * 1024

using namespace std;

MemoryManager::MemoryManager():
m_pageSize(4096*1024),
m_frameSize(4096*1024),
m_maxPages(1024),
m_maxFrames(32)
{
	m_leastActiveFrame = 0;	// FIFO: assuming first frame is least active
	m_totalReads = 0;
	m_totalWrites = 0;

	m_pageTable  = new PageTable(getMaxPages(), getPageSize(), getMaxFrames()+1);  // 1024 * 4096 = 4GB
	m_mainMemory = new MainMemory(getMaxFrames(), getFrameSize()); // 32 * 4096 = 128MB
	m_scndMemory = new SecondaryMemory(getMaxPages(), getPageSize());	// 1024 * 4096 = 4GB
	cout << "Page Table size: " << m_pageTable->getTableSize() << endl;
	cout << "Page size: " << m_pageTable->getPageSize() << endl;
	cout << "Main memory frames: " << m_mainMemory->getMaxFrames() << endl;
	cout << "Main memory frame size: " << m_mainMemory->getFrameSize() << endl;

	// register callback operation to handle page fault
	this->m_mainMemory->registerMemoryMgr(this);
}

MemoryManager::~MemoryManager() {
	delete m_pageTable;
	delete m_mainMemory;
}

void MemoryManager::set_init_mem(uint8_t value)
{
	cout << "Initializing memory" << endl;

	m_scndMemory->initMemory(value);

	cout << "Memory initialized" << endl;
}

size_t MemoryManager::num_reads() const
{
	return getTotalReads();
}

void MemoryManager::read(uint32_t addr, uint8_t *buffer, uint32_t nbytes) const
{
	cout << "Reading " << nbytes << " bytes from address " << addr << endl;
	// map address to page number first
	uint32_t pageNumber = m_pageTable->getPageNumber(addr);
	uint32_t offset 	= m_pageTable->getPageOffset(addr);
	cout << "Page Number " << pageNumber << " offset " << offset << endl;
	uint32_t frameNumber = m_pageTable->getFrameNumber(pageNumber);
	cout << "Frame number " << frameNumber << endl;


	if(frameNumber > getMaxFrames()) // not initialized
	{
		cout << "Not Initialized. Loading page from secondary space" << endl;
		// load page to main memory from secondary memory
		frameNumber = this->loadNewPage(pageNumber);
	}

	// access data in main memory
	m_mainMemory->readData(offset, buffer, nbytes, frameNumber);

	m_totalReads++;
}

void MemoryManager::reset()
{
	cout << "Resetting Page Table" << endl;
	// Reset the page table
	m_pageTable->reset(m_mainMemory->getMaxFrames()+1);

	cout << "Resetting Main Memory" << endl;
	// delete the frames from main memory
	m_mainMemory->reset();

	cout << "Resetting Secondary Memory" << endl;
	// reset the secondary memory
	m_scndMemory->reset();

	// resetting the counters
	m_leastActiveFrame = 0;	// FIFO: assuming first frame is least active
	m_totalReads = 0;
	m_totalWrites = 0;
}

size_t MemoryManager::num_writes() const
{
	cout << "File Size: " << m_scndMemory->getFileSize();
	return getTotalWrites();
}

void MemoryManager::read(uint32_t addr, uint32_t & word) const
{
	uint8_t buffer[4];
	this->read(addr, buffer, 4);
	cout << "Buffer = " << buffer << endl;
	word = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | (buffer[3]);
}

void MemoryManager::write(uint32_t addr, uint32_t word)
{
	uint8_t buffer[4];
	buffer[0] = (word >> 24) & 0xFF;
	buffer[1] = (word >> 16) & 0xFF;
	buffer[2] = (word >> 8) & 0xFF;
	buffer[3] = (word & 0xFF);
	cout << "Buffer to write = " << buffer << endl;
	this->write(addr, buffer, 4);
}

void MemoryManager::write(uint32_t addr, const uint8_t *buffer, uint32_t nbytes)
{
	cout << "Writing " << nbytes << " bytes to address " << addr << endl;
	// map address to page number first
	uint32_t pageNumber = m_pageTable->getPageNumber(addr);
	uint32_t offset 	= m_pageTable->getPageOffset(addr);
	cout << "Page Number " << pageNumber << " offset " << offset << endl;
	uint32_t frameNumber = m_pageTable->getFrameNumber(pageNumber);
	cout << "Frame number " << frameNumber << endl;


	if(frameNumber > getMaxFrames()) // not initialized
	{
		cout << "Not Initialized. Loading page from secondary space" << endl;
		// load page to main memory from secondary memory
		frameNumber = this->loadNewPage(pageNumber);
	}

	// access data in main memory
	m_mainMemory->writeData(offset, buffer, nbytes, frameNumber);

	m_totalWrites++;
}

const uint32_t MemoryManager::getFrameSize() const
{
    return m_frameSize;
}

const uint32_t MemoryManager::getMaxFrames() const
{
    return m_maxFrames;
}

const uint32_t MemoryManager::getMaxPages() const
{
    return m_maxPages;
}

const uint32_t MemoryManager::getPageSize() const
{
    return m_pageSize;
}

uint32_t MemoryManager::loadNewPage(uint32_t pageNumber) const
{
	Page *newPage = m_scndMemory->readPage(pageNumber);
	// check if main memory has empty frames
	if(m_mainMemory->getTotOccupiedFrames() == this->getMaxFrames())
	{
		// all the frames are occupied, swap a page with secondary memory to make some place here
		// TODO: get the appropriate frameNumber to be removed using suitable algo
		cout << "Main memory is full" << endl;
		uint32_t oldFrameNumber = this->m_leastActiveFrame;
		Page *oldPage = m_mainMemory->retrievePage(oldFrameNumber);
		m_scndMemory->writePage(oldPage);

		uint32_t frameNumber = m_mainMemory->addPage(newPage,
				m_pageTable->getFrameNumber(oldPage->m_pageNumber));

		// unlink old frame from page table
		m_pageTable->setFrameNumber(oldPage->m_pageNumber, getMaxFrames()+1);
		// link the new frame in page table
		m_pageTable->setFrameNumber(pageNumber, frameNumber);

		// free the memory which was allocated for old page
		delete[] oldPage->m_data;
		delete oldPage;

		// we would have removed the least active frame from the main memory. so, point for the next one now
		m_leastActiveFrame = m_leastActiveFrame + 1;
		if(m_leastActiveFrame == getMaxFrames())
			m_leastActiveFrame = 0;

		return frameNumber;
	}
	else
	{
		uint32_t frameNumber = m_mainMemory->addPage(newPage);
		// link the new frame in page table
		m_pageTable->setFrameNumber(pageNumber, frameNumber);
		return frameNumber;
	}
}

uint32_t MemoryManager::getTotalReads() const
{
    return m_totalReads;
}

uint32_t MemoryManager::getTotalWrites() const
{
    return m_totalWrites;
}

void MemoryManager::setTotalReads(uint32_t m_totalReads)
{
    this->m_totalReads = m_totalReads;
}

void MemoryManager::setTotalWrites(uint32_t m_totalWrites)
{
    this->m_totalWrites = m_totalWrites;
}








