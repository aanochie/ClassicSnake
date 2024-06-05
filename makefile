final: main.o assetMan.o Game.o mainMenu.o stateMan.o gamePlay.o snake.o gameOver.o pause.o
	g++ -std=c++17 main.o assetMan.o Game.o mainMenu.o stateMan.o gamePlay.o snake.o gameOver.o pause.o -o run -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -std=c++17 -c main.cpp 

assetMan.o: assetMan.cpp
	g++ -std=c++17 -c assetMan.cpp

Game.o: Game.cpp
	g++ -std=c++17 -c Game.cpp

mainMenu.o: mainMenu.cpp
	g++ -std=c++17  -c mainMenu.cpp

stateMan.o: stateMan.cpp
	g++ -std=c++17 -c stateMan.cpp

gamePlay.o: gamePlay.cpp
	g++ -std=c++17 -c gamePlay.cpp

snake.o: snake.cpp
	g++ -std=c++17 -c snake.cpp
gameOver.o: gameOver.cpp
	g++ -std=c++17 -c gameOver.cpp

pause.o: pause.cpp
	g++ -std=c++17 -c pause.cpp
clean:
	rm *.o run
