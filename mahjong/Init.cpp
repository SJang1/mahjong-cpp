#include "std.h"

queue<Tiles*> Init::Set_tiles()
{
    vector<Tiles> tiles = {
	{"1M", "1만", 1}, {"2M", "2만", 2}, {"3M", "3만", 3}, {"4M", "4만", 4}, {"5M", "5만", 5},
	{"6M", "6만", 6}, {"7M", "7만", 7}, {"8M", "8만", 8}, {"9M", "9만", 9}, // 만자패 (M)
	{"1P", "1통", 10}, {"2P", "2통", 11}, {"3P", "3통", 12}, {"4P", "4통", 13}, {"5P", "5통", 14},
	{"6P", "6통", 15}, {"7P", "7통", 16}, {"8P", "8통", 17}, {"9P", "9통", 18}, // 통패 (P)
	{"1S", "1삭", 19}, {"2S", "2삭", 20}, {"3S", "3삭", 21}, {"4S", "4삭", 22}, {"5S", "5삭", 23},
	{"6S", "6삭", 24}, {"7S", "7삭", 25}, {"8S", "8삭", 26}, {"9S", "9삭", 27}, // 삭패 (S)
	{"1Z", "동", 28}, {"2Z", "남", 29}, {"3Z", "서", 30}, {"4Z", "북", 31},     // 바람패 (동/남/서/북)
	{"5Z", "백", 32}, {"6Z", "발", 33}, {"7Z", "중", 34}          // 삼원패 (백/발/중)
	};


	// x4 each tiles and shuffle in vector -> put into queue
	vector<Tiles*> tile_full;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < tiles.size(); j++)
		{
			tile_full.push_back(new Tiles(tiles[j].getName(), tiles[j].getReadableName(), tiles[j].getPriority()));
		}
	}

	// Shuffle without algorithm library
	srand((unsigned int)time(NULL));
	for (int i = 0; i < tile_full.size(); i++)
	{
		int j = rand() % tile_full.size();
		swap(tile_full[i], tile_full[j]);
	}

	queue<Tiles*> tile;
	for (int i = 0; i < tile_full.size(); i++)
	{
		tile.push(tile_full[i]);
	}

	return tile;
}



