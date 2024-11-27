#include "std.h"

// 리치마작

int main()
{
	Game game;
	game.Start_Remove_14();
	game.Disturb_Tiles(1, 1);
	game.Disturb_Tiles(4, 3);

	while (true)
	{
		cout << endl;
		cout << endl;

		game.Print_Reach_Users();
		game.sort();
		game.print_thrown_tiles();
		game.print_ai_tiles();
		if (!game.get_newTile()) {
			game.endGame();
			break;
		}
		cout << endl;
		game.print_my_tiles(true);
		game.print_my_newTile();
		bool res = game.throw_tile();
		if (!res) {
			game.endGame();
			break;
		}

		if (!game.processAITurns()) {
			break;  // endGame은 이미 호출되었음
		}
	}
	return 0;
}