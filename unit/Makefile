
# any commented line that uses $(TARG_) is a template line,
# and should be replicated whenever a test is added (remember to make it TARG_++)

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
# add to this variable list and then mirror the code at the bottom
TARG_1=test_dragitem
TARG_2=test_mainwindow
#TARG_=test_
## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##

CXX=g++
LIBS=-L/usr/lib -lQtGui -lQtCore -lpthread 

# remember to use -I/usr/include   where you installed the cxxtest headers
INC=-I/usr/include -I/usr/share/qt4/mkspecs/linux-g++ -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I./tests/ -I./

# if windows people need to change any of these includes, please uncomment and edit this INC line, 
# and re-comment before committing. this is to keep the continuous tester working at all times
#INC=-I/usr/include -I/usr/share/qt4/mkspecs/linux-g++ -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I./tests/ -I./

# objects for linking
# add to this list as needed using relative paths
OBJECTS = ../src/borderlayout.o \
../src/dragitem.o \
../src/dragscene.o \
../src/dragview.o \
../src/drawarea.o \
../src/ellipse.o \
../src/global.o \
../src/icon.o \
../src/mainwindow.o \
../src/markerbox.o \
../src/optionsdialog.o \
../src/shapes.o \
../src/tabmanager.o \
../src/TestEllipse.o \
../src/TestIcon.o \
../src/toolbar.o \
../src/moc_drawarea.o \
../src/moc_mainwindow.o \
../src/moc_optionsdialog.o \
../src/moc_tabmanager.o \
../src/moc_toolbar.o


all: $(TARG_1) $(TARG_2) #$(TARG_)
	./$(TARG_1); ./$(TARG_2); #./$(TARG_);

# test_dragitem
$(TARG_1): $(TARG_1).o $(OBJECTS)
	$(CXX) $(INC) -o $(TARG_1) $(TARG_1).o $(OBJECTS) $(LIBS)


$(TARG_1).o: $(TARG_1).cpp
	$(CXX) $(INC) -c $(TARG_1).cpp $(LIBS)


$(TARG_1).cpp: ./tests/$(TARG_1).h
	cxxtestgen --error-printer -o $(TARG_1).cpp ./tests/$(TARG_1).h


# test_mainwindow
$(TARG_2): $(TARG_2).o $(OBJECTS)
	$(CXX) $(INC) -o $(TARG_2) $(TARG_2).o $(OBJECTS) $(LIBS)


$(TARG_2).o: $(TARG_2).cpp
	$(CXX) $(INC) -c $(TARG_2).cpp $(LIBS)


$(TARG_2).cpp: ./tests/$(TARG_2).h
	cxxtestgen --error-printer -o $(TARG_2).cpp ./tests/$(TARG_2).h

# test_
#$(TARG_): $(TARG_).o $(OBJECTS)
#	$(CXX) $(INC) -o $(TARG_) $(TARG_).o $(OBJECTS) $(LIBS)


#$(TARG_).o: $(TARG_).cpp
#	$(CXX) $(INC) -c $(TARG_).cpp $(LIBS)


#$(TARG_).cpp: ./tests/$(TARG_).h
#	cxxtestgen --error-printer -o $(TARG_).cpp ./tests/$(TARG_).h


# add your test name to the end of the clean directive
clean:
	rm -rf *.o *.cpp $(TARG_1) $(TARG_2) #$(TARG_)



