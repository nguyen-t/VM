# Edit to fit needs
HDREXT=.h
SRCEXT=.c
OBJEXT=.o
CC=gcc
LINKS=a b c
SANS=undefined,address,leak
WARNS=all pedantic extra
OUTPUT=vm
EXEC=exec
ARGS=$(shell wc -l test/input)

# Shouldn't really be touched
HDRDIR=include
SRCDIR=src
OBJDIR=objects
TSTDIR=test
DEPS=$(basename $(shell ls $(HDRDIR)))
INPUTS=$(basename $(shell ls $(SRCDIR)))
HEADERS=$(addprefix $(HDRDIR)/, $(addsuffix $(HDREXT), $(DEPS)))
SOURCES=$(addprefix $(SRCDIR)/, $(addsuffix $(SRCEXT), $(INPUTS)))
OBJECTS=$(addprefix $(OBJDIR)/, $(addsuffix $(OBJEXT), $(INPUTS)))
CFLAGS=$(addprefix -W, $(WARNS)) $(addprefix -l, $(LINKS)) -I$(HDRDIR) -c -o
LDFLAGS=-fsanitize=$(SANS) -o

.PHONY: all
.PHONY: run
.PHONY: clean

all: | $(HDRDIR) $(SRCDIR) $(OBJDIR) $(TSTDIR) $(OUTPUT)

run: $(OUTPUT)
	$(EXEC) ./$(OUTPUT) $(ARGS)

clean:
	rm $(OBJECTS) $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CC) $(LDFLAGS) $@ $^

$(OBJDIR)/%$(OBJEXT): $(SRCDIR)/%$(SRCEXT) $(HEADERS)
	$(CC) $(CFLAGS) $@ $<

$(HDRDIR) $(SRCDIR) $(OBJDIR) $(TSTDIR): % :
	mkdir $@
