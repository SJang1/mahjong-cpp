#include "std.h"

queue<Tiles*> Init::Set_tiles()
{
    vector<Tiles> tiles = {
	{"1M", "1��", 1}, {"2M", "2��", 2}, {"3M", "3��", 3}, {"4M", "4��", 4}, {"5M", "5��", 5},
	{"6M", "6��", 6}, {"7M", "7��", 7}, {"8M", "8��", 8}, {"9M", "9��", 9}, // ������ (M)
	{"1P", "1��", 10}, {"2P", "2��", 11}, {"3P", "3��", 12}, {"4P", "4��", 13}, {"5P", "5��", 14},
	{"6P", "6��", 15}, {"7P", "7��", 16}, {"8P", "8��", 17}, {"9P", "9��", 18}, // ���� (P)
	{"1S", "1��", 19}, {"2S", "2��", 20}, {"3S", "3��", 21}, {"4S", "4��", 22}, {"5S", "5��", 23},
	{"6S", "6��", 24}, {"7S", "7��", 25}, {"8S", "8��", 26}, {"9S", "9��", 27}, // ���� (S)
	{"1Z", "��", 28}, {"2Z", "��", 29}, {"3Z", "��", 30}, {"4Z", "��", 31},     // �ٶ��� (��/��/��/��)
	{"5Z", "��", 32}, {"6Z", "��", 33}, {"7Z", "��", 34}          // ����� (��/��/��)
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



