CC = gcc
DEBUGFLAGS = -g -O0

CCFLAGS = $(CC)

journal: journal.c
		$(CCFLAGS) -o journal journal.c

debug: CCFLAGS += $(DEBUGFLAGS)
debug: journal

clean:
		rm journal
