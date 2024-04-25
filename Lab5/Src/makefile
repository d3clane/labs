CXX = g++-13
CXXFLAGS = -D _DEBUG -D INT_TYPE=1 -D FLOAT_TYPE=2 -D STR_TYPE=3 -D TYPE=INT_TYPE \
		   -D OPEN_TABLE -D LINEAR=1 -D QUADRATIC=2 -D HASH=3 -D PROBE_FUNC=HASH -std=c++17 -O3 -g \
		   #-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

HOME = $(shell pwd)
CXXFLAGS += -I $(HOME)

PROGRAMDIR = build/bin
TARGET = tester
OBJECTDIR = build
DOXYFILE = Others/Doxyfile

TESTING_DIR     = Testing
TESTING_HEADERS = $(TESTING_DIR)/Testing.h
TESTING_CPP		= Testing.c main.c 
TESTING_OBJ     = $(TESTING_CPP:%.c=$(OBJECTDIR)/%.o)

HASHES_DIR 	    = Hash
HASHES_CPP	    = Hash.c
HASHES_OBJ		= $(HASHES_CPP:%.c=$(OBJECTDIR)/%.o)

HASH_TABLE_DIR  = HashTable
HASH_TABLE_CPP  = HashTableOpen.c HashTableWithList.c
HASH_TABLE_OBJ  = $(HASH_TABLE_CPP:%.c=$(OBJECTDIR)/%.o)

HASH_TABLE_LIST_DIR = HashTable/HashTableList
HASH_TABLE_LIST_CPP = HashTableList.c
HASH_TABLE_LIST_OBJ = $(HASH_TABLE_LIST_CPP:%.c=$(OBJECTDIR)/%.o)

.PHONY: all docs clean install
	
all: $(PROGRAMDIR)/$(TARGET)
	@cp $(PROGRAMDIR)/$(TARGET) ../

$(PROGRAMDIR)/$(TARGET): $(TESTING_OBJ) $(HASHES_OBJ) $(HASH_TABLE_OBJ) $(HASH_TABLE_LIST_OBJ)
	$(CXX) $^ -o $(PROGRAMDIR)/$(TARGET) $(CXXFLAGS)

$(OBJECTDIR)/%.o : $(TESTING_DIR)/%.c
	$(CXX) -c $< -o $@ $(CXXFLAGS) 

$(OBJECTDIR)/%.o : $(HASHES_DIR)/%.c
	$(CXX) -c $< -o $@ $(CXXFLAGS) 

$(OBJECTDIR)/%.o : $(HASH_TABLE_DIR)/%.c
	$(CXX) -c $< -o $@ $(CXXFLAGS) 

$(OBJECTDIR)/%.o : $(HASH_TABLE_LIST_DIR)/%.c
	$(CXX) -c $< -o $@ $(CXXFLAGS) 

docs: 
	doxygen $(DOXYFILE)

clean:
	rm -rf $(OBJECTDIR)/*.o

buildDirs:
	mkdir $(OBJECTDIR)
	mkdir $(PROGRAMDIR)
