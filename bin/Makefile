demo:demo.o DocumentKits.o Document.o
	g++ -o demo demo.o DocumentKits.o Document.o -I../include -L../lib -lcode -lelus

demo.o:demo.cpp
	g++ -c demo.cpp -I../include

DocumentKits.o:DocumentKits.cpp Document.o
	g++ -c DocumentKits.cpp Document.o -I../include -L../lib -lcode -lelus

Document.o:Document.cpp
	g++ -c Document.cpp -I../include
