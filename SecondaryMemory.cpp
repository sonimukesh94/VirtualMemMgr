/*
 * SecondaryMemory.cpp
 *
 *  Created on: 08-Oct-2017
 *      Author: hp
 */

#include "SecondaryMemory.h"
#include <stdio.h>
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

SecondaryMemory::SecondaryMemory(uint32_t tableSize, uint32_t pageSize):
m_fileName("storageFile.bin")
{
	this->m_maxPages = tableSize;
	this->m_pageSize = pageSize;
}

SecondaryMemory::~SecondaryMemory() {
	// TODO Auto-generated destructor stub
}

Page *SecondaryMemory::readPage(uint32_t pageNumber)
{
	FILE *fp = fopen(m_fileName.c_str(), "rb");
	if(fp != NULL)
	{
		cout << "Successfully opened file " << m_fileName << endl;
		// set the file pointer position
		fseek(fp, pageNumber * this->getPageSize(), SEEK_SET);

		// read the data into buffer
		Page *newPage = new Page(pageNumber, this->getPageSize());
		fread(newPage->m_data, this->getPageSize(), 1, fp);
		cout << "Returning new page " << pageNumber << endl;
		return newPage;
	}
	else
	{
		std::cout << "Failed to open file" << endl;
		return NULL;
	}
}

bool SecondaryMemory::writePage(Page *page)
{
	cout << "Writing page " << page->m_pageNumber << " to file"  << endl;

	FILE *fp = fopen(m_fileName.c_str(), "rwb");
	if(fp != NULL)
	{
		cout << "Successfully opened file " << m_fileName << endl;
		// set the file pointer position
		fseek(fp, page->m_pageNumber * this->getPageSize(), SEEK_SET);

		fwrite(page->m_data, sizeof(uint8_t), this->getPageSize(), fp);

		return true;
	}
	else
	{
		std::cout << "Failed to open file" << endl;
		return false;
	}
}

uint32_t SecondaryMemory::getMaxPages()
{
    return m_maxPages;
}

uint32_t SecondaryMemory::getPageSize()
{
    return m_pageSize;
}

void SecondaryMemory::reset()
{
	FILE *fp = fopen(m_fileName.c_str(), "wb");
	fclose(fp);
}

bool SecondaryMemory::initMemory(uint8_t value)
{
	cout << "Initializing Memory of Size: " << getMaxPages() << " X " << getPageSize()
			<< " Bytes" << endl;
	//create new file
	FILE *fp = fopen(m_fileName.c_str(), "wb");
	if(fp == NULL)
	{
		std::cout << "Failed to create secondary storage file" << endl;
		return false;
	}

	uint8_t arr[getMaxPages()];
	for(uint32_t i = 0; i < getMaxPages() ; i++)
		arr[i] = value;
//	for(int i = 0; i < getPageSize() ; i++)
//		std::fstream(m_fileName.c_str(), std::ios::app | std::ios::binary).write((char*)&arr, sizeof(arr));
	struct timeval tp;
	gettimeofday(&tp, NULL);
	long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;

	for(uint32_t i = 0; i < getPageSize() ; i++)
			fwrite(&arr, sizeof(uint8_t), sizeof(arr), fp);
	struct timeval tp2;
	gettimeofday(&tp2, NULL);
	long int ms2 = tp2.tv_sec * 1000 + tp2.tv_usec / 1000;
	cout << "Total time taken to initialize the memory " << ms2 - ms << endl;
//	uint8_t arr[1024] = "";
//	for(unsigned long long int i = 0; i < 4096; i++)
//		fwrite(&arr, sizeof(uint8_t), sizeof(arr)-1, fp);
	//fprintf(fp, "Test Data");
	fclose (fp);
	cout << "Successfully Initialized secondary memory" << endl;
	return true;
}

uint32_t SecondaryMemory::getFileSize()
{
	fstream file(m_fileName.c_str(), ios::ate | ios::binary | ios::in | ios::out);

	fstream::pos_type size = file.tellg();

	cout << "File Size: " << file.tellg() << endl;
	return 0;
}



//bool SecondaryMemory::initMemory(uint8_t value)
//{
//	cout << "Initializing Memory of Size: " << getMaxPages() << " X " << getPageSize()
//			<< " Bytes" << endl;
//	fstream outFile(m_fileName.c_str(), ios::binary|ios::out|ios::in);
//	someFile.write(someData, 100);
//	cout << "Successfully Initialized secondary memory" << endl;
//	return true;
//}

