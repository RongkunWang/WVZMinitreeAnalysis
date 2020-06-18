ROOTLIBS = `root-config --libs`
OPTCOMP = `root-config --cflags`

SPECIALFLAGS= --exceptions
CFLAGS = -I.
LFLAGS =

RCXX = $(CFLAGS) $(ROOTCFLAGS)
DBG = -g -L -O -m32
CC = g++ ${DBG} $(RCXX) $(OPTCOMP)
F77 = f77

all: run

run: run.o ana.o ana_base.o ZZZ_ana.o WZZ_ana.o WWZ_ana.o
	$(CC) run.o ana.o ana_base.o ZZZ_ana.o WZZ_ana.o WWZ_ana.o $(ROOTLIBS) -o run

run.o: run.cpp
	$(CC) -c run.cpp -o run.o

ana.o: ana.cpp ana.h
	$(CC) -c ana.cpp -o ana.o

ana_base.o: ana_base.C ana_base.h
	$(CC) -c ana_base.C -o ana_base.o

ZZZ_ana.o: ZZZ_ana.cpp ana.h
	$(CC) -c ZZZ_ana.cpp -o ZZZ_ana.o

WZZ_ana.o: WZZ_ana.cpp ana.h
	$(CC) -c WZZ_ana.cpp -o WZZ_ana.o

WWZ_ana.o: WWZ_ana.cpp ana.h
	$(CC) -c WWZ_ana.cpp -o WWZ_ana.o

clean: 
	\rm -rf *.o
