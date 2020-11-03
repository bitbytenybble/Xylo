#ifndef TSS_H
#define TSS_H

#define NUM_OF_TSS_FIELDS 26

#define LINK 0
#define ESP0 1
#define SS0 2
#define ESP1 3
#define SS1 4
#define ESP2 5
#define SS2 6
#define CR3 7
#define EIP 8
#define EFLAGS 9
#define EAX 10
#define ECX 11
#define EDX 12
#define EBX 13
#define ESP 14
#define EBP 15
#define ESI 16
#define EDI 17
#define ES 18
#define CS 19
#define SS 20
#define DS 21
#define FS 22
#define GS 23
#define LDTR 24
#define IOPB_offset 25



#define GDT_TSS_ACCESS 0x89




/* Template

#define LINK
#define ESP0
#define SS0
#define ESP1
#define SS1
#define ESP2
#define SS2
#define CR3
#define EIP
#define EFLAGS
#define EAX
#define ECX
#define EDX
#define EBX
#define ESP
#define EBP
#define ESI
#define EDI
#define ES
#define CS
#define SS
#define DS
#define FS
#define GS
#define LDTR
#define IOPB_offset
*/



typedef struct {
	uint32_t tss_fields[NUM_OF_TSS_FIELDS];
} __attribute__((packed)) TSS; // Possibly redundant attribute due to 4 byte alignment


#endif
