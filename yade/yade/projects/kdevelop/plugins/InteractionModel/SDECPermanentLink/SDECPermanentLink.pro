# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./plugins/InteractionModel/SDECPermanentLink
# Target is a library:  

LIBS += -lSerialization \
        -lMath \
        -lInteraction \
        -rdynamic 
INCLUDEPATH = ../../../yade/yade \
              ../../../yade/Interaction \
              ../../../yade/Factory \
              ../../../toolboxes/Libraries/Math \
              ../../../toolboxes/Libraries/Serialization 
MOC_DIR = $(YADECOMPILATIONPATH) 
UI_DIR = $(YADECOMPILATIONPATH) 
OBJECTS_DIR = $(YADECOMPILATIONPATH) 
QMAKE_LIBDIR = ../../../toolboxes/Libraries/Serialization/$(YADEDYNLIBPATH) \
               ../../../toolboxes/Libraries/Math/$(YADEDYNLIBPATH) \
               $(YADEDYNLIBPATH) 
DESTDIR = $(YADEDYNLIBPATH) 
CONFIG += debug \
          warn_on \
          dll 
TEMPLATE = lib 
HEADERS += SDECPermanentLink.hpp 
SOURCES += SDECPermanentLink.cpp 
