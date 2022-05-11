#include "GameManager.h"

GameManager::GameManager()
	: playerBlack(Team::Black), playerRed(Team::Red), board(), chessManager()
{
	this->initVar();
	this->initWindow();
	sf::Vector2f tmpPos(window->getSize().x / 20, (window->getSize().y - board.getBoardSize().y) / 2);
	this->board.setSpritePosition(tmpPos);
	window->setFramerateLimit(144);
	this->status = Status::WaitBlackPressed;
	board.update(playerBlack, playerRed);
	blackRound = true;
	redRound = true;

	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}
}

GameManager::~GameManager()
{
	delete window;
}

void GameManager::run()
{

	while (this->window->isOpen())
	{

		this->processEvent();
		this->update();
		this->render();
	}
}

void GameManager::whoWin(const Player& playerBlack, const Player& playerRed)
{
	if (!playerBlack.getChessList()[0]->getActive())
	{
		std::cout << "RedPlayer Win\n";
		exit(0);
	}
	if (!playerRed.getChessList()[0]->getActive())
	{
		std::cout << "BlackPlayer Win\n";
		exit(0);
	}
}

void GameManager::initWindow()
{
	this->videoMode.width = WINDOW_RESOLUTION_WIDTH;
	this->videoMode.height = WINDOW_RESOLUTION_HEIGHT;
	this->window = new sf::RenderWindow(videoMode, "Game1", sf::Style::Close | sf::Style::Titlebar);

}

void GameManager::checkmate()
{

	bool find = false;
	if (blackRound)
	{
		for (auto& tmpChess : playerBlack.getChessList())
		{
			std::vector<sf::Vector2f> tmpPath;
			if (tmpChess->getActive())
			{
				tmpPath = tmpChess->findPath(board);
				for (auto& tmpPos : tmpPath)
				{
					//std::cout <<tmpChess->getId()<< "->" << tmpPos.x << " " << tmpPos.y << "\t" << opponent.getChessList()[0]->getPosition().x << " " << opponent.getChessList()[0]->getPosition().y << std::endl;
					if (tmpPos == playerRed.getChessList()[0]->getPosition())
					{
						find = true;
						break;
					}
				}

			}
			if (find)
				break;

		}
		if (find)
		{
			std::cout << "Black Checkmate!!!!!!!!!!!!!!!!!!!!!\n";
		}
	}
	else if (redRound)
	{
		for (auto& tmpChess : playerRed.getChessList())
		{
			std::vector<sf::Vector2f> tmpPath;
			if (tmpChess->getActive())
			{
				tmpPath = tmpChess->findPath(board);
				for (auto& tmpPos : tmpPath)
				{
					//std::cout <<tmpChess->getId()<< "->" << tmpPos.x << " " << tmpPos.y << "\t" << opponent.getChessList()[0]->getPosition().x << " " << opponent.getChessList()[0]->getPosition().y << std::endl;
					if (tmpPos == playerBlack.getChessList()[0]->getPosition())
					{
						find = true;
						break;
					}
				}

			}
			if (find)
				break;

		}
		if (find)
		{
			std::cout << "Red Checkmate!!!!!!!!!!!!!!!!!!!!!\n";
		}
	}

}

void GameManager::initVar()
{
	this->window = nullptr;
}

sf::Vector2f GameManager::BoardToWindowPosition(sf::Vector2f boardArrPosition)
{
	sf::Vector2f windowPosition;
	int x = (board.getBoardSize().x / 8) * boardArrPosition.x + board.getSprite().getPosition().x;
	int y = (board.getBoardSize().y / 9) * boardArrPosition.y + board.getSprite().getPosition().y;
	windowPosition = sf::Vector2f(x, y);
	return windowPosition;
}

sf::Vector2f GameManager::WindowToBoardPosition(sf::Vector2f windowPosition)
{
	sf::Vector2f boardPosition;
	int x = (windowPosition.x - (board.getSprite().getPosition().x - board.getBoardSize().x / 16)) / (board.getBoardSize().x / 8);
	int y = (windowPosition.y - (board.getSprite().getPosition().y - board.getBoardSize().x / 18)) / (board.getBoardSize().y / 9);
	boardPosition.x = x;
	boardPosition.y = y;
	//std::cout << boardPosition.x << " " << boardPosition.y << "\n";
	return boardPosition;
}

void GameManager::processEvent()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		}
	}
	if (status == Status::WaitBlackPressed || status == Status::WaitBlackPathPressed)
		playerBlack.handleRealtimeInput(chessManager, status, board);

	if (status == Status::WaitRedPressed || status == Status::WaitRedPathPressed)
		playerRed.handleRealtimeInput(chessManager, status, board);
}

void GameManager::update()
{
	//showStatus();
	whoWin(playerBlack, playerRed);
	board.update(playerBlack, playerRed);
	for (auto chess : playerBlack.getChessList()) {
		if (chess->getActive()) {
			chess->resetIsPressed();
			chess->setSpritePosition(BoardToWindowPosition(chess->getPosition()));
			if (status == Status::WaitBlackPressed || status == Status::WaitBlackPathPressed)
				chess->update(*window, ev);
		}
	}
	for (auto chess : playerRed.getChessList()) {
		if (chess->getActive()) {
			chess->resetIsPressed();
			chess->setSpritePosition(BoardToWindowPosition(chess->getPosition()));
			if (status == Status::WaitRedPressed || status == Status::WaitRedPathPressed)
				chess->update(*window, ev);
		}
	}
	for (auto& tmpChess : tmpChessObj) {
		if (tmpChess->getActive()) {
			tmpChess->resetIsPressed();
			tmpChess->setSpritePosition(BoardToWindowPosition(tmpChess->getPosition()));
			tmpChess->update(*window, ev);
		}
	}
	switch (status)
	{
	case Status::WaitBlackPressed:
		checkmate();
		while (chessManager.getCommandNum()) {
			std::vector<sf::Vector2f> tmpValidPath = chessManager.doCommand(*selectChess);
			this->selectChess = chessManager.getSelectedChess();
			playerBlack.setSelectChess(this->selectChess);
			// if valid path number >= 1
			if (tmpValidPath.size()) {
				validPath = std::make_unique<std::vector<sf::Vector2f>>(tmpValidPath);

				Factory tmpChessfac;
				for (const auto& path : *(validPath.get())) {
					// create tmp chess
					if (selectChess != nullptr && selectChess->getActive())
					{
						Chess* tmpChess = (tmpChessfac.getChess(selectChess->getCharacters(), selectChess->getTeam(), -1));
						tmpChess->setPosition(path);
						tmpChessObj.push_back(tmpChess);
					}
				}
				playerBlack.setValidMoveChessList(tmpChessObj);
				status = Status::WaitBlackPathPressed;
			}
		}
		break;
	case Status::WaitBlackPathPressed:
		while (chessManager.getCommandNum()) {
			std::vector<sf::Vector2f> tmpValidPath = chessManager.doCommand(*(this->selectChess));
			// if valid path number >= 1 -> succcess move
			if (tmpValidPath.size()) {
				tmpChessObj.clear();
				this->selectChess = nullptr;
				playerBlack.setSelectChess(nullptr);
				status = Status::WaitRedPressed;
				blackRound = false;
				redRound = true;
				break;
			}
			else {
				tmpChessObj.clear();
				this->selectChess = nullptr;
				playerBlack.setSelectChess(nullptr);
				status = Status::WaitBlackPressed;
				break;
			}
		}
		break;
	case Status::WaitRedPressed:
		checkmate();
		while (chessManager.getCommandNum()) {
			std::vector<sf::Vector2f> tmpValidPath = chessManager.doCommand(*selectChess);
			this->selectChess = chessManager.getSelectedChess();
			playerRed.setSelectChess(this->selectChess);
			// if valid path number >= 1
			if (tmpValidPath.size()) {
				validPath = std::make_unique<std::vector<sf::Vector2f>>(tmpValidPath);

				Factory tmpChessfac;
				for (const auto& path : *(validPath.get())) {
					// create tmp chess
					if (selectChess != nullptr && selectChess->getActive())
					{
						Chess* tmpChess = (tmpChessfac.getChess(selectChess->getCharacters(), selectChess->getTeam(), -1));
						tmpChess->setPosition(path);
						tmpChessObj.push_back(tmpChess);
					}
				}
				playerRed.setValidMoveChessList(tmpChessObj);
				status = Status::WaitRedPathPressed;
			}
		}
		break;
	case Status::WaitRedPathPressed:
		while (chessManager.getCommandNum()) {
			std::vector<sf::Vector2f> tmpValidPath = chessManager.doCommand(*(this->selectChess));
			// if valid path number >= 1 -> succcess move
			if (tmpValidPath.size()) {
				tmpChessObj.clear();
				this->selectChess = nullptr;
				playerRed.setSelectChess(nullptr);
				status = Status::WaitBlackPressed;
				blackRound = true;
				redRound = false;
				break;
			}
			else {
				tmpChessObj.clear();
				this->selectChess = nullptr;
				playerRed.setSelectChess(nullptr);
				status = Status::WaitRedPressed;
				break;
			}
		}
		break;
	default:
		break;

	}

	//switch (status)
	//{
	//case Status::WaitBlackPressed:
	//{
	//	
	//	for (auto& redChess : playerRed.getChessList())
	//	{
	//		if (redChess->getActive())
	//			redChess->setSpritePosition(BoardToWindowPosition(redChess->getPosition()));
	//	}
	//	for (auto& blackChess : playerBlack.getChessList())
	//	{
	//		if (!blackChess->getActive())
	//			continue;
	//		
	//		blackChess->setSpritePosition(BoardToWindowPosition(blackChess->getPosition()));

	//		blackChess->update(*(this->window), ev);
	//		if (blackChess->getIsPressed())
	//		{
	//			selectChess = blackChess;
	//			status = Status::WaitBlackPathPressed;
	//		}
	//	}
	//	break;
	//}
	//case Status::BlackFindPath:
	//{
	//	
	//	validPath = std::make_unique<std::vector<sf::Vector2f>>(selectChess->findPath(this->board));
	//	inputClock.restart();
	//	
	//	if (!validPath.get()->size())
	//	{
	//		status = Status::WaitBlackPressed;
	//		break;
	//	}
	//	else
	//	{
	//		
	//		
	//		status = Status::WaitBlackPathPressed;
	//		break;
	//	}
	//	break;
	//}
	//case Status::WaitBlackPathPressed:
	//{
	//	bool isPressed = false, validPressed = false;
	//	
	//	for (auto& tmpChess : tmpChessObj) {
	//		tmpChess->setSpritePosition(BoardToWindowPosition(tmpChess->getPosition()));
	//		tmpChess->update(*(this->window), ev);
	//		if (ev.type == sf::Event::MouseButtonPressed)
	//		{
	//			isPressed = true;
	//			if (tmpChess->getIsPressed()) 
	//			{
	//				validPressed = true;
	//				selectPathChess = tmpChess;
	//				break;
	//			}
	//		}
	//		tmpChess->setSpritePosition(BoardToWindowPosition(tmpChess->getPosition()));
	//	}
	//	if (isPressed && validPressed)
	//	{
	//		status = Status::BlackMove;
	//		validPath.release();
	//		break;
	//	}
	//	else if(isPressed && !validPressed)
	//	{
	//		status = Status::WaitBlackPressed;
	//		for (auto& tmpChess : tmpChessObj)
	//		{
	//			delete tmpChess;
	//		}
	//		tmpChessObj.clear();
	//		validPath.release();
	//		break;
	//	}
	//	else
	//	{ }
	//	break;
	//}
	//case Status::BlackMove:
	//{
	//	if (inputClock.getElapsedTime().asMilliseconds() > DELAY_TIME)
	//	{
	//		bool validPressed = false;
	//		inputClock.restart();
	//		for (auto& tmpChess : tmpChessObj)
	//		{
	//			if (selectPathChess == tmpChess)
	//				validPressed = true;
	//		}

	//		if (validPressed == false)
	//		{
	//			tmpChessObj.clear();
	//			status = Status::WaitBlackPressed;
	//			break;
	//		}
	//		else
	//		{
	//			for (auto& tmpChess : tmpChessObj)
	//			{
	//				if (tmpChess->getIsPressed())
	//					selectChess->move(tmpChess, board);
	//				delete tmpChess;
	//			}
	//			tmpChessObj.clear();
	//			status = Status::WaitRedPressed;
	//			validPath.release();
	//			break;
	//		}
	//	}
	//	break;
	//}
	//case Status::WaitRedPressed:
	//{
	//	for (auto& blackChess : playerBlack.getChessList())
	//	{
	//		if(blackChess->getActive())
	//			blackChess->setSpritePosition(BoardToWindowPosition(blackChess->getPosition()));
	//	}
	//	for (auto& redChess : playerRed.getChessList())
	//	{
	//		if (!redChess->getActive())
	//			continue;
	//		if(redChess->getActive())
	//			redChess->setSpritePosition(BoardToWindowPosition(redChess->getPosition()));
	//		redChess->update(*(this->window), ev);
	//		if (redChess->getIsPressed())
	//		{
	//			selectChess = redChess;
	//			status = Status::RedFindPath;
	//		}
	//	}
	//	break;
	//}
	//case Status::RedFindPath:
	//{
	//	validPath = std::make_unique<std::vector<sf::Vector2f>>(selectChess->findPath(this->board));
	//	inputClock.restart();
	//	if (!validPath.get()->size())
	//	{
	//		status = Status::WaitRedPressed;
	//		break;
	//	}
	//	else
	//	{
	//		Factory tmpChessfac;
	//		for (const auto& path : *(validPath.get())) {
	//			// create tmp chess
	//			if (selectChess != nullptr && selectChess->getActive())
	//			{
	//				Chess* tmpChess = (tmpChessfac.getChess(selectChess->getCharacters(), selectChess->getTeam(), -1));
	//				tmpChess->setPosition(path);
	//				tmpChessObj.push_back(tmpChess);
	//			}
	//			else
	//			{
	//				status = Status::WaitRedPressed;
	//				validPath.release();
	//				break;
	//			}
	//		}
	//		status = Status::WaitRedPathPressed;
	//		break;
	//	}
	//	break;
	//}
	//case Status::WaitRedPathPressed:
	//{
	//	bool isPressed = false, validPressed = false;

	//	for (auto& tmpChess : tmpChessObj) {
	//		tmpChess->setSpritePosition(BoardToWindowPosition(tmpChess->getPosition()));
	//		tmpChess->update(*(this->window), ev);
	//		if (ev.type == sf::Event::MouseButtonPressed)
	//		{
	//			isPressed = true;
	//			if (tmpChess->getIsPressed())
	//			{
	//				validPressed = true;
	//				selectPathChess = tmpChess;
	//				break;
	//			}
	//		}
	//		tmpChess->setSpritePosition(BoardToWindowPosition(tmpChess->getPosition()));
	//	}
	//	if (isPressed && validPressed)
	//	{
	//		status = Status::RedMove;
	//		validPath.release();
	//		break;
	//	}
	//	else if (isPressed && !validPressed)
	//	{
	//		status = Status::WaitRedPressed;
	//		for (auto& tmpChess : tmpChessObj)
	//		{
	//			delete tmpChess;
	//		}
	//		tmpChessObj.clear();
	//		validPath.release();
	//		break;
	//	}
	//	else
	//	{
	//	}
	//	break;
	//}
	//case Status::RedMove:
	//{
	//	if (inputClock.getElapsedTime().asMilliseconds() > DELAY_TIME)
	//	{
	//		bool validPressed = false;
	//		inputClock.restart();
	//		for (auto& tmpChess : tmpChessObj)
	//		{
	//			if (selectPathChess == tmpChess)
	//				validPressed = true;
	//		}

	//		if (validPressed == false)
	//		{
	//			tmpChessObj.clear();
	//			status = Status::WaitRedPressed;
	//			break;
	//		}
	//		else
	//		{
	//			for (auto& tmpChess : tmpChessObj)
	//			{
	//				if (tmpChess->getIsPressed())
	//					selectChess->move(tmpChess, board);
	//				delete tmpChess;
	//			}
	//			tmpChessObj.clear();
	//			status = Status::WaitBlackPressed;
	//			validPath.release();
	//			break;
	//		}
	//	}
	//	break;
	//}
	//}

}
void GameManager::render()
{

	window->clear(sf::Color::White);

	/* Drawing */
	window->draw(board.getSprite());
	for (auto& tmpChess : playerBlack.getChessList()) {
		if (tmpChess->getActive())
			window->draw(*tmpChess);
	}
	for (auto& tmpChess : playerRed.getChessList()) {
		if (tmpChess->getActive())
			window->draw(*tmpChess);
	}

	for (auto& tmpChess : tmpChessObj) {
		window->draw(*tmpChess);
	}


	window->display();
}

void GameManager::showStatus()
{
	if (status == Status::WaitBlackPressed)
		std::cout << "WaitBlackPressed";
	else if (status == Status::WaitBlackPathPressed)
		std::cout << "WaitBlackPathPressed";
	else if (status == Status::WaitRedPressed)
		std::cout << "WaitRedPressed";
	else if (status == Status::WaitRedPathPressed)
		std::cout << "WaitRedPathPressed";
	std::cout << "\n";
}
