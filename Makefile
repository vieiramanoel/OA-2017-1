# Cross-compiler
CC = g++

# C building settings
CFLAGS = -O2 -Wall -std=c++11

# C++ source and object files
C_DIR = .
C_SRC = $(wildcard $(C_DIR)/*.cpp)
C_OBJ = $(C_SRC:$(C_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Object files directory
OBJ_DIR = obj

# Header source files
INC_DIR = .
HEADERS_SRC = $(wildcard $(INC_DIR)/*.hpp)

# All object files
OBJ = $(C_OBJ)

# Executable kernel file
EXEC = oa
dir_guard=@mkdir -p $(OBJ_DIR)
.PHONY: all
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	

$(OBJ_DIR)/%.o: $(C_DIR)/%.cpp $(HEADERS_SRC)
	$(dir_guard)
	$(CC) $(CFLAGS) -I./$(INC_DIR) -c $< -o $@
		
.PHONY: clean
clean:
	-rm -f $(EXEC) $(OBJ_DIR)/*.o

.PHONY: print
print:
	@echo C src: $(C_SRC)
	@echo Obj: $(OBJ)
	@echo Exec: $(EXEC)
	@echo Header: $(HEADERS_SRC)
