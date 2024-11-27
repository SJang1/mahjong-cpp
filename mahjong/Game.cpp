#include "std.h"

Game::Game()
{
	Player* player1 = new Player("사용자");
	Player* player2 = new Player("AI 2");
	Player* player3 = new Player("AI 3");
	Player* player4 = new Player("AI 4");
	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);
	players.push_back(player4);

	Init Init;
	tiles = Init.Set_tiles();

}

bool Game::Start_Remove_14()
{
	for (int i = 0; i < 14; i++)
	{
		if (tiles.empty())
		{
			cout << "타일 14개를 지우는데 실패했습니다" << endl;
			return false;
		}
		Tiles* del = tiles.front();
		tiles.pop();
		delete del;
	}
	return true;
}

bool Game::Disturb_Tiles(int _count, int _repeat)
{
	// _count: 배분할 패의 개수(1개/4개 예상)
	// _repeat: 반복 횟수

	for (int i = 0; i < _repeat; i++)
	{
		for (int j = 0; j < _count; j++)
		{
			if (tiles.empty())
			{
				cout << "타일을 분배하는데 실패했습니다" << endl;
				return false;
			}
			Tiles* temp = tiles.front();
			tiles.pop();
			player1.push_back(temp);
		}
		for (int j = 0; j < _count; j++)
		{
			if (tiles.empty())
			{
				cout << "타일을 분배하는데 실패했습니다" << endl;
				return false;
			}
			Tiles* temp = tiles.front();
			tiles.pop();
			player2.push_back(temp);
		}
		for (int j = 0; j < _count; j++)
		{
			if (tiles.empty())
			{
				cout << "타일을 분배하는데 실패했습니다" << endl;
				return false;
			}
			Tiles* temp = tiles.front();
			tiles.pop();
			player3.push_back(temp);
		}
		for (int j = 0; j < _count; j++)
		{
			if (tiles.empty())
			{
				cout << "타일을 분배하는데 실패했습니다" << endl;
				return false;
			}
			Tiles* temp = tiles.front();
			tiles.pop();
			player4.push_back(temp);
		}
	}
	return true;
}

void Game::print_my_tiles()
{
	if (player1.empty())
	{
		cout << "플레이어 1의 타일이 없습니다" << endl;
		return;
	}

	cout << "플레이어 1의 타일: ";
	for (int i = 0; i < player1.size(); i++)
	{
		cout << player1[i]->getReadableName() << " ";
	}

}

void Game::print_thrown_tiles()
{
	system("CLS");
	cout << "버려진 타일: ";
	if (throwntiles.empty())
	{
		cout << endl;
		return;
	}
	for (int i = 0; i < throwntiles.size(); i++)
	{
		cout << throwntiles[i]->getReadableName() << " ";
	}
	cout << endl;
}

void Game::print_my_newTile()
{
	cout << "[ " << player1.back()->getReadableName() << " ]" << endl;
}

void Game::sort()
{
	for (int i = 0; i < player1.size(); i++)
	{
		for (int j = 0; j < player1.size() - 1; j++)
		{
			if (player1[j]->getPriority() > player1[j + 1]->getPriority())
			{
				swap(player1[j], player1[j + 1]);
			}
		}
	}
}

bool Game::get_newTile()
{
	if (tiles.empty())
	{
		cout << "더 이상 타일이 없습니다" << endl;
		cout << "화료(승리) 실패" << endl;
		return false;
	}
	Tiles* temp = tiles.front();
	tiles.pop();
	player1.push_back(temp);
	return true;
}


bool Game::throw_tile()
{
	Sleep(1000);
	
	while (true)
	{

		if (checkWinningPrint())
		{
			if (player1.size() != 14) {
				return true;
			}
			if (Winning::isWinningHand(player1))
				return false;
			throwntiles.push_back(player1.back());
			player1.pop_back();
			return true;
		}
		string throw_tile;
		cout << "타패할 (버릴) 타일을 골라주세요: ";
		cin >> throw_tile;

		auto myfindif = [&throw_tile](Tiles* t) {
			return t->getReadableName() == throw_tile;
			};

		vector<Tiles*>::iterator found = find_if(player1.begin(), player1.end(), myfindif);
		if (found == player1.end())
		{
			cout << "해당 타일이 없습니다" << endl;
			continue;
		}
		throwntiles.push_back(*found);
		player1.erase(found);
		break;
	}
	return true;
	
}

bool Game::checkWinningPrint()
{
	if (Winning::isWinningHand(player1))
	{
		cout << "화료 패입니다" << endl;
		while (true)
		{
			char answer;
			cout << "화료 하시겠습니까? (Y/N): ";
			cin >> answer;
			if (answer == 'Y' || answer == 'y')
			{
				players[0]->setWin();
				return true;
			}
			else if (answer == 'N' || answer == 'n')
			{
				cout << "게임을 계속합니다." << endl;
				return false;
			}
			else
			{
				cout << "잘못된 입력입니다." << endl;
				continue;
			}
		}
		
	}
	else if (Winning::canDeclareRiichi(player1, discardableTiles) && !players[0]->getReach())
	{
		cout << "아래 패 중 하나를 타패시 리치 가능합니다."<<endl;
		for (int i = 0; i < discardableTiles.size(); i++)
		{
			cout << discardableTiles[i]->getReadableName() << " ";
		}
		cout << endl;
		char answer;
		while (true)
		{
			cout << "리치 하시겠습니까? (Y/N): ";
			cin >> answer;
			if (answer == 'Y' || answer == 'y')
			{
				string answer2;
				cout << "어떤 패를 타패하시겠습니까?: ";
				cin >> answer2;
				auto myfindif = [&answer2](Tiles* t) {
					return (t->getReadableName() == answer2);
					};
				vector<Tiles*>::iterator found = find_if(player1.begin(), player1.end(), myfindif);
				if (found == player1.end())
				{
					cout << "해당 타일이 없습니다" << endl;
					continue;
				}
				throwntiles.push_back(*found);
				player1.erase(found);
				players[0]->setReach();
				return true;
			}
			else if (answer == 'N' || answer == 'n')
			{
				cout << "게임을 계속합니다." << endl;
				return false;
			}
			else
			{
				cout << "잘못된 입력입니다." << endl;
				continue;
			}
		}
	}
	else if (players[0]->getReach())
	{
		cout << "현재 리치 상태입니다." << endl;
		return true;
	}
	else
	{
		cout << "화료 패가 아닙니다" << endl;
		return false;
	}
}