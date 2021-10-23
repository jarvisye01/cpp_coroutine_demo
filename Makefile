targets = sync_add async_add co_add co_generator

objects = util.o sync_add.o async_add.o co_add.o co_generator.o

all: $(targets)
.PHONY: all

util.o: util.cpp
sync_add.o: sync_add.cpp
async_add.o: async_add.cpp
co_add.o: co_add.cpp
	g++ -fcoroutines -lpthread -std=c++20 -o co_add.o -c co_add.cpp
co_generator.o:
	g++ -fcoroutines -std=c++20 -o co_generator.o -c co_generator.cpp

sync_add: sync_add.o util.o
	g++ -lpthread -o sync_add sync_add.o util.o

async_add: async_add.o util.o
	g++ -lpthread -o async_add async_add.o util.o

co_add: co_add.o util.o
	g++ -lpthread -o co_add co_add.o util.o

co_generator: co_generator.o
	g++ -fcoroutines -o co_generator co_generator.o


.PHONY: clean
clean:
	rm -rf $(targets) $(objects)


