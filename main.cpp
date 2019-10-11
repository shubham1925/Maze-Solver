
/**
* @file main.cpp
* @authors 
* 
* Group 5 
* 
* Shubham Sonawane shubhams@umd.edu \n
* Sanket Goyal sanket193@gmail.com \n
* Dipam Patel dipu18@umd.edu \n
* Kartik Venkat kartik.venkat86@gmail.com \n
* Arjun Srinivasan arjunsrinivasan.a@gmail.com \n 
* Kulbir Singh Ahluwalia kulbir@umd.edu \n
*
* @version 1.1
*
* @section LICENSE
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation; either version 2 of
* the License, or (at your option) any later version.
*
* @section DESCRIPTION
*
* This project finds a path between two points in a maze recursively using backtracking algorithm.
*/


#include <iostream>
#include <fstream>
// Initializing 2D character array to store the maze data.
char maze[31][47] = {0};
// Initializing start and goal positions.
int start_x, start_y, goal_x, goal_y = 0 ;  
// Checks if Goal is reached.
int goal_flag = 0;
void PrintMaze();
void TakeInput();
bool FindPath(int, int);
void ClearMarker();
bool ObstacleFound(int , int);

int main () 
{
	std::ifstream MazeFile;
	MazeFile.open("/home/kulbir/Documents/rwa2_group5/maze.txt");
    char singleChar;
	if (MazeFile.is_open()) //if the file is open
        {
            while (! MazeFile.eof() ) //while the end of file is NOT reached
            {
				for(int i = 0; i <= 31; i++)
				{
					for(int j = 0; j <= 46; j++)
					{
						MazeFile.get(singleChar);
						maze[i][j] = singleChar;
					}		
				}
			}
			MazeFile.close();	
		}	
	
	else {
			std::cout << "Unable to open file. Please check the maze.txt path.\n"; //if the file is not open output
			exit(1);
		}
         
	TakeInput();	

    while(start_x==goal_x&&start_y==goal_y)        // Check if start and Goal positions are same.
    { std::cout << "Start and Goal positions are same"<<std::endl;
      TakeInput();
       }
    maze[start_x][start_y] = 'S';
	maze[goal_x][goal_y] = 'G';	
	FindPath(start_x , start_y);
	ClearMarker();
	bool result = FindPath(start_x , start_y);
	
	// Detecting partial path.
	if(result == false && goal_flag != 1)
	{
		std::cout << "Partial path found" << std::endl;
	}
	maze[start_x][start_y] = 'S';	
	PrintMaze();
	return 0;	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
* @brief A function that is used to display the maze output.
*/
void PrintMaze()
{
	for(int x = 0; x <= 31; x++)
	{
		for(int y = 0; y <= 45; y++)
		{
			std::cout << maze[x][y];
		}
		std::cout << " " << std::endl;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
* @brief A function that is used to find the path for the robot recursively.
* @param x  Start x position
* @param y  Start y position
* @return Returns either True or False.
*/
bool FindPath(int x, int y)
{
	if((x < 0 || x > 30) || (y < 0 || y > 45))
		return false;	
	if(maze[x][y] == 'G')
	{
		goal_flag = 1;
		std::cout << "Complete Path Found " << std::endl;
		return true;
	}			
	if(maze[x][y] == '+')
		return false;
	if(maze[x][y] == '#')
		return false;
	if(maze[x][y] == 'x')
		return false;

	maze[x][y] = '+' ;
	if(FindPath(x-1, y))	
	{
		return true;	
	}
	if(FindPath(x, y+1))
	{
		return true;	
	}
	if(FindPath(x+1, y))
	{
		return true;	
	}
	if(FindPath(x, y-1))
	{
		return true;	
	}	
	maze[x][y] = 'x';
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
* @brief A function that is used to remove the failed path for the robot.
*/
void ClearMarker()
{
	for(int i = 0; i <= 31; i++)
	{
		for(int j = 0; j < 45; j++)
		{
			if(maze[i][j] == 'x')
				maze[i][j] = ' ';
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
* @brief A function that is used to take the start and goal positions of the robot by the user.
*/
void TakeInput()
{ bool done {false};
    while (!done)
    {std::cout << "Enter the robot start position co-ordinates within range (x: 0-45, y: 0-30) and press Enter: " << std::endl;
	std::cin >> start_x >> start_y;
	while (std::cin.fail())
	{ 
		std::cout<< "INVALID INPUT!! Please enter an integer value.\n";
		std::cin.clear();
		std::cin.ignore(256,'\n');             
        std::cin>> start_x >> start_y;	
    }	 
	    if(start_x >= 46 || start_x < 0 ||start_y >= 31 || start_y < 0)
		    std::cout << "The  start position is out of the maze. Please re-enter the position: " << std::endl;
        else if (ObstacleFound(start_x,start_y))
            std::cout << "Start Position is at an  Obstacle\n";
        else
          { std::cout << "The Start position is: " << start_x<<","<<start_y<<std::endl;
            done = true;}
        } 
     done = false;
     while (!done)
    {std::cout << "Enter the robot Goal position co-ordinates within range (x: 0-45, y: 0-30) and press Enter: " << std::endl;
	std::cin >> goal_x >> goal_y;
	while (std::cin.fail())
	{ 
		std::cout<< "INVALID INPUT!! Please enter an integer value.\n";
		std::cin.clear();
		std::cin.ignore(256,'\n');
        std::cin>> goal_x >> goal_y;}		 
	    if(goal_x >= 46 || goal_x < 0 ||goal_y >= 31 || goal_y < 0)
		    std::cout << "The  goal position is out of the maze. Please re-enter the position: " << std::endl;
        else if (ObstacleFound(goal_x,goal_y))
            std::cout << "Goal Position is at an  Obstacle\n";
        else
          { std::cout << "The Goal position is: " << goal_x<<","<<goal_y<<std::endl;
            done = true;}
        } 
        int t1 = start_y;
        int t2 = goal_y;
        goal_y = goal_x;
        start_y = start_x;
        start_x = 30 - t1;
        goal_x = 30 - t2;
} 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
* @brief A function that is used to detect an obstacle in the path for the robot.
* @param x  x co-ordinate of the robot
* @param y  y co-ordinate of the robot
* @return Returns either True or False.
*/
bool ObstacleFound(int x, int y)
{
    int t1 = y;
    y = x;
    x = 30 - t1;
	if(maze[x][y] == '#' )
        return true;
		
    else
         return false;
}

