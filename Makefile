ola: clean
	@echo "=================================="
	@echo "         PROGRAMA OLA"
	@echo "=================================="
	@echo "- Compilando ola mundo"
	gcc teste.c -o ola
	@echo "- Torna o programa olamundo executásvel"
	chmod +x ola
	@echo "- Executando o programa ola mundo"
	./ola
	@echo "=================================="

clean:
	@echo "===================================="
	@echo "Removendo os programas compilados"
	@echo "===================================="
	@echo "Removendo o programa olamundo"
	rm -f ola
	@echo "===================================="

help:
	@echo "======================"
	@echo "         AJUDA"
	@echo "======================"
	@echo "help		| ajuda"
	@echo "ela		| executar mensagem de texto"
	@echo "clean| apagar codigos compilados"

lista:
	@echo "=================================="
	@echo "Executando lista simplesmente ligada"
	@echo "=================================="
	@echo "Compilando LinkedList"
	gcc LinkedList.c LinkedList.h -o lista
	chmod +x lista
	./lista
	@echo "=================================="