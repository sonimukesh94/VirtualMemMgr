/*
 * MemoryInterface.h
 *
 *  Created on: 08-Oct-2017
 *      Author: hp
 */

#ifndef MEMORYINTERFACE_H_
#define MEMORYINTERFACE_H_

#include <stddef.h>
#include <stdint.h>

class MemoryInterface {
public:

	/// Read #nbytes from memory into buffer from given byte-address
	virtual void read(uint32_t addr, uint8_t *buffer, uint32_t nbytes) const = 0;
	/// Write #nbytes from buffer into memory specified by byte-address
	virtual void write(uint32_t addr, const uint8_t *buffer, uint32_t nbytes) = 0;

	/// Read 4 bytes from memory into word from given byte-address
	virtual void read(uint32_t addr, uint32_t &word) const = 0;
	/// Write 4 bytes from word into memory specified by byte-address
	virtual void write(uint32_t addr, uint32_t word)  = 0;

	/// Return the number of read ops until now.
	virtual size_t num_reads() const = 0;
	/// Return the number of write ops until now.
	virtual size_t num_writes() const  = 0;

	/// Byte value to initialize the memory
	virtual void set_init_mem(uint8_t value) = 0;

	/// Reset the memory
	virtual void reset() = 0;

};

#endif /* MEMORYINTERFACE_H_ */
