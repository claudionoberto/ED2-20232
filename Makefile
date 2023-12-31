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
	gcc LinkedList.c LinkedList.h LinkedListTeste.c -o lista
	chmod +x lista
	./lista
	@echo "=================================="

olamundo:
	@echo "=================================="
	@echo "Executando olamundo"
	@echo "=================================="
	@echo "Compilando olamundo"
	gcc olamundo.c -o olamundo
	chmod +x olamundo
	./olamundo
	@echo "=================================="

dlinkedlist:
	@echo
	@echo ==========================
	@echo      LISTA DUPLA
	@echo ==========================
	@echo Compilando o programa dlinkedlist
	@gcc --std=c99 -DLOG_USE_COLOR DoublyLinkedList.h DoublyLinkedList.c DoublyLinkedListTeste.c -o dlinkedlist
	@echo Tornando o arquivo executável
	@chmod +x dlinkedlist
	@echo Executando o programa dlinkedlist
	@echo ======================================================
	@echo
	@./dlinkedlist

tabelaHash:
	@echo "=================================="
	@echo "         PROGRAMA HASH"
	@echo "=================================="
	@echo "- Compilando"
	gcc  DoublyLinkedList.h DoublyLinkedList.c Hash.h Hash.c HashMain.c -o Hash
	@echo "- Torna o programa Hash executável"
	chmod +x Hash
	@echo "- Executando o Hash"
	./Hash
	@echo "=================================="

Huffman:
	@echo "=================================="
	@echo "PROGRAMA ARVORE DE HUFFMAN"
	@echo "=================================="
	@echo "- Compilando"
	gcc  arvoreHuffman.h arvoreHuffman.c HuffmanMain.c -o Huffman
	@echo "- Torna o programa Huffman executável"
	chmod +x Huffman
	@echo "- Executando o programa Huffman"
	./Huffman
	@echo "=================================="