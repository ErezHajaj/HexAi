all: Move.cpp Main.cpp Position.cpp
	g++ -std=c++17 -O3 Move.cpp Main.cpp Position.cpp -o HexPlayer
clean:
	$(RM) HexPlayer
