HDRDIR=include
SRCDIR=src
OBJDIR=objects
TSTDIR=test
DEPS=$(basename $(shell ls $(HDRDIR)))
INPUTS=$(basename $(shell ls $(SRCDIR)))
HEADERS=$(addprefix $(HDRDIR)/, $(addsuffix .h, $(DEPS)))
SOURCES=$(addprefix $(SRCDIR)/, $(addsuffix .c, $(INPUTS)))
OBJECTS=$(addprefix $(OBJDIR)/, $(addsuffix .o, $(INPUTS)))
CC=gcc
CFLAGS=-c -Werror -Wextra -I$(HDRDIR) -o
LDFLAGS=-I$(HDRDIR) -o
OUTPUT=vm
ARGS=$(shell wc -l test/store.txt)

.PHONY: run
.PHONY: clean
.PHONY: all

all: | $(HDRDIR) $(SRCDIR) $(OBJDIR) $(TSTDIR) $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT) $(TEST) $(ARGS)

clean:
	rm $(OBJECTS) $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CC) $(LDFLAGS) $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $@ $<

$(HDRDIR) $(SRCDIR) $(OBJDIR) $(TSTDIR): % :
	mkdir $@
