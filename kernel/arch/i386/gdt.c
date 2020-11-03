#include "gdt.h"
#include <stdio.h>
#include <string.h>

#define GDT_TSS_INDEX 5

TSS kernel_tss;




const SegmentDescriptor gdt[] = {
	{.limit = 0, .flags_and_lim_end = 0, .base_1_2 = 0, .base_3=0, .base_4=0, .access = 0},


	{.limit = 0xffff, .flags_and_lim_end = 0x0f | GDT_UNIVERSAL_FLAGS, .base_1_2 = 0, .base_3=0, .base_4=0,
		.access = GDT_KERNEL_CODE_SEGMENT_ACCESS},


	{.limit = 0xffff, .flags_and_lim_end = 0x0f | GDT_UNIVERSAL_FLAGS, .base_1_2 = 0, .base_3=0, .base_4=0,
		.access = GDT_KERNEL_DATA_SEGMENT_ACCESS},


	{.limit = 0xffff, .flags_and_lim_end = 0x0f | GDT_UNIVERSAL_FLAGS, .base_1_2 = 0, .base_3=0, .base_4=0,
			.access = GDT_USER_CODE_SEGMENT_ACCESS},


	{.limit = 0xffff, .flags_and_lim_end = 0x0f | GDT_UNIVERSAL_FLAGS, .base_1_2 = 0, .base_3=0, .base_4=0,
			.access = GDT_USER_DATA_SEGMENT_ACCESS},


	{.limit = 0, .flags_and_lim_end = 0, .base_1_2 = 0, .base_3=0, .base_4=0, .access = 0},

};


void setup_tss(){
	uint32_t tss_addr =(uint32_t)(&kernel_tss);
	uint8_t tss_size = sizeof(kernel_tss);

	SegmentDescriptor temp_tss;
	// Set the base address for the TSS, in the TSS descriptor of the GDT
	temp_tss.base_1_2 = tss_addr & 0x0000FFFF;
	temp_tss.base_3   = (tss_addr & 0x00FF0000) >> 16; // Shift masked bits to 8-bit range, to tbe truncated.
	temp_tss.base_4   = (tss_addr & 0xFF000000) >> 24;


	temp_tss.limit = tss_size & 0xFF;   // Max size 255
	temp_tss.flags_and_lim_end =  0x00; // Flags are set to 0, limit should never need the last 4
   	    					 		    // bits (fixed TSS size of 104 bytes).

	// TSS access flags
	temp_tss.access = GDT_TSS_ACCESS;

	// Copy TSS descriptor into CONST array.
	void * destPtr = (((uint64_t*)gdt) + GDT_TSS_INDEX);
	memmove(destPtr, &temp_tss, sizeof(SegmentDescriptor));
}

// The first descriptor in the GDT is always a null descriptor and can never be used to access memory.
// At least two segment descriptors (plus the null descriptor) are needed for the GDT, because the descriptor contains
// more information than just the base and limit fields.
// The two most relevant fields for us are the Type field and the Descriptor Privilege Level (DPL) field.
void initGDT(){

	// Sets up the tss descriptor
	setup_tss();


	// Passes pointer to array, and size-1 of array to be loaded into the 6-byte GDTR
	// The size is passed in as size-1 because it represents the final index position/offset from the start of the
	// table. E.g if the GDT is 48 bytes, the final address will be 47 (size-1) from the starting address (position 0)
	load_gdt(&gdt, sizeof(gdt)-1);
}
