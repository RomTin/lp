.cc.o:

	g++ -c $(CFLAGS) $<

VPATH = ${SOURCEDIR}:${TESTDIR}
CC = g++
YACC = bison

YFLAGS = -d -v -y
DFLAG = 
CFLAGS = -I${INCDIR} ${EXINCFLAG}
SOURCEDIR = ..
TESTDIR = .
PSOURCEDIR = ..
INCDIR = ${PSOURCEDIR}
EXINCFLAG = 
YFILES = ${SOURCEDIR}/strlist.y
OFILES = error.o
I86OBJFILES = ${TESTDIR}/scanner.o

MACHINE = $(shell uname -i)


all:	strlist

strlist : y.tab.c y.tab.h ${OFILES}
ifneq (,$(findstring i86,${MACHINE}))
	${CC} ${CFLAGS} -o $@ y.tab.c ${I86OBJFILES} ${OFILES}
endif

y.tab.c y.tab.h: ${YFILES}
	${YACC} ${YFLAGS} ${DFLAG} ${YFILES}

clean:
	rm -f strlist y.tab.* y.output ${OFILES} \
              test[0-9].in.result test[0-9][0-9].in.result

