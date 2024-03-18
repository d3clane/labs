CXX = g++-13
CXXFLAGS = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations \
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
		   -fPIE -Werror=vla -D STACK_ON_ARR=0 -D STACK_ON_LIST=1 -D STACK_TYPE=STACK_ON_ARR

HOME = $(shell pwd)
CXXFLAGS += -I $(HOME)

PROGRAMDIR = build/bin
TARGET = tester
OBJECTDIR = build
DOXYFILE = Others/Doxyfile

#LIST_DIR     	= List
#LIST_HEADERS	= $(LIST_DIR)/list.h $(LIST_DIR)/stackOnList.h 
#LIST_CPP	  	= list.c stackOnList.c
#LIST_OBJ	  	= $(LIST_CPP:%.c=$(OBJECTDIR)/%.o)

ARRAY_DIR     = Array
ARRAY_HEADERS = $(ARRAY_DIR)/dynamicArr.h $(ARRAY_DIR)/stackOnArr.h
ARRAY_CPP     = dynamicArr.c stackOnArr.c 
ARRAY_OBJ     = $(ARRAY_CPP:%.c=$(OBJECTDIR)/%.o)

FILES_HEADERS = tests.h
FILES_CPP     = main.c tests.c
FILES_OBJ     = $(FILES_CPP:%.c=$(OBJECTDIR)/%.o)

.PHONY: all docs clean install
	
all: $(PROGRAMDIR)/$(TARGET)
	@cp $(PROGRAMDIR)/$(TARGET) ../

$(PROGRAMDIR)/$(TARGET): $(ARRAY_OBJ) $(FILES_OBJ)
	$(CXX) $^ -o $(PROGRAMDIR)/$(TARGET) $(CXXFLAGS)

#$(OBJECTDIR)/%.o : $(LIST_DIR)/%.c
#	$(CXX) -c $< -o $@ $(CXXFLAGS) 

$(OBJECTDIR)/%.o : $(ARRAY_DIR)/%.c
	$(CXX) -c $< -o $@ $(CXXFLAGS) 

$(OBJECTDIR)/%.o : %.c
	$(CXX) -c $< -o $@ $(CXXFLAGS) 

docs: 
	doxygen $(DOXYFILE)

clean:
	rm -rf $(OBJECTDIR)/*.o

buildDirs:
	mkdir $(OBJECTDIR)
	mkdir $(PROGRAMDIR)