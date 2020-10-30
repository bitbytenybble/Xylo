#include "gdt.h"
#include <stdio.h>
// Always set paged





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

};



// The first descriptor in the GDT is always a null descriptor and can never be used to access memory.
// At least two segment descriptors (plus the null descriptor) are needed for the GDT, because the descriptor contains
// more information than just the base and limit fields.
// The two most relevant fields for us are the Type field and the Descriptor Privilege Level (DPL) field.
void initGDT(){
	// Passes pointer to array, and size-1 of array to be loaded into the 6-byte GDTR
	// The size is passed in as size-1 because it represents the final index position/offset from the start of the
	// table. E.g if the GDT is 48 bytes, the final address will be 47 (size-1) from the starting address (position 0)
	load_gdt(&gdt, sizeof(gdt)-1);
}
