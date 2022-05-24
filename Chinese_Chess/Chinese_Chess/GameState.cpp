#include "GameState.h"

//GameState::GameState(StateStack& stack, StateContext context)
//	: State(stack, context)
//	, playerBlack(Team::Black)
//	, playerRed(Team::Red)
//	, board()
//	, chessManager()
//	, ev()
//{
//	isPause = false;
//	hintHasShowed = false;
//	checkStalemate = false;
//	selectChess = nullptr;
//	selectPathChess = nullptr;
//	window = context.window;
//	sf::Vector2f tmpPos(window->getSize().x / 20, (window->getSize().y - board.getBoardSize().y) / 2);
//	this->board.setSpritePosition(tmpPos);
//	this->status = Status::WaitBlackPressed;
//	board.update(playerBlack, playerRed);
//	font = context.fontHolder->get(Fonts::ID::BiauKai);
//}
//
//GameState::~GameState()
//{
//	delete window;
//}
//
//void GameState::run()
//{
//	/*while (this->window->isOpen())
//	{
//		this->processEvent();
//		this->update();
//		this->render();
//	}*/
//}
//
void GameState::whoWin(const Player& playerBlack, const Player& playerRed)
{
	if (!playerBlack.getChessList()[0]->getActive())
	{
		std::cout << "RedPlayer Win\n";
		currentStatus = Status::end;
	}
	if (!playerRed.getChessList()[0]->getActive())
	{
		std::cout << "BlackPlayer Win\n";
		currentStatus = Status::end;
	}
}
void GameState::hint()
{
	if (currentStatus == Status::intitialize)
		return;
	if (hintHasShowed)
		return;
	//紅方剛移動完
	if (currentStatus == Status::WaitBlackPressed)
	{
		bool end = true;
		for (auto const& chess : playerBlack.getChessList())
		{
			//有路可走
			if (chess->getActive() && chess->findPath(board).size() != 0)
			{
				std::vector <sf::Vector2f> validPath = chess->findPath(board);
				for (auto const& path : validPath)
				{
					if (validMove(*chess, path))
					{
						end = false;
						break;
					}
				}
				if (!end)
					break;
			}
		}
		//欠行
		if (end)
		{
			currentStatus == Status::end;
			requestStackPush(States::ID::BlackIsStalemate);
		}
		//將軍
		else if (checkmate() == 1)
		{
			requestStackPush(States::ID::BlackIsCheckMate);
		}
		hintHasShowed = true;

	}
	//黑方剛移動完
	else if (currentStatus == Status::WaitRedPressed)
	{
		bool end = true;
		for (auto const& chess : playerRed.getChessList())
		{
			//有路可走
			if (chess->getActive() && chess->findPath(board).size() != 0)
			{
				//std::cout << chess->getId() << "<-\n";
				std::vector <sf::Vector2f> validPath = chess->findPath(board);
				for (auto const& path : validPath)
				{
					if (validMove(*chess, path))
					{
						//std::cout << "O\n";
						end = false;
						break;
					}
					else
					{
						std::cout << chess->getBoardPosition().x << " " << chess->getBoardPosition().y << " =>" << path.x << " " << path.y;
						//std::cout << "X\n";
					}
				}
				if (!end)
					break;
			}
		}
		//欠行


		if (end)
		{
			currentStatus == Status::end;
			requestStackPush(States::ID::RedIsStalemate);
		}
		//將軍
		else if (checkmate() == 2)
		{
			requestStackPush(States::ID::RedIsCheckMate);
		}
		hintHasShowed = true;
	}
}
int GameState::checkmate()
{
	//黑方剛移動完
	if (currentStatus == Status::WaitRedPressed)
	{
		for (auto& tmpChess : playerBlack.getChessList())
		{
			if (tmpChess->getActive())
			{
				std::vector <sf::Vector2f> tmpPath = tmpChess->findPath(this->board);
				for (auto& tmpPos : tmpPath)
				{

					if (tmpPos == playerRed.getChessList()[0]->getBoardPosition())
					{
						//黑方將紅方軍
						return 2;
					}
				}
			}

		}
	}
	//紅方剛移動完
	else if (currentStatus == Status::WaitBlackPressed)
	{
		for (auto& tmpChess : playerRed.getChessList())
		{
			if (tmpChess->getActive())
			{
				std::vector <sf::Vector2f> tmpPath = tmpChess->findPath(this->board);
				for (auto& tmpPos : tmpPath)
				{

					if (tmpPos == playerBlack.getChessList()[0]->getBoardPosition())
					{
						//紅方將黑方軍
						return 1;
					}
				}

			}
		}
	}
	return 0;
}

bool GameState::validMove(Chess& _selectedChess, sf::Vector2f goalPos)
{
	Board tmpBoard = board;
	bool valid = true;
	sf::Vector2f originalPos = _selectedChess.getBoardPosition();
	sf::Vector2f kingPos;
	//先移動
	int indexOfAliveChess = -1;
	if (tmpBoard.getBoard()[goalPos.y][goalPos.x]!=nullptr && tmpBoard.getBoard()[goalPos.y][goalPos.x]->getActive())
	{
		for (int index=0;index<16;index++)
		{
			if (goalPos == playerBlack.getChessList()[index]->getBoardPosition()&& 
				playerBlack.getChessList()[index]->getActive())
			{
				indexOfAliveChess = index;
				playerBlack.getChessList()[index]->setActive(false);
				break;
			}
			if (goalPos == playerRed.getChessList()[index]->getBoardPosition() &&
				playerRed.getChessList()[index]->getActive())
			{
				indexOfAliveChess = index;
				playerRed.getChessList()[index]->setActive(false);
				break;
			}
		}
	}
	_selectedChess.setBoardPosition(goalPos);
	
	tmpBoard.update(playerBlack.getChessList(), playerRed.getChessList());

	//若被選擇的棋子是黑色的
	if (_selectedChess.getTeam() == Team::Black)
	{
		//先找出黑色將軍位置
		kingPos = playerBlack.getChessList()[0]->getBoardPosition();
		//遍歷紅色棋子的下一步
		for (auto const& tmpChess : playerRed.getChessList())
		{
			if (tmpChess->getActive())
			{
				std::vector <sf::Vector2f> tmpPath = tmpChess->findPath(tmpBoard);
				
				for (auto const& path : tmpPath)
				{
					//若任一紅色棋子的下一步為黑色將軍位置
					//非法的路徑
					if (path == kingPos)
					{
						if (indexOfAliveChess != -1)
						{
							playerRed.getChessList()[indexOfAliveChess]->setActive(true);
						}
						_selectedChess.setBoardPosition(originalPos);
						return false;
					}

				}
			}
		}
		if (indexOfAliveChess != -1)
		{
			playerRed.getChessList()[indexOfAliveChess]->setActive(true);
		}
	}
	//若被選擇的棋子是紅色的
	else if (_selectedChess.getTeam() == Team::Red)
	{
		//先找出紅色將軍位置
		kingPos = playerRed.getChessList()[0]->getBoardPosition();
		//遍歷黑色棋子的下一步
		for (auto const& tmpChess : playerBlack.getChessList())
		{
			if (tmpChess->getActive())
			{
				std::vector <sf::Vector2f> tmpPath = tmpChess->findPath(tmpBoard);
				for (auto const& path : tmpPath)
				{
					//若任一黑色棋子的下一步為紅色將軍位置
					//非法的路徑
					if (path == kingPos)
					{
						if (indexOfAliveChess != -1)
						{
							playerBlack.getChessList()[indexOfAliveChess]->setActive(true);
						}
						_selectedChess.setBoardPosition(originalPos);
						return false;
					}

				}
			}
		}
		if (indexOfAliveChess != -1)
		{
			playerBlack.getChessList()[indexOfAliveChess]->setActive(true);
		}
	}
	_selectedChess.setBoardPosition(originalPos);
	return true;

}
//
//int GameState::checkmate()
//{
//	//黑方剛移動完
//	if (status == Status::WaitRedPressed)
//	{
//		for (auto& tmpChess : playerBlack.getChessList())
//		{
//			if (tmpChess->getActive())
//			{
//				std::vector <sf::Vector2f> tmpPath = tmpChess->findPath(this->board);
//				for (auto& tmpPos : tmpPath)
//				{
//					if (tmpPos == playerRed.getChessList()[0]->getPosition())
//					{
//						//黑方將紅方軍
//						return 2;
//					}
//				}
//			}
//
//		}
//	}
//	//紅方剛移動完
//	else if (status == Status::WaitBlackPressed)
//	{
//		for (auto& tmpChess : playerRed.getChessList())
//		{
//			if (tmpChess->getActive())
//			{
//				std::vector <sf::Vector2f> tmpPath = tmpChess->findPath(this->board);
//				for (auto& tmpPos : tmpPath)
//				{
//
//					if (tmpPos == playerBlack.getChessList()[0]->getPosition())
//					{
//						//紅方將黑方軍
//						return 1;
//					}
//				}
//
//			}
//		}
//	}
//	return 0;
//}
//
//bool GameState::validMove(Chess& _selectedChess, sf::Vector2f _goalPos)
//{
//	Board tmpBoard = board;
//	bool valid = true;
//	sf::Vector2f originalPos = _selectedChess.getPosition();
//	sf::Vector2f kingPos;
//
//	tmpBoard.setBoard(&_selectedChess, _goalPos);
//
//	_selectedChess.setPosition(_goalPos);
//	for (auto const& chessY : tmpBoard.getBoard())
//	{
//		for (auto const& chessX : chessY)
//		{
//			if (chessX != nullptr && chessX->getTeam() == _selectedChess.getTeam())
//			{
//				if (chessX->getCharacters() == Characters::King)
//				{
//					kingPos = chessX->getPosition();
//				}
//			}
//		}
//	}
//
//	for (int y = 0;y < 10;y++)
//	{
//		for (int x = 0;x < 9;x++)
//		{
//			if (tmpBoard.getBoard()[y][x] != nullptr && tmpBoard.getBoard()[y][x]->getTeam() != _selectedChess.getTeam())
//			{
//				std::vector <sf::Vector2f> tmpPath = tmpBoard.getBoard()[y][x]->findPath(tmpBoard);
//				for (auto const& path : tmpPath)
//				{
//					if (path == kingPos)
//					{
//						_selectedChess.setPosition(originalPos);
//						return false;
//					}
//
//				}
//			}
//		}
//	}
//	_selectedChess.setPosition(originalPos);
//	return true;
//}
//
//sf::Vector2f GameState::BoardToWindowPosition(sf::Vector2f boardArrPosition)
//{
//	sf::Vector2f windowPosition;
//	int x = (board.getBoardSize().x / 8) * boardArrPosition.x + board.getSprite().getPosition().x;
//	int y = (board.getBoardSize().y / 9) * boardArrPosition.y + board.getSprite().getPosition().y;
//	windowPosition = sf::Vector2f(x, y);
//	return windowPosition;
//}
//
//sf::Vector2f GameState::WindowToBoardPosition(sf::Vector2f windowPosition)
//{
//	sf::Vector2f boardPosition;
//	int x = (windowPosition.x - (board.getSprite().getPosition().x - board.getBoardSize().x / 16)) / (board.getBoardSize().x / 8);
//	int y = (windowPosition.y - (board.getSprite().getPosition().y - board.getBoardSize().x / 18)) / (board.getBoardSize().y / 9);
//	boardPosition.x = x;
//	boardPosition.y = y;
//	//std::cout << boardPosition.x << " " << boardPosition.y << "\n";
//	return boardPosition;
//}
//
//bool GameState::handleEvent(const sf::Event& event)
//{
//	if (getStackNum() == 1)
//		isPause = false;
//	while (this->window->pollEvent(this->ev))
//	{
//		switch (event.type)
//		{
//		case sf::Event::KeyPressed: {
//
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
//				if (isPause == false) {
//					requestStackPush(States::ID::Pause);
//					isPause = true;
//				}
//				else {
//					requestStackPop();
//					isPause = false;
//				}
//			}
//			break;
//		}
//		case sf::Event::Closed:
//			this->window->close();
//			break;
//		}
//	}
//	if (status == Status::WaitBlackPressed || status == Status::WaitBlackPathPressed)
//		playerBlack.handleRealtimeInput(chessManager, status, board);
//
//	if (status == Status::WaitRedPressed || status == Status::WaitRedPathPressed)
//		playerRed.handleRealtimeInput(chessManager, status, board);
//
//	//將軍&欠行跳出視窗
//	//紅方剛移動完
//	if (status == Status::WaitBlackPressed && !hintHasShowed)
//	{
//		bool end = true;
//		for (auto const& chess : playerBlack.getChessList())
//		{
//			//有路可走
//			if (chess->getActive() && chess->findPath(board).size() != 0)
//			{
//				std::vector <sf::Vector2f> validPath = chess->findPath(board);
//				for (auto const& path : validPath)
//				{
//					if (validMove(*chess, path))
//					{
//						end = false;
//						break;
//					}
//				}
//			}
//			if (!end)
//				break;
//		}
//		//欠行
//		if (end)
//		{
//			isPause = true;
//			requestStackPush(States::ID::BlackIsStalemate);
//		}
//		//將軍
//		else if (!hintHasShowed && checkmate() == 1)
//		{
//			isPause = true;
//			requestStackPush(States::ID::BlackIsCheckMate);
//		}
//		hintHasShowed = true;
//
//	}
//	//黑方剛移動完
//	else if (status == Status::WaitRedPressed && !hintHasShowed)
//	{
//		bool end = true;
//		for (auto const& chess : playerRed.getChessList())
//		{
//			//有路可走
//			if (chess->getActive() && chess->findPath(board).size() != 0)
//			{
//				std::vector <sf::Vector2f> validPath = chess->findPath(board);
//				for (auto const& path : validPath)
//				{
//					if (validMove(*chess, path))
//					{
//						end = false;
//						break;
//					}
//				}
//			}
//			if (!end)
//				break;
//		}
//		//欠行
//		if (end)
//		{
//			isPause = true;
//			requestStackPush(States::ID::RedIsStalemate);
//		}
//		//將軍
//		else if (checkmate() == 2)
//		{
//
//			isPause = true;
//			requestStackPush(States::ID::RedIsCheckMate);
//		}
//		hintHasShowed = true;
//	}
//
//	return true;
//}
//
//bool GameState::update(sf::Time dt)
//{
//
//	if (!isPause) {
//		whoWin(playerBlack, playerRed);
//
//		board.update(playerBlack, playerRed);
//		for (auto chess : playerBlack.getChessList()) {
//			if (chess->getActive()) {
//				chess->resetIsPressed();
//				chess->setSpritePosition(BoardToWindowPosition(chess->getPosition()));
//				if (status == Status::WaitBlackPressed || status == Status::WaitBlackPathPressed)
//					chess->update(*window, ev);
//			}
//		}
//		for (auto chess : playerRed.getChessList()) {
//			if (chess->getActive()) {
//				chess->resetIsPressed();
//				chess->setSpritePosition(BoardToWindowPosition(chess->getPosition()));
//				if (status == Status::WaitRedPressed || status == Status::WaitRedPathPressed)
//					chess->update(*window, ev);
//			}
//		}
//		for (auto& tmpChess : tmpChessObj) {
//			if (tmpChess->getActive()) {
//				tmpChess->resetIsPressed();
//				tmpChess->setSpritePosition(BoardToWindowPosition(tmpChess->getPosition()));
//				tmpChess->update(*window, ev);
//			}
//		}
//		switch (status)
//		{
//		case Status::WaitBlackPressed:
//			while (chessManager.getCommandNum()) {
//				std::vector<sf::Vector2f> tmpValidPath = chessManager.doCommand(*selectChess);
//				this->selectChess = chessManager.getSelectedChess();
//				playerBlack.setSelectChess(this->selectChess);
//				// if valid path number >= 1
//				if (tmpValidPath.size()) {
//					validPath = std::make_unique<std::vector<sf::Vector2f>>(tmpValidPath);
//
//					Factory tmpChessfac;
//					for (const auto& path : *(validPath.get())) {
//						// create tmp chess
//						if (selectChess != nullptr && selectChess->getActive())
//						{
//							Chess* tmpChess = (tmpChessfac.getChess(selectChess->getCharacters(), selectChess->getTeam(), -1));
//							tmpChess->setPosition(path);
//							tmpChessObj.push_back(tmpChess);
//						}
//					}
//					playerBlack.setValidMoveChessList(tmpChessObj);
//					status = Status::WaitBlackPathPressed;
//				}
//			}
//			break;
//		case Status::WaitBlackPathPressed:
//			while (chessManager.getCommandNum()) {
//				std::vector<sf::Vector2f> tmpValidPath = chessManager.doCommand(*(this->selectChess));
//				// if valid path number >= 1 -> succcess move
//				if (tmpValidPath.size()) {
//					tmpChessObj.clear();
//					this->selectChess = nullptr;
//					playerBlack.setSelectChess(nullptr);
//					hintHasShowed = false;
//					checkStalemate = false;
//					status = Status::WaitRedPressed;
//					break;
//				}
//				else {
//					tmpChessObj.clear();
//					this->selectChess = nullptr;
//					playerBlack.setSelectChess(nullptr);
//					status = Status::WaitBlackPressed;
//					break;
//				}
//			}
//			break;
//		case Status::WaitRedPressed:
//			while (chessManager.getCommandNum()) {
//				std::vector<sf::Vector2f> tmpValidPath = chessManager.doCommand(*selectChess);
//				this->selectChess = chessManager.getSelectedChess();
//				playerRed.setSelectChess(this->selectChess);
//				// if valid path number >= 1
//				if (tmpValidPath.size()) {
//					validPath = std::make_unique<std::vector<sf::Vector2f>>(tmpValidPath);
//
//					Factory tmpChessfac;
//					for (const auto& path : *(validPath.get())) {
//						// create tmp chess
//						if (selectChess != nullptr && selectChess->getActive())
//						{
//							Chess* tmpChess = (tmpChessfac.getChess(selectChess->getCharacters(), selectChess->getTeam(), -1));
//							tmpChess->setPosition(path);
//							tmpChessObj.push_back(tmpChess);
//						}
//					}
//					playerRed.setValidMoveChessList(tmpChessObj);
//					status = Status::WaitRedPathPressed;
//				}
//			}
//			break;
//		case Status::WaitRedPathPressed:
//			while (chessManager.getCommandNum()) {
//				std::vector<sf::Vector2f> tmpValidPath = chessManager.doCommand(*(this->selectChess));
//				// if valid path number >= 1 -> succcess move
//				if (tmpValidPath.size()) {
//					tmpChessObj.clear();
//					this->selectChess = nullptr;
//					playerRed.setSelectChess(nullptr);
//					hintHasShowed = false;
//					checkStalemate = false;
//					status = Status::WaitBlackPressed;
//					break;
//				}
//				else {
//					tmpChessObj.clear();
//					this->selectChess = nullptr;
//					playerRed.setSelectChess(nullptr);
//					status = Status::WaitRedPressed;
//					break;
//				}
//			}
//			break;
//		default:
//			break;
//		}
//	}
//	return true;
//}
//
//void GameState::draw()
//{
//
//	/* Drawing */
//	window->draw(board.getSprite());
//	for (auto& tmpChess : playerBlack.getChessList()) {
//		if (tmpChess->getActive())
//			window->draw(*tmpChess);
//	}
//	for (auto& tmpChess : playerRed.getChessList()) {
//		if (tmpChess->getActive())
//			window->draw(*tmpChess);
//	}
//
//	for (auto& tmpChess : tmpChessObj) {
//		window->draw(*tmpChess);
//	}
//
//}
//
//void GameState::showStatus()
//{
//	if (status == Status::WaitBlackPressed)
//		std::cout << "WaitBlackPressed";
//	else if (status == Status::WaitBlackPathPressed)
//		std::cout << "WaitBlackPathPressed";
//	else if (status == Status::WaitRedPressed)
//		std::cout << "WaitRedPressed";
//	else if (status == Status::WaitRedPathPressed)
//		std::cout << "WaitRedPathPressed";
//	std::cout << "\n";
//}

GameState::GameState(StateStack& _stack, StateContext _context)
	: State(_stack, _context)
	, board()
	, playerRed(Team::Red)
	, playerBlack(Team::Black)
	, sysInfo()
{
	
	window = _context.window;
	//player setName
	playerRed.setName(window);
	playerBlack.setName(window);
	sysInfo.setName(playerRed.getName(), playerBlack.getName());

	currentStatus = Status::intitialize;
	sf::Vector2f tmpPos(window->getSize().x / 20, (window->getSize().y - board.getBoardSize().y) / 2);
	this->board.setSpritePosition(tmpPos);
	hintHasShowed = false;
	isPause = false;
	isPressed = false;
	selectedChess = nullptr;
}

void GameState::draw()
{
	window->draw(board);
	for (const auto& tmpChess : playerRed.getChessList()) {
		window->draw(*tmpChess);
	}
	for (const auto& tmpChess : playerBlack.getChessList()) {
		window->draw(*tmpChess);
	}
	if (selectedChess != nullptr && selectedChess->validSpot.size()) {
		for (const auto& validPathChess : selectedChess->validSpot)
		{
			if (validPathChess != nullptr)
			{
				window->draw(*validPathChess);
			}

		}
	}
	sysInfo.draw(window);
}
bool GameState::update(sf::Time dt)
{
	if (!isPause) {
		board.update(playerBlack.getChessList(), playerRed.getChessList());
		whoWin(playerBlack, playerRed);
		hint();

		if (currentStatus == Status::intitialize) {
			// first uptade, set sprite position.
			for (const auto& tmpChess : playerRed.getChessList()) {
				tmpChess->update(*window);
				tmpChess->setSpritePosition(board.BoardToWindowPosition(tmpChess->getBoardPosition()));
			}
			for (const auto& tmpChess : playerBlack.getChessList()) {
				tmpChess->update(*window);
				tmpChess->setSpritePosition(board.BoardToWindowPosition(tmpChess->getBoardPosition()));
			}
			currentStatus = Status::WaitBlackPressed;
		}
		else if (currentStatus == Status::WaitBlackPressed) {
			// update chess
			sysInfo.setArrow(true);
			for (const auto& tmpChess : playerRed.getChessList()) {
				tmpChess->setSpritePosition(board.BoardToWindowPosition(tmpChess->getBoardPosition()));
			}
			for (const auto& playerChess : playerBlack.getChessList()) {

				playerChess->update(*window);

				// if button press
				if (playerChess->isPressed() && playerChess->getActive()) {
					std::vector<sf::Vector2f> tmpPosList = playerChess->findPath(board);
					//std::cout << tmpPosList.size() << "\n";
					Factory chessFac;
					// new selected chessList
					selectedChess = new SelectedChess{ playerChess, std::vector<Chess*>() };
					Chess* tmpChess;
					for (size_t idx = 0; idx < tmpPosList.size(); idx++) {
						int tmpId = 0;
						if (validMove(*selectedChess->selectChess, tmpPosList[idx]))
						{
							tmpChess = chessFac.getChess(playerChess->getCharacters(), Team::Black, -1);
							tmpChess->setBoardPosition(tmpPosList[idx]);
							tmpChess->setSpritePosition(board.BoardToWindowPosition(tmpChess->getBoardPosition()));
							selectedChess->validSpot.push_back(tmpChess);
						}
					}
					//std::cout << "WaitBlackPathPressed\n";
					currentStatus = Status::WaitBlackPathPressed;
				}
			}

		}
		else if (currentStatus == Status::WaitBlackPathPressed) {
			for (const auto& validPathChess : selectedChess->validSpot) {
				validPathChess->update(*window);
				if (validPathChess->isPressed() && validPathChess->getActive()) {
					selectedChess->selectChess->move(validPathChess, board);
					selectedChess->selectChess->setSpritePosition(board.BoardToWindowPosition(selectedChess->selectChess->getBoardPosition()));
					delete selectedChess;
					selectedChess = nullptr;
					//std::cout << "WaitRedPressed\n";
					currentStatus = Status::WaitRedPressed;
					hintHasShowed = false;
					return true;
				}
			}
			// there is no valid path, go back to WaitPressed status
			if (isPressed || selectedChess->validSpot.size() == 0) {
				delete selectedChess;
				selectedChess = nullptr;
				//std::cout << "WaitBlackPressed\n";
				currentStatus = Status::WaitBlackPressed;
				return true;
			}
		}
		else if (currentStatus == Status::WaitRedPressed) {
			sysInfo.setArrow(false);
			// update chess
			for (const auto& tmpChess : playerBlack.getChessList()) {
				tmpChess->setSpritePosition(board.BoardToWindowPosition(tmpChess->getBoardPosition()));
			}
			for (const auto& playerChess : playerRed.getChessList()) {
				playerChess->update(*window);

				// if button press
				if (playerChess->isPressed() && playerChess->getActive()) {
					std::vector<sf::Vector2f> tmpPosList = playerChess->findPath(board);
					//std::cout << tmpPosList.size() << "\n";
					Factory chessFac;
					// new selected chessList
					selectedChess = new SelectedChess{ playerChess, std::vector<Chess*>() };
					Chess* tmpChess;
					for (size_t idx = 0; idx < tmpPosList.size(); idx++) {
						int tmpId = 0;
						if (validMove(*selectedChess->selectChess, tmpPosList[idx]))
						{
							tmpChess = chessFac.getChess(playerChess->getCharacters(), Team::Red, -1);
							tmpChess->setBoardPosition(tmpPosList[idx]);
							tmpChess->setSpritePosition(board.BoardToWindowPosition(tmpChess->getBoardPosition()));
							selectedChess->validSpot.push_back(tmpChess);
						}
					}
					//std::cout << "WaitRedPathPressed\n";
					currentStatus = Status::WaitRedPathPressed;
				}
			}

		}
		else if (currentStatus == Status::WaitRedPathPressed) {
			for (const auto& validPathChess : selectedChess->validSpot) {
				validPathChess->update(*window);
				if (validPathChess->isPressed() && validPathChess->getActive()) {
					selectedChess->selectChess->move(validPathChess, board);
					selectedChess->selectChess->setSpritePosition(board.BoardToWindowPosition(selectedChess->selectChess->getBoardPosition()));
					delete selectedChess;
					selectedChess = nullptr;
					//std::cout << "WaitRedPressed\n";
					currentStatus = Status::WaitBlackPressed;
					hintHasShowed = false;
					return true;
				}
			}
			// there is no valid path, go back to WaitPressed status
			if (isPressed || selectedChess->validSpot.size() == 0) {
				delete selectedChess;
				selectedChess = nullptr;
				//std::cout << "WaitBlackPressed\n";
				currentStatus = Status::WaitRedPressed;
				return true;
			}
		}
		else if (currentStatus == Status::end) {
			
		}
	}

	if (isPause && !inStack(States::ID::Pause)) {
		isPause = false;
	}
	else if (!isPause && inStack(States::ID::Pause)) {
		requestStackPop();
	}

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	sf::Clock clock;
	if(event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Escape) {
			clock.restart();
			isPause = !isPause;
			requestStackPush(States::ID::Pause);
		}
	}

	for (const auto& tmpChess : playerBlack.getChessList()) {
		tmpChess->handleEvent(*window);
	}
	for (const auto& tmpChess : playerRed.getChessList()) {
		tmpChess->handleEvent(*window);
	}
	if (selectedChess != nullptr && selectedChess->validSpot.size()) {
		for (const auto& validPathChess : selectedChess->validSpot) {
			if(validPathChess != nullptr)
				validPathChess->handleEvent(*window);
		}
	}
	/*sf::Clock pressedClock;*/
	isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	return true;
}

GameState::SelectedChess::~SelectedChess()
{
	for (auto& chess : validSpot) {
		free(chess);
		chess = nullptr;
	}
	validSpot.clear();
}
