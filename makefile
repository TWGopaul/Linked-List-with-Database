all: grocery.o LinkFun.o receiptFun.o
	g++ -o all  grocery.o LinkFun.o receiptFun.o

grocery.o: grocery.cpp
	g++ -c grocery.cpp

LinkFun.o: LinkFun.cpp
	g++ -c LinkFun.cpp

receiptFun.o: receiptFun.cpp
	g++ -c receiptFun.cpp

clean:
	rm all grocery.o
