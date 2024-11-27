#include "std.h"

Game::Game()
{
	Player* player1 = new Player("�����");
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
			cout << "Ÿ�� 14���� ����µ� �����߽��ϴ�" << endl;
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
	// _count: ����� ���� ����(1��/4�� ����)
	// _repeat: �ݺ� Ƚ��

	for (int i = 0; i < _repeat; i++)
	{
		for (int j = 0; j < _count; j++)
		{
			if (tiles.empty())
			{
				cout << "Ÿ���� �й��ϴµ� �����߽��ϴ�" << endl;
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
				cout << "Ÿ���� �й��ϴµ� �����߽��ϴ�" << endl;
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
				cout << "Ÿ���� �й��ϴµ� �����߽��ϴ�" << endl;
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
				cout << "Ÿ���� �й��ϴµ� �����߽��ϴ�" << endl;
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
		cout << "�÷��̾� 1�� Ÿ���� �����ϴ�" << endl;
		return;
	}

	cout << "�÷��̾� 1�� Ÿ��: ";
	for (int i = 0; i < player1.size(); i++)
	{
		cout << player1[i]->getReadableName() << " ";
	}

}

void Game::print_thrown_tiles()
{
	system("CLS");
	cout << "������ Ÿ��: ";
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
		cout << "�� �̻� Ÿ���� �����ϴ�" << endl;
		cout << "ȭ��(�¸�) ����" << endl;
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
		cout << "Ÿ���� (����) Ÿ���� ����ּ���: ";
		cin >> throw_tile;

		auto myfindif = [&throw_tile](Tiles* t) {
			return t->getReadableName() == throw_tile;
			};

		vector<Tiles*>::iterator found = find_if(player1.begin(), player1.end(), myfindif);
		if (found == player1.end())
		{
			cout << "�ش� Ÿ���� �����ϴ�" << endl;
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
		cout << "ȭ�� ���Դϴ�" << endl;
		while (true)
		{
			char answer;
			cout << "ȭ�� �Ͻðڽ��ϱ�? (Y/N): ";
			cin >> answer;
			if (answer == 'Y' || answer == 'y')
			{
				players[0]->setWin();
				return true;
			}
			else if (answer == 'N' || answer == 'n')
			{
				cout << "������ ����մϴ�." << endl;
				return false;
			}
			else
			{
				cout << "�߸��� �Է��Դϴ�." << endl;
				continue;
			}
		}
		
	}
	else if (Winning::canDeclareRiichi(player1, discardableTiles) && !players[0]->getReach())
	{
		cout << "�Ʒ� �� �� �ϳ��� Ÿ�н� ��ġ �����մϴ�."<<endl;
		for (int i = 0; i < discardableTiles.size(); i++)
		{
			cout << discardableTiles[i]->getReadableName() << " ";
		}
		cout << endl;
		char answer;
		while (true)
		{
			cout << "��ġ �Ͻðڽ��ϱ�? (Y/N): ";
			cin >> answer;
			if (answer == 'Y' || answer == 'y')
			{
				string answer2;
				cout << "� �и� Ÿ���Ͻðڽ��ϱ�?: ";
				cin >> answer2;
				auto myfindif = [&answer2](Tiles* t) {
					return (t->getReadableName() == answer2);
					};
				vector<Tiles*>::iterator found = find_if(player1.begin(), player1.end(), myfindif);
				if (found == player1.end())
				{
					cout << "�ش� Ÿ���� �����ϴ�" << endl;
					continue;
				}
				throwntiles.push_back(*found);
				player1.erase(found);
				players[0]->setReach();
				return true;
			}
			else if (answer == 'N' || answer == 'n')
			{
				cout << "������ ����մϴ�." << endl;
				return false;
			}
			else
			{
				cout << "�߸��� �Է��Դϴ�." << endl;
				continue;
			}
		}
	}
	else if (players[0]->getReach())
	{
		cout << "���� ��ġ �����Դϴ�." << endl;
		return true;
	}
	else
	{
		cout << "ȭ�� �а� �ƴմϴ�" << endl;
		return false;
	}
}