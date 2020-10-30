#ifndef GDT_H
#define GDT_H
#include <stdint.h>


// ########################### FLAGS ###########################

// GRANULARITY
// Byte granularity specifies that the limit specified by the descriptor is the number of bytes
// Page granularity specifies that the limit specified by the descriptor is the number of pages
// NOTE: 1 PAGE = 4KiB = 2^12 Bytes
#define BYTE_GRANULARITY 0x00
#define PAGE_GRANULARITY 0x80

// SEGMENT OPERAND SIZE
// Can choose to run 16 or 32 bit segments in 32-bit protected mode
#define SEGMENT_OP_SIZE_16BIT 0x00
#define SEGMENT_OP_SIZE_32BIT 0x40

// AVL (Available for use by system software)
#define AVL 0x10
#define NOT_AVL 0x00


// IA-32e long mode
#define LONG_MODE_SET 0x20
#define LONG_MODE_NOT_SET 0x00

// ########################### ACCESS BYTE ###########################

// DESCRIPTOR PRIVILEGE LEVEL (RING LEVEL)
#define DPL_KERNEL_MODE 0x00
#define DPL_RING_1 0x20
#define DPL_RING_2 0x40
#define DPL_USER_MODE 0x60

// SEGMENT TYPE
#define SYSTEM_SEGMENT 0x00
#define CODE_OR_DATA_SEGMENT 0x10

// SEGMENT VALIDITY
#define SEGMENT_VALID  0x80
#define SEGMENT_INVALID 0x00


// EXECUTABLE BIT (1 for exec, 0 for data)
#define CODE_SEGMENT 0x08
#define DATA_SEGMENT 0x00


// DIRECTION BIT OR CONFORMING BIT

// If the segment is a data segment, then the bit is considered a direction bit.
// Set 0 if segment grows upwards. Or set 1 if segment grows downward, but the offset has to be greater than the limit.

// If the segment is a code segment, then the bit is a conforming bit.
// Set 0 if this code can only be executed from the ring set in the DPL ring selected. Or
// set 1 if the code in this segment can be executed from an equal or lower privelege level
// For example, code in ring 3 can far-jump to conforming code in a ring 2 segment.
// The privl-bits represent the highest privilege level that is allowed to execute the segment.
// For example, code in ring 0 cannot far-jump to a conforming code segment with privl==0x2, while
// code in ring 2 and 3 can. Note that the privilege level remains the same,
// ie. a far-jump form ring 3 to a privl==2-segment remains in ring 3 after the jump.
#define GROW_UPWARD 0x00
#define GROW_DOWNWARD 0x04
// BELOW IS REDUNDANT BUT IS USED FOR ABSTRACTION PURPOSES
#define CONFORMS_TO_DPL_RING 0x00
#define CONFORMS_TO_CURR_OR_LOWER 0x04



// READ/WRITE BIT
// if code segment, set bit to READ - execute persmission is already set
// if data segment, set bit to WRITE - read permission is already set
// Note: Both macros are the same but duplicated for abstraction
#define EXECUTE_AND_READ 0x0A
#define READ_AND_WRITE 0x02



// ACCESSED
// Access bit is set to 1 by CPU when accessed
#define SEGMENT_NOT_ACCESSED_YET 0x00



// ########################### SEGMENT DEFINITIONS ###########################
// BASIC FLAT MODEL


// Standard/Universal flags for all segments
#define GDT_UNIVERSAL_FLAGS PAGE_GRANULARITY | SEGMENT_OP_SIZE_32BIT | LONG_MODE_NOT_SET | NOT_AVL


// Kernel code access byte
#define GDT_KERNEL_CODE_SEGMENT_ACCESS (SEGMENT_VALID        | \
										DPL_KERNEL_MODE      | \
										CODE_OR_DATA_SEGMENT | \
										CODE_SEGMENT         | \
										CONFORMS_TO_DPL_RING | \
										EXECUTE_AND_READ     | \
										SEGMENT_NOT_ACCESSED_YET)




// Kernel data access byte
#define GDT_KERNEL_DATA_SEGMENT_ACCESS (SEGMENT_VALID   | \
										DPL_KERNEL_MODE | \
										CODE_OR_DATA_SEGMENT  | \
										DATA_SEGMENT    | \
										GROW_UPWARD     | \
										READ_AND_WRITE  | \
										SEGMENT_NOT_ACCESSED_YET)




// Userspace code segment
#define GDT_USER_CODE_SEGMENT_ACCESS  (SEGMENT_VALID | \
									   DPL_USER_MODE | \
									   CODE_OR_DATA_SEGMENT  | \
									   CODE_SEGMENT | \
									   CONFORMS_TO_DPL_RING |\
									   EXECUTE_AND_READ | \
									   SEGMENT_NOT_ACCESSED_YET)



// Userspace data segment
#define GDT_USER_DATA_SEGMENT_ACCESS   (SEGMENT_VALID | \
										DPL_USER_MODE | \
										CODE_OR_DATA_SEGMENT  | \
										DATA_SEGMENT | \
										GROW_UPWARD    | \
										READ_AND_WRITE | \
									    SEGMENT_NOT_ACCESSED_YET)





// ########################### STRUCT DEFINITION ###########################






typedef struct {
	// LSB of struct
	uint16_t limit;
	uint16_t base_1_2; // Least significant 16 bits of base (total 32-bits)
	uint8_t  base_3;   // 3rd byte of base (total 32-bits)
	uint8_t  access;   // Configures segment type, descriptor type, descriptor privllege level, and segment present
	uint8_t  flags_and_lim_end; // Sets most sig 4-bits of limit and configures avl, granularity, default operand size
	uint8_t  base_4;   // 4th byte of base (total 32-bits)
} __attribute__((packed)) SegmentDescriptor;






// Loads the GDT's address into the GDTR
void initGDT();
extern void load_gdt();

#endif
