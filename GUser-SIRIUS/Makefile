#---------------------------------------------------------//
# Makefile for SIRIUS that allows including user classes
# 
# Rikel CHAKMA
# Date: 20/06/2022
#------------------------------------------------------------//

#some general variables
# GNU gcc's option for debugging
# -g           Produce debugging information in the operating system’s native format 
# -ggdb        Produce debugging information for use by GDB
# -glevel      Level 0 produces no debug information at all
# -ggdblevel

BINDIR = $(shell pwd)/
SRCDIR = $(shell pwd)/
INCDIR = $(shell pwd)/
#Get GRU, MFM and vigru

GRU_LIBDIR   := $(GRUDIR)/grulib/
VIGRUDIR     := $(GRUDIR)/vigru/
GSOAPDIR     := $(GRUDIR)/gsoap/
MFM_DIR      := $(MFMDIR)
GRUFLAGS     := -I$(GRUDIR)/include/ -I$(GRU_LIBDIR) -I$(VIGRUDIR) -I$(GSOAPDIR)  -I$(MFM_DIR) -I$(MFM_DIR)/include/

# compiler:
# gcc for C
# g++ for C++
CC = gcc
CXX = g++
LINKER = g++
# Options
# -Wall to enable all compiler's warning messages
# -w to disable all warning messages
# -Wextra to enable extra warning messages
# -g<level> to generate debug information used by GDB, -g0 (no debug information), -g1 (minimal info), -g3 (maximal info)
# -c to compile the source files without linking
# -o to build an output file
# -O<level> to set optimization level: O0 (default) -O1, -O2, O3, -Os, -Ofast
# -I to include directory of header files
# -l to link with a library file 
# -L to look in directory for library files
# -fPIC to gnerate position independent code for shared libraries
# -shared to generate shared object file for shared library
# -D defines a macro to be used by the preprocessor, -D name=defination 
# -U<name> undefine a preprocessor macro
#  -p program instrumentation option
#  

#--------------------
# syntax 
# gcc -O<Level> -D <name> -g<level> -I<dir> [options] [source files] [object files] [-L<dir>] -l<libname> [-o output file]
CFLAGS = -c -Wall #Flag to pass to gcc
CPPFLAGS = -I #Flag to pass to the C processor, here -I means include directories to the compiler seach path
#
DEBUG_FLAG = -g
CXXFLAGS = -O3 -Wall -Wno-overloaded-virtual -Wno-unknown-pragmas $(DEBUG_FLAG) -fPIC -std=c++11 #passes to g++
EXTRA_CXXFLAGS = -Wno-write-strings -Wno-deprecated -fpermissive 
LDFLAGS = -O $(DEBUG_FLAG)
ROOTFLAGS = $(shell root-config --cflags) -I$(ROOTSYS)/xmlparser/inc -I$(ROOTSYS)/io/xmlparser/inc
ROOTLDFLAGS = $(shell root-config --ldflags)
ROOTLIBS = $(shell root-config --libs --glibs) -lSpectrum
ROOTINCDIR = $(ROOTSYS)/include
FLAGS = $(CXXFLAGS) $(EXTRA_CXXFLAGS) $(DEBUG_FLAG) $(ROOTFLAGS)
LIBS = $(SYSLIBS) $(ROOTLIBS)
EXT_LIBS = -ltinyxml -lgomp -lm -lpthread
#LDFLAGS is used to pass extra flags to the linker lD
#search for libraries in the current directories. Use -L/path/to/lib to search for libraries in /path/to/lib diectory
#LDFLAGS =  -L$(MFMDIR)/mfmlib/ -L$(GRUDIR)/grulib/
#list of libraries seprated by space. -l<Name>
#should be included after all the source files have been included otherwise the linker will not be able to to link them properly
#LDLIBS = -lGRU -lMFM
#------------------------------------------------
COMPILE = $(CXX) $(CPPFLAGS) $(FLAGS) -I$(INCDIR) -I$(MFMDIR) $(GRUFLAGS) 

#define a variable for the source files
HEADERS =  $(SRCDIR)global.h\
           $(SRCDIR)dssdData.h\
           $(SRCDIR)digitalFilters.h\
           $(SRCDIR)digitalCFD.h\
           $(SRCDIR)Calibration.h\
           $(SRCDIR)DataPoint.h\
           $(SRCDIR)EventPoint.h

SOURCES = $(SRCDIR)global.cc\
          $(SRCDIR)dssdData.cc\
          $(SRCDIR)digitalFilters.cc\
          $(SRCDIR)digitalCFD.cc\
          $(SRCDIR)Calibration.cc\
          $(SRCDIR)DataPoint.cc\
          $(SRCDIR)EventPoint.cc
	
#define a variable for the objects
OBJECTS = $(BINDIR)global.o\
          $(BINDIR)dssdData.o\
          $(BINDIR)digitalFilters.o\
          $(BINDIR)digitalCFD.o\
          $(BINDIR)Calibration.o\
          $(BINDIR)DataPoint.o\
          $(BINDIR)EventPoint.o
	

#Target
.PHONY : all
all: $(BINDIR)GUser.o $(BINDIR)GUser_C.so $(OBJECTS) 

$(BINDIR)GUser_C.so: $(SRCDIR)GUserDict.o $(SRCDIR)GUser.o $(OBJECTS)
	$(COMPILE) -g -shared -fPIC $(GRUFLAGS) $^ -o $@
	@echo "$@ done"

$(BINDIR)GUserDict.o: $(SRCDIR)GUserDict.C
	$(COMPILE) -c $< 

#Root dictionary generation
$(SRCDIR)GUserDict.C: $(INCDIR)GUser.h
	@echo "Generating dictionary ..."
	@rootcint -f $@ -c -p $(GRUFLAGS)  $^ $(INCDIR)GUser_linkdef.h
	@echo "$@ generation done ..."
#Automatic varibales
# $@ filename of the target
# $< filename of the first prerequisite
# $^ filenames of all prerequisites, separated by spaces.
# $* the stem of the target filename


$(BINDIR)GUser.o : GUser.C GUser.h  
	#$(CXX) $(CPPFLAGS) $(GRUFLAGS) $(FLAGS) -c $< 
	$(COMPILE) -c $< 

$(BINDIR)global.o : global.cc global.h
	$(COMPILE) -c $< 

$(BINDIR)dssdData.o : dssdData.cc dssdData.h
	$(COMPILE) -c $< 

$(BINDIR)digitalFilters.o : digitalFilters.cc digitalFilters.h 
	$(COMPILE) -c $< 

$(BINDIR)digitalCFD.o : digitalCFD.cc digitalCFD.h
	$(COMPILE) -c $< 

$(BINDIR)Calibration.o : Calibration.cc Calibration.h
	$(COMPILE) -c $< 

$(BINDIR)DataPoint.o : DataPoint.cc DataPoint.h
	$(COMPILE) -c $< 

$(BINDIR)EventPoint.o : EventPoint.cc EventPoint.h
	$(COMPILE) -c $< 

.PHONY : clean
clean :
	@rm -f core *.o *Dict*.* *.so
	@echo "Cleaning done...."
