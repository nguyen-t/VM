
OBJDIR=objects/
SRCDIR=src/
HDRDIR=include/
OBJECTS=$(addprefix $(OBJDIR), vm.o instructions.o cpu.o)
SOURCES=$(addprefix $(SRCDIR), vm.c instructions.c cpu.c)
HEADERS=$(addprefix $(HDRDIR), cpu.h instructions.h)
TEST=test/store.txt
CC=gcc
CFLAGS=-c -Werror -Wextra -I$(HDRDIR) -o
LDFLAGS=-I$(HDRDIR) -o
TFLAGS=-I$(HDRDIR) -E
OUTPUT=vm

.PHONY: run
.PHONY: clean

$(OUTPUT): | $(OBJDIR) $(OBJECTS)
	$(CC) $(LDFLAGS) $@ $(OBJECTS)

objects/vm.o: src/vm.c $(HEADERS)
	$(CC) $(CFLAGS) $@ src/vm.c

objects/instructions.o: src/instructions.c $(HEADERS)
	$(CC) $(CFLAGS) $@ src/instructions.c

objects/cpu.o: src/cpu.c $(HEADERS)
	$(CC) $(CFLAGS) $@ src/cpu.c

$(OBJDIR):
	mkdir $@

translate: src/cpu.c
	$(CC) $(TFLAGS) src/cpu.c -o asm.vm

run: $(OUTPUT)
	./$(OUTPUT) $(TEST) $(shell wc -l < $(TEST))

clean:
	rm -r $(OBJECTS) $(OUTPUT)
