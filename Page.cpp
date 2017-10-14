/*
 * Page.cpp
 *
 *  Created on: 08-Oct-2017
 *      Author: hp
 */

#include "Page.h"

Page::Page(uint32_t pageNumber, uint32_t pageSize) {
	this->m_pageNumber = pageNumber;
	this->m_data = new uint8_t[pageSize];
}

Page::~Page() {
	// TODO Auto-generated destructor stub
}
