/*
 * MainMemory.cpp
 *
 *  Created on: 08-Oct-2017
 *      Author: hp
 */

#include "MainMemory.h"
#include <string.h>
#include "MemoryManager.h"
#include <iostream>

using namespace std;

MainMemory::MainMemory(uint32_t maxFrames, uint32_t frameSize) {
	m_frameSize = frameSize;
	m_maxFrames = maxFrames;
	memoryManager = NULL;
	m_frames.resize(m_maxFrames);
	m_frames.clear();
}

MainMemory::~MainMemory() {
	// TODO Auto-generated destructor stub
}

uint32_t MainMemory::addPage(Page *newPage)
{
	cout << "Adding new page to the main memory " << newPage->m_pageNumber << endl;

	// FIXME: adding page at last to implement FIFO page replacement algo.
	// Page must be inserted at appropriate place based on page replacement algo.
	m_frames.push_back(newPage);
	cout << "Number of frames present in main memory: " << m_frames.size() << endl;
	return (m_frames.size()-1);
}
uint32_t MainMemory::addPage(Page *newPage, uint32_t frameIndex)
{
	cout << "Adding new page " <<  newPage->m_pageNumber
			<< " to the main memory at index " << frameIndex << endl;
	m_frames[frameIndex] = newPage;
	cout << "Number of frames present in main memory: " << m_frames.size() << endl;
	return (frameIndex);
}

Page *MainMemory::retrievePage(uint32_t frameNumber)
{
	// FIXME: need to remove particular frame number
	if(frameNumber > getMaxFrames())
		return NULL;
	Page *page = m_frames[frameNumber];

	//m_frames.pop_back();
	return page;
}

Page* MainMemory::getPageAtFrame(uint32_t frame)
{
	return m_frames[frame];
}

#if 0
uint32_t MainMemory::addPage(uint32_t pageNumer)
{
	Page *newPage = new Page(pageNumer);

	// check if main memory has empty frames
	if(m_frames.size() == this->getMaxFrames())
	{
		// all the frames are occupied, swap a page with secondary memory to make some place here
		// TODO:
	}
	// FIXME: adding page at last to implement FIFO page replacement algo.
	// Page must be inserted at appropriate place based on page replacement algo.
	m_frames.push_back(newPage);
	return (m_frames.size()-1);

}
#endif
uint32_t MainMemory::getFrameSize() const
{
    return m_frameSize;
}

uint32_t MainMemory::getMaxFrames() const
{
    return m_maxFrames;
}

bool MainMemory::readData(uint32_t offset, uint8_t *buffer, uint32_t nbytes, uint32_t frameNumber)
{
	cout << "Reading data from frame " << frameNumber << endl;
	// get the active page based on frameNumber
	Page *curFrame = m_frames[frameNumber];
	uint32_t avaibytes = this->getFrameSize() - offset;
	cout << "Total bytes to read " << nbytes << " .Available bytes in current frame "
			<< avaibytes << endl;
	if(nbytes > avaibytes)
	{
		memcpy(buffer, curFrame->m_data + offset, avaibytes);
		uint32_t remainbytes = nbytes - avaibytes;
		// demand for the next frame from memory manager to copy rest of the data
		// Its a page fault, which will block the current operation until new frame is loaded in
		// main memory
		uint32_t nextFrame = this->demandNewPage(curFrame->m_pageNumber + 1);
		readData(0, buffer + avaibytes, remainbytes, nextFrame);
	}
	else
	{
		memcpy(buffer, curFrame->m_data + offset, nbytes);
	}
	return true;
}
bool MainMemory::writeData(uint32_t offset, const uint8_t *buffer, uint32_t nbytes, uint32_t frameNumber)
{
	cout << "Writing data to frame " << frameNumber << endl;
	// get the current active page based on frameNumber
	Page *curFrame = m_frames[frameNumber];
	uint32_t avaibytes = this->getFrameSize() - offset;
	cout << "Total bytes to write " << nbytes << " .Available bytes in current frame "
			<< avaibytes << endl;
	if(nbytes > avaibytes)
	{
		memcpy(curFrame->m_data + offset, buffer, avaibytes);
		uint32_t remainbytes = nbytes - avaibytes;
		// demand for the next frame from memory manager to copy rest of the data
		// Its a page fault, which will block the current operation until new frame is loaded in
		// main memory
		uint32_t nextFrame = this->demandNewPage(curFrame->m_pageNumber + 1);
		writeData(0, buffer + avaibytes, remainbytes, nextFrame);
	}
	else
	{
		memcpy(curFrame->m_data + offset, buffer, nbytes);
	}
	return true;
}

void MainMemory::setMaxFrames(uint32_t m_maxFrames)
{
    this->m_maxFrames = m_maxFrames;
}

void MainMemory::registerMemoryMgr(MemoryManager *mm)
{
	this->memoryManager = mm;
}

void MainMemory::reset()
{
	for(vector<Page*>::iterator it = m_frames.begin(); it != m_frames.end(); it++)
	{
		Page *page = *(it);
		delete[] page->m_data;
		delete page;
	}
	m_frames.clear();
}

uint32_t MainMemory::demandNewPage(uint32_t pageNumber)
{
	return this->memoryManager->loadNewPage(pageNumber);
}

uint32_t MainMemory::getTotOccupiedFrames()
{
	return m_frames.size();
}






