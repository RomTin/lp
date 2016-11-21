.cc.o:
	g++ $(CFLAGS) -c $<

VPATH = ${SOURCEDIR}:${TESTDIR}:${PSOURCEDIR}
CC = g++
SOURCEDIR = ..
PSOURCEDIR = ..
TESTDIR = .
CFLAGS = -I${TESTDIR} -I${INCDIR} ${EXINCFLAG}
OBJFILES = symtable-test.o error.o
INCDIR = ${PSOURCEDIR}
EXINCFLAG = -I${TESTDIR}


all:	test01 test02 test03 test04 test05 test06 test07 test08  \
        test09 test10 test11 test12 test13 test14 test15 test16  \
        test17 test18 test19 test20 test21 test22 test23 test24  \
        test25 test26 test27 test28 test29 test30


test01 : test01.cc ${OBJFILES}
	${CC} ${CFLAGS} -o $@ $^
 
test02 : test02.cc ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test03 : test03.cc ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^
test04 : test04.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test05 : test05.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^
test06 : test06.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test07 : test07.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test08 : test08.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test09 : test09.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test10 : test10.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test11 : test11.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test12 : test12.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test13 : test13.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test14 : test14.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test15 : test15.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test16 : test16.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test17 : test17.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test18 : test18.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^
test19 : test19.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test20 : test20.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test21 : test21.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test22 : test22.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test23 : test23.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test24 : test24.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test25 : test25.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test26 : test26.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test27 : test27.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test28 : test28.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test29 : test29.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

test30 : test30.o ${OBJFILES} 
	${CC} ${CFLAGS} -o $@ $^

error.o: ${PSOURCEDIR}/error.cc
	${CC} -c -o $@ ${CFLAGS} $^

symtable-test.o: ${SOURCEDIR}/symtable.cc ${SOURCEDIR}/symtable.h
	${CC} -c ${CFLAGS} -o $@ ${TESTDIR}/symtable-test.cc


clean:
	rm -f *.o test[0-9][0-9] test[0-9][0-9].result
