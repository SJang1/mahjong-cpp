#include "std.h"

// ��ġ����

int main()
{
	Game game;
	game.Start_Remove_14();
	game.Disturb_Tiles(1, 1);
	game.Disturb_Tiles(4, 3);

	while (true)
	{
		game.sort();
		game.print_thrown_tiles();
		game.print_my_tiles();
		if(!game.get_newTile())
			break;
		game.print_my_newTile();
		//game.checkWinningPrint();
		bool res = game.throw_tile();
		if (!res)
		{
			cout << "���� �¸��Դϴ�" << endl;
			break;
		}
			
	}
	return 0;
}