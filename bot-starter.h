// Christos Savvopoulos <savvopoulos@gmail.com>
// Elias Sprengel <blockbattle@webagent.eu>

#ifndef __BOT_STARTER_H
#define __BOT_STARTER_H

#include <cstdlib>
#include <vector>

#include "bot-state.h"
#include "move.h"

using namespace std;

/**
 * This class is where the main logic should be. Implement getMoves() to
 * return something better than random moves.
 */
class BotStarter {
 public:
  /**
   * @param state : current state of the bot
   * @param timeout : time to respond
   * @return : a list of moves to execute
   */
  vector<Move::MoveType> GetMoves(const BotState& state, long long timeout) const 
  {
    vector<Move::MoveType> moves;
    const Field& f = state.MyField();
    Shape::ShapeType s = state.CurrentShape();
	bool myField[20][10];
	bool sentinel = false, pathBlocked;
	int manhattanDistance, manhattanDistance1, manhattanDistance2, manhattanDistance3, manhattanDistance4;
	int depth1, depth2, depth3, depth4;
	int depthNo = 0;
	
	for (int i=0; i<20; i++)
	{
		for (int j=0; j<10; j++)
		{
			if (f.GetCell(j,19-i).IsEmpty()) myField[i][j] = false;
			else myField[i][j] = true;
		}
	}
	
	if (s == Shape::ShapeType::O)
	{
		for (int i=0; i<19; i++)
		{
			for (int j=0; j<9; j++)
			{
				if (myField[i][j] == false && myField[i][j+1] == false && myField[i+1][j] == false && myField[i+1][j+1] == false)
				{	
					pathBlocked = false;
					for (int m=i; m<19; m++)
					{
						for (int n=j; n<j+2; n++) if (myField[m][n]) pathBlocked = true;
					}
					
					if (!pathBlocked)
					{
						manhattanDistance = j - 4;
						sentinel = true;
						break;
					}
				}
			}
			if (sentinel) break;
		}	
	} 
	
	if (s == Shape::ShapeType::I)
	{
		for (int i=0; i<20; i++)
		{
			for (int j=0; j<7; j++)
			{
				if (myField[i][j] == false && myField[i][j+1] == false && myField[i][j+2] == false && myField[i][j+3] == false)
				{
					pathBlocked = false;
					for (int m=i; m<19; m++)
					{
						for (int n=j; n<j+4; n++) if (myField[m][n]) pathBlocked = true;
					}
					
					if (!pathBlocked)
					{
						depth1 = i;
						manhattanDistance1 = j - 3;	
						sentinel = true;
						break;
					}
				}
			}
			if (sentinel) break;
		}
		sentinel = false;
		
		for (int i=0; i<16; i++)
		{
			for (int j=0; j<10; j++)
			{
				if (myField[i][j] == false && myField[i+1][j] == false && myField[i+2][j] == false && myField[i+3][j] == false)
				{	
					pathBlocked = false;
					for (int m=i; m<19; m++)
					{
						if (myField[m][j]) pathBlocked = true;
					}
					
					if (!pathBlocked)
					{
						depth2 = i;
						manhattanDistance2 = j - 4;
						sentinel = true;
						break;
					}
				}
			}
			if (sentinel) break;
		}
		
		if (depth1 <= depth2) manhattanDistance = manhattanDistance1;
		else
		{
			manhattanDistance = manhattanDistance2;
			moves.push_back(Move::MoveType::TURNLEFT);
		}
	}
	
	if (s == Shape::ShapeType::T)
	{
		for (int i=0; i<19; i++)
		{
			for (int j=0; j<8; j++)
			{
				if (myField[i][j] == false && myField[i][j+1] == false && myField[i][j+2] == false && myField[i+1][j+1] == false)
				{
					pathBlocked = false;
					for (int m=i; m<19; m++)
					{
						for (int n=j; n<j+3; n++) if (myField[m][n]) pathBlocked = true;
					}
					
					if (!pathBlocked)
					{
						depth1 = i;
						manhattanDistance1 = j - 3;	
						sentinel = true;
						break;
					}	
				}
			}
			if (sentinel) break;
		}
		sentinel = false;
		
		for (int i=0; i<18; i++)
		{
			for (int j=0; j<9; j++)
			{
				if (myField[i+1][j] == false && myField[i][j+1] == false && myField[i+1][j+1] == false && myField[i+2][j+1] == false)
				{
					pathBlocked = false;
					for (int m=i+1; m<17; m++)
					{
						for (int n=j; n<j+2; n++) if (myField[m][n]) pathBlocked = true;
					}
					
					if (!pathBlocked)
					{
						if (myField[i][j] == true) depth2 = i-1;
						else depth2 = i;
						manhattanDistance2 = j - 3;	
						sentinel = true;
						break;
					}	
				}
			}
			if (sentinel) break;
		}
		sentinel = false;
		
		for (int i=0; i<19; i++)
		{
			for (int j=0; j<8; j++)
			{
				if (myField[i][j+1] == false && myField[i+1][j] == false && myField[i+1][j+1] == false && myField[i+1][j+2] == false)
				{
					pathBlocked = false;
					for (int m=i+1; m<19; m++)
					{
						for (int n=j; n<j+3; n++) if (myField[m][n]) pathBlocked = true;
					}
					
					if (!pathBlocked)
					{
						if (myField[i][j] == true && myField[i][j+2] == true) depth3 = i-2;
						else depth3 = i;
						manhattanDistance3 = j - 3;	
						sentinel = true;
						break;
					}	
				}
			}
			if (sentinel) break;
		}
		sentinel = false;
		
		for (int i=0; i<18; i++)
		{
			for (int j=0; j<9; j++)
			{
				if (myField[i][j] == false && myField[i+1][j] == false && myField[i+2][j] == false && myField[i+1][j+1] == false)
				{
					pathBlocked = false;
					for (int m=i+1; m<19; m++)
					{
						for (int n=j; n<j+3; n++) if (myField[m][n]) pathBlocked = true;
					}
					
					if (!pathBlocked)
					{
						if (myField[i][j+1] == true) depth4 = i-1;
						else depth4 = i;
						manhattanDistance4 = j - 3;	
						sentinel = true;
						break;
					}	
				}
			}
			if (sentinel) break;
		}		
		int min = depth1;
  		int numbers[4] = {depth1,depth2,depth3,depth4};
  	
  		for (int i=1; i<4; i++) if (numbers[i] < min) min = numbers[i]; 		
		for (int i=0; i<4; i++) 
		{
			if (min == numbers[i])
			{
		 		depthNo = i;
		 		break;
		 	}
		}
		
		if (depthNo == 0) manhattanDistance = manhattanDistance1;
		else if (depthNo == 1)
		{
			manhattanDistance = manhattanDistance2;
			moves.push_back(Move::MoveType::TURNLEFT);
		}
		else if (depthNo == 2)
		{
			manhattanDistance = manhattanDistance3;
			moves.push_back(Move::MoveType::TURNLEFT);
			moves.push_back(Move::MoveType::TURNLEFT);
		}
		else if (depthNo == 3)
		{
			manhattanDistance = manhattanDistance4;
			moves.push_back(Move::MoveType::TURNLEFT);
			moves.push_back(Move::MoveType::TURNLEFT);
			moves.push_back(Move::MoveType::TURNLEFT);
		}
		else cerr << "Something went wrong in block T" << endl;
	}
	
	if (s == Shape::ShapeType::J)
	{
		for (int i=0; i<18; i++)
		{
			for (int j=0; j<8; j++)
			{
				if (myField[i][j] == false && myField[i][j+1] == false && myField[i][j+2] == false && myField[i+1][j] == false)
				{
					pathBlocked = false;
					for (int m=i; m<19; m++)
					{
						for (int n=j; n<j+3; n++) if (myField[m][n]) pathBlocked = true;
					}
					
					if (!pathBlocked)
					{
						depth1 = i;
						manhattanDistance1 = j - 3;	
						sentinel = true;
						break;
					}	
				}
			}
			if (sentinel) break;
		}
		sentinel = false;
		
		for (int i=0; i<17; i++)
		{
			for (int j=0; j<9; j++)
			{
				if (myField[i][j] == false && myField[i][j+1] == false && myField[i+1][j+1] == false && myField[i+2][j+1] == false)
				{
					pathBlocked = false;
					for (int m=i; m<19; m++)
					{
						for (int n=j; n<j+2; n++) if (myField[m][n]) pathBlocked = true;
					}
					
					if (!pathBlocked)
					{
						depth2 = i;
						manhattanDistance2 = j - 3;	
						sentinel = true;
						break;
					}	
				}
			}
			if (sentinel) break;
		}
		sentinel = false;
		
		for (int i=0; i<18; i++)
		{
			for (int j=0; j<8; j++)
			{
				if (myField[i][j+2] == false && myField[i+1][j+2] == false && myField[i+1][j+1] == false && myField[i+1][j] == false)
				{
					pathBlocked = false;
					for (int m=i+1; m<19; m++)
					{
						for (int n=j; n<j+3; n++) if (myField[m][n]) pathBlocked = true;
					}
					
					if (!pathBlocked)
					{
						if (myField[i][j] == true && myField[i][j+1] == true) depth3 = i-2;
						else depth3 = i;
						manhattanDistance3 = j - 3;	
						sentinel = true;
						break;
					}	
				}
			}
			if (sentinel) break;
		}
		sentinel = false;
		
		for (int i=0; i<17; i++)
		{
			for (int j=0; j<9; j++)
			{
				if (myField[i][j] == false && myField[i][j+1] == false && myField[i][j+2] == false && myField[i+1][j] == false)
				{
					pathBlocked = false;
					for (int m=i+2; m<19; m++)
					{
						for (int n=j; n<j+2; n++) if (myField[m][n]) pathBlocked = true;
					}
					
					if (!pathBlocked)
					{
						if (myField[i][j+1] == true && myField[i+1][j+1] == true) depth4 = i-2;
						else depth4 = i;
						manhattanDistance4 = j - 3;	
						sentinel = true;
						break;
					}	
				}
			}
			if (sentinel) break;
		}
		int min = depth1;
  		int numbers[4] = {depth1,depth2,depth3,depth4};
  	
  		for (int i=1; i<4; i++) if (numbers[i] < min) min = numbers[i]; 		
		for (int i=0; i<4; i++) 
		{
			if (min == numbers[i])
			{
		 		depthNo = i;
		 		break;
		 	}
		}
		
		if (depthNo == 0) manhattanDistance = manhattanDistance1;
		else if (depthNo == 1)
		{
			manhattanDistance = manhattanDistance2;
			moves.push_back(Move::MoveType::TURNLEFT);
		}
		else if (depthNo == 2)
		{
			manhattanDistance = manhattanDistance3;
			moves.push_back(Move::MoveType::TURNLEFT);
			moves.push_back(Move::MoveType::TURNLEFT);
		}
		else if (depthNo == 3)
		{
			manhattanDistance = manhattanDistance4;
			moves.push_back(Move::MoveType::TURNLEFT);
			moves.push_back(Move::MoveType::TURNLEFT);
			moves.push_back(Move::MoveType::TURNLEFT);
		}
		else cerr << "Something went wrong in block T" << endl;
	}
	
	if (s == Shape::ShapeType::L)
	{
		for (int i=0; i<18; i++)
		{
			for (int j=0; j<8; j++)
			{
				if (myField[i][j] == false && myField[i][j+1] == false && myField[i][j+2] == false && myField[i+1][j+2] == false)
				{
					pathBlocked = false;
					for (int m=i; m<18; m++)
					{
						for (int n=j; n<j+3; n++) if (myField[m][n]) pathBlocked = true;
					}
					
					if (!pathBlocked)
					{
						depth1 = i;
						manhattanDistance1 = j - 3;	
						sentinel = true;
						break;
					}
				}
			}
			if (sentinel) break;
		}
		sentinel = false;
		
		for (int i=0; i<17; i++)
		{
			for (int j=0; j<9; j++)
			{
				if (myField[i][j+1] == false && myField[i+1][j+1] == false && myField[i+2][j+1] == false && myField[i+2][j] == false)
				{
					pathBlocked = false;
					for (int m=i+2; m<19; m++)
					{
						for (int n=j; n<j+2; n++) if (myField[m][n]) pathBlocked = true;
					}
					
					if (!pathBlocked)
					{
						if (myField[i][j] == true && myField[i+1][j] == true) depth2 = i-2;
						else depth2 = i;
						manhattanDistance2 = j - 3;	
						sentinel = true;
						break;
					}
				}
			}
			if (sentinel) break;
		}
		sentinel = false;
		
		for (int i=0; i<18; i++)
		{
			for (int j=0; j<8; j++)
			{
				if (myField[i][j] == false && myField[i+1][j] == false && myField[i+1][j+1] == false && myField[i+1][j+2] == false)
				{
					pathBlocked = false;
					for (int m=i; m<19; m++)
					{
						for (int n=j; n<j+3; n++) if (myField[m][n]) pathBlocked = true;
					}
					
					if (!pathBlocked)
					{
						if (myField[i][j+1] == true && myField[i][j+2] == true) depth3 = i-2;
						else depth3 = i;
						manhattanDistance3 = j - 3;	
						sentinel = true;
						break;
					}
				}
			}
			if (sentinel) break;
		}
		sentinel = false;
		
		for (int i=0; i<17; i++)
		{
			for (int j=0; j<8; j++)
			{
				if (myField[i][j] == false && myField[i+1][j] == false && myField[i+2][j] == false && myField[i][j+1] == false)
				{
					pathBlocked = false;
					for (int m=i+1; m<19; m++)
					{
						for (int n=j; n<j+2; n++) if (myField[m][n]) pathBlocked = true;
					}
					
					if (!pathBlocked)
					{
						depth4 = i;
						manhattanDistance4 = j - 4;	
						sentinel = true;
						break;
					}
				}
			}
			if (sentinel) break;
		}	
		int min = depth1;
  		int numbers[4] = {depth1,depth2,depth3,depth4};
  	
  		for (int i=1; i<4; i++) if (numbers[i] < min) min = numbers[i]; 		
		for (int i=0; i<4; i++) 
		{
			if (min == numbers[i])
			{
		 		depthNo = i;
		 		break;
		 	}
		}
		
		if (depthNo == 0) manhattanDistance = manhattanDistance1;
		else if (depthNo == 1)
		{
			manhattanDistance = manhattanDistance2;
			moves.push_back(Move::MoveType::TURNLEFT);
		}
		else if (depthNo == 2)
		{
			manhattanDistance = manhattanDistance3;
			moves.push_back(Move::MoveType::TURNLEFT);
			moves.push_back(Move::MoveType::TURNLEFT);
		}
		else if (depthNo == 3)
		{
			manhattanDistance = manhattanDistance4;
			moves.push_back(Move::MoveType::TURNLEFT);
			moves.push_back(Move::MoveType::TURNLEFT);
			moves.push_back(Move::MoveType::TURNLEFT);
		}
		else cerr << "Something went wrong in block T" << endl;
	}
	
	if (s == Shape::ShapeType::S)
	{
		for (int i=0; i<19; i++)
		{
			for (int j=0; j<8; j++)
			{
				if (myField[i][j] == false && myField[i][j+1] == false && myField[i+1][j+1] == false && myField[i+1][j+2] == false)
				{
					pathBlocked = false;
					for (int m=i+1; m<19; m++)
					{
						for (int n=j; n<j+3; n++) if (myField[m][n]) pathBlocked = true;
					}
					
					if (!pathBlocked)
					{
						depth1 = i;
						manhattanDistance1 = j - 3;	
						sentinel = true;
						break;
					}	
				}
			}
			if (sentinel) break;
		}
		sentinel = false;
		
		for (int i=0; i<17; i++)
		{
			for (int j=0; j<8; j++)
			{
				if (myField[i][j+1] == false && myField[i+1][j] == false && myField[i+2][j] == false && myField[i+1][j+1] == false)
				{
					pathBlocked = false;
					for (int m=i+1; m<19; m++)
					{
						for (int n=j; n<j+2; n++) if (myField[m][n]) pathBlocked = true;
					}
					
					if (!pathBlocked)
					{
						if (myField[i][j] == true) depth2 = i-1;
						else depth2 = i;
						manhattanDistance2 = j - 3;	
						sentinel = true;
						break;
					}	
				}
			}
			if (sentinel) break;
		}
		
		if (depth1 <= depth2) manhattanDistance = manhattanDistance1;
		else
		{
			manhattanDistance = manhattanDistance2;
			moves.push_back(Move::MoveType::TURNLEFT);
		}
	}
	
	if (s == Shape::ShapeType::Z)
	{
		for (int i=0; i<19; i++)
		{
			for (int j=0; j<8; j++)
			{
				if (myField[i][j+1] == false && myField[i][j+2] == false && myField[i+1][j] == false && myField[i+1][j+1] == false)
				{
					pathBlocked = false;
					for (int m=i+1; m<19; m++)
					{
						for (int n=j; n<j+3; n++) if (myField[m][n]) pathBlocked = true;
					}
					
					if (!pathBlocked)
					{
						depth1 = i;
						manhattanDistance1 = j - 3;	
						sentinel = true;
						break;
					}
				}
			}
			if (sentinel) break;
		}
		sentinel = false;
		
		for (int i=0; i<17; i++)
		{
			for (int j=0; j<9; j++)
			{
				if (myField[i][j] == false && myField[i+1][j+1] == false && myField[i+1][j] == false && myField[i+2][j+1] == false)
				{
					pathBlocked = false;
					for (int m=i+1; m<19; m++)
					{
						for (int n=j; n<j+2; n++) if (myField[m][n]) pathBlocked = true;
					}
					
					if (!pathBlocked)
					{
						if (myField[i][j+1] == true) depth2 = i-1;
						else depth2 = i;
						manhattanDistance2 = j - 3;	
						sentinel = true;
						break;
					}
				}
			}
			if (sentinel) break;
		}
		
		if (depth1 <= depth2) manhattanDistance = manhattanDistance1;
		else
		{
			manhattanDistance = manhattanDistance2;
			moves.push_back(Move::MoveType::TURNLEFT);
		}
	}
	
	if (manhattanDistance < 0) for (int k=0; k>manhattanDistance; k--) moves.push_back(Move::MoveType::LEFT);
	else for (int k=0; k<manhattanDistance; k++) moves.push_back(Move::MoveType::RIGHT);
    
    moves.push_back(Move::MoveType::DROP);
    return moves;
  }
};

#endif  //__BOT_STARTER_H
