
## ## ## ## ## ## ## ## ## ## ##
##           MODIFY           ##
## ## ## ## ## ## ## ## ## ## ##
FUNCS=

## ## ## ## ## ## ## ## ## ## ##
##         VARIABLES          ##
## ## ## ## ## ## ## ## ## ## ##

## executable list
TESTS:=$(wildcard ./tests/*.h)
TARGS:=$(patsubst ./tests/%.h,%,$(TESTS))
EXE:=$(patsubst ./tests/%.h,./%;,$(TESTS))

## src objects
OBJS:=$(wildcard ../src/*.o)
OBJS:=$(patsubst ../src/main.o,,$(OBJS))

## build options
CXX=g++
LIBS=-L/usr/lib -lQtGui -lQtCore -lpthread -lgcov
INC=-I/usr/include -I/usr/share/qt4/mkspecs/linux-g++ -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I./tests/ -I./

## src build options
SRC_DEFINES= -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
SRC_CXX= -pipe -O2 -Wall -W -D_REENTRANT $(SRC_DEFINES) -fprofile-arcs -ftest-coverage
SRC_LIBS= -L/usr/lib -lQtGui -lQtCore -lpthread -lgcov

## ## ## ## ## ## ## ## ## ## ##
##           RULES            ##
## ## ## ## ## ## ## ## ## ## ##

## collection rules
all_coverage: $(TARGS)
	cp $(TARGS) ../src/; cd ../src/; trucov all_report --selection * '$(EXE)'; rm moc_*.svg moc_*.trucov; mv *.svg *.trucov ../unit/; rm $(TARGS)

all: $(TARGS)
	$(EXE)

## individual rules
%_coverage: %
	trucov all_report --srcdir ../src/ --builddir ../src/ selection $(FUNCS) ./$<

%: %.o $(OBJS)
	$(CXX) $(INC) -o $@ $< $(OBJS) $(LIBS)

%.o: %.cpp
	$(CXX) $(INC) -c $< $(LIBS)

%.cpp: ./tests/%.h
	cxxtestgen --error-printer -o $@ $<

## maintenance rules
clean:
	rm -rf *.o *.cpp *.trucov *.svg $(TARGS)

setup:
	cd ../src/; make DEFINES='$(SRC_DEFINES)' CXXFLAGS='$(SRC_CXX)' LIBS='$(SRC_LIBS)'

full_setup:
	cd ../src/; make clean; qmake -project; qmake; make DEFINES='$(SRC_DEFINES)' CXXFLAGS='$(SRC_CXX)' LIBS='$(SRC_LIBS)'
