# テスト用のmakefile

.cc.o:
	g++ $(CFLAGS) -c $<


VPATH = ${SOURCEDIR}:${TESTDIR}
CC = g++
YACC = bison

YFLAGS = -d -v -y
CFLAGS = -I. -I${INCDIR} -I${TESTDIR} ${EXINCFLAG}
INCDIR = ${SOURCEDIR}
PSOURCEDIR = ..
SOURCEDIR = ..
TESTDIR = .
OFILES = ${TESTDIR}/interpret.o ${TESTDIR}/symtable.o \
         ${TESTDIR}/error.o ${TESTDIR}/print.o ${TESTDIR}/system.o
OBJFILES = ${OFILES} ${TESTDIR}/scanner.o
DOBJFILES = ${OFILES} ${TESTDIR}/scanner-debug.o
YFILES = $(SOURCEDIR)/tglc.y

MACHINE = $(shell uname -i)

all:    tglc

debug:  tglcd

tglc : y.tab.o
ifneq (,$(findstring i86,$(MACHINE)))
	$(CC) -o tglc -lm -L/usr/X11R6/lib -lX11 $(OBJFILES) $^
endif

tglcd : y.tab.o
ifneq (,$(findstring i86,$(MACHINE)))
	$(CC) -o tglc -lm -L/usr/X11R6/lib -lX11 $(DOBJFILES) $^
endif

# y.tab.o: y.tab.c
#	$(CC) -c ${CFLAGS} y.tab.c

y.tab.c: $(YFILES)
ifeq ($(MAKECMDGOALS),debug)
	$(YACC) $(YFLAGS) -t $(YFILES)
else
	$(YACC) $(YFLAGS) $(YFILES)
endif

clean:
	rm -f tglc *.result y.tab.* y.output
