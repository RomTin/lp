CC = g++
CFLAGS = -DTEST -I. -I${INCDIR} ${EXINCFLAG}
EXINCFLAG = 
SOURCEDIR = ..
TESTDIR = .
PSOURCEDIR = ..
INCDIR = ..
CFILES = ${SOURCEDIR}/scanner.cc ${PSOURCEDIR}/error.cc
TESTFILES = ${TESTDIR}/driver.cc

all:	test01 test02 test03 test04 test05 test06

test01 : ${CFILES}
	${CC} ${CFLAGS} -DTEST01 -o $@ ${TESTFILES} ${CFILES}

test02 : ${CFILES}
	${CC} ${CFLAGS} -DTEST02 -o $@ ${TESTFILES} ${CFILES}

test03 : ${CFILES}
	${CC} ${CFLAGS} -DTEST03 -o $@ ${TESTFILES} ${CFILES}

test04 : ${CFILES}
	${CC} ${CFLAGS} -DTEST04 -o $@ ${TESTFILES} ${CFILES}

test05 : ${CFILES}
	${CC} ${CFLAGS} -DTEST05 -o $@ ${TESTFILES} ${CFILES}

test06 : ${CFILES}
	${CC} ${CFLAGS} -DTEST06 -o $@ ${TESTFILES} ${CFILES}

clean:
	rm -f *.o test[0-9][0-9] test[0-9][0-9].result tmp.in

