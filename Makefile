# Definir o compilador
CC = gcc

# Definir as flags de compilação
CFLAGS = -Wall -I./include

# Definir o nome do executável final
TARGET = build/knn_program

# Diretórios
SRCDIR = src
INCDIR = include
OBJDIR = build/obj

# Definir os arquivos fonte
SOURCES = $(SRCDIR)/main.c $(SRCDIR)/knn.c $(SRCDIR)/data_utils.c $(SRCDIR)/csv_utils.c

# Definir os arquivos objetos (substituindo src/ por build/obj/ e .c por .o)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Regra padrão
all: $(TARGET)

# Compilar o executável
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) -lm

# Compilar os .c em .o dentro do build/obj
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Criar a pasta build/obj se não existir
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Limpar os arquivos de compilação
clean:
	rm -rf build/obj/*.o $(TARGET)
