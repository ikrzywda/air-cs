============================================================================================
all: hello writeText compareText

hello: hello.s
    as hello.s -o hello.o --32
    ld hello.o -o hello -m elf_i386

writeText: writeText.s
    as writeText.s -o writeText.o --32
    ld writeText.o -o writeText -m elf_i386 

compareText: compareText.s
    as compareText.s -o compareText.o --32
    ld compareText.o -o compareText -m elf_i386
