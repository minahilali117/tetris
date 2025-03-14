// PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
//NAME:MINAHIL ALI, RN;22I-0849

#include <SFML/Graphics.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
#include <sstream>

using namespace sf;
int main(){
	
    srand(time(0));
    
   Font tetris;
    tetris.loadFromFile("tetris/Tetris.ttf");	//font loaded
    
    Text score;
    score.setFont(tetris);			
    score.setCharacterSize(22);
    score.setString("   Tetris   ");		//text displayed in the menu
    score.setPosition(0.f, 0.f);
    
    Text help;
    help.setFont(tetris);			
    help.setCharacterSize(22);
    help.setString("HELP\n\n   -Rotate using up key\n   -Left & right keys to move\n   ");		//text displayed in the menu
    help.setPosition(0.f, 0.f);
    
    Texture menuPic, helpPic, pausePic, overPic;
    menuPic.loadFromFile("img/menu.jpg");
    helpPic.loadFromFile("img/help.jpg");
    pausePic.loadFromFile("img/paused.jpg");
    overPic.loadFromFile("img/endGame.jpg");
    
    Sprite Menu(menuPic), Help(helpPic), Paused(pausePic), Over(overPic);
    
    RenderWindow windowMenu(VideoMode(320, 480), "Menu");	//calling the menu window
    while (windowMenu.isOpen())
    {
    	Event e;
    	while (windowMenu.pollEvent(e))
    	{
    		if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
			windowMenu.close();                            //Opened window disposes
		if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
			if (e.key.code == Keyboard::Escape)            //when esc pressed, window closes
				windowMenu.close();                         
			else if (e.key.code == Keyboard::S)     //Check if the other key pressed is S key
				windowMenu.close();                          //close menu, start new game
			else if (e.key.code == Keyboard::H)   //Check if the other key pressed is RIGHT key
			{
				RenderWindow windowHelp(VideoMode(320, 680), "help");                          //renders a new help window
				while (windowHelp.isOpen())
				{
					Event e;
					while (windowHelp.pollEvent(e))
					{
						if (e.type == Event::Closed)
							windowHelp.close();
						if (e.type == Event::KeyPressed) 
						{
							if (e.key.code == Keyboard::Escape)
								windowHelp.close();
							else if (e.key.code == Keyboard::S)
							{
								windowHelp.close();
								windowMenu.close();
							}
						}
					}
				windowHelp.draw(Help);
				windowHelp.display();
				}
			}
		}
    	}
    	windowMenu.draw(Menu);	//the menu img
    	windowMenu.display();		
    }
       
    
    RenderWindow window(VideoMode(320, 480), title);
    
    Texture obj1, obj2, obj3, obj4, obj5;
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/shadows.png");
    obj5.loadFromFile("img/bomb.png");
    
    Sprite sprite(obj1), background(obj2), frame(obj3), shadows(obj4), bombs(obj5); //declaration of the sprites
    
    int delta_x=0, colorNum=(rand()%7) + 1, current_score=0, lines_cleared;
    int bombColorNum=1;
    float timer=0, delay=0.3;
    bool rotate=0, spaceFlag=0, bombFlag=0;
    int piece=rand()%8;
    
    
    Clock clock;
    
    while (window.isOpen()){
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                    rotate = true;                         //Rotation gets on
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                    delta_x = -1;                          //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                    delta_x = 1;                          //Change in X-Axis - Positive
                else if (e.key.code == Keyboard::Space)    //Check if the other key pressed is space key
                   spaceFlag=1;
                   
                else if (e.key.code == Keyboard::P)
                {
                	RenderWindow windowPause(VideoMode(320, 480), "Paused");
                	while (windowPause.isOpen())
                	{
                		Event e;
				while (windowPause.pollEvent(e))
				{
					if (e.type == Event::Closed)
					windowPause.close();
					
					if (e.type == Event::KeyPressed) 
					{
						if (e.key.code == Keyboard::C)
							windowPause.close();
						else if (e.key.code == Keyboard::E)
						{
							windowPause.close();
							window.close();
						}
						else if (e.key.code == Keyboard::H)
						{
							RenderWindow windowHelp(VideoMode(320, 680), "help");                          //renders a new help window
							while (windowHelp.isOpen())
							{
							Event e;
							while (windowHelp.pollEvent(e))
							{
								if (e.type == Event::Closed)
									windowHelp.close();
								if (e.type == Event::KeyPressed) 
								{
									if (e.key.code == Keyboard::Escape)
										windowHelp.close();
									else if (e.key.code == Keyboard::S)
									{
										windowHelp.close();
										//windowMenu.close();
									}
								}
							
							}
							
							windowHelp.draw(Help);
							windowHelp.display();
							}
							
						}
						else if (e.key.code == Keyboard::R)
						{
							delay=0.3;
							rotate=0;
							spaceFlag=0;
							clock.restart();
							delta_x=0; 
							colorNum=1;
							timer=0;
							windowPause.close();
						}
					}
					
				}
				windowPause.draw(Paused);
				windowPause.display();
                	}
                 }     				
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))   //Just another way to detect key presses without event listener
            delay=0.1;                                    //If DOWN key is pressed, delay in falling piece decreases from 0.3 to 0.1


        
        isBomb(piece, bombFlag);//checks if bomb has occured
        
        
        fallingPiece(timer, delay, colorNum, piece, bombFlag);  //makes pieces fall down; single tile pieces are considered bombs
        
        horzontalMove(delta_x);//enables the sprite to move left and right
        
        rotateFlag(rotate);//rotates the falling piece
        
        lines_cleared=clearLine();//when a line gets filled with tiles completely, it is cleared up. returns the number of lines cleared up
        
        shadow();  //shows ghost of piece falling, helps u decide where to place the piece
        
        drop(spaceFlag); //when spacebar pressed, piece falls. space flag turned to 1 when space pressed
        
        current_score=show_score(current_score, lines_cleared);//keeps count of the current score which is then displayed on the play window
        
        if (endGame()==0)
        {
        	window.close();
        	RenderWindow windowOver(VideoMode(320, 480), "game over");                          //renders game over window
			while (windowOver.isOpen())
			{
				Event e;
				while (windowOver.pollEvent(e))
				{
					if (e.type == Event::Closed)
					windowOver.close();	
				}
				windowOver.draw(Over);
				windowOver.display();
			}
        }
        
        

	delay=0.3;//returns to old speed when button released
	rotate=0;
	spaceFlag=0;
        window.clear(Color::Black);
        window.draw(background);
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                if (gameGrid[i][j]==0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(28,31); //offset
                window.draw(sprite);
            }
        }
        for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            sprite.move(28,31);
            window.draw(sprite);
          }
          
         for (int i=0; i<4; i++){
            shadows.setPosition(point_s1[i][0]*18,point_s1[i][1]*18);
            shadows.move(28,31);
            window.draw(shadows);
          }
          
            Text score, update_score, level;
            score.setFont(tetris);			
	    score.setCharacterSize(22);
	    score.setString("Score: ");		//text displayed in the menu
	    score.setPosition(25.f, 0.f);
	    
	    update_score.setFont(tetris);			
	    update_score.setCharacterSize(22);
	    update_score.setString(std::__cxx11::to_string(current_score));		//text displayed in the menu
	    update_score.setPosition(125.f, 0.f);
	    
	    level.setFont(tetris);			
	    level.setCharacterSize(22);
	    level.setString("Level: 1");		//text displayed in the menu
	    level.setPosition(225.f, 0.f);

	window.draw(score);  
	window.draw(update_score);  
	window.draw(level);      
        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
    }
   
    return 0;
}
