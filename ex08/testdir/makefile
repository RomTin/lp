.cc.o:

	g++ -c $(CFLAGS) $<


VPATH = ${SOURCEDIR}:${TESTDIR}
CC = g++
YACC = bison

YFLAGS = -d -v -y
DFLAG = 
CFLAGS = -I. -I${INCDIR} -I${TESTDIR} ${EXINCFLAG}
INCDIR = ${SOURCEDIR}
PSOURCEDIR = ..
SOURCEDIR = ..
TESTDIR = .
OBJFILES = ${TESTDIR}/symtable.o ${TESTDIR}/interpret.o
OBJ = ${TESTDIR}/scanner.o
DOBJ = ${TESTDIR}/scanner-debug.o
YFILES = ${SOURCEDIR}/smplc.y

MACHINE = $(shell uname -i)


all:	smplc

debug:  smplcd

smplc : y.tab.o
ifneq (,$(findstring i86,${MACHINE}))
	${CC} -o smplc -lm ${OBJFILES} ${OBJ} ${PSOURCEDIR}/error.cc $^
endif

smplcd: y.tab.o
ifneq (,$(findstring i86,${MACHINE}))
	${CC} -o smplc -lm ${OBJFILES} ${DOBJ} ${PSOURCEDIR}/error.cc $^
endif

y.tab.c: smplc.y
ifeq (${MAKECMDGOALS},debug)
	${YACC} ${YFLAGS} -t ${YFILES}
else
	${YACC} ${YFLAGS} ${YFILES}
endif

y.tab.o: y.tab.c
	${CC} -c ${CFLAGS} y.tab.c

clean:
	rm -f smplc y.tab.* test[0-9][0-9].smpl.result y.output
