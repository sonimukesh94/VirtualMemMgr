/*
 * Client.cpp
 *
 *  Created on: 10-Oct-2017
 *      Author: hp
 */

#include <iostream>
#include "MemoryInterface.h"
#include "MemoryManager.h"
#include <string.h>
#include <stdint.h>

using namespace std;


int main()
{
	cout << "###### START ######" << endl;
	uint8_t *buffer = new uint8_t[1025];
	MemoryInterface *mm = new MemoryManager;
	//mm->set_init_mem('a');
	memset(buffer, 0x00, 1025);
#if 0
	// TEST CASE 1: Reading bytes from different pages in multiple read requests, when
	// all the required memory bytes are present in the same page
	uint32_t addr = 0x0000000A;
	for(uint32_t i = 0; i < 75; i++)
	{
		memset(buffer, 0x00, 1024);
		mm->read(addr, buffer, 5);
		addr = addr + (0x00400000) ;
		cout << "Buffer = " << buffer << endl;
		cout << "Next address " << addr << endl;
	}
#endif

#if 0
	// TEST CASE 2: Reading bytes from different pages in single read requests, when
	// all the required memory bytes are distributed across multiple pages
	uint32_t addr = 0x003FFFF6;
	memset(buffer, 0x00, 1024);
	mm->read(addr, buffer, 15);
	cout << "Buffer = " << buffer << endl;
#endif

#if 0
	// TEST CASE 3: Read a single word from address having all the 4 bytes present in single page
	uint32_t word;
	mm->read(0x00000000, word);
	cout << "Word = " << word << endl;
#endif

//#if 0
	// TEST CASE 4: Writing bytes to different pages in multiple read requests, when
	// all the required memory bytes are present in the same page
	uint32_t addr = 0x0000000A;
	memset(buffer, 0x00, 1024);
	memset(buffer, 'b', 1024);
	for(uint32_t i = 0; i < 100; i++)
	{
		mm->write(addr, buffer, 1024);
		addr = addr + (0x00400000) ;
//		cout << "Buffer = " << buffer << endl;
		cout << "Next address " << addr << endl;
	}
	addr = 0x00000000;
	for(uint32_t i = 0; i < 10; i++)
	{
		memset(buffer, 0x00, 1024);
		mm->read(addr, buffer, 25);
		addr = addr + (0x00400000) ;
		cout << "Buffer = " << buffer << endl;
		cout << "Next address " << addr << endl;
	}
//#endif

#if 0
	// TEST CASE 5: Read a single word from address having all the 4 bytes present in single page
	uint32_t word = 1633837924; // abcd
	uint32_t addr = 0x00000000;
	mm->write(addr, word);

	memset(buffer, 0x00, 1024);
	mm->read(addr, buffer, 4);
	cout << "Buffer = " << buffer << endl;
#endif
	size_t num = mm->num_writes();
	cout << num << endl;
	num = mm->num_reads();
	cout << num << endl;

	cout << "###### END #######" << endl;
}
