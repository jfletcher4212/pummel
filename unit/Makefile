
## ## ## ## ## ## ## ## ## ## ##
##            LISTS           ##
## ## ## ## ## ## ## ## ## ## ##
TARGS=test_xml_io test_diff test_else
FUNCS=*

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
##          touch nothing below this line                         ##
## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##

CXX=g++
LIBS=-L/usr/lib -lQtGui -lQtCore -lpthread 

INC=-I/usr/include -I/usr/share/qt4/mkspecs/linux-g++ -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I./tests/ -I./

# objects for linking
OBJECTS:=$(wildcard ../src/*.o)
EXE=for test in `echo test_xml_io test_diff test_else | sed 's/test_/\.\/test_/g'`; do $$test; done


all: $(TARGS)
	$(EXE)
#	trucov all_report selection $(FUNCS) $(TARGS)


%_coverage: %
	trucov all_report selection $(FUNCS) ./$<

%: %.o $(OBJECTS)
	$(CXX) $(INC) -o $@ $< $(OBJECTS) $(LIBS)

%.o: %.cpp
	$(CXX) $(INC) -c $< $(LIBS)

%.cpp: ./tests/%.h
	cxxtestgen --error-printer -o $@ $<

clean:
	rm -rf *.o *.cpp $(TARGS)

setup:
	cd ../src/; make; rm main.o

full_setup:
	cd ../src/; make clean; qmake -project; qmake; make; rm main.o
