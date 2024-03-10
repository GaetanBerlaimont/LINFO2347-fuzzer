CC := gcc

CFLAGS := -Wall

PROG := fuzzer
OBJS := src/help.o src/util.o

all: $(PROG)
	./fuzzer ./extractor_x86_64

%.o: src/%.c
	$(CC) -c $(CFLAGS) src/help.c
	$(CC) -c $(CFLAGS) src/util.c

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


visu:
	hexdump -C archive_basic.tar >  tar_contents/visu_basic.txt
	hexdump -C archive_medium.tar > tar_contents/visu_medium.txt
	hexdump -C archive_linked.tar > tar_contents/visu_linked.txt

clean:
	rm -f src/*.o
	touch src/vide.txt
