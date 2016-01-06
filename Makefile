CC = gcc
DEBUGFLAGS = -g -O0

CCFLAGS = $(CC)

journal: src/journal.c
		$(CCFLAGS) -o journal src/journal.c

debug: CCFLAGS += $(DEBUGFLAGS)
debug: journal

clean:
		rm journal
		rm .current
		rm entries/2*
