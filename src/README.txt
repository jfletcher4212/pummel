The source in this directory depends on QT.

To compile, you must first create a project file.
Run the following in the src directory:

qmake -project

This will produce a file named 'src.pro'.

In order to remove unfinished files from the 
project file (to avoid compile errors),
run the following sed command or an equivalent:

sed -i '/NotImplemented/d' ./src.pro
or
sed.exe -i "/NotImplemented/d" .\src.pro
if you use Windows and the gnuwin32 binaries.


To create a platform specific Makefile, use the
following command:

qmake src.pro


And finally, compile with the 'make' command.

If you use Windows, use mingw32-make.exe, which comes included with Qt Creator.
You may need to set env variable QMAKESPEC=<pathToQtSDK>\Simulator\Qt\mingw\mkspecs\win32-g++
in order to force qmake to build the makefiles for mingw32-make.exe.


If compilation succeeds, there will be an executable
binary named 'src'.


Thanks to "Ravi" at the "All About Linux"
blog for these instruction.
http://linuxhelp.blogspot.com/2006/01/creating-and-compiling-qt-projects-on.html

