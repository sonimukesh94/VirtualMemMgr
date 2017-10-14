/*
 * PageTable.h
 *
 *  Created on: 08-Oct-2017
 *      Author: hp
 */

#ifndef PAGETABLE_H_
#define PAGETABLE_H_

#include "AbsPageReplacement.h"
#include <vector>
#include <stdint.h>
class PageTable {
public:
	//PageTable();
	PageTable(uint32_t tableSize, uint32_t pageSize, uint32_t init);
	virtual ~PageTable();
    uint32_t getPageSize() const;
    uint32_t getTableSize() const;
    uint32_t getPageNumber(uint32_t addr);
    uint32_t getPageOffset(uint32_t addr);
    uint32_t getFrameNumber(uint32_t pageNumber);
    void setFrameNumber(uint32_t pageNumber, uint32_t frameNumber);
    std::vector<int> getMapPageToFrame() const;
    AbsPageReplacement *getPageAlgo() const;
    void setMapPageToFrame(std::vector<int> mapPageToFrame);
    void setPageAlgo(AbsPageReplacement *pageAlgo);
    void setPageSize(uint32_t m_pageSize);
    void setTableSize(uint32_t m_tableSize);
    void printTable();
    void reset(uint32_t init);
private:
	uint32_t m_tableSize;
	uint32_t m_pageSize;
	// Page Map Table
	std::vector<int> mapPageToFrame;
};

#endif /* PAGETABLE_H_ */
