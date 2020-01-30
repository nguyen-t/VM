OBJDIR=objects
SRCDIR=src
HDRDIR=include
TSTDIR=test
INPUTS=$(basename $(shell ls $(SRCDIR)))
DEPS=$(basename $(shell ls $(HDRDIR)))
OBJECTS=$(addprefix $(OBJDIR)/, $(addsuffix .o, $(INPUTS)))
SOURCES=$(addprefix $(SRCDIR)/, $(addsuffix .c, $(INPUTS)))
HEADERS=$(addprefix $(HDRDIR)/, $(addsuffix .h, $(DEPS)))
CC=gcc
CFLAGS=-c -Werror -Wextra -I$(HDRDIR) -o
LDFLAGS=-I$(HDRDIR) -o
OUTPUT=vm
ARGS=$(shell wc -l test/store.txt)

.PHONY: run
.PHONY: clean
.PHONY: all

all: | $(OBJDIR) $(SRCDIR) $(HDRDIR) $(TSTDIR) $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT) $(TEST) $(ARGS)

clean:
	rm $(OBJECTS) $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CC) $(LDFLAGS) $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $@ $<

$(OBJDIR):
	mkdir $@

$(SRCDIR):
	mkdir $@

$(HDRDIR):
	mkdir $@

$(TSTDIR):
	mkdir $@
