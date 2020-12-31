sources = $(wildcard *.cpp)
objects = $(addsuffix .o, $(basename $(sources)))
flags = -g -W -Wall -std=c++17 -DDEBUG=1 -DTEST=1 -fopenmp
target = chess 


$(target) : $(objects)
	g++ -g $(flags) -o $(target) $(objects)

%.o : %.cc
	g++ -c -g $(flags) $< -o $@
clean :
	rm $(target) $(objects)
