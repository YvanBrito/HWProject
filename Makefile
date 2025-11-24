# Configurações
CXX = g++
CXXFLAGS = -g -I src `pkg-config --cflags sdl2 SDL2_image SDL2_mixer SDL2_ttf`
LIBS = `pkg-config --libs sdl2 SDL2_image SDL2_mixer SDL2_ttf`
TARGET = main

# Encontra automaticamente todos os arquivos .cpp
SOURCES = $(shell find src -name "*.cpp")
OBJECTS = $(SOURCES:.cpp=.o)

# Regra principal
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LIBS)

# Regra para arquivos .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
# Limpar arquivos compilados
clean:
	rm -f $(OBJECTS) $(TARGET)

# Compilar e executar
run: $(TARGET)
	./$(TARGET)
# Compilar tudo novamente
rebuild: clean $(TARGET)

.PHONY: clean run rebuild