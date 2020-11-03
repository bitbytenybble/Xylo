#Author: bitbytenybble@Github
# Date: 10/19/2020


############ AT&T SYNTAX - INTEL OPERAND ORDER ##################
.intel_syntax noprefix
# intel syntax changes:
#             1) Removes requirement for register and constant prefixes
#			  2) Can use intel syntax memory addressing (Square brackets and manual addition/multiplication)
#             3) Changes operand order to - instruction dest, src
#
.section .data
gdtr_val:
	.ZERO 6 # Declare 6 bytes initialized to 0








.global load_gdt
.section .text


# GTDR holds:
#    1) Size of GDT - lower 16 bits. I.E (2^16)
#	 2) Upper 32-bits holds memory location of table

refresh_segments:
	mov eax, 0x10             # Points to the new kernel data descriptor

	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret


load_gdt:
	cli
	xor eax, eax		      # clear eax
	add eax, [esp+4]		  # Get frst argument (32-bit int)
	mov [gdtr_val + 2], eax   # Set 32-bit address to last 4 bytes of 6 bit array
	mov ax, [esp+8]           # Get second argument (16-bit int)
	mov [gdtr_val], ax		  # Move the size to the first 16 bits of the gdtr_value array to be loaded into the gdtr
	lgdt [gdtr_val]			  # Load the the gdtr_value array into the actual gdtr.

	jmp 0x08:refresh_segments # 0x08 points to the new kernel code segment
