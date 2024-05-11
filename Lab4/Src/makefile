CXX = g++-13
CXXFLAGS = -D NDEBUG -ggdb3 -std=c++17 -O3

HOME = $(shell pwd)
CXXFLAGS += -I $(HOME)

PROGRAMDIR = build/bin
TARGET = tester
OBJECTDIR = build
DOXYFILE = Others/Doxyfile

SORTS_DIR     	= Sorts
SORTS_HEADERS	= $(SORTS_DIR)/HeapSort.h

SORTS_CPP	  	= HeapSort.c
SORTS_OBJ	  	= $(SORTS_CPP:%.c=$(OBJECTDIR)/%.o)

TESTING_DIR     = Testing
TESTING_HEADERS = $(TESTING_DIR)/Testing.h
TESTING_CPP		= Testing.c main.c 
TESTING_OBJ     = $(TESTING_CPP:%.c=$(OBJECTDIR)/%.o)

HEAP_DIR     = Heap
HEAP_HEADERS = $(HEAP_DIR)/Heap.h
HEAP_CPP	 = Heap.c
HEAP_OBJ     = $(HEAP_CPP:%.c=$(OBJECTDIR)/%.o)

.PHONY: all docs clean install
	
all: $(PROGRAMDIR)/$(TARGET)
	@cp $(PROGRAMDIR)/$(TARGET) ../

$(PROGRAMDIR)/$(TARGET): $(TESTING_OBJ) $(SORTS_OBJ) $(HEAP_OBJ)
	$(CXX) $^ -o $(PROGRAMDIR)/$(TARGET) $(CXXFLAGS)

$(OBJECTDIR)/%.o : $(SORTS_DIR)/%.c
	$(CXX) -c $< -o $@ $(CXXFLAGS) 

$(OBJECTDIR)/%.o : $(TESTING_DIR)/%.c
	$(CXX) -c $< -o $@ $(CXXFLAGS) 

$(OBJECTDIR)/%.o : $(HEAP_DIR)/%.c
	$(CXX) -c $< -o $@ $(CXXFLAGS) 

docs: 
	doxygen $(DOXYFILE)

clean:
	rm -rf $(OBJECTDIR)/*.o

buildDirs:
	mkdir $(OBJECTDIR)
	mkdir $(PROGRAMDIR)
