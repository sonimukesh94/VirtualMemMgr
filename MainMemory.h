/*
 * MainMemory.h
 *
 *  Created on: 08-Oct-2017
 *      Author: hp
 */

#ifndef MAINMEMORY_H_
#define MAINMEMORY_H_

#include "Page.h"
#include "MemoryManager.h"
#include <stdint.h>
#include <vector>

class MainMemory {
public:
	MainMemory(uint32_t maxFrames, uint32_t frameSize);
	virtual ~MainMemory();

	uint32_t addPage(Page* newPage);
	uint32_t addPage(Page* newPage, uint32_t pageNumber);
	Page* getPageAtFrame(uint32_t frame);
	bool readData(uint32_t addr, uint8_t *buffer, uint32_t nbytes, uint32_t frameNumber);
	bool writeData(uint32_t addr, const uint8_t *buffer, uint32_t nbytes, uint32_t frameNumber);
	uint32_t addPage(uint32_t pageNumer);
    uint32_t getFrameSize() const;
    uint32_t getMaxFrames() const;
    void setMaxFrames(uint32_t m_maxFrames);
    uint32_t getTotOccupiedFrames();

    void registerMemoryMgr(MemoryManager *mm);
    Page* retrievePage(uint32_t frameNumber);

    void reset();
private:
//	Page *m_pages;
//	std::pair<Page*, int> m_frames;
//	std::map<int, Page*> m_frames;
	std::vector<Page*> m_frames;
	uint32_t m_maxFrames;
	uint32_t m_frameSize;

	MemoryManager *memoryManager;
	uint32_t demandNewPage(uint32_t pageNumber);
};

#endif /* MAINMEMORY_H_ */
