# You may modify Makefile as your like
# but you should keep `make clean` and `make` works correct

PROGRAM = code 

CXX = g++
CXXFLAGS = -std=c++14 -O3 -g

CPP_FILES = $(wildcard *.cpp)
H_FILES = $(wildcard *.h)

LDOPTIONS =
LIB = 

all: $(PROGRAM)

$(PROGRAM): $(CPP_FILES) $(H_FILES) 
	$(CXX) -o $(PROGRAM) $(CXXFLAGS) $(LDOPTIONS) $(CPP_FILES) $(LIB)

tidy:
	rm -f ,* .,* *~ core a.out *.err

clean scratch: tidy
	rm -f *.o *.a $(PROGRAM) 
