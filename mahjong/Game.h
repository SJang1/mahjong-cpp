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

	bool gameEnded;


private:
	
	Tiles* findTileToDiscard(vector<Tiles*>& playerTiles, Player* player);
	bool checkConsecutiveHonorTiles(const vector<Tiles*>& tiles, int priority, int& count);
	bool isSingleHonorTile(const vector<Tiles*>& tiles, int priority);
	bool isIsolatedNumberTile(const vector<Tiles*>& tiles, int priority);
	bool isEdgeOfFourConsecutive(const vector<Tiles*>& tiles, int priority);
	vector<vector<Tiles*>> findConsecutiveGroups(const vector<Tiles*>& tiles);
	bool isPartOfLongConsecutive(const vector<Tiles*>& tiles, int priority);

	bool checkRon(const Tiles* discardedTile, const vector<Tiles*>& playerTiles, Player* player);

	bool isPartOfSequence(const vector<Tiles*>& tiles, Tiles* tile);
	bool isPartOfTriplet(const vector<Tiles*>& tiles, Tiles* tile);
	int getNumSimilarTiles(const vector<Tiles*>& tiles, Tiles* tile);
	vector<Tiles*> getFinalCandidates(vector<Tiles*>& tiles);

public:
	Game();
	~Game();
	void Print_Reach_Users();

	bool Start_Remove_14();
	bool Disturb_Tiles(int _count, int _repeat);

	void print_my_tiles();
	void print_my_tiles(bool);
	void print_my_newTile();
	void print_thrown_tiles();
	void endGame();

	
	void sort();

	bool get_newTile();

	bool throw_tile();

	bool checkWinningPrint();
	bool checkRonForAllPlayers(Tiles* discardedTile);
	bool processAITurns();
	void print_ai_tiles();
	void printFinalGameState();
};


