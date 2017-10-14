/*
 * SecondaryMemory.h
 *
 *  Created on: 08-Oct-2017
 *      Author: hp
 */

#ifndef SECONDARYMEMORY_H_
#define SECONDARYMEMORY_H_
#include "string"
#include "Page.h"

class SecondaryMemory {
public:
	SecondaryMemory(uint32_t tableSize, uint32_t pageSize);
	virtual ~SecondaryMemory();

	Page* readPage(uint32_t pageNumber);
	bool  writePage(Page *page);

	uint32_t getMaxPages();
	uint32_t getPageSize();

	bool initMemory(uint8_t value);
	void reset();
	uint32_t getFileSize();

private:
	uint32_t m_pageSize;
	uint32_t m_maxPages;
	const std::string m_fileName;


};

#endif /* SECONDARYMEMORY_H_ */
