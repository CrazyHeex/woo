# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./toolboxes/Libraries/IOManager
# Target is a library:  

LIBS += -rdynamic 
INCLUDEPATH = ../../../yade/yade \
              ../../../yade/Factory \
              ../../../toolboxes/Libraries/Serialization 
MOC_DIR = $(YADECOMPILATIONPATH) 
UI_DIR = $(YADECOMPILATIONPATH) 
OBJECTS_DIR = $(YADECOMPILATIONPATH) 
QMAKE_LIBDIR = $(YADEDYNLIBPATH) 
DESTDIR = $(YADEDYNLIBPATH) 
CONFIG += debug \
          warn_on \
          dll 
TEMPLATE = lib 
HEADERS += IOManager.hpp \
           IOManagerExceptions.hpp 
SOURCES += IOManager.cpp \
           IOManagerExceptions.cpp 
