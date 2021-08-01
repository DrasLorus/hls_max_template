############################################################
#
# Copyright © 2021 "DrasLorus"
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this
# file and associated documentation files (the “Software”),
# to deal in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all 
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
# INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
# PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
# CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
# OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
############################################################

CXX=g++
CXXFLAGS:=-std=c++14 -Wno-unused-label -Wno-unknown-pragmas -Wall -D_MAX_IS_TOP_
LDFLAGS:=

XILINX_HOME=/opt/Xilinx
XILINX_VER=2020.2
VITIS_HOME=${XILINX_HOME}/Vitis_HLS/${XILINX_VER}

CXXFLAGS:=${CXXFLAGS} -isystem ${VITIS_HOME}/include

SRCDIR=sources
OBJDIR=obj
BINDIR=bin

CATCHOBJ=$(OBJDIR)/catch.cpp.o

SOURCES:=$(SRCDIR)/modules/max.cpp
SOURCES+=$(SRCDIR)/testbenches/max_catch_tb.cpp

OBJ=$(SOURCES:.cpp=.cpp.o)

TBBIN=$(BINDIR)/tb.out

all: $(BINDIR) $(OBJDIR) $(TBBIN)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TBBIN): $(OBJ) $(CATCHOBJ)
	$(CXX) -o $(TBBIN) $(OBJ) $(CATCHOBJ) $(LDFLAGS)

$(CATCHOBJ) :
	$(CXX) -o $@ -c $(SRCDIR)/testbenches/catch.cpp $(CXXFLAGS)

%.cpp.o : %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean clear
clean:
	rm -vf $(OBJ)

.PHONY: clean clear
clear: clean
	rm -vf $(TBBIN) $(BINDIR)/results.dat $(COMPDB_ENTRIES) compile_commands.json

.PHONY: clean clear
fullclear: clear
	rm -vf $(CATCHOBJ)

testbench: $(TBBIN)
	cd $(BINDIR); ../$(TBBIN)

.PHONY: %.compdb_entry
%.compdb_entry: %.cpp
	@echo "    {" > $@
	@echo "        \"command\": \"$(CXX)  $(CFLAGS) $(CXXFLAGS) -c $<\","   >> $@
	@echo "        \"directory\": \"$(CURDIR)\","               >> $@
	@echo "        \"file\": \"$<\""                    >> $@
	@echo "    },"                              >> $@

COMPDB_ENTRIES = $(addsuffix .compdb_entry, $(basename $(SOURCES)))

compile_commands.json: $(COMPDB_ENTRIES)
	@echo "[" > $@.tmp
	@cat $^ >> $@.tmp
	@sed '$$d' < $@.tmp > $@
	@echo "    }" >> $@
	@echo "]" >> $@
	@rm $@.tmp

clang-tidy: compile_commands.json
	clang-tidy -p $(CURDIR) $(SOURCES)

cppcheck: compile_commands.json
	cppcheck --suppress=missingIncludeSystem --enable=all --inconclusive --std=c++14 --project=$(CURDIR)/compile_commands.json