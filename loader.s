.set MAGIC, 0x1badb002	#magic number
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
	.long MAGIC
	.long FLAGS
	.long CHECKSUM

.section .text
.extern kernelEntry
.extern callConstructors
.global loader

loader:
	mov $kernelStack, %esp
	call callConstructors	#call constructors for all objects
	push %eax	# multiboot structure with some information about the pc
	push %ebx	# the magic number
	call kernelEntry	# jump to kernel, shouldnt come back

_stop: #infinite loop if for some reason kernel comes back
	cli
	hlt
	jmp _stop




.section .bss
.space 2*1024*1024 # 2MiB space away from the loader
kernelStack:
