CXX = g++-13
CXXFLAGS = -D _DEBUG -ggdb3 -std=c++17 -O3 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations \
		   -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts \
		   -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal \
		   -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op \
		   -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self \
		   -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel \
		   -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods \
		   -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand \
		   -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix \
		   -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs \
		   -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow \
		   -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie \
		   -fPIE -Werror=vla

HOME = $(shell pwd)
CXXFLAGS += -I $(HOME)

PROGRAMDIR = build/bin
TARGET = tester
OBJECTDIR = build
DOXYFILE = Others/Doxyfile

SORTS_DIR     	= Sorts
SORTS_HEADERS	= $(SORTS_DIR)/QuadraticSorts.h $(SORTS_DIR)/MergeSorts.h $(SORTS_DIR)/Sorts.h	\
				  $(SORTS_DIR)/Qsorts.h $(SORTS_DIR)/DigitsSorts.h $(SORTS_DIR)/HeapSort.h 		\
				  $(SORTS_DIR)/IntroSort.h

SORTS_CPP	  	= QuadraticSorts.c MergeSorts.c Qsorts.c DigitsSorts.c HeapSort.c IntroSort.c
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
