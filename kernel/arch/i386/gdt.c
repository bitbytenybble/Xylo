#include "gdt.h"
#include <stdio.h>
// Always set paged




// TODO FILL OUT ABOVE 3 DESCRIPTORS AND ENTER ALL 5 INTO ARRAY BELOW



const SegmentDescriptor GDT[] = {
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

	//printf(""%p", (void*)&(GDT[0]));
	asm("hlt");
}
