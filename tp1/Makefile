# Variáveis
CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Fontes e objetos
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
TARGET = $(BIN_DIR)/main

# Regras
all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Regra para compilar os arquivos .cpp em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Diretórios
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Executar o programa
run: all
	./$(TARGET)

# Limpar arquivos compilados
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Regras especiais
.PHONY: all run clean
