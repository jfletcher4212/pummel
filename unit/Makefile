
# add your test to this list
TARGS=test_xml_io #test_diff test_else

# tests to execute
#EXECS=./test_xml_io && ./test_diff && ./test_else

# the names of the functions you want coverage on
FUNCS=*

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##

CXX=g++
LIBS=-L/usr/lib -lQtGui -lQtCore -lpthread 

INC=-I/usr/include -I/usr/share/qt4/mkspecs/linux-g++ -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I./tests/ -I./

# objects for linking
OBJECTS:=$(wildcard ../src/*.o)


all: $(TARGS)
	echo $(TARGS) | sed 's/test_/\.\/test_/g' | `sed 's/ / \&\& /g'`

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
