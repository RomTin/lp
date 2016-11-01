.cc.o:

	g++ -c $(CFLAGS) $<

CC = g++
YACC = bison

YFLAGS = -d -v -y
DFLAG = 
CFLAGS = -I${INCDIR} ${EXINCFLAG}
SOURCEDIR = ..
PSOURCEDIR = ..
INCDIR = ${PSOURCEDIR}
EXINCFLAG = 
YFILES = calc2.y
I86OBJFILES = ${PSOURCEDIR}/calc12-scanner.o

MACHINE = $(shell uname -i)


calc2 : y.tab.c y.tab.h ${OFILES}
ifneq (,$(findstring i86,${MACHINE}))
	${CC} ${CFLAGS} -o $@ y.tab.c ${I86OBJFILES}
endif

y.tab.c y.tab.h: ${YFILES}
	${YACC} ${YFLAGS} ${DFLAG} ${YFILES}

clean:
	rm -f calc2 y.tab.* y.output

