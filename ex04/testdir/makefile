CC = g++
CFLAGS = -DTEST -I. -I${INCDIR} ${EXINCFLAG}
SOURCEDIR = ..
TESTDIR = .
PSOURCEDIR = ..
INCDIR = ${SOURCEDIR}
CFILES = ${SOURCEDIR}/parse.cc ${PSOURCEDIR}/error.cc ${PSOURCEDIR}/lf.cc
OBJFILES = ${TESTDIR}/lf-scanner.o

MACHINE = $(shell uname -i)


lf : ${CFILES}
	${CC} ${CFLAGS} -o $@ ${CFILES} ${OBJFILES}

clean:
	rm -f lf test[0-9][0-9].in.result
