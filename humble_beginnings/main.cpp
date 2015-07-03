

#include <iostream>
#include <SDL.h>
#include <Stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define FRAMES_PER_SECOND 60
#define MS_PER_FRAME 17

int Screen_height(648);
int Screen_width(1152);

bool init();
bool loadMedia();

void close();

SDL_Window* gWindow(NULL);
SDL_Renderer *gRenderer(NULL);

//==========MovingParts class start========== [basically everything]
class MovingParts
{
public:
	MovingParts();
	MovingParts(float P1xx, float P1yy, float P2xx, float P2yy, float Bxx, float Byy);
	~MovingParts();

	void PaddleControl();
	void BallControl();
	void ScoreDisp();
	void render();

	// for player one paddle
	float P1x;
	float P1y;
	float P1yVel;

	// for player two paddle
	float P2x;
	float P2y;
	float P2yVel;

	// for ball
	float Bx;
	float By;
	float ByVel;
	float BxVel;

	// for score
	int RoundStart;
	int RoundCount;
	int P1Score;
	int P2Score;
	int LastWin;
	bool NewRound;
	bool P1TensDigit;
	bool P1OnesSegmentOne;
	bool P1OnesSegmentTwo;
	bool P1OnesSegmentThree;
	bool P1OnesSegmentFour;
	bool P1OnesSegmentFive;
	bool P1OnesSegmentSix;
	bool P1OnesSegmentSeven;
	bool P1OnesSegmentEight;
	bool P1OnesSegmentNine;
	bool P1OnesSegmentTen;
	bool P1OnesSegmentEleven;
	bool P1OnesSegmentTwelve;
	bool P1OnesSegmentThirteen;
	bool P2TensDigit;
	bool P2OnesSegmentOne;
	bool P2OnesSegmentTwo;
	bool P2OnesSegmentThree;
	bool P2OnesSegmentFour;
	bool P2OnesSegmentFive;
	bool P2OnesSegmentSix;
	bool P2OnesSegmentSeven;
	bool P2OnesSegmentEight;
	bool P2OnesSegmentNine;
	bool P2OnesSegmentTen;
	bool P2OnesSegmentEleven;
	bool P2OnesSegmentTwelve;
	bool P2OnesSegmentThirteen;
};

MovingParts::MovingParts()
{
	P1x = 140;
	P2x = Screen_width - 160;
	P1y = P2y = Screen_height / 2 - 80;
	P1yVel = P2yVel = 0;
	Bx = Screen_width / 2 - 10;
	By = Screen_height / 2 - 10;
	ByVel = BxVel = 0;
	RoundCount = 0;
	P1Score = 0;
	P2Score = 0;
	LastWin = 0;
	P1TensDigit = 0;
	P1OnesSegmentOne = 0;
	P1OnesSegmentTwo = 0;
	P1OnesSegmentThree = 0;
	P1OnesSegmentFour = 0;
	P1OnesSegmentFive = 0;
	P1OnesSegmentSix = 0;
	P1OnesSegmentSeven = 0;
	P1OnesSegmentEight = 0;
	P1OnesSegmentNine = 0;
	P1OnesSegmentTen = 0;
	P1OnesSegmentEleven = 0;
	P1OnesSegmentTwelve = 0;
	P1OnesSegmentThirteen = 0;
	P2TensDigit = 0;
	P2OnesSegmentOne = 0;
	P2OnesSegmentTwo = 0;
	P2OnesSegmentThree = 0;
	P2OnesSegmentFour = 0;
	P2OnesSegmentFive = 0;
	P2OnesSegmentSix = 0;
	P2OnesSegmentSeven = 0;
	P2OnesSegmentEight = 0;
	P2OnesSegmentNine = 0;
	P2OnesSegmentTen = 0;
	P2OnesSegmentEleven = 0;
	P2OnesSegmentTwelve = 0;
	P2OnesSegmentThirteen = 0;
}

MovingParts::~MovingParts()
{
	//Don't understand why a destructor is needed
}

void MovingParts::PaddleControl()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	// control for player 1
	if (currentKeyStates[SDL_SCANCODE_W] && P1y >= 0)
	{
		P1yVel = -7;
	}
	else if (currentKeyStates[SDL_SCANCODE_S] && P1y <= Screen_height - 160)
	{
		P1yVel = 7;
	}
	else
	{
		P1yVel = 0;
	}
	P1y += P1yVel;

	//control for player 2
	if (currentKeyStates[SDL_SCANCODE_UP] && P2y >= 0)
	{
		P2yVel = -7;
	}
	else if (currentKeyStates[SDL_SCANCODE_DOWN] && P2y <= Screen_height - 160)
	{
		P2yVel = 7;
	}
	else
	{
		P2yVel = 0;
	}
	P2y += P2yVel;
}

void MovingParts::BallControl()
{
	// Starting Launch
	if (RoundCount == 0)
	{
		const Uint8* currentKeyState = SDL_GetKeyboardState(NULL);
		if (currentKeyState[SDL_SCANCODE_SPACE])
		{
			RoundCount = 1;
			int StartShot;
			srand(time(NULL));
			StartShot = rand() % 100;
			if (StartShot >= 50)
			{
				BxVel = -5;
			}
			else if (StartShot < 50)
			{
				BxVel = 5;
			}
		}
	}
		
	// Bouncing off walls
	if (By <= 0 || By >= Screen_height - 20)
	{
		ByVel = (ByVel * -1);
	}

	//Bouncing off Paddles
	if (Bx <= 160)
	{
		if (By <= P1y + 160 && By >= P1y - 20)
		{
			BxVel = (BxVel * -1);
			ByVel = (ByVel + P1yVel);
		}
		else
		{
			LastWin = 2;
			P2Score++;
			Bx = Screen_width / 2 - 10;
			By = Screen_height / 2 - 10;
			BxVel = -5;
			ByVel = 0;
		}
	}
	if (Bx >= Screen_width - 180)
	{
		if (By <= P2y + 160 && By >= P2y - 20)
		{
			BxVel = (BxVel * -1);
			ByVel = (ByVel + P2yVel);
		}
		else
		{
			LastWin = 1;
			P1Score++;
			Bx = Screen_width / 2 - 10;
			By = Screen_height / 2 - 10;
			BxVel = 5;
			ByVel = 0;
		}
	}

	Bx += BxVel;
	By += ByVel;
}

void MovingParts::ScoreDisp()
{
	//Player One
	if (P1Score % 10 == 0) 
	{
		P1OnesSegmentOne = 1;
		P1OnesSegmentTwo = 1;
		P1OnesSegmentThree = 1;
		P1OnesSegmentFour = 1;
		P1OnesSegmentFive = 1;
		P1OnesSegmentSix = 1;
		P1OnesSegmentSeven = 0;
		P1OnesSegmentEight = 1;
		P1OnesSegmentNine = 1;
		P1OnesSegmentTen = 1;
		P1OnesSegmentEleven = 1;
		P1OnesSegmentTwelve = 1;
		P1OnesSegmentThirteen = 1;
	}
	else if (P1Score % 10 == 1)
	{
		P1OnesSegmentOne = 1;
		P1OnesSegmentTwo = 0;
		P1OnesSegmentThree = 0;
		P1OnesSegmentFour = 1;
		P1OnesSegmentFive = 0;
		P1OnesSegmentSix = 1;
		P1OnesSegmentSeven = 0;
		P1OnesSegmentEight = 0;
		P1OnesSegmentNine = 1;
		P1OnesSegmentTen = 0;
		P1OnesSegmentEleven = 1;
		P1OnesSegmentTwelve = 0;
		P1OnesSegmentThirteen = 0;
	}
	else if (P1Score % 10 == 2)
	{
		P1OnesSegmentOne = 1;
		P1OnesSegmentTwo = 1;
		P1OnesSegmentThree = 1;
		P1OnesSegmentFour = 0;
		P1OnesSegmentFive = 1;
		P1OnesSegmentSix = 1;
		P1OnesSegmentSeven = 1;
		P1OnesSegmentEight = 1;
		P1OnesSegmentNine = 1;
		P1OnesSegmentTen = 0;
		P1OnesSegmentEleven = 1;
		P1OnesSegmentTwelve = 1;
		P1OnesSegmentThirteen = 1;
	}
	else if (P1Score % 10 == 3)
	{
		P1OnesSegmentOne = 1;
		P1OnesSegmentTwo = 1;
		P1OnesSegmentThree = 1;
		P1OnesSegmentFour = 0;
		P1OnesSegmentFive = 1;
		P1OnesSegmentSix = 1;
		P1OnesSegmentSeven = 1;
		P1OnesSegmentEight = 1;
		P1OnesSegmentNine = 0;
		P1OnesSegmentTen = 1;
		P1OnesSegmentEleven = 1;
		P1OnesSegmentTwelve = 1;
		P1OnesSegmentThirteen = 1;
	}
	else if (P1Score % 10 == 4)
	{
		P1OnesSegmentOne = 1;
		P1OnesSegmentTwo = 0;
		P1OnesSegmentThree = 1;
		P1OnesSegmentFour = 1;
		P1OnesSegmentFive = 1;
		P1OnesSegmentSix = 1;
		P1OnesSegmentSeven = 1;
		P1OnesSegmentEight = 1;
		P1OnesSegmentNine = 0;
		P1OnesSegmentTen = 1;
		P1OnesSegmentEleven = 0;
		P1OnesSegmentTwelve = 0;
		P1OnesSegmentThirteen = 1;
	}
	else if (P1Score % 10 == 5)
	{
		P1OnesSegmentOne = 1;
		P1OnesSegmentTwo = 1;
		P1OnesSegmentThree = 1;
		P1OnesSegmentFour = 1;
		P1OnesSegmentFive = 0;
		P1OnesSegmentSix = 1;
		P1OnesSegmentSeven = 1;
		P1OnesSegmentEight = 1;
		P1OnesSegmentNine = 0;
		P1OnesSegmentTen = 1;
		P1OnesSegmentEleven = 1;
		P1OnesSegmentTwelve = 1;
		P1OnesSegmentThirteen = 1;
	}
	else if (P1Score % 10  == 6)
	{
		P1OnesSegmentOne = 1;
		P1OnesSegmentTwo = 1;
		P1OnesSegmentThree = 0;
		P1OnesSegmentFour = 1;
		P1OnesSegmentFive = 0;
		P1OnesSegmentSix = 1;
		P1OnesSegmentSeven = 1;
		P1OnesSegmentEight = 1;
		P1OnesSegmentNine = 1;
		P1OnesSegmentTen = 1;
		P1OnesSegmentEleven = 1;
		P1OnesSegmentTwelve = 1;
		P1OnesSegmentThirteen = 1;
	}
	else if (P1Score % 10 == 7)
	{
		P1OnesSegmentOne = 1;
		P1OnesSegmentTwo = 1;
		P1OnesSegmentThree = 1;
		P1OnesSegmentFour = 1;
		P1OnesSegmentFive = 1;
		P1OnesSegmentSix = 0;
		P1OnesSegmentSeven = 0;
		P1OnesSegmentEight = 1;
		P1OnesSegmentNine = 0;
		P1OnesSegmentTen = 1;
		P1OnesSegmentEleven = 0;
		P1OnesSegmentTwelve = 0;
		P1OnesSegmentThirteen = 1;
	}
	else if (P1Score % 10 == 8)
	{
		P1OnesSegmentOne = 1;
		P1OnesSegmentTwo = 1;
		P1OnesSegmentThree = 1;
		P1OnesSegmentFour = 1;
		P1OnesSegmentFive = 1;
		P1OnesSegmentSix = 1;
		P1OnesSegmentSeven = 1;
		P1OnesSegmentEight = 1;
		P1OnesSegmentNine = 1;
		P1OnesSegmentTen = 1;
		P1OnesSegmentEleven = 1;
		P1OnesSegmentTwelve = 1;
		P1OnesSegmentThirteen = 1;
	}
	else if (P1Score % 10 == 9)
	{
		P1OnesSegmentOne = 1;
		P1OnesSegmentTwo = 1;
		P1OnesSegmentThree = 1;
		P1OnesSegmentFour = 1;
		P1OnesSegmentFive = 1;
		P1OnesSegmentSix = 1;
		P1OnesSegmentSeven = 1;
		P1OnesSegmentEight = 1;
		P1OnesSegmentNine = 0;
		P1OnesSegmentTen = 1;
		P1OnesSegmentEleven = 0;
		P1OnesSegmentTwelve = 0;
		P1OnesSegmentThirteen = 1;
	}

	//Player Two
	if (P2Score % 10 == 0)
	{
		P2OnesSegmentOne = 1;
		P2OnesSegmentTwo = 1;
		P2OnesSegmentThree = 1;
		P2OnesSegmentFour = 1;
		P2OnesSegmentFive = 1;
		P2OnesSegmentSix = 1;
		P2OnesSegmentSeven = 0;
		P2OnesSegmentEight = 1;
		P2OnesSegmentNine = 1;
		P2OnesSegmentTen = 1;
		P2OnesSegmentEleven = 1;
		P2OnesSegmentTwelve = 1;
		P2OnesSegmentThirteen = 1;
	}
	else if (P2Score % 10 == 1)
	{
		P2OnesSegmentOne = 1;
		P2OnesSegmentTwo = 0;
		P2OnesSegmentThree = 0;
		P2OnesSegmentFour = 1;
		P2OnesSegmentFive = 0;
		P2OnesSegmentSix = 1;
		P2OnesSegmentSeven = 0;
		P2OnesSegmentEight = 0;
		P2OnesSegmentNine = 1;
		P2OnesSegmentTen = 0;
		P2OnesSegmentEleven = 1;
		P2OnesSegmentTwelve = 0;
		P2OnesSegmentThirteen = 0;
	}
	else if (P2Score % 10 == 2)
	{
		P2OnesSegmentOne = 1;
		P2OnesSegmentTwo = 1;
		P2OnesSegmentThree = 1;
		P2OnesSegmentFour = 0;
		P2OnesSegmentFive = 1;
		P2OnesSegmentSix = 1;
		P2OnesSegmentSeven = 1;
		P2OnesSegmentEight = 1;
		P2OnesSegmentNine = 1;
		P2OnesSegmentTen = 0;
		P2OnesSegmentEleven = 1;
		P2OnesSegmentTwelve = 1;
		P2OnesSegmentThirteen = 1;
	}
	else if (P2Score % 10 == 3)
	{
		P2OnesSegmentOne = 1;
		P2OnesSegmentTwo = 1;
		P2OnesSegmentThree = 1;
		P2OnesSegmentFour = 0;
		P2OnesSegmentFive = 1;
		P2OnesSegmentSix = 1;
		P2OnesSegmentSeven = 1;
		P2OnesSegmentEight = 1;
		P2OnesSegmentNine = 0;
		P2OnesSegmentTen = 1;
		P2OnesSegmentEleven = 1;
		P2OnesSegmentTwelve = 1;
		P2OnesSegmentThirteen = 1;
	}
	else if (P2Score % 10 == 4)
	{
		P2OnesSegmentOne = 1;
		P2OnesSegmentTwo = 0;
		P2OnesSegmentThree = 1;
		P2OnesSegmentFour = 1;
		P2OnesSegmentFive = 1;
		P2OnesSegmentSix = 1;
		P2OnesSegmentSeven = 1;
		P2OnesSegmentEight = 1;
		P2OnesSegmentNine = 0;
		P2OnesSegmentTen = 1;
		P2OnesSegmentEleven = 0;
		P2OnesSegmentTwelve = 0;
		P2OnesSegmentThirteen = 1;
	}
	else if (P2Score % 10 == 5)
	{
		P2OnesSegmentOne = 1;
		P2OnesSegmentTwo = 1;
		P2OnesSegmentThree = 1;
		P2OnesSegmentFour = 1;
		P2OnesSegmentFive = 0;
		P2OnesSegmentSix = 1;
		P2OnesSegmentSeven = 1;
		P2OnesSegmentEight = 1;
		P2OnesSegmentNine = 0;
		P2OnesSegmentTen = 1;
		P2OnesSegmentEleven = 1;
		P2OnesSegmentTwelve = 1;
		P2OnesSegmentThirteen = 1;
	}
	else if (P2Score % 10 == 6)
	{
		P2OnesSegmentOne = 1;
		P2OnesSegmentTwo = 1;
		P2OnesSegmentThree = 0;
		P2OnesSegmentFour = 1;
		P2OnesSegmentFive = 0;
		P2OnesSegmentSix = 1;
		P2OnesSegmentSeven = 1;
		P2OnesSegmentEight = 1;
		P2OnesSegmentNine = 1;
		P2OnesSegmentTen = 1;
		P2OnesSegmentEleven = 1;
		P2OnesSegmentTwelve = 1;
		P2OnesSegmentThirteen = 1;
	}
	else if (P2Score % 10 == 7)
	{
		P2OnesSegmentOne = 1;
		P2OnesSegmentTwo = 1;
		P2OnesSegmentThree = 1;
		P2OnesSegmentFour = 1;
		P2OnesSegmentFive = 1;
		P2OnesSegmentSix = 0;
		P2OnesSegmentSeven = 0;
		P2OnesSegmentEight = 1;
		P2OnesSegmentNine = 0;
		P2OnesSegmentTen = 1;
		P2OnesSegmentEleven = 0;
		P2OnesSegmentTwelve = 0;
		P2OnesSegmentThirteen = 1;
	}
	else if (P2Score % 10 == 8)
	{
		P2OnesSegmentOne = 1;
		P2OnesSegmentTwo = 1;
		P2OnesSegmentThree = 1;
		P2OnesSegmentFour = 1;
		P2OnesSegmentFive = 1;
		P2OnesSegmentSix = 1;
		P2OnesSegmentSeven = 1;
		P2OnesSegmentEight = 1;
		P2OnesSegmentNine = 1;
		P2OnesSegmentTen = 1;
		P2OnesSegmentEleven = 1;
		P2OnesSegmentTwelve = 1;
		P2OnesSegmentThirteen = 1;
	}
	else if (P2Score % 10 == 9)
	{
		P2OnesSegmentOne = 1;
		P2OnesSegmentTwo = 1;
		P2OnesSegmentThree = 1;
		P2OnesSegmentFour = 1;
		P2OnesSegmentFive = 1;
		P2OnesSegmentSix = 1;
		P2OnesSegmentSeven = 1;
		P2OnesSegmentEight = 1;
		P2OnesSegmentNine = 0;
		P2OnesSegmentTen = 1;
		P2OnesSegmentEleven = 0;
		P2OnesSegmentTwelve = 0;
		P2OnesSegmentThirteen = 1;
	}

}
void MovingParts::render()
{
	//Paddles
	SDL_Rect fillRectPaddleOne = {(P1x), (int)round(P1y), 20, 160 };
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRectPaddleOne);

	SDL_Rect fillRectPaddleTwo = {(P2x), (int)round(P2y), 20, 160 };
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRectPaddleTwo);

	//Ball
	SDL_Rect fillRectBall = { (int)round(Bx), (int)round(By), 20, 20 };
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRectBall);

	//P1 Score
	if (P1Score >= 10)
	{
		SDL_Rect fillRectP1ScoreTens = { 20, 20, 20, 100 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP1ScoreTens);
	}	
	if (P1OnesSegmentOne == 1)
	{
		SDL_Rect fillRectP1ScoreSegOne = { 60, 20, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP1ScoreSegOne);
	}
	if (P1OnesSegmentTwo == 1)
	{
		SDL_Rect fillRectP1ScoreSegTwo = { 80, 20, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP1ScoreSegTwo);
	}
	if (P1OnesSegmentThree == 1)
	{
		SDL_Rect fillRectP1ScoreSegThree = { 100, 20, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP1ScoreSegThree);
	}
	if (P1OnesSegmentFour == 1)
	{
		SDL_Rect fillRectP1ScoreSegFour = { 60, 40, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP1ScoreSegFour);
	}
	if (P1OnesSegmentFive == 1)
	{
		SDL_Rect fillRectP1ScoreSegFive = { 100, 40, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP1ScoreSegFive);
	}
	if (P1OnesSegmentSix == 1)
	{
		SDL_Rect fillRectP1ScoreSegSix = { 60, 60, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP1ScoreSegSix);
	}
	if (P1OnesSegmentSeven == 1)
	{
		SDL_Rect fillRectP1ScoreSegSeven = { 80, 60, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP1ScoreSegSeven);
	}
	if (P1OnesSegmentEight == 1)
	{
		SDL_Rect fillRectP1ScoreSegEight = { 100, 60, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP1ScoreSegEight);
	}
	if (P1OnesSegmentNine == 1)
	{
		SDL_Rect fillRectP1ScoreSegNine = { 60, 80, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP1ScoreSegNine);
	}
	if (P1OnesSegmentTen == 1)
	{
		SDL_Rect fillRectP1ScoreSegTen = { 100, 80, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP1ScoreSegTen);
	}
	if (P1OnesSegmentEleven == 1)
	{
		SDL_Rect fillRectP1ScoreSegEleven = { 60, 100, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP1ScoreSegEleven);
	}
	if (P1OnesSegmentTwelve == 1)
	{
		SDL_Rect fillRectP1ScoreSegTwelve = { 80, 100, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP1ScoreSegTwelve);
	}
	if (P1OnesSegmentThirteen == 1)
	{
		SDL_Rect fillRectP1ScoreSegThirteen = { 100, 100, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP1ScoreSegThirteen);
	}

	//P2 Score
	if (P2Score >= 10)
	{
		SDL_Rect fillRectP2ScoreTens = { Screen_width - 120, 20, 20, 100 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP2ScoreTens);
	}
	if (P2OnesSegmentOne == 1)
	{
		SDL_Rect fillRectP2ScoreSegOne = { Screen_width - 80, 20, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP2ScoreSegOne);
	}
	if (P2OnesSegmentTwo == 1)
	{
		SDL_Rect fillRectP2ScoreSegTwo = { Screen_width - 60, 20, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP2ScoreSegTwo);
	}
	if (P2OnesSegmentThree == 1)
	{
		SDL_Rect fillRectP2ScoreSegThree = { Screen_width - 40, 20, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP2ScoreSegThree);
	}
	if (P2OnesSegmentFour == 1)
	{
		SDL_Rect fillRectP2ScoreSegFour = { Screen_width - 80, 40, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP2ScoreSegFour);
	}
	if (P2OnesSegmentFive == 1)
	{
		SDL_Rect fillRectP2ScoreSegFive = { Screen_width - 40, 40, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP2ScoreSegFive);
	}
	if (P2OnesSegmentSix == 1)
	{
		SDL_Rect fillRectP2ScoreSegSix = { Screen_width - 80, 60, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP2ScoreSegSix);
	}
	if (P2OnesSegmentSeven == 1)
	{
		SDL_Rect fillRectP2ScoreSegSeven = { Screen_width - 60, 60, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP2ScoreSegSeven);
	}
	if (P2OnesSegmentEight == 1)
	{
		SDL_Rect fillRectP2ScoreSegEight = { Screen_width - 40, 60, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP2ScoreSegEight);
	}
	if (P2OnesSegmentNine == 1)
	{
		SDL_Rect fillRectP2ScoreSegNine = { Screen_width - 80, 80, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP2ScoreSegNine);
	}
	if (P2OnesSegmentTen == 1)
	{
		SDL_Rect fillRectP2ScoreSegTen = { Screen_width - 40, 80, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP2ScoreSegTen);
	}
	if (P2OnesSegmentEleven == 1)
	{
		SDL_Rect fillRectP2ScoreSegEleven = { Screen_width - 80, 100, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP2ScoreSegEleven);
	}
	if (P2OnesSegmentTwelve == 1)
	{
		SDL_Rect fillRectP2ScoreSegTwelve = { Screen_width - 60, 100, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP2ScoreSegTwelve);
	}
	if (P2OnesSegmentThirteen == 1)
	{
		SDL_Rect fillRectP2ScoreSegThirteen = { Screen_width - 40, 100, 20, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRectP2ScoreSegThirteen);
	}


}
//==========MovingParts class end==========


//===============Main=================
int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	gWindow = SDL_CreateWindow("PONG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Screen_width, Screen_height, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
 
	SDL_Event e;

	MovingParts player;

	bool quit = false;

	while (!quit)
	{
		//Start time of this loop in milliseconds from program start
		int start = SDL_GetTicks();

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		player.PaddleControl();

		player.BallControl();

		player.ScoreDisp();

		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		//Draw a black background
		SDL_Rect fillRect = { 0, 0, Screen_width, Screen_height };
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect);


		player.render();

		SDL_RenderPresent(gRenderer);

		//Cap to 60 fps
		if (!quit)
		{
			int delay = start + MS_PER_FRAME - SDL_GetTicks();
			if (delay > 0)
			{
				SDL_Delay(delay);
			}
		}

	}

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	SDL_Quit();

	return 0;
}
