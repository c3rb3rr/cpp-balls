#ELEMENTY KOMPILACJI
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 

#INSTRUKCJE
all:
	g++ -c "main.cpp" -o main.o
	g++ -c "Game.cpp" -o Game.o
	g++ -c "Player.cpp" -o Player.o
	g++ -c "kulki.cpp" -o kulki.o
	g++ -o Kulki main.o Game.o Player.o kulki.o $(LIBS)

