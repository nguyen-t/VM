OBJDIR=objects
SRCDIR=src
HDRDIR=include
INPUTS=vm instructions cpu
DEPS=cpu instructions
OBJECTS=$(addprefix $(OBJDIR)/, $(addsuffix .o, $(INPUTS)))
SOURCES=$(addprefix $(SRCDIR)/, $(addsuffix .c, $(INPUTS)))
HEADERS=$(addprefix $(HDRDIR)/, $(addsuffix .h, $(DEPS)))
TEST=test/store.txt
CC=gcc
CFLAGS=-c -Werror -Wextra -I$(HDRDIR) -o
LDFLAGS=-I$(HDRDIR) -o
OUTPUT=vm

.PHONY: run
.PHONY: clean
.PHONY: all

all: | $(OBJDIR) $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT) $(TEST) $(shell wc -l < $(TEST))

clean:
	rm -r $(OBJECTS) $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CC) $(LDFLAGS) $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $@ $<

$(OBJDIR):
	mkdir $@
