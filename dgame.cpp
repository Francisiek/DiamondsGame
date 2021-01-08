//Francisiek (C) 2020

#include <iostream>
#include <time.h>
//#include <curses.h>
#include "src/inchar.h"
#include "src/sinput.h"
	
//global var
	int** Dway=NULL;
	bool** Dmap=NULL;
	char** displ=NULL;
	int m_Width=0, m_Height=0, m_Diamonds=0;
	int p_Y=0, p_X=0;


//alloc and init memory
template<typename type>
void mloc2d(type** &ptr, int& height, int& width)
{
	ptr = new type*[height];
	for(int i=0; i<height; ++i)
		ptr[i]=new type[width];

	for(int i=0; i<height; ++i)
		for(int j=0; j<width; ++j)
			ptr[i][j]=0;
}

//free memory
template<typename type>
void free2d(type** &ptr, int& height, int& width)
{
	for(int i=0; i<height; ++i)
		delete[] ptr[i];
	
	delete[] ptr;
}

//moves player
void Move(int y, int x)
{
	if(p_Y+y < m_Height && p_Y+y >= 0 && p_X+x < m_Width && p_X+x >= 0)
	{
		displ[p_Y][p_X]='#';
		p_Y+=y;
		p_X+=x;
	}	

}

void Log()
{
	std::cout<<"log\n";
}

int main()
{
	srand(time(NULL));
	
	bool GameOver=false;
	bool Exit=false;
	bool Rep=true;

	while(!Exit) //settings, map creator
	{
		//input and checking if it matches
		system("echo '\t\e[43mWelcome!\n\e[0m'");
		std::cout<<"Please enter height, width of map\nand number of diamonds:\n";
		
		sinput(m_Height);
		while(m_Height < 2 || m_Height > 30)
		{
			std::cout<<"Type height from 2 to 30: ";
			sinput(m_Height);
		}
		
		sinput(m_Width);
		while(m_Width < 2 || m_Width > 30)
		{
			std::cout<<"Type width from 2 to 30: ";
			sinput(m_Width);
		}
		
		sinput(m_Diamonds);
		while(m_Diamonds < 2 || m_Diamonds > 30 || m_Diamonds > m_Height*m_Width/2)
		{
			std::cout<<"Type diamonds from 2 to 450 (not more than w*h/2): ";
			sinput(m_Diamonds);
		}
			
		
		generate:
		//new settings delete map
		//make map
		mloc2d(Dway, m_Height, m_Width);
		mloc2d(Dmap, m_Height, m_Width);
		mloc2d(displ, m_Height, m_Width);
		
		//generate diamonds
		int a=1,b=1;
		for(int i=0; i<m_Diamonds; ++i)
		{
		while( Dmap[ (a = rand() % m_Height) ][ (b = rand() % m_Width) ] == 1 || (a==0 && b==0));
			
			Dmap[a][b]=1;
		}
		
		//calculating max diamonds
		for(int i=1; i<m_Height; ++i)
		{
			Dway[i][0]=Dway[i-1][0];
			if(Dmap[i][0]) ++Dway[i][0];
		}
		
		for(int j=1; j<m_Width; ++j)
		{
			Dway[0][j]=Dway[0][j-1];
			if(Dmap[0][j]) ++Dway[0][j];
		}

		for(int i=1; i<m_Height; ++i)
		{
			for(int j=1; j<m_Width; ++j)
			{
				Dway[i][j]=std::max(Dway[i-1][j], Dway[i][j-1]);
				if(Dmap[i][j])
					++Dway[i][j];
			}
		}


		Rep=true;
		while(Rep)	//replay loop
		{
		
			//set up outmap
			for(int i=0; i<m_Height; ++i)
			{
				for(int j=0; j<m_Width; ++j)
				{
					if(Dmap[i][j])
						displ[i][j]='X';
					else
						displ[i][j]='#';
				}
			}
			
			//set var
			char Key = '0';
			int points = 0;
			p_X = p_Y = 0;
			
			system("clear");
			while(!GameOver)	//game loop
			{
				system("clear");
				
				displ[p_Y][p_X] = '@';

				//display
				for(int i=0; i<m_Height; ++i)
				{
					for(int j=0; j<m_Width; ++j)
					{
						std::cout << displ[i][j];
					}
					std::cout << '\n';
				}
				
				//game logics
				if(Dmap[p_Y][p_X])
				{
					printf("\a");
					++points;
				}
				
				if(p_Y == m_Height-1 && p_X == m_Width-1)
				{	
					GameOver=true;
					break;
				}
				
				//input
				Key=getch();
				if(Key < 97)
					Key+=32;

				switch(Key)
				{
					case 's': Move(1, 0); break;
					case 'd': Move(0, 1); break;
					case 'x': GameOver=true; break;
				}
		
			}
			
			
			//game over
			std::cout<<"\tGAME OVER! You collected: "<<points<<" diamonds.\n";
			std::cout<<"\tMAX diamonds: "<<Dway[m_Height-1][m_Width-1]<<'\n';
			
			if(Dway[m_Height-1][m_Width-1] > points)
				system("echo '\t\e[41m YOU LOOSE. \e[0m'");
			else
				system("echo '\t\e[42m YOU WON! \e[0m'");

			//new map or replay or exit
			std::cout<<"\n\tOptons: Replay this map r/R";
			std::cout<<"\n\tAnother map, this same settings f/F";
			std::cout<<"\n\tPlay antoher map e/E";
			std::cout<<"\n\tExit game x/X\n";
			
			xdfgh:
			//options
			Key=getch();
			if(Key < 97)
				Key+=32;

			switch(Key)
			{
				case 'r': GameOver=false; Rep=true; break;
				case 'f': GameOver=false; Rep=true; goto generate; break;
				case 'e': GameOver=false; Rep=false; break;
				case 'x': Rep=false; Exit=true; break;
				default: GameOver=true; goto xdfgh; break; 
			}
			system("clear");
		}
	}
	
	//delete everything
	free2d(Dmap, m_Height, m_Width);
	free2d(Dway, m_Height, m_Width);
	free2d(displ, m_Height, m_Width);

	return 0;
}
