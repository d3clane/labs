CXX = g++-13
CXXFLAGS = -D NDEBUG -ggdb3 -O3 -D BST_TYPE=0 -D AVL_TYPE=1 -D TREAP_TYPE=2 -D SPLAY_TYPE=3 -D TREE_TYPE=SPLAY_TYPE

HOME = $(shell pwd)
CXXFLAGS += -I $(HOME)

PROGRAMDIR = build/bin
TARGET = tester
OBJECTDIR = build
DOXYFILE = Others/Doxyfile

TESTING_DIR     = Testing
TESTING_CPP		= Testing.c main.c 
TESTING_OBJ     = $(TESTING_CPP:%.c=$(OBJECTDIR)/%.o)

SPLAY_DIR 	 = Splay
SPLAY_CPP    = Splay.c
SPLAY_OBJ    = $(SPLAY_CPP:%.c=$(OBJECTDIR)/%.o)

BST_DIR    = BST
BST_CPP    = BST.c
BST_OBJ    = $(BST_CPP:%.c=$(OBJECTDIR)/%.o)

AVL_DIR    = AVL
AVL_CPP    = AVL.c
AVL_OBJ    = $(AVL_CPP:%.c=$(OBJECTDIR)/%.o)

TREAP_DIR    = Treap
TREAP_CPP    = Treap.c
TREAP_OBJ    = $(TREAP_CPP:%.c=$(OBJECTDIR)/%.o)

.PHONY: all docs clean install
	
all: $(PROGRAMDIR)/$(TARGET)
	@cp $(PROGRAMDIR)/$(TARGET) ../

$(PROGRAMDIR)/$(TARGET): $(TESTING_OBJ) $(SPLAY_OBJ) $(AVL_OBJ) $(BST_OBJ) $(TREAP_OBJ)
	$(CXX) $^ -o $(PROGRAMDIR)/$(TARGET) $(CXXFLAGS)

$(OBJECTDIR)/%.o : $(TESTING_DIR)/%.c
	$(CXX) -c $< -o $@ $(CXXFLAGS) 

$(OBJECTDIR)/%.o : $(BST_DIR)/%.c
	$(CXX) -c $< -o $@ $(CXXFLAGS) 

$(OBJECTDIR)/%.o : $(TREAP_DIR)/%.c
	$(CXX) -c $< -o $@ $(CXXFLAGS) 

$(OBJECTDIR)/%.o : $(AVL_DIR)/%.c
	$(CXX) -c $< -o $@ $(CXXFLAGS) 

$(OBJECTDIR)/%.o : $(SPLAY_DIR)/%.c
	$(CXX) -c $< -o $@ $(CXXFLAGS) 

docs: 
	doxygen $(DOXYFILE)

clean:
	rm -rf $(OBJECTDIR)/*.o

buildDirs:
	mkdir $(OBJECTDIR)
	mkdir $(PROGRAMDIR)
