CC = gcc
CXX = g++
CFLAGS += -Wall -pipe -O2
#CFLAGS += -Wall -pipe -g -fsanitize=address	# for debug
CXXFLAGS := $(CFLAGS)
LOBJS = ssw.o
LCPPOBJS = ssw_cpp.o
PROG = ssw_test
LIB = libssw.so
JAVA_JAR = ssw.jar
JAVA_LIB = libsswjni.so
JAVA_INLCUDES = -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux
JAVA_OBJ = ssw/Aligner.class ssw/Alignment.class ssw/Example.class

.PHONY: all default java clean

default: $(PROG) $(LIB)
core: $(PROG)
java: java_home $(JAVA_JAR) $(JAVA_LIB)
all: default java

$(LIB): ssw.c ssw.h
	$(CC) $(CFLAGS) -fPIC -shared -rdynamic -o $@ $<

$(PROG): main.c kseq.h

ifdef __arm__ # (M1)
$(PROG): $(LOBJS)
	$(CC) -o $@ $(filter-out %.h,$^) $(CFLAGS) $(LDFLAGS) -lm -lz -march=armv8-a+fp+simd+crypto+crc
else # x86(Intel)
$(PROG): $(LOBJS)
	$(CC) -o $@ $(filter-out %.h,$^) $(CFLAGS) $(LDFLAGS) -lm -lz
endif

$(JAVA_LIB): sswjni.c ssw.c ssw.h
	$(CC) $(CFLAGS) $(JAVA_INLCUDES) -fPIC -shared -rdynamic -o $@ $< ssw.c 

$(JAVA_JAR): $(JAVA_OBJ)
	jar cvfe $@ ssw.Example $^

%.class: %.java
	javac -cp ./ $<

java_home:
ifndef JAVA_HOME
	@$(ECHO) "ERROR: Your JAVA_HOME environment variable is not set."
	exit 1
endif

ssw.o: ssw.c ssw.h
	$(CC) -c -o $@ $< $(CFLAGS)

ssw_cpp.o: ssw_cpp.cpp ssw_cpp.h ssw.h
	$(CXX) -c -o $@ $< $(CXXFLAGS)

clean:
	-rm -f $(LOBJS) $(LCPPOBJS) $(PROG) $(LIB) $(JAVA_LIB) $(JAVA_JAR) $(JAVA_OBJ) *~
