/*
 * PageTable.cpp
 *
 *  Created on: 08-Oct-2017
 *      Author: hp
 */

#include "PageTable.h"
#include <vector>
#include <iostream>

using namespace std;
/*
PageTable::PageTable() {
	// TODO Auto-generated constructor stub

}
*/

PageTable::PageTable(uint32_t tableSize, uint32_t pageSize, uint32_t init)
{
	this->m_tableSize = tableSize;
	this->m_pageSize = pageSize;
	this->mapPageToFrame.resize(tableSize);
	this->reset(init);
}

PageTable::~PageTable() {
	// TODO Auto-generated destructor stub
}

uint32_t PageTable::getPageNumber(uint32_t addr)
{
	// FIXME: hard coding for now. change MASK value based on page table dimensions.
	uint32_t pageNumber = (0xFFC00000 & addr) >> 22;
	return pageNumber;
}

uint32_t PageTable::getPageOffset(uint32_t addr)
{
	// FIXME: hard coding for now. change MASK value based on page table dimensions.
	uint32_t pageOffset = (0x003FFFFF & addr);
	return pageOffset;
}

uint32_t PageTable::getPageSize() const
{
    return m_pageSize;
}

uint32_t PageTable::getTableSize() const
{
    return m_tableSize;
}

void PageTable::setPageSize(uint32_t m_pageSize)
{
    this->m_pageSize = m_pageSize;
}

uint32_t PageTable::getFrameNumber(uint32_t pageNumber)
{
	return mapPageToFrame[pageNumber];
}

void PageTable::setFrameNumber(uint32_t pageNumber, uint32_t frameNumber)
{
	mapPageToFrame[pageNumber] = frameNumber;;
}

void PageTable::setTableSize(uint32_t m_tableSize)
{
    this->m_tableSize = m_tableSize;
}

void PageTable::printTable()
{
	// FIXME: remove later
//	for(uint32_t i = 0; i < getTableSize(); i++)
	for(uint32_t i = 0; i < 10; i++)
		cout << "Index " << i << " Value " << mapPageToFrame[i] << endl;
}

void PageTable::reset(uint32_t init)
{
	for(uint32_t i = 0; i < getTableSize(); i++)
		mapPageToFrame[i] = init;
}








