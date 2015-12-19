CC = gcc
DEBUGFLAGS = -g -O0

CCFLAGS = $(CC)

journal: src/journal.c
		$(CCFLAGS) -o journal src/journal.c

debug: CCFLAGS += $(DEBUGFLAGS)
debug: journal

clean:
		rm journal
