CC := gcc

CFLAGS := -Wall

PROG := fuzzer
OBJS := src/help.o src/util.o src/test.o

all: $(PROG)
	./fuzzer ./extractor_x86_64

%.o: src/%.c
	$(CC) -c $(CFLAGS) src/help.c
	$(CC) -c $(CFLAGS) src/util.c
	$(CC) -c $(CFLAGS) src/test.c

$(PROG): $(OBJS)
	$(CC) -o $@ $^ -lm



#helper function
arch_basic:
	tar --posix --pax-option delete=".*" --pax-option delete="*time*" --no-xattrs --no-acl --no-selinux -c tar_contents/vide.txt > archive_basic.tar

medium_arch:
	tar --posix --pax-option delete=".*" --pax-option delete="*time*" --no-xattrs --no-acl --no-selinux -c tar_contents/fable.txt tar_contents/wikipedia_pokemon.txt > archive_medium.tar

arch_linked:
#ln -s fable.txt simlink_fable
	tar --posix --pax-option delete=".*" --pax-option delete="*time*" --no-xattrs --no-acl --no-selinux -c simlink_fable fable.txt > archive_linked.tar

arch_dir:
	tar --posix --pax-option delete=".*" --pax-option delete="*time*" --no-xattrs --no-acl --no-selinux -c my_dir/ > archive_dir.tar


visu:
	hexdump -C archives/archive_basic.tar >  tar_contents/visu_basic.txt
	hexdump -C archives/archive_medium.tar > tar_contents/visu_medium.txt
	hexdump -C archives/archive_linked.tar > tar_contents/visu_linked.txt
	hexdump -C archives/archive_dir.tar > tar_contents/visu_dir.txt
	hexdump -C archives/archive.tar > tar_contents/current.txt

clean:
	rm -f src/*.o
