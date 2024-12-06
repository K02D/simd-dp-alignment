CC = gcc
CXX = g++
CFLAGS += -Wall -pipe -O2
#CFLAGS += -Wall -pipe -g -fsanitize=address	# for debug
CXXFLAGS := $(CFLAGS)
LOBJS1 = ssw1.o
LOBJS2 = ssw2.o
PROG1 = ssw_test_1
PROG2 = ssw_test_2
LIB = libssw.so

.PHONY: all default clean

default: $(PROG1) $(PROG2) $(LIB)
core: $(PROG1) $(PROG2)
all: default

$(LIB): ssw_optimized.c ssw.h
	$(CC) $(CFLAGS) -fPIC -shared -rdynamic -o $@ $<

$(PROG1): main.c kseq.h $(LOBJS1)
ifdef __arm__ # (M1)
	$(CC) -o $@ $(filter-out %.h,$^) $(CFLAGS) $(LDFLAGS) -lm -lz -march=armv8-a+fp+simd+crypto+crc
else # x86(Intel)
	$(CC) -o $@ $(filter-out %.h,$^) $(CFLAGS) $(LDFLAGS) -lm -lz
endif

$(PROG2): main.c kseq.h $(LOBJS2)
ifdef __arm__ # (M1)
	$(CC) -o $@ $(filter-out %.h,$^) $(CFLAGS) $(LDFLAGS) -lm -lz -march=armv8-a+fp+simd+crypto+crc
else # x86(Intel)
	$(CC) -o $@ $(filter-out %.h,$^) $(CFLAGS) $(LDFLAGS) -lm -lz
endif

ssw1.o: ssw.c ssw.h
	$(CC) -c -o $@ $< $(CFLAGS)

ssw2.o: ssw_optimized.c ssw.h
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	-rm -f $(LOBJS1) $(LOBJS2) $(PROG1) $(PROG2) $(LIB) *~
