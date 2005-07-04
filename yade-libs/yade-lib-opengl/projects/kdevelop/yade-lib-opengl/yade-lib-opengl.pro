# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./yade-lib-opengl
# Target is a library:  ../../../bin/yade-lib-opengl

LIBS += -lyade-lib-time 
INCLUDEPATH += /usr/local/include/yade 
QMAKE_LIBDIR = /usr/local/lib/yade/yade-libs/ 
TARGET = ../../../bin/yade-lib-opengl 
CONFIG += release \
          warn_on \
          dll 
TEMPLATE = lib 
HEADERS += FpsTracker.hpp \
           GLTextLabel.hpp \
           GLWindow.hpp \
           GLWindowsManager.hpp \
           OpenGLWrapper.hpp 
SOURCES += FpsTracker.cpp \
           GLTextLabel.cpp \
           GLWindow.cpp \
           GLWindowsManager.cpp 
