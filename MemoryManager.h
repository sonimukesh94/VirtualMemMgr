/*
 * MemoryManager.h
 *
 *  Created on: 08-Oct-2017
 *      Author: hp
 */

#ifndef MEMORYMANAGER_H_
#define MEMORYMANAGER_H_

#include "MemoryInterface.h"
#include "PageTable.h"

#include "SecondaryMemory.h"

#include <stdint.h>
#include <stddef.h>

class MainMemory;

class MemoryManager: public MemoryInterface {
public:
	MemoryManager();
	virtual ~MemoryManager();
    virtual void read(uint32_t addr, uint8_t *buffer, uint32_t nbytes) const;
    virtual void write(uint32_t addr, const uint8_t *buffer, uint32_t nbytes);
    virtual void read(uint32_t addr, uint32_t & word) const;
    virtual void write(uint32_t addr, uint32_t word);
    virtual size_t num_reads() const;
    virtual size_t num_writes() const;
    virtual void set_init_mem(uint8_t value);
    virtual void reset();
    const uint32_t getFrameSize() const;
    const uint32_t getMaxFrames() const;
    const uint32_t getMaxPages() const;
    const uint32_t getPageSize() const;
    uint32_t loadNewPage(uint32_t pageNumber) const;
    uint32_t getTotalReads() const;
    uint32_t getTotalWrites() const;
    void setTotalReads(uint32_t m_totalReads);
    void setTotalWrites(uint32_t m_totalWrites);

private:
	const uint32_t m_pageSize;
	const uint32_t m_frameSize;
	const uint32_t m_maxPages;
	const uint32_t m_maxFrames;

mutable	uint32_t m_leastActiveFrame;

mutable	uint32_t m_totalReads;
		uint32_t m_totalWrites;

	PageTable 		*m_pageTable;
	MainMemory 		*m_mainMemory;
	SecondaryMemory *m_scndMemory;

	AbsPageReplacement *pageAlgo;
};

#endif /* MEMORYMANAGER_H_ */
