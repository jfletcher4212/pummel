
## ## ## ## ## ## ## ## ## ## ##
##           MODIFY           ##
## ## ## ## ## ## ## ## ## ## ##
FUNCS=write_xml parse_xml

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
all_report: all_coverage
	./push_reports.py $(TARGS)

all_coverage: $(TARGS)
	cp $(TARGS) ../src/; cd ../src/; trucov all_report --selection * '$(EXE)'; rm moc_*.svg moc_*.trucov; mv *.svg *.trucov ../unit/; rm $(TARGS)

all: $(TARGS)
	$(EXE)

## individual rules
%_report: %
	./push_reports.py $<

%_coverage: %
	trucov all_report --srcdir ../src/ --builddir ../src/ selection $(FUNCS) ./$<

%: %.o $(OBJS)
	$(CXX) $(INC) -o $@ $< $(OBJS) $(LIBS); ./$@ > $@_ut.txt 2>&1; touch $@_log.txt

%.o: %.cpp
	$(CXX) $(INC) -c $< $(LIBS)

%.cpp: ./tests/%.h
	cxxtestgen --error-printer -o $@ $<

## maintenance rules
clean:
	rm -rf *.o *.cpp *.trucov *.svg *.ut *_log.txt *_ut.txt  $(TARGS)

setup:
	cd ../src/; make DEFINES='$(SRC_DEFINES)' CXXFLAGS='$(SRC_CXX)' LIBS='$(SRC_LIBS)'

full_setup:
	cd ../src/; make clean; qmake -project; qmake; make DEFINES='$(SRC_DEFINES)' CXXFLAGS='$(SRC_CXX)' LIBS='$(SRC_LIBS)'

help:
	#	usage: make rule
	#
	#	rules:
	#
	#	setup			- build the project with testing options (does a make)
	#	full_setup		- build the project from scratch with testing options (make clean; make)
	#	test_something		- build a given test (corresponds to ./tests/test_something.h)
	#	test_something_coverage	- generage coverage reports for a given test
	#	test_something_report	- push reports for a given test to the wiki repository
	#	make all		- build and run all tests in the tests/ directory
	#	make all_report		- build and run all tests and push their reports to the wiki repository