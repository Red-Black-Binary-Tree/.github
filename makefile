# Nome do executável final
EXEC = myrb

# Fontes e objetos
SRC = main.c redblack.c
OBJ = $(SRC:.c=.o)

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Regra padrão: gera o executável
all: $(EXEC)

# Como compilar o executável
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Limpa arquivos temporários
clean:
	rm -f $(OBJ) $(EXEC)
