GPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = loader.o kernel.o

%.o: %.cpp
	g++ $(GPPPARAMS) -o $@ -c $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<

thekernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

os.iso: thekernel.bin
	mkdir -p isodir/boot/grub
	cp thekernel.bin isodir/boot/thekernel.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue --output=$@ isodir
	rm -rf isodir

install: os.iso
	qemu-system-i386 -cdrom os.iso &

run: thekernel.bin
	qemu-system-i386 -kernel thekernel.bin &

clean:
	rm *.o
	rm *.iso
	rm *.bin