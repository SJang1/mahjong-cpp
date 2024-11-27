#pragma once
class Game
{
private:
	vector<Player*> players;
	queue<Tiles*> tiles;
	vector<Tiles*> player1;
	vector<Tiles*> player2;
	vector<Tiles*> player3;
	vector<Tiles*> player4;
	vector<Tiles*> throwntiles;
	vector<Tiles*> discardableTiles;

public:
	Game();
	void Print_Reach_Users();

	bool Start_Remove_14();
	bool Disturb_Tiles(int _count, int _repeat);

	void print_my_tiles();
	void print_my_newTile();
	void print_thrown_tiles();

	
	void sort();

	bool get_newTile();

	bool throw_tile();

	bool checkWinningPrint();
};

