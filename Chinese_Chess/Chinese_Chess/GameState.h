#pragma once
#include "GameHeader.h"
#include "Player.h"
#include "Board.h"
#include "State.h"
#include "SystemInformation.h"
class GameState : public State
{
private:
    sf::RenderWindow* window;
    /* Game Status */
    enum class Status
    {
        // 初始化階段
        intitialize,

        WaitBlackPressed,
        WaitBlackPathPressed,

        WaitRedPressed,
        WaitRedPathPressed,

        // 遊戲結束
        end,
    };
    typedef struct SelectedChess {
        Chess* selectChess;
        std::vector<Chess*> validSpot;
        ~SelectedChess();
    };

public:
    GameState(StateStack& _stack, StateContext _context);
    Status currentStatus;
    Player playerBlack;
    Player playerRed;
    Board board;
    SelectedChess* selectedChess;
    SystemInformation sysInfo;
    bool isPressed;
    bool hintHasShowed;
    bool isPause;

private:
    virtual void draw() override;
    virtual bool update(sf::Time dt) override;
    virtual bool handleEvent(const sf::Event& event) override;
    void whoWin(const Player& playerBlack, const Player& playerRed);

    void hint();
    int checkmate();
    bool validMove(Chess& _selectedChess, sf::Vector2f goalPos);
};


//#include "Player.h"
//#include "Board.h"
//class GameState : public State
//{
//private:
//	sf::RenderWindow* window;
//	sf::Event ev;
//	sf::CircleShape cir;
//
//private:
//	Player playerBlack;
//	Player playerRed;
//	Board board;
//	Status status;
//
//	ChessManager chessManager;
//	std::unique_ptr<std::vector<sf::Vector2f>> validPath;
//	std::vector<Chess*> tmpChessObj;
//	Chess* selectChess;
//	Chess* selectPathChess;
//	sf::Clock inputClock;
//	sf::Font font;
//	bool isPause;
//
//	bool checkStalemate;
//	bool hintHasShowed;
//public:
//	GameState(StateStack& stack, StateContext context);
//	~GameState();
//	void run();
//
//private:
//	void whoWin(const Player& playerBlack, const Player& playerRed);
//	int checkmate();
//
//	bool validMove(Chess& _selectedChess, sf::Vector2f _goalPos);
//
//	sf::Vector2f BoardToWindowPosition(sf::Vector2f boardPosition);
//	sf::Vector2f WindowToBoardPosition(sf::Vector2f windowPosition);
//
//	virtual bool handleEvent(const sf::Event& event) override;
//	virtual bool update(sf::Time dt) override;
//	virtual void draw() override;
//
//	void showStatus();
//};
