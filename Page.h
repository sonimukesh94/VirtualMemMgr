/*
 * Page.h
 *
 *  Created on: 08-Oct-2017
 *      Author: hp
 */

#ifndef PAGE_H_
#define PAGE_H_
#include <stdint.h>

class Page {
public:
	Page(uint32_t pageNumber, uint32_t pageSize);
	virtual ~Page();

public:
	uint32_t m_size;
	uint8_t *m_data;
	uint32_t m_pageNumber;
};

#endif /* PAGE_H_ */
