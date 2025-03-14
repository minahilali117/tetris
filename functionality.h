// PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
//NAME:MINAHIL ALI, RN;22I-0849


void fallingPiece(float& timer, float& delay, int &colorNum, int &piece, bool &bombFlag){
    if (timer>delay){
        for (int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;                   //How much units downward
        }
        
        if (!anamoly())
        {	
        
        	if (piece != 0)
        	{
			
            		for (int i=0; i<4; i++)
            			gameGrid[point_2[i][1]][point_2[i][0]]= colorNum;

          		int n=rand()%8;
          		piece=n;
          
               		 for (int i=0;i<4;i++)
               		 {
                    		point_1[i][0] = BLOCKS[n][i] % 2; //0 is for x
                   		point_1[i][1] = BLOCKS[n][i] / 2; //1 is for y
               		 }
               		 
               		 colorNum=(rand()%7) + 1;
               	}
               	
               	else if (piece==0)  //bomb occured
               	{	
               		bombFlag=0;  //reset bombFlag
               		if ( colorNum == gameGrid[point_1[0][1]][point_1[0][0]] ) //color of tile nd bomb matches
            		{
            			for ( int i = 0; i < M ; ++i )
            				for ( int j = 0; j < N ; ++j)
            					gameGrid[i][j] = 0;  //clear grid
			}
            	
            		else if ( gameGrid[point_1[0][1]][point_1[0][0]] ) // color dont match
            		{
            			gameGrid[point_1[0][1]][point_1[0][0]] = 0; //point on where the bomb fell
            			gameGrid[point_1[0][1]+1][point_1[0][0]] = 0; //point above where the bomb fell
            			gameGrid[point_1[0][1]][point_1[0][0]+1] = 0; //right to where the bomb fell
            			gameGrid[point_1[0][1]][point_1[0][0]-1] = 0; //left to where the bomb fell
            			gameGrid[point_1[0][1]+1][point_1[0][0]+1] = 0; // above and right
            		}
            		
            		
            		int n=rand()%8;
            		piece=n;
			colorNum=(rand()%7) + 1;
			
		        for (int i=0;i<4;i++)
		        {
		  	  	point_1[i][0] = BLOCKS[n][i] % 2;
		    		point_1[i][1] = BLOCKS[n][i] / 2;
		        }
               	
               	
               	}
              	
        } //end of !anamoly
        timer=0;
    }
}




void horzontalMove(int &delta_x)
{
	for (int i=0; i<4; i++)
	{
		point_2[i][0]=point_1[i][0];
		point_2[i][1]=point_1[i][1];
		point_1[i][0]+=delta_x;
	}
	delta_x=0;
	
	if (!anamoly())//makes sure sprites are staying wit in the matrix when shifting right or left
	{
		for (int i=0;i<4;i++)
		{
			point_1[i][0]=point_2[i][0];
			point_1[i][1]=point_2[i][1];
		}
	}

}

void rotateFlag(bool &rotate)
{
	int cenX=0; //x coordinate of the center of rotation
	int cenY=0; //y coordinate of the center of rotation
	int newX, newY;
	if (rotate==true)
	{
		cenX=point_1[1][0];//set center points so tile can be rotated again
		cenY=point_1[1][1];
		for (int i=0; i<4; i++)
		{
			newX= point_1[i][1] - cenY; 
			newY= point_1[i][0] - cenX;
			point_1[i][0]=cenX - newX;
			point_1[i][1]=cenY + newY;
			//for 90 degree rotation, use the laws of transformation to calculate new coordinates
			rotate=0;
		}
		
		if (!anamoly())//makes sure sprites are staying with in the matrix when rotated
		{
			for (int i=0;i<4;i++)
			{
				point_1[i][0]=point_2[i][0];
				point_1[i][1]=point_2[i][1];
			}
		}	
		
	}
}


int clearLine()
{
	int lines=0;
	int tempLine=M-1, numOfTimes=0;//serves as a counter to control stoping condition of for loop
	for (int i= M-1; i>0; i-=1)//loop stops when i becomes 0; 
	{
		numOfTimes=0;//reset counter each time the colomns are traversed thru
		for(int j=0; j<N; j+=1)//nested for loop to traverse through each element of grid array
		{
			if (gameGrid[i][j])
				numOfTimes+=1;
			gameGrid[tempLine][j]=gameGrid[i][j];//replaces the line
		}
		if (numOfTimes<N) 
			tempLine-=1; 
		if (numOfTimes==N) //counts the number of lines
			++lines;
	}
	
	
	return lines;
}

void shadow()//shows the shadow of falling block 4 rows below the center
{	
       	for (int i=0;i<4;i++)
	{
		point_s1[i][0]=point_1[i][0];
		point_s1[i][1]=point_1[i][1];
		//point_s1[i][1]=point_s1[i][1]+4;
	}

	while (shadow_anamoly())//the shadow comes at the place of block if removed
	{
		for (int i=0;i<4;i++)
		{	

			point_s2[i][0]=point_s1[i][0];
			point_s2[i][1]=point_s1[i][1];
			++point_s1[i][1];	//adds 1 to the y component until anamoly is met
		}
	}
	
	if (!shadow_anamoly())
	{
		for (int i=0;i<4;i++)
		{	

			point_s1[i][0]=point_s2[i][0];
			point_s1[i][1]=point_s2[i][1];
			
		}
	}


}

void drop(bool space_Flag)
{	
	if (space_Flag==1)
	{	
		space_Flag=0;
		while (anamoly()){
		
     		   for (int i=0;i<4;i++){
         		   point_2[i][0]=point_1[i][0];
         		   point_2[i][1]=point_1[i][1];
          		   point_1[i][1]+=1;                   //How much units downward
       		   }
       		}
       		   if (!anamoly())
      		   {
       		      	for (int i=0;i<4;i++)
          	     	{
             	       	    point_1[i][0]=point_2[i][0];
			    point_1[i][1]=point_2[i][1];
              		}
   		   }
   		   
   		
   	}
   	
}

bool endGame ()
{	
	bool over=0;
	for (int i=0;i<N;i++)
	{
		if (gameGrid[i][1]*18<point_1[i][1])		//reached the top of grid//18 is for 18 pixels
			over=1;
	}
	return over;
}
/*
void blae	cst_piWCDKece(int i)
{
	if(gameGridlsdncdc[point_b2[i][1]][point_b2[i][0]]==gameGrid[point_b2[ie;lcm][1]+1][poincdCDCt_b2[i][0]] && !(point_b2[i][1]==M-1)) //color matches
	{
		for (int i=0;iwed	2w,<M;i++)
		{
			for (int j=0;cDSCCDSj<N;j++)
			{
				gameGrid[i][j]=0;
			}
		}
	
	}
	
	else if (gameGrid[powCL,	[Wint_b2[i][1]][point_b2[i][0]]!=gameGrid[point_b2[i][1]+1][point_b2[i][0]] && !(point_b2[i][1]==M-1)) //color dont match
	{
		gameGrid[pE2LCWoint_b2[i][1]+1][point_b2[i][0]]=0;
		gameGrid[point_b2[i][1]+2][point_b2[i][0]]=0;
		gameGrid[WEOCFM	PO2Epoint_b2[i]WEC ;LX[1]+1][point_b2[i][0]+1]=0;
		gameGrid[point_b2[i][1]+2][point_b'2E;	C[2[i][0]+1]=0;
	}
	
	else if (point_b2[i][1WECL,	PO]==M-1) //vacant area
	{
		gameGridWE;XC,LPWOC[point_b2[i][1]][pW;LCKOKoint_b2[i][0]]=0;
	}

}
*/

bool isBomb(int &piece, bool &bombFlag) //checks if the current piece is a bomb
{
	if (piece==7) //true
		bombFlag=1;
	else
		bombFlag=0;
	return bombFlag;
}

int show_score(int &current_score, int &lines_cleared)
{
	if (lines_cleared==1)
		current_score+=10;
	
	if (lines_cleared==2)
		current_score += 30;
	
	if(lines_cleared==3)
		current_score += 60;
	
	if(lines_cleared>=4)
		current_score += 100;

	return current_score;
}





