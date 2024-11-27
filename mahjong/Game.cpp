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

	gameEnded = false;

}

Game::~Game()
{

}


void Print_Tiles(const Tiles* tile)
{

	int color = 0;
	// 0: ����, 1: �Ķ�, 2: ���, 3: �ϴû�, 4: ����, 5: ����, 6: ���, 7: ���, 8: ȸ��, 9: �Ķ�, 10: ���, 11: �ϴû�, 12: ����, 13: ����, 14: ���, 15: ���
	if (tile->getName().find("M") != string::npos)
		color = 4;
	else if (tile->getName().find("P") != string::npos)
		color = 1;
	else if (tile->getName().find("S") != string::npos)
		color = 2;
	else if (tile->getName().find("Z") != string::npos)
		color = 3;

	CONSOLE_SCREEN_BUFFER_INFO buff;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buff);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		(buff.wAttributes & 0xf0) | (color & 0xf));
	cout << tile->getReadableName() << " ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void Game::Print_Reach_Users()
{
	cout << "���� ��ġ ������ �����: ";
	int reach_users = 0;
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->getReach())
		{
			cout << players[i]->getName() << " ";
			reach_users++;
		}
	}
	if (reach_users == 0)
		cout << "����";
	cout << endl;
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
	cout << "���� Ÿ�� ��: " << tiles.size() << endl;
	cout << "�÷��̾� 1�� Ÿ��: ";
	for (int i = 0; i < player1.size(); i++)
	{
		Print_Tiles(player1[i]);
		cout << " ";
	}
}
void Game::print_my_tiles(bool)
{
	if (player1.empty())
	{
		cout << "�÷��̾� 1�� Ÿ���� �����ϴ�" << endl;
		return;
	}
	cout << "���� Ÿ�� ��: " << tiles.size() << endl;
	cout << "�÷��̾� 1�� Ÿ��: ";
	for (int i = 0; i < player1.size() - 1; i++)
	{
		Print_Tiles(player1[i]);
		cout << " ";
	}
}

void Game::print_thrown_tiles()
{
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
	for (int i = 0; i < player2.size(); i++)
	{
		for (int j = 0; j < player2.size() - 1; j++)
		{
			if (player2[j]->getPriority() > player2[j + 1]->getPriority())
			{
				swap(player2[j], player2[j + 1]);
			}
		}
	}
	for (int i = 0; i < player3.size(); i++)
	{
		for (int j = 0; j < player3.size() - 1; j++)
		{
			if (player3[j]->getPriority() > player3[j + 1]->getPriority())
			{
				swap(player3[j], player3[j + 1]);
			}
		}
	}
	for (int i = 0; i < player4.size(); i++)
	{
		for (int j = 0; j < player4.size() - 1; j++)
		{
			if (player4[j]->getPriority() > player4[j + 1]->getPriority())
			{
				swap(player4[j], player4[j + 1]);
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

bool Game::checkRon(const Tiles* discardedTile, const vector<Tiles*>& playerTiles, Player* player) {
	if (!player->getReach()) {
		return false;
	}

	// Make a temporary copy of the hand
	vector<Tiles*> tempHand = playerTiles;

	// Add the discarded tile without modifying the original
	if (discardedTile != nullptr) {
		tempHand.push_back(const_cast<Tiles*>(discardedTile));
	}

	// Check if this creates a winning hand
	if (Winning::isWinningHand(tempHand)) {
		return true;
	}

	tempHand.clear();  // Clean up the temporary vector
	return false;
}

void Game::endGame() {
	if (!gameEnded) {
		gameEnded = true;
		cout << "\n=== ���� ���� ===\n" << endl;

		// ���� ���� �� ���� ���
		Print_Reach_Users();
		print_thrown_tiles();
		cout << "���� Ÿ�� ��: " << tiles.size() << endl;
		print_my_tiles();
		cout << endl;
		print_ai_tiles();
	}
}


bool Game::checkRonForAllPlayers(Tiles* discardedTile) {
	if (discardedTile == nullptr || gameEnded) return false;

	// �� �÷��̾ ���� �� üũ
	for (int i = 0; i < players.size(); i++) {
		const vector<Tiles*>& currentPlayerTiles = (i == 0) ? player1 :
			(i == 1) ? player2 :
			(i == 2) ? player3 : player4;

		if (checkRon(discardedTile, currentPlayerTiles, players[i])) {
			cout << players[i]->getName() << "�� ������ �¸��߽��ϴ�!" << endl;
			players[i]->setWin();
			endGame();
			return true;
		}
	}
	return false;
}

bool Game::throw_tile() {
	Sleep(1000);

	while (true) {
		// First check for Tsumo (self-draw win) when in Riichi
		if (players[0]->getReach() && Winning::isWinningHand(player1)) {
			cout << "���� �¸��� �� �ֽ��ϴ�!" << endl;
			char answer;
			while (true) {
				cout << "�¸��Ͻðڽ��ϱ�? (Y/N): ";
				cin >> answer;
				if (answer == 'Y' || answer == 'y') {
					players[0]->setWin();
					return false;
				}
				else if (answer == 'N' || answer == 'n') {
					break;
				}
				else {
					cout << "�߸��� �Է��Դϴ�." << endl;
				}
			}
		}

		if (checkWinningPrint()) {
			if (player1.size() != 14) {
				return true;
			}
			if (players[0]->getWin())
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
		if (found == player1.end()) {
			cout << "�ش� Ÿ���� �����ϴ�" << endl;
			continue;
		}

		// Store the discarded tile before erasing it
		Tiles* discardedTile = *found;
		player1.erase(found);
		throwntiles.push_back(discardedTile);

		// After discarding, check if any other player can Ron
		if (checkRonForAllPlayers(discardedTile)) {
			return false;  // Game ends due to Ron
		}

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
			else if ((answer == 'N' || answer == 'n') && players[0]->getReach())
			{
				cout << "��ġ ���¿��� ȭ�Ḧ ���� �ʽ��ϴ�. ������ ����մϴ�." << endl;
				return true;
			}
			else if ((answer == 'N' || answer == 'n') && !players[0]->getReach())
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


bool Game::processAITurns() {
	if (gameEnded) return false;

	for (int i = 1; i < players.size(); i++) {
		vector<Tiles*>& currentPlayerTiles = (i == 1) ? player2 :
			(i == 2) ? player3 : player4;

		if (tiles.empty()) {
			cout << "�� �̻� Ÿ���� �����ϴ�" << endl;
			endGame();
			return false;
		}

		cout << "\n" << players[i]->getName() << "�� �����Դϴ�." << endl;

		// �� Ÿ�� �̱�
		Tiles* newTile = tiles.front();
		tiles.pop();
		currentPlayerTiles.push_back(newTile);

		cout << players[i]->getName() << "�� ���ο� Ÿ���� �̾ҽ��ϴ�: ";
		Print_Tiles(newTile);
		cout << endl;

		// ��� üũ
		if (players[i]->getReach() && Winning::isWinningHand(currentPlayerTiles)) {
			cout << players[i]->getName() << "�� ���� �¸��߽��ϴ�!" << endl;
			players[i]->setWin();
			endGame();
			return false;
		}

		// Ÿ�� ������
		Tiles* discardTile = findTileToDiscard(currentPlayerTiles, players[i]);
		if (discardTile) {
			cout << players[i]->getName() << "�� ���� ��: ";
			Print_Tiles(discardTile);
			cout << endl;

			auto it = find(currentPlayerTiles.begin(), currentPlayerTiles.end(), discardTile);
			if (it != currentPlayerTiles.end()) {
				currentPlayerTiles.erase(it);
				throwntiles.push_back(discardTile);

				// �� üũ
				if (checkRonForAllPlayers(discardTile)) {
					return false;
				}
			}
		}

		Sleep(1000);
	}
	return !gameEnded;
}

Tiles* Game::findTileToDiscard(vector<Tiles*>& playerTiles, Player* player) {
	vector<Tiles*> candidates = getFinalCandidates(playerTiles);

	if (candidates.empty()) {
		// Fallback to any tile if no candidates found
		if (!playerTiles.empty()) {
			return playerTiles[0];
		}
		return nullptr;
	}

	// Choose randomly from candidates to add variety
	int randomIndex = rand() % candidates.size();
	return candidates[randomIndex];
}

vector<Tiles*> Game::getFinalCandidates(vector<Tiles*>& tiles) {
	vector<Tiles*> candidates;

	// Rule 1: First check for honor tiles (winds and dragons)
	for (Tiles* tile : tiles) {
		int priority = tile->getPriority();
		if (priority >= 28) { // Honor tiles
			int count = getNumSimilarTiles(tiles, tile);
			if (count == 4 || count == 1) {
				candidates.push_back(tile);
			}
		}
	}

	// If we found honor tiles to discard, return them
	if (!candidates.empty()) {
		return candidates;
	}

	// Rule 2: Look for isolated number tiles
	for (Tiles* tile : tiles) {
		int priority = tile->getPriority();
		if (priority <= 27) { // Number tiles
			bool isIsolated = true;
			int suite = (priority - 1) / 9;
			int number = (priority - 1) % 9 + 1;

			// Check for connections in same suite
			for (Tiles* other : tiles) {
				int otherPriority = other->getPriority();
				if (otherPriority <= 27) {
					int otherSuite = (otherPriority - 1) / 9;
					int otherNumber = (otherPriority - 1) % 9 + 1;

					if (suite == otherSuite && abs(number - otherNumber) == 1) {
						isIsolated = false;
						break;
					}
				}
			}

			if (isIsolated) {
				candidates.push_back(tile);
			}
		}
	}

	// If we found isolated tiles, return them
	if (!candidates.empty()) {
		return candidates;
	}

	// Rule 3: Look for tiles at the edge of sequences
	for (Tiles* tile : tiles) {
		int priority = tile->getPriority();
		if (priority <= 27) {
			if (!isPartOfTriplet(tiles, tile) && isPartOfSequence(tiles, tile)) {
				int suite = (priority - 1) / 9;
				int number = (priority - 1) % 9 + 1;

				// Check if it's at the edge of a sequence
				if (number == 1 || number == 9 ||
					getNumSimilarTiles(tiles, tile) >= 2) {
					candidates.push_back(tile);
				}
			}
		}
	}

	// Rule 4: If still no candidates, look for tiles that aren't part of any meaningful combination
	if (candidates.empty()) {
		for (Tiles* tile : tiles) {
			if (!isPartOfSequence(tiles, tile) && !isPartOfTriplet(tiles, tile)) {
				candidates.push_back(tile);
			}
		}
	}

	// Rule 5: If still nothing, add any tile that isn't part of a triplet
	if (candidates.empty()) {
		for (Tiles* tile : tiles) {
			if (!isPartOfTriplet(tiles, tile)) {
				candidates.push_back(tile);
			}
		}
	}

	return candidates;
}

bool Game::isPartOfSequence(const vector<Tiles*>& tiles, Tiles* tile) {
	int priority = tile->getPriority();
	if (priority > 27) return false; // Honor tiles can't be part of sequence

	int suite = (priority - 1) / 9;
	int number = (priority - 1) % 9 + 1;

	// Check for potential sequences
	bool hasPrev = false, hasNext = false;

	for (Tiles* other : tiles) {
		if (other == tile) continue;

		int otherPriority = other->getPriority();
		if (otherPriority <= 27) {
			int otherSuite = (otherPriority - 1) / 9;
			int otherNumber = (otherPriority - 1) % 9 + 1;

			if (suite == otherSuite) {
				if (otherNumber == number - 1) hasPrev = true;
				if (otherNumber == number + 1) hasNext = true;
			}
		}
	}

	return hasPrev || hasNext;
}

bool Game::isPartOfTriplet(const vector<Tiles*>& tiles, Tiles* tile) {
	return getNumSimilarTiles(tiles, tile) >= 3;
}

int Game::getNumSimilarTiles(const vector<Tiles*>& tiles, Tiles* tile) {
	int count = 0;
	int targetPriority = tile->getPriority();

	for (Tiles* other : tiles) {
		if (other->getPriority() == targetPriority) {
			count++;
		}
	}

	return count;
}

bool Game::checkConsecutiveHonorTiles(const vector<Tiles*>& tiles, int priority, int& count) {
	count = 0;
	for (auto tile : tiles) {
		if (tile->getPriority() == priority) {
			count++;
		}
	}
	return count >= 1;
}

bool Game::isSingleHonorTile(const vector<Tiles*>& tiles, int priority) {
	int count = 0;
	for (auto tile : tiles) {
		if (tile->getPriority() == priority) {
			count++;
		}
	}
	return count == 1;
}

bool Game::isIsolatedNumberTile(const vector<Tiles*>& tiles, int priority) {
	// Check if the tile is a number tile and is isolated
	if (priority > 27) return false;

	int suite = (priority - 1) / 9;
	int number = (priority - 1) % 9 + 1;

	bool hasAdjacent = false;
	for (auto tile : tiles) {
		int otherPriority = tile->getPriority();
		if (otherPriority > 27) continue;

		int otherSuite = (otherPriority - 1) / 9;
		int otherNumber = (otherPriority - 1) % 9 + 1;

		if (suite == otherSuite && abs(number - otherNumber) == 1) {
			hasAdjacent = true;
			break;
		}
	}

	return !hasAdjacent;
}

bool Game::isEdgeOfFourConsecutive(const vector<Tiles*>& tiles, int priority) {
	if (priority > 27) return false;

	int suite = (priority - 1) / 9;
	int number = (priority - 1) % 9 + 1;

	vector<bool> hasNumber(10, false);
	for (auto tile : tiles) {
		int otherPriority = tile->getPriority();
		if (otherPriority > 27) continue;

		int otherSuite = (otherPriority - 1) / 9;
		int otherNumber = (otherPriority - 1) % 9 + 1;

		if (suite == otherSuite) {
			hasNumber[otherNumber] = true;
		}
	}

	// Check if this is part of exactly 4 consecutive tiles
	for (int i = 1; i <= 6; i++) {
		if (hasNumber[i] && hasNumber[i + 1] && hasNumber[i + 2] && hasNumber[i + 3] &&
			(!hasNumber[i - 1] || i == 1) && (!hasNumber[i + 4] || i + 3 == 9)) {
			return (number == i || number == i + 3);
		}
	}

	return false;
}

vector<vector<Tiles*>> Game::findConsecutiveGroups(const vector<Tiles*>& tiles) {
	vector<vector<Tiles*>> groups;
	vector<Tiles*> currentGroup;

	for (int suite = 0; suite < 3; suite++) {
		vector<bool> hasNumber(10, false);
		for (auto tile : tiles) {
			int priority = tile->getPriority();
			if (priority > 27) continue;

			int tileSuite = (priority - 1) / 9;
			int number = (priority - 1) % 9 + 1;

			if (tileSuite == suite) {
				hasNumber[number] = true;
			}
		}

		// Find consecutive groups
		for (int i = 1; i <= 9; i++) {
			if (hasNumber[i]) {
				if (currentGroup.empty() ||
					(currentGroup.back()->getPriority() - 1) % 9 + 1 == i - 1) {
					for (auto tile : tiles) {
						if (tile->getPriority() == suite * 9 + i) {
							currentGroup.push_back(tile);
							break;
						}
					}
				}
				else {
					if (!currentGroup.empty()) {
						groups.push_back(currentGroup);
						currentGroup.clear();
					}
					for (auto tile : tiles) {
						if (tile->getPriority() == suite * 9 + i) {
							currentGroup.push_back(tile);
							break;
						}
					}
				}
			}
			else {
				if (!currentGroup.empty()) {
					groups.push_back(currentGroup);
					currentGroup.clear();
				}
			}
		}
		if (!currentGroup.empty()) {
			groups.push_back(currentGroup);
			currentGroup.clear();
		}
	}

	return groups;
}

bool Game::isPartOfLongConsecutive(const vector<Tiles*>& tiles, int priority) {
	auto groups = findConsecutiveGroups(tiles);

	for (const auto& group : groups) {
		if (group.size() >= 5) {
			// Check if this tile is not part of a complete triplet within the group
			for (auto tile : group) {
				if (tile->getPriority() == priority) {
					int pos = tile->getPriority() % 9;
					if (pos < 3 || pos >= group.size() - 2) {
						return true;
					}
				}
			}
		}
	}

	return false;
}

void Game::print_ai_tiles() {
	// Print Player 2's tiles
	cout << "Player 2�� Ÿ��: ";
	for (int i = 0; i < player2.size(); i++) {
		Print_Tiles(player2[i]);
		cout << " ";
	}
	cout << endl;

	// Print Player 3's tiles
	cout << "Player 3�� Ÿ��: ";
	for (int i = 0; i < player3.size(); i++) {
		Print_Tiles(player3[i]);
		cout << " ";
	}
	cout << endl;

	// Print Player 4's tiles
	cout << "Player 4�� Ÿ��: ";
	for (int i = 0; i < player4.size(); i++) {
		Print_Tiles(player4[i]);
		cout << " ";
	}
	cout << endl;
}

void Game::printFinalGameState() {
	Print_Reach_Users();
	print_thrown_tiles();
	cout << "���� Ÿ�� ��: " << tiles.size() << endl;
	print_my_tiles();
	cout << endl;
	print_ai_tiles();
}