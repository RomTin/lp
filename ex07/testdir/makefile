.cc.o:

	g++ -c $(CFLAGS) $<


CC = g++
SOURCEDIR = ..
PSOURCEDIR = ..
TESTDIR = .
CFLAGS = -I. -I${INCDIR} ${EXINCFLAG}
OBJFILES = symtable-test.o error.o
INCDIR = ${PSOURCEDIR}
OFILES = error.o

all:	test01 test02 test03 test04 test05 test06 test07 test08 test09 \
	test10 test11 test12 test13 test14 test15 test16 test17

test01 : ${TESTDIR}/test01.cc ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test02 : ${TESTDIR}/test02.cc ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test03 : ${TESTDIR}/test03.cc ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test04 : ${TESTDIR}/test04.cc ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test05 : ${TESTDIR}/test05.cc ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test06 : ${TESTDIR}/test06.cc ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test07 : ${TESTDIR}/test07.cc ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test08 : ${TESTDIR}/test08.cc ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test09 : ${TESTDIR}/test09.cc ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test10 : ${TESTDIR}/test10.cc ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test11 : ${TESTDIR}/test11.cc ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test12 : ${TESTDIR}/test12.cc ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test13 : ${TESTDIR}/test13.cc ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test14 : ${TESTDIR}/test14.cc ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test15 : ${TESTDIR}/test15.cc ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test16 : ${TESTDIR}/test16.cc ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test17 : ${TESTDIR}/test17.cc ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

symtable-test.o: ${SOURCEDIR}/symtable.cc ${SOURCEDIR}/symtable.h
	${CC} -c ${CFLAGS} -o $@ ${TESTDIR}/symtable-test.cc

error.o: ${PSOURCEDIR}/error.cc
	${CC} -c -o $@ ${CFLAGS} $^

clean:
	rm -f *.o test[0-9][0-9] test[0-9][0-9].result

