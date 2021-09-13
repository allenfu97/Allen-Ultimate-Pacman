#include<graphics.h>
#include<dos.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<fstream.h>
void about();
void restart(int );  //restarts the game
void scorefile();   //keep the score file
void highscore();  //show high score
char Qexit();    //last screen asking (do you want to exit or not)
void instructions();
char start();  //first screen
char game();   //controls the game
char escscrn(); //when you press Escape
char gameends();   //when game is over
void dots(int a=0,int b=0);   //prints the dots
void ctrl_lives();    //controls lives
void info_at_game();
void controls();
void assconts(char []);
int menu(int ,const int , const int ,const int ,const int ,char );
unsigned long count=1,score,hg_scr,prevscr=-1,killcount;
const int sizehalf=10;
int changecolor=0,level=1,x0,x1,x2,x3,y0,y2,y3,y1,px,py,number,scorewhenkill=200,num_pow=4,num_dots=329,lives,killover=1000;
char version[14]={"Version 2.3.2"},key[4]={72/*up*/,80/*down*/,75/*left*/,77/*right*/};
class CONTROLS
{
	char con[4];
public :
	void get()
	{
		con[0]=key[0];
		con[1]=key[1];
		con[2]=key[2];
		con[3]=key[3];
	}
	void put()
	{
		key[0]=con[0];
		key[1]=con[1];
		key[2]=con[2];
		key[3]=con[3];
	}
}conts;
class data      //highscore datafiles
{
		char name[20];
		unsigned long points;
	public :
		void get()
		{
			char string[10];
			cleardevice();
			setcolor(WHITE);
			line(0,80,640,80);
			outtextxy(175,185,"ENTER NAME : ");
			rectangle(315,185,465,215);
			outtextxy(175,227,"SCORE : ");
			rectangle(315,220,465,255);
			outtextxy(323,225,itoa(score,string,10));
			settextstyle(0,0,2);
			outtextxy(180,50,"New High Score!!!");
			gotoxy(41,13);
			gets(name);
			points=score;
		}
		unsigned long retscore()
		{
			return points;
		}
		void put(int j)
		{
			const int dec=60,inc=40;
			char string[10];
			outtextxy(5,j,itoa(((j-dec)/inc)+1,string,10));
			outtextxy(100,j,name);
			outtextxy(420,j,itoa(points,string,10));
			delay(350);
		}
};
class pacman
{
	int left_top;
	int left_mid;
	int left_bottom;
	int right_top;
	int right_bottom;
	int right_mid;
	int mid_top;
	int mid_bottom;
	int stop;
	char final;
	int i;
	int j;
	int mouth;
	int inc_dec;
	void movement();
public:
	int reti()
	{
		return i;
	}
	int retj()
	{
		return j;
	}
	void disp_still();
	char move_ctrl(char );
	pacman(int x,int y)
	{
		final='l';
		stop=0;
		i=x;
		j=y;
		left_top=0;
		left_mid=0;
		left_bottom=0;
		right_top=0;
		right_bottom=0;
		right_mid=0;
		mid_top=0;
		mid_bottom=0;
		mouth=0;
		inc_dec=3;
	}
};
class ghost
{
private:
	int i_g;
	int j_g;
	int gleft_top;
	int gleft_mid;
	int gleft_bottom;
	int gmid_bottom;
	int gright_bottom;
	int gright_mid;
	int gright_top;
	int gmid_top;
	int g_no;
	int ioro;
	char d;
	int color;
	int trans;
	int pixforpac_up;
	int pixforpac_le;
	int pixforpac_ri;
	int pixforpac_do;
	void inhome();
	void moveghost(int ,int );
	void gmove_rand();
	void gchase_smthin(int ,int );
	void findupdown();
	void findleftright();
	void convtrans(int true)
	{
		trans=true;
	}
public:
	void addcolor(int n)
	{
		color=n;
	}
	void gwork(int ,int );
	void disp_still(int =0,int =0);
	int reti()
	{
		return i_g;
	}
	int retj()
	{
		return j_g;
	}
	ghost()
	{
		g_no=0;
		trans=1;
		d='l';
		ioro=1;
		gleft_top=0;
		gleft_mid=0;
		gleft_bottom=0;
		gmid_bottom=0;
		gright_bottom=0;
		gright_mid=0;
		gright_top=0;
		gmid_top=0;
	}
};
char pacman::move_ctrl(char command)    //controls the movement of THE PACMAN
{
	int pointx,pointy;
	if(mid_top==15||mid_bottom==15||left_mid==15||right_mid==15)
	{ //if it touches any thing white(dots or powerups)
		char string[10];
		setcolor(0);
		settextstyle(0,0,2);
		outtextxy(463,93,itoa(score,string,10));
		setfillstyle(1,0);
		if(score>=hg_scr)
			bar(460,28,630,50);
		setfillstyle(1,YELLOW);
		score+=10;
		setcolor(15);
		if(score>hg_scr)
			outtextxy(463,30,itoa(score,string,10));
		outtextxy(463,93,itoa(score,string,10));
		if(final=='u')
		{
			pointx=i;
			pointy=j-1-sizehalf;
		}
		else if(final=='l')
		{
			pointx=i-1-sizehalf;
			pointy=j;
		}
		else if(final=='r')
		{
			pointx=i+1+sizehalf;
			pointy=j;
		}
		else if(final=='d')
		{
			pointx=i;
			pointy=j+1+sizehalf;
		}
		if((i==413&&(j==38-sizehalf||j==39-sizehalf||j==40-sizehalf||j==41-sizehalf))||(i==413&&(j==54+sizehalf||j==53+sizehalf||j==52+sizehalf||j==51+sizehalf)))
		{     //   413,46
			changecolor=1;
			killcount=count;
			if(killcount==0)
				killcount=1;
			pointx=-413;
			pointy=-46;
		}
		else if(((i==405-sizehalf||i==406-sizehalf||i==407-sizehalf||i==408-sizehalf)&&j==365)||(i==413&&(j==357-sizehalf||j==358-sizehalf||j==359-sizehalf||j==360-sizehalf)))
		{//413,365
			changecolor=1;
			killcount=count;
			if(killcount==0)
				killcount=1;
			pointx=-413;
			pointy=-365;
		}
		else if((i==15&&(j==38-sizehalf||j==39-sizehalf||j==40-sizehalf||j==41-sizehalf))||(i==15&&(j==54+sizehalf||j==53+sizehalf||j==52+sizehalf||j==51+sizehalf)))
		{//		15,46
			changecolor=1;
			killcount=count;
			if(killcount==0)
				killcount=1;
			pointx=-15;
			pointy=-46;
		}
		else if((i==15&&(j==357-sizehalf||j==358-sizehalf||j==359-sizehalf||j==360-sizehalf))||((i==23+sizehalf||i==22+sizehalf||i==21+sizehalf||i==20+sizehalf)&&j==365))
		{//	15,365
			changecolor=1;
			killcount=count;
			if(killcount==0)
				killcount=1;
			pointx=-15;
			pointy=-365;
		}
	}
	else if((left_mid==3||right_mid==3||mid_top==3||mid_bottom==3||left_mid==4||right_mid==4||mid_top==4||mid_bottom==4||left_mid==2||right_mid==2||mid_top==2||mid_bottom==2||left_mid==6||right_mid==6||mid_top==6||mid_bottom==6))
	{   //if pacman touches any of the ghost
		if(command!=0)
			return 'P';
		delay(700);
		setcolor(0);
		setfillstyle(1,0);
		bar(x1-sizehalf,y1-sizehalf,x1+sizehalf,y1+sizehalf);
		bar(x2-sizehalf,y2-sizehalf,x2+sizehalf,y2+sizehalf);
		bar(x3-sizehalf,y3-sizehalf,x3+sizehalf,y3+sizehalf);
		bar(x0-sizehalf,y0-sizehalf,x0+sizehalf,y0+sizehalf);
		dots();
		for(int a=0,b=360;a!=b;)
		{//the last salute
			setcolor(0);
			setfillstyle(1,0);
			pieslice(i,j,a,b,sizehalf);
			a++;
			b--;
			setcolor(YELLOW);
			setfillstyle(1,YELLOW);
			pieslice(i,j,a,b,sizehalf);
			delay(10);
		}
		putpixel(i,j,0);
		delay(70);
		for(int ti=1;ti<=2;ti++)
			for(int rad=0;rad<=3*ti;rad++)
			{
				setcolor(YELLOW);
				circle(i,j,rad);
				circle(i,j,rad+3);
				circle(i,j,rad+2);
				delay(40);
				setcolor(0);
				circle(i,j,rad);
				circle(i,j,rad+3);
				circle(i,j,rad+2);
			}
		delay(200);
		if(lives>0)
		{
			lives--;
			scorewhenkill=200;
			return 'g';  //game();
		}
		else
		{
			setcolor(RED);
			settextstyle(0,0,0);
			outtextxy(180,266,"GAME OVER");
			delay(4000);
			scorefile();
			return 'e';//gameends()
		}
	}
	if(right_top==1&&right_bottom==1&&left_top==1&&left_bottom==1)
	{ //works only if all four corners are detected to be blue
		if(right_mid==1&&left_mid==1&&mid_top==1)
		{
			if(command=='d')
			{
				stop=0;
				final='d';
			}
		}
		else if(right_mid==1&&left_mid==1&&mid_bottom==1)
		{
			if(command=='u')
			{
				stop=0;
				final='u';
			}
		}
		else if(mid_bottom==1&&left_mid==1&&mid_top==1)
		{
			if(command=='r')
			{
				stop=0;
				final='r';
			}
		}
		else if(right_mid==1&&mid_bottom==1&&mid_top==1)
		{
			if(command=='l')
			{
				stop=0;
				final='l';
			}
		}
		else if(right_mid==1&&left_mid==1)
		{
			if(command=='d')
			{
				stop=0;
				final='d';
			}
			else if(command=='u')
			{
				stop=0;
				final='u';
			}
		}
		else if(right_mid==1&&mid_top==1)
		{
			if(command=='d')
			{
				stop=0;
				final='d';
			}
			else if(command=='l')
			{
				stop=0;
				final='l';
			}
		}
		else if(right_mid==1&&mid_bottom==1)
		{
			if(command=='l')
			{
				stop=0;
				final='l';
			}
			else if(command=='u')
			{
				stop=0;
				final='u';
			}
		}
		else if(mid_top==1&&left_mid==1)
		{
			if(command=='d')
			{
				stop=0;
				final='d';
			}
			else if(command=='r')
			{
				stop=0;
				final='r';
			}
		}
		else if(mid_bottom==1&&left_mid==1)
		{
			if(command=='r')
			{
				stop=0;
				final='r';
			}
			else if(command=='u')
			{
				stop=0;
				final='u';
			}
		}
		else if(mid_top==1&&mid_bottom==1)
		{
			if(command=='r')
			{
				stop=0;
				final='r';
			}
			else if(command=='l')
			{
				stop=0;
				final='l';
			}
		}
		else if(right_mid==1)
		{
			if(command=='d')
			{
				stop=0;
				final='d';
			}
			else if(command=='u')
			{
				stop=0;
				final='u';
			}
			else if(command=='l')
			{
				stop=0;
				final='l';
			}
		}
		else if(left_mid==1)
		{
			if(command=='d')
			{
				stop=0;
				final='d';
			}
			else if(command=='u')
			{
				stop=0;
				final='u';
			}
			else if(command=='r')
			{
				stop=0;
				final='r';
			}
		}
		else if(mid_top==1)
		{
			if(i==213&&j==173);
			else if(command=='d')
			{
				stop=0;
				final='d';
			}
			else if(command=='r')
			{
				stop=0;
				final='r';
			}
			else if(command=='l')
			{
				stop=0;
				final='l';
			}
		}
		else if(mid_bottom==1)
		{
			if(command=='r')
			{
				stop=0;
				final='r';
			}
			else if(command=='u')
			{
				stop=0;
				final='u';
			}
			else if(command=='l')
			{
				stop=0;
				final='l';
			}
		}
		else
		{
			if(command=='r')
			{
				stop=0;
				final='r';
			}
			else if(command=='l')
			{
				stop=0;
				final='l';
			}
			else if(command=='u')
			{
				stop=0;
				final='u';
			}
			else if(command=='d')
			{
				stop=0;
				final='d';
			}
		}
	}
	if(command=='u'&&final=='u'&&mid_top==1)  //when to stop?
		stop=1;
	else if(command=='l'&&final=='l'&&left_mid==1)
		stop=1;
	else if(command=='d'&&final=='d'&&mid_bottom==1)
		stop=1;
	else if(command=='r'&&final=='r'&&right_mid==1)
		stop=1;
	else if((command=='l'||command=='u')&&(final=='u'||final=='l')&&mid_top==1&&left_mid==1)
		stop=1;
	else if((command=='r'||command=='u')&&(final=='r'||final=='u')&&right_mid==1&&mid_top==1)
		stop=1;
	else if((command=='d'||command=='l')&&(final=='d'||final=='l')&&mid_bottom==1&&left_mid==1)
		stop=1;
	else if((command=='r'||command=='d')&&(final=='r'||final=='d')&&right_mid==1&&mid_bottom==1)
		stop=1;
	dots(pointx,pointy);
	movement();
	return '\0';
}
void pacman::movement()    //control pac man movement
{
	if(stop==0)  //if the pacman is able to move
	{
		setcolor(0);
		setfillstyle(1,0);
		bar(i-sizehalf,j-sizehalf,i+sizehalf,j+sizehalf);
		if(i==422+sizehalf&&j==221) //connects the 2 open ends of the maze
			i=-sizehalf;
		else if(i==-sizehalf&&j==221)
			i=422+sizehalf;
	setcolor(YELLOW);
	setfillstyle(1,YELLOW);
	switch(final) //depending on final decsion
	{
		case 'u':j--;
			pieslice(i,j,0,360,sizehalf);
			setcolor(0);
			setfillstyle(1,0);
			if(mouth)//closes and opens its gigantic mouth
			{
				setcolor(0);
				setfillstyle(1,0);
				pieslice(i,j+4,90-mouth,90+mouth,sizehalf+4);
			}
			break;
		case 'd':j++;
			pieslice(i,j,0,360,sizehalf);
			setcolor(0);
			setfillstyle(1,0);
			if(mouth)
			{
				setcolor(0);
				setfillstyle(1,0);
				pieslice(i,j-4,270-mouth,270+mouth,sizehalf+4);
			}
			break;
		case 'l':i--;
			pieslice(i,j,0,360,sizehalf);
			if(mouth)
			{
				setcolor(0);
				setfillstyle(1,0);
				pieslice(i+4,j,180-mouth,180+mouth,sizehalf+4);
			}
			break;
		case 'r':i++;
			pieslice(i,j,0,360,sizehalf);
			if(mouth)
			{
				setcolor(0);
				setfillstyle(1,0);
				pieslice(i-4,j,0,mouth,sizehalf+4);
				pieslice(i-4,j,360-mouth,360,sizehalf+4);
			}
	}
	}
	else
		disp_still();
	if(mouth==27)
		inc_dec=-3;
	else if(mouth==0)
		inc_dec=3;
	mouth+=inc_dec;
	//checks the color at all the six sides
	left_top=getpixel(i-1-sizehalf,j-1-sizehalf);
	left_mid=getpixel(i-1-sizehalf,j);
	left_bottom=getpixel(i-1-sizehalf,j+1+sizehalf);
	right_top=getpixel(i+1+sizehalf,j-1-sizehalf);
	right_bottom=getpixel(i+1+sizehalf,j+1+sizehalf);
	right_mid=getpixel(i+1+sizehalf,j);
	mid_top=getpixel(i,j-1-sizehalf);
	mid_bottom=getpixel(i,j+1+sizehalf);
}
void pacman::disp_still()
{
	setcolor(YELLOW);
	setfillstyle(1,YELLOW);
	pieslice(i,j,0,360,sizehalf);
	setcolor(0);
	setfillstyle(1,0);
	switch(final)
	{
		case 'u': pieslice(i,j+4,71,111,14);
			break;
		case 'd': pieslice(i,j-4,249,291,14);
			break;
		case 'l': pieslice(i+4,j,154,206,14);
			break;
		case 'r':pieslice(i-4,j,0,26,14);
			pieslice(i-4,j,334,360,14);

	}
}
void maze()
{
	cleardevice();
	setlinestyle(0,1,2);
	//  num cubes y=29cubes  num cubes x=26cubes
	//y(total)=480-10=472  x(total)=424
	//y start=0    x start =0
	//original y start=4, x=4    pacman radius =20
	//effective radius=22
	setcolor(1);
	line(4,4,200,4);
	line(4,4,4,136);
	line(226,4,424,4);
	line(424,4,424,136);
	line(200,4,200,66);   //v1
	line(200,66,226,66); //v1
	line(226,66,226,4);   //v1
	rectangle(26,26,82,66);    //r1
	rectangle(104,26,178,66);   //r2
	rectangle(248,26,322,66);   //r3
	rectangle(344,26,402,66);   //r4
	rectangle(26,88,82,114);  //r5
	rectangle(344,88,402,114);  //r6
	line(104,88,130,88);   //i2
	line(104,88,104,210);  //i2
	line(104,210,130,210);  //i2
	line(130,88,130,136);  //i2
	line(130,210,130,162); //i2
	line(130,136,178,136); //i2
	line(130,162,178,162);  //12
	line(178,136,178,162);   //i2
	line(152,88,274,88);   //i3
	line(152,88,152,114);   //i3
	line(152,114,200,114);  //i3
	line(200,114,200,162);  //i3
	line(200,162,226,162);  //i3
	line(226,162,226,114);   //i3
	line(226,114,274,114);    //i3
	line(274,114,274,88);  //i3
	line(296,88,296,136);   //i4
	line(296,136,248,136);   //i4
	line(248,136,248,162);  //i4
	line(248,162,296,162);  //i4
	line(296,162,296,210); //i4
	line(296,210,322,210);  //i4
	line(322,210,322,88);    //i4
	line(322,88,296,88);  //i4
	line(4,136,82,136);  //v2
	line(82,136,82,210);   //v2
	line(82,210,0,210);   //v2
	line(424,136,344,136);   //v3
	line(344,136,344,210);  //v3
	line(344,210,428,210);   //v3
	line(0,232,82,232);  //v4
	line(82,232,82,306);  //v4
	line(82,306,4,306);   //v4
	line(428,232,344,232);    //v5
	line(344,232,344,306);  //v5
	line(344,306,424,306);  //v5
	line(202,184,152,184);   //ghost box
	line(152,184,152,258);   //ghost box
	line(152,258,274,258);   //ghost box
	line(274,258,274,184);   //ghost box
	line(274,184,224,184);   //ghost box
	line(224,184,224,188);   //ghost box
	line(224,188,270,188);   //ghost box
	line(270,188,270,254);   //ghost box
	line(270,254,156,254);   //ghost box
	line(156,254,156,188);   //ghost box
	line(156,188,202,188);   //ghost box
	line(202,188,202,184);   //ghost box
	setcolor(WHITE);
	line(203,186,223,186);
	setcolor(BLUE);
	rectangle(104,232,130,306);  //r7
	rectangle(296,232,322,306);   //r8
	rectangle(104,328,178,354);    //r9
	rectangle(248,328,322,354);    //r10
	line(152,280,274,280);  //i5
	line(152,280,152,306);   //i5
	line(152,306,200,306);  //i5
	line(200,306,200,354);   //i5
	line(200,354,226,354);   //i5
	line(226,354,226,306);   //i5
	line(226,306,274,306);   //i5
	line(274,306,274,280);   //i5
	line(4,306,4,376);
	line(4,376,38,376);    //v6
	line(38,376,38,402);   //v6
	line(38,402,4,402);   //v6
	line(4,402,4,472);
	line(4,472,424,472);
	line(424,472,424,402);
	line(424,402,392,402);    //v7
	line(392,402,392,376);    //v7
	line(392,376,424,376);   //v7
	line(424,376,424,306);
	line(26,328,26,354);  //i6
	line(26,354,60,354); //i6
	line(60,354,60,402);  //i6
	line(60,402,82,402);   //i6
	line(82,402,82,328);   //i6
	line(82,328,26,328);   //i6
	line(344,328,344,402);    //i7
	line(344,402,370,402);  //i7
	line(370,402,370,354);  //i7
	line(370,354,402,354);   //i7
	line(402,354,402,328);  //i7
	line(402,328,344,328);    //i7
	line(26,424,26,450);    //i8
	line(26,450,178,450);   //i8
	line(178,450,178,424);   //i8
	line(178,424,130,424);    //i8
	line(130,424,130,376);   //i8
	line(130,376,104,376);   //i8
	line(104,376,104,424);   //i8
	line(104,424,26,424);   //i8
	line(152,376,152,402);    //i9
	line(152,402,200,402);   //i9
	line(200,402,200,450);  //i9
	line(200,450,226,450);    //i9
	line(226,450,226,402);       //i9
	line(226,402,274,402);    //i9
	line(274,402,274,376);      //i9
	line(274,376,152,376);  //i9
	line(248,424,248,450);      //i10
	line(248,450,402,450);    //i10
	line(402,450,402,424);   //i10
	line(402,424,322,424);   //i10
	line(322,424,322,376);     //i10
	line(322,376,296,376);    //i10
	line(296,376,296,424);       //i10
	line(296,424,248,424);   //i10
	//outlint
	line(0,0,204,0);
	line(204,0,204,62);
	line(204,62,222,62);
	line(222,62,222,0);
	line(222,0,428,0);
	line(428,0,428,140);
	line(428,140,348,140);
	line(348,140,348,206);
	line(348,206,428,206);
	line(428,236,348,236);
	line(348,236,348,302);
	line(348,302,428,302);
	line(428,302,428,380);
	line(428,380,396,380);
	line(396,380,396,398);
	line(396,398,428,398);
	line(428,398,428,476);
	line(428,476,0,476);
	line(0,476,0,398);
	line(0,398,34,398);
	line(34,398,34,380);
	line(34,380,0,380);
	line(0,380,0,302);
	line(0,302,78,302);
	line(78,302,78,236);
	line(78,236,0,236);
	line(0,206,78,206);
	line(78,206,78,140);
	line(78,140,0,140);
	line(0,140,0,0);
}
void dots(int pointx,int pointy)
{
	setcolor(15);
	setfillstyle(1,15);
	int i;
	static int dotx[329];//={15,27,37,49,61,72,81,93,105,116,129,141,153,164,177,189,237,249,260,273,285,297,308,321,333,345,359,370,381,391,401,413,15,93,189,237,333,413,15,93,189,237,333,413,15,27,37,49,61,72,81,93,105,116,129,141,153,164,177,189,201,212,225,237,249,260,273,285,297,308,321,333,345,359,370,381,391,401,413,15,93,141,285,333,413,15,93,141,285,333,413,15,27,37,49,61,72,81,93,141,153,164,177,189,237,249,260,273,285,333,345,359,370,381,391,401,413,93,333,93,333,15,27,37,49,61,72,81,93,105,116,129,141,153,164,177,189,237,249,260,273,285,297,308,321,333,345,359,370,381,391,401,413,15,93,189,237,333,413,15,93,189,237,333,413,27,37,49,93,105,116,129,141,153,164,177,189,201,212,225,237,249,260,273,285,297,308,321,333,381,391,401,49,93,141,285,333,381,49,93,141,285,333,381,15,27,37,49,61,72,81,93,141,153,164,177,189,237,249,260,273,285,333,345,359,370,381,391,401,413,15,189,237,413,15,189,237,413,
			     //15,27,37,49,61,72,81,93,105,116,129,141,153,164,177,189,201,212,225,237,249,260,273,285,297,308,321,333,345,359,370,381,391,401,413,93,93,189,189,237,237,333,333,15,93,141,285,333,413,93,93,93,93,93,93,93,93,93,93,93,93,93,333,333,333,333,333,333,333,333,333,333,333,333,333,15,93,189,237,333,413,49,93,141,285,333,381,15,189,237,413};
	static int doty[329];//={15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,27,27,27,27,27,27,65,65,65,65,65,65,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,89,89,89,89,89,89,113,113,113,113,113,113,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,137,137,305,305,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,329,329,329,329,329,329,353,353,353,353,353,353,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,377,377,377,377,377,377,401,401,401,401,401,401,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,425,425,425,425,449,449,449,449,461,
			     //  461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,38,49,38,49,38,49,38,49,101,101,101,101,101,101,148,159,170,181,192,206,294,283,272,261,250,236,221,148,159,170,181,192,206,294,283,272,261,250,236,221,341,341,341,341,341,341,389,389,389,389,389,389,437,437,437,437};
	static int powerx[4];//={413,15,15,413};
	static int powery[4];//={46,46,365,365};
	if(pointx==-1&&pointy==-1)
	{//saving all the positions of the dots in the static arrays
		int x[329]={15,27,37,49,61,72,81,93,105,116,129,141,153,164,177,189,237,249,260,273,285,297,308,321,333,345,359,370,381,391,401,413,15,93,189,237,333,413,15,93,189,237,333,413,15,27,37,49,61,72,81,93,105,116,129,141,153,164,177,189,201,212,225,237,249,260,273,285,297,308,321,333,345,359,370,381,391,401,413,15,93,141,285,333,413,15,93,141,285,333,413,15,27,37,49,61,72,81,93,141,153,164,177,189,237,249,260,273,285,333,345,359,370,381,391,401,413,93,333,93,333,15,27,37,49,61,72,81,93,105,116,129,141,153,164,177,189,237,249,260,273,285,297,308,321,333,345,359,370,381,391,401,413,15,93,189,237,333,413,15,93,189,237,333,413,27,37,49,93,105,116,129,141,153,164,177,189,201,212,225,237,249,260,273,285,297,308,321,333,381,391,401,49,93,141,285,333,381,49,93,141,285,333,381,15,27,37,49,61,72,81,93,141,153,164,177,189,237,249,260,273,285,333,345,359,370,381,391,401,413,15,189,237,413,15,189,237,413,
			    15,27,37,49,61,72,81,93,105,116,129,141,153,164,177,189,201,212,225,237,249,260,273,285,297,308,321,333,345,359,370,381,391,401,413,93,93,189,189,237,237,333,333,15,93,141,285,333,413,93,93,93,93,93,93,93,93,93,93,93,93,93,333,333,333,333,333,333,333,333,333,333,333,333,333,15,93,189,237,333,413,49,93,141,285,333,381,15,189,237,413};
		int y[329]={15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,27,27,27,27,27,27,65,65,65,65,65,65,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,89,89,89,89,89,89,113,113,113,113,113,113,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,137,137,305,305,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,317,329,329,329,329,329,329,353,353,353,353,353,353,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,365,377,377,377,377,377,377,401,401,401,401,401,401,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,413,425,425,425,425,449,449,449,449,461,
			    461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,461,38,49,38,49,38,49,38,49,101,101,101,101,101,101,148,159,170,181,192,206,294,283,272,261,250,236,221,148,159,170,181,192,206,294,283,272,261,250,236,221,341,341,341,341,341,341,389,389,389,389,389,389,437,437,437,437};
		int px[4]={413,15,15,413};
		int py[4]={46,46,365,365};
		for(int i=0;i<num_dots;i++)
		{
			dotx[i]=x[i];
			doty[i]=y[i];
		}
		for(i=0;i<num_pow;i++)
		{
			powerx[i]=px[i];
			powery[i]=py[i];
		}
	}
	else if(pointx<0&&pointy<0)//if it eats a power dot
	for(i=0;i<num_pow;++i)
	{ //that coordinates are removed
		if(powerx[i]==-(pointx)&&powery[i]==-(pointy))
		{
			for(int j=i;j<num_pow;j++)
			{
				powerx[j]=powerx[j+1];
				powery[j]=powery[j+1];
			}
			num_pow--;
			break;
		}
	}
	else if(pointx>0&&pointy>0)
	for(i=0;i<num_dots;++i)
	{
		if(dotx[i]==pointx&&doty[i]==pointy)
		{
			for(int j=i;j<num_dots;j++)
			{
				dotx[j]=dotx[j+1];
				doty[j]=doty[j+1];
			}
			num_dots--;
			break;
		}
	}
/*print all again, so that when the ghosts move
	on them, they cannot eat them*/
	for(i=0;i<num_dots;i++)
		putpixel(dotx[i],doty[i],15);
	for(i=0;i<num_pow;i++)
	{
		setcolor(0);
		setfillstyle(1,0);
		pieslice(powerx[i],powery[i],0,360,8);
		setcolor(15);
		setfillstyle(1,15);
		if(count%36>=1&&count%36<=5)
			pieslice(powerx[i],powery[i],0,360,8);
		else if((count%36>=6&&count%36<=11)||(count%36>=30&&count%36<=35))
			pieslice(powerx[i],powery[i],0,360,7);
		else if((count%36>=12&&count%36<=17)||(count%36>=24&&count%36<=29))
			pieslice(powerx[i],powery[i],0,360,6);
		else
			pieslice(powerx[i],powery[i],0,360,5);
	}
	if(num_pow==3)
		delay(1);
	else if(num_pow==2)
		delay(2);
	else if(num_pow==1)
		delay(3);
	else if(num_pow==0)
		delay(4);
}
void restart(int type)
{            //1->    the whole game starts again
	     //2->    next level
	num_dots=329;
	num_pow=4;
	scorewhenkill=200;
	switch(type)
	{
		case 1: score=0;
			lives=2;
			level=1;
			break;
		case 2: if(killover>500)
				killover-=400;
	}
	dots(-1,-1);
}
void ghost::disp_still(int xg,int yg)
{
	if(xg!=0&&yg!=0)
	{
		if(yg==173)
			ioro=0;
		i_g=xg;
		j_g=yg;
	}
	setcolor(0);
	setfillstyle(1,0);
	pieslice(i_g,j_g,0,180,sizehalf);
	bar(i_g-sizehalf,j_g,i_g+sizehalf,j_g+sizehalf);
	setcolor(color);
	setfillstyle(trans,color);
	if(trans==1)
	{
		pieslice(i_g,j_g,0,180,sizehalf);
		if(count%2==0)
		{
			int poly1[28]={i_g-sizehalf,j_g,i_g-sizehalf,j_g+sizehalf,i_g-sizehalf+1,j_g+sizehalf,i_g-7,j_g+6,i_g-4,j_g+sizehalf,i_g-3,j_g+sizehalf,i_g,j_g+6,i_g+3,j_g+sizehalf,i_g+4,j_g+sizehalf,i_g+7,j_g+6,i_g+sizehalf-1,j_g+sizehalf,i_g+sizehalf,j_g+sizehalf,i_g+sizehalf,j_g,i_g-sizehalf,j_g};
			drawpoly(14,poly1);
		}
		else
		{
			int poly2[22]={i_g-sizehalf,j_g,i_g-sizehalf,j_g+sizehalf,i_g-sizehalf+1,j_g+sizehalf,i_g-5,j_g+6,i_g-1,j_g+sizehalf,i_g+1,j_g+sizehalf,i_g+5,j_g+6,i_g+sizehalf-1,j_g+sizehalf,i_g+sizehalf,j_g+sizehalf,i_g+sizehalf,j_g,i_g-sizehalf,j_g};
			drawpoly(11,poly2);
		}
		floodfill(i_g+1,j_g+2,color);
		if((color==9||color==15)&&g_no==0)
		{
			if(color==15)
			{
				setcolor(12);
				setfillstyle(1,12);
			}
			else
			{
				setcolor(15);
				setfillstyle(1,15);
			}
			pieslice(i_g-4,j_g-2,0,360,2);
			pieslice(i_g+4,j_g-2,0,360,2);
			line(i_g-8,j_g+5,i_g-6,j_g+3);
			line(i_g-6,j_g+3,i_g-4,j_g+5);
			line(i_g-4,j_g+5,i_g-2,j_g+3);
			line(i_g-2,j_g+3,i_g,j_g+5);
			line(i_g,j_g+5,i_g+2,j_g+3);
			line(i_g+2,j_g+3,i_g+4,j_g+5);
			line(i_g+4,j_g+5,i_g+6,j_g+3);
			line(i_g+6,j_g+3,i_g+8,j_g+5);
		}
	}
	if(g_no==1||(color!=9&&color!=15))  {
	setcolor(15);
	setfillstyle(1,15);
	pieslice(i_g-5,j_g-2,0,360,3);
	pieslice(i_g+4,j_g-2,0,360,3);
	setcolor(0);
	setfillstyle(1,0);
	if(d=='u')
	{ //eg. the ghost looks up while it moves up
		pieslice(i_g-5,j_g-3,0,360,2);
		pieslice(i_g+4,j_g-3,0,360,2);
	}
	else if(d=='d')
	{
		pieslice(i_g-5,j_g-1,0,360,2);
		pieslice(i_g+4,j_g-1,0,360,2);
	}
	else if(d=='l')
	{
		pieslice(i_g-6,j_g-2,0,360,2);
		pieslice(i_g+3,j_g-2,0,360,2);
	}
	else
	{
		pieslice(i_g-4,j_g-2,0,360,2);
		pieslice(i_g+5,j_g-2,0,360,2);
	}
	}
}
void ghost::gmove_rand()
{ /*have ghost in different decison)*/
	int num2,num3;
	num2=random(2);
	num3=random(3);
	if(i_g==213&&j_g==173)
	{
		if(d=='u')
		{
			if(num2==0)
				d='r';
			else
				d='l';
		}
	}
	else if(gright_top==1&&gright_bottom==1&&gleft_top==1&&gleft_bottom==1)
	{
		if(gright_mid==1&&gmid_top==1)
		{
			if(d=='r')
				d='d';
			else if(d=='u')
				d='l';
		}
		else if(gright_mid==1&&gmid_bottom==1)
		{
			if(d=='d')
				d='l';
			else if(d=='r')
				d='u';
		}
		else if(gmid_top==1&&gleft_mid==1)
		{
			if(d=='l')
				d='d';
			else if(d=='u')
				d='r';
		}
		else if(gmid_bottom==1&&gleft_mid==1)
		{
			if(d=='d')
				d='r';
			else if(d=='l')
				d='u';
		}
		else if(gmid_bottom==1&&gmid_top==1);
		else if(gleft_mid==1&&gright_mid==1);
		else if(gright_mid==1)
		{
			if(d=='u'||d=='d')
			{
				if(num2==0)
					d='l';
			}
			else if(d=='r')
			{
				if(num2==0)
					d='u';
				else
					d='d';
			}
		}
		else if(gleft_mid==1)
		{
			if(d=='u'||d=='d')
			{
				if(num2==0)
					d='r';
			}
			else if(d=='l')
			{
				if(num2==0)
					d='u';
				else
					d='d';
			}
		}
		else if(gmid_top==1)
		{
			if(i_g==213&&j_g==173);
			else if(d=='u')
			{
				if(num2==0)
					d='l';
				else
					d='r';
			}
			else if(d=='l'||d=='r')
			{
				if(num2==0)
					d='d';
			}
		}
		else if(gmid_bottom==1)
		{
			if(d=='l'||d=='r')
			{
				if(num2==0)
					d='u';
			}
			else if(d=='d')
			{
				if(num2==0)
					d='l';
				else
					d='r';
			}
		}
		else
		{
			if(d=='u'||d=='d')
			{
				if(num3==0)
					d='r';
				else if(num3==1)
					d='l';
			}
			else if(d=='r'||d=='l')
			{
				if(num3==0)
					d='u';
				else if(num3==1)
					d='d';
			}
		}
	}
}
void ghost::moveghost(int px=0,int py=0)
{ //makes the fantastic four move
	char string[5];
	setfillstyle(1,0);
	setcolor(0);
	pieslice(i_g,j_g,0,180,sizehalf);
	bar(i_g-sizehalf,j_g,i_g+sizehalf,j_g+sizehalf);
	if(i_g==422+sizehalf&&j_g==221)   //connects the two open ends of the maze
		i_g=-sizehalf;
	else if(i_g==-sizehalf&&j_g==221)
		i_g=422+sizehalf;
	else if((j_g==173||j_g==197)&&i_g==213)
	{ //reprints the line in the entrance of their home
		setcolor(WHITE);
		line(203,186,223,186);
	}
	if(g_no==0&&killcount>0&&(color==9||color==15)&&(count>killcount+(killover-500))&&count<=killcount+killover+1)
	{   //ending up the kill mode
		if(count%50<=49&&count%50>=24)
			color=15;   //blinking of ghosts
		else
			color=9;
		if(count==killcount+killover||count==killcount+killover+1) //killmode is over
		{
			if(number==0)
				color=2;
			else if(number==1)
				color=3;
			else if(number==2)
				color=4;
			else
			{
				color=6;
				killcount=0;
			}
			scorewhenkill=200;
			trans=1;
		}
	}
	if(g_no==0&&killcount>0&&(color==9||color==15)&&(pixforpac_le==14||pixforpac_do==14||pixforpac_ri==14||pixforpac_up==14||gmid_bottom==14||gleft_mid==14||gright_mid==14||gmid_top==14))
	{   //if our hero slams the ghost it while they are blue
		setcolor(0);
		setfillstyle(1,0);
		pieslice(px,py,0,360,sizehalf);
		settextstyle(0,0,2);
		outtextxy(463,93,itoa(score,string,10));
		if(score>hg_scr)
			bar(460,28,630,50);
		score+=scorewhenkill;
		setcolor(15);
		if(score>hg_scr)
			outtextxy(463,30,itoa(score,string,10));
		outtextxy(463,93,itoa(score,string,10));
		settextstyle(2,0,4);
		outtextxy(i_g-6,j_g-5,itoa(scorewhenkill,string,10));
		delay(600);
		setcolor(0);
		outtextxy(i_g-6,j_g-5,itoa(scorewhenkill,string,10));
		trans=0;
		g_no=1;
		if(scorewhenkill==800)
			scorewhenkill=200;
		else
			scorewhenkill+=200;
	}
	switch(d)
	{
		case 'r': i_g++;
			break;
		case 'l': i_g--;
			break;
		case 'u': j_g--;
			break;
		case 'd': j_g++;
	}
	if(trans==1)
	{
	setcolor(color);
	setfillstyle(trans,color);
	if(count%10<=9&&count%10>=4)
	{
		int poly1[28]={i_g-sizehalf,j_g,i_g-sizehalf,j_g+sizehalf,i_g-sizehalf+1,j_g+sizehalf,i_g-7,j_g+6,i_g-4,j_g+sizehalf,i_g-3,j_g+sizehalf,i_g,j_g+6,i_g+3,j_g+sizehalf,i_g+4,j_g+sizehalf,i_g+7,j_g+6,i_g+sizehalf-1,j_g+sizehalf,i_g+sizehalf,j_g+sizehalf,i_g+sizehalf,j_g,i_g-sizehalf,j_g};
		drawpoly(14,poly1);
	}
	else
	{
		int poly2[22]={i_g-sizehalf,j_g,i_g-sizehalf,j_g+sizehalf,i_g-sizehalf+1,j_g+sizehalf,i_g-5,j_g+6,i_g-1,j_g+sizehalf,i_g+1,j_g+sizehalf,i_g+5,j_g+6,i_g+sizehalf-1,j_g+sizehalf,i_g+sizehalf,j_g+sizehalf,i_g+sizehalf,j_g,i_g-sizehalf,j_g};
		drawpoly(11,poly2);
	}
	floodfill(i_g+1,j_g+2,color);
	pieslice(i_g,j_g,0,180,sizehalf);
	if((color==9||color==15)&&g_no==0)
	{

		if(color==15)
		{
			setcolor(12);
			setfillstyle(1,12);
		}
		else
		{
			setcolor(15);
			setfillstyle(1,15);
		}
		pieslice(i_g-4,j_g-2,0,360,2);
		pieslice(i_g+4,j_g-2,0,360,2);
		line(i_g-8,j_g+5,i_g-6,j_g+3);
		line(i_g-6,j_g+3,i_g-4,j_g+5);
		line(i_g-4,j_g+5,i_g-2,j_g+3);
		line(i_g-2,j_g+3,i_g,j_g+5);
		line(i_g,j_g+5,i_g+2,j_g+3);
		line(i_g+2,j_g+3,i_g+4,j_g+5);
		line(i_g+4,j_g+5,i_g+6,j_g+3);
		line(i_g+6,j_g+3,i_g+8,j_g+5);
	}
	}
	if(g_no==1||(color!=9&&color!=15))  {
	setcolor(15);
	setfillstyle(1,15);
	pieslice(i_g-5,j_g-2,0,360,3);
	pieslice(i_g+4,j_g-2,0,360,3);
	setcolor(0);
	setfillstyle(1,0);
	if(d=='u')
	{ //eg. the ghost looks up while it moves up
		pieslice(i_g-5,j_g-3,0,360,2);
		pieslice(i_g+4,j_g-3,0,360,2);
	}
	else if(d=='d')
	{
		pieslice(i_g-5,j_g-1,0,360,2);
		pieslice(i_g+4,j_g-1,0,360,2);
	}
	else if(d=='l')
	{
		pieslice(i_g-6,j_g-2,0,360,2);
		pieslice(i_g+3,j_g-2,0,360,2);
	}
	else
	{
		pieslice(i_g-4,j_g-2,0,360,2);
		pieslice(i_g+5,j_g-2,0,360,2);
	}
	}
	gleft_top=getpixel(i_g-1-sizehalf,j_g-1-sizehalf);
	gleft_mid=getpixel(i_g-1-sizehalf,j_g);
	gleft_bottom=getpixel(i_g-1-sizehalf,j_g+1+sizehalf);
	gright_top=getpixel(i_g+1+sizehalf,j_g-1-sizehalf);
	gright_bottom=getpixel(i_g+1+sizehalf,j_g+1+sizehalf);
	gright_mid=getpixel(i_g+1+sizehalf,j_g);
	gmid_top=getpixel(i_g,j_g-1-sizehalf);
	gmid_bottom=getpixel(i_g,j_g+1+sizehalf);
	if(color==9||color==15)
	{
		pixforpac_up=getpixel(i_g-6,j_g-2-sizehalf);
		pixforpac_do=getpixel(i_g-6,j_g+2+sizehalf);
		pixforpac_le=getpixel(i_g-2-sizehalf,j_g-6);
		pixforpac_ri=getpixel(i_g+2+sizehalf,j_g-6);
	}
}
void ghost::gchase_smthin(int i,int j)   //needs improvment
{//ghost chase pacman and the ghosts retreat back to their home after the
 //pacman takes them out
	int x=i,y=j;
	if(i_g==213&&j_g==173)
	{
		if(d=='u')
		{
			if(number==2)
				d='r';
			else
				d='l';
		}
	}
	if(i_g==213&&j_g==221)
	{
		g_no=0;
		trans=1;
		if(number==0)
			color=2;
		else if(number==1)
			color=3;
		else if(number==2)
			color=4;
		else if(number==3)
			color=6;
		ioro=1;
	}
	else if(gright_top==1&&gright_bottom==1&&gleft_top==1&&gleft_bottom==1)
	{
		if(gright_mid==1&&gmid_top==1)
		{
			if(d=='r')
				d='d';
			else if(d=='u')
				d='l';
		}
		else if(gright_mid==1&&gmid_bottom==1)
		{
			if(d=='d')
				d='l';
			else if(d=='r')
				d='u';
		}
		else if(gmid_top==1&&gleft_mid==1)
		{
			if(d=='l')
				d='d';
			else if(d=='u')
				d='r';
		}
		else if(gmid_bottom==1&&gleft_mid==1)
		{
			if(d=='d')
				d='r';
			else if(d=='l')
				d='u';
		}
		else if(gmid_bottom==1&&gmid_top==1);
		else if(gleft_mid==1&&gright_mid==1);
		else if(gright_mid==1)
		{
			if(d=='u'||d=='d')
			{
				if(i_g>x)
					d='l';
			}
			else if(d=='r')
			{
				if(j_g>=y)
					d='u';
				else if(j_g<y)
					d='d';
			}
		}
		else if(gleft_mid==1)
		{
			if(d=='u'||d=='d')
			{
				if(i_g<x)
					d='r';
			}
			else if(d=='l')
			{
				if(j_g>=y)
					d='u';
				else if(j_g<y)
					d='d';
			}
		}
		else if(gmid_top==1)
		{
			if(trans==1&&i_g==213&&j_g==173);
			else if(d=='u')
			{
				if(i_g<=x)
					d='r';
				else if(i_g>x)
					d='l';
			}
			else if(d=='l'||d=='r')
			{
				if(j_g<y)
					d='d';
			}
		}
		else if(gmid_bottom==1)
		{
			if(d=='l'||d=='r')
			{
				if(j_g>y)
					d='u';
			}
			else if(d=='d')
			{
				if(i_g>=x)
					d='l';
				else if(i_g<x)
					d='r';
			}
		}
		else
		{
			if(d=='u'||d=='d')
			{

				{
					if(i_g<=x)
						d='r';
					else if(i_g>x)
						d='l';
				}
			}
			else if(d=='r'||d=='l')
			{
				{
					if(j_g>=y)
						d='u';
					else if(j_g<y)
						d='d';
				}
			}
		}
	}
}
void ghost::inhome()
{ //when the ghost is in the home
	int num=random(4);
	if(i_g==213)
	{
		if(num==0)
		{
			d='u';
			ioro=0;
		}
	}
	else if(i_g==167)
		d='r';
	else if(i_g==259)
		d='l';
	if(ioro!=0)
		moveghost();
}
void ghost::gwork(int i,int j)
{      //for ghosts to move differently in different situations
	if((color==6||color==4||color==3||color==2)&&ioro==0&&g_no==0) //when the ghost is alive
	{
		if(number== 2||(number==1&&abs(i-i_g)>50&&abs(j-j_g)>50)||(number==0&&abs(i-i_g)>100&&abs(j-j_g)>100))
			gchase_smthin(i,j);
		else
			gmove_rand();
	}
	else if(g_no==1&&trans==0)  //when ghost dies
	{
		gchase_smthin(213,221);    //coordinates of home
		moveghost();
	}
	else if(ioro==1)
		inhome();
	else if((color==9||color==15)&&ioro==0)  //while the ghost is vulnerable
	{
		if(count%2==0)
		{
			gmove_rand();
			moveghost(i,j);
		}
	}
	if(color!=9&&color!=15&&ioro==0)
		moveghost();
}
char game()
{  //main control
	pacman pac(210,365); //giving birth
	ghost g[4]; //giving birth
	maze(); //creating the world
	dots();
	ctrl_lives();
	info_at_game();
	pac.disp_still();
	g[0].addcolor(2);  //green
	g[1].addcolor(3);//cyan
	g[2].addcolor(4);//red
	g[3].addcolor(6);//brown
	count=0;
	while(count<=30)
	{
		if(count==2)
		{
			setcolor(WHITE);
			settextstyle(0,0,0);
			outtextxy(171,266,"GET READY !");
		}
		else if(count==30)
		{
			setcolor(BLACK);
			outtextxy(171,266,"GET READY !");
		}
		g[0].disp_still(213,231);
		g[1].disp_still(248,231);
		g[2].disp_still(213,173);
		g[3].disp_still(178,231);
		count++;
		delay(77);
	}
	count=0;
	char hit=0,command='l';
	char whatreturn;
	while(++count)
	{
		if(kbhit())
		{
			hit=getch();
			if(hit==key[0])
				command='u';
			else if(hit==key[1])
				command='d';
			else if(hit==key[2])
				command='l';
			else if(hit==key[3])
				command='r';
			else if(hit==27)
			{
				whatreturn=escscrn();
				if(whatreturn!='\0')
					return whatreturn;
				maze();
				dots();
				ctrl_lives();
				info_at_game();
				pac.disp_still();
				unsigned long xcount=count;
				while(count<=15+xcount)
				{
					g[0].disp_still();
					g[1].disp_still();
					g[2].disp_still();
					g[3].disp_still();
					if(count>=1+xcount&&count!=15+xcount)
					{
						setcolor(WHITE);
						settextstyle(0,0,0);
						outtextxy(171,266,"GET READY !");
					}
					else if(count==15+xcount)
					{
						setcolor(BLACK);
						outtextxy(171,266,"GET READY !");
						g[0].disp_still();
						g[1].disp_still();
						g[2].disp_still();
						g[3].disp_still();
					}
					count++;
					delay(110);
				}
				count=xcount;
			}
		}
		whatreturn=pac.move_ctrl(command);
		if(whatreturn=='P')
		{
			x0=g[0].reti();
			x1=g[1].reti();
			x2=g[2].reti();
			x3=g[3].reti();
			y0=g[0].retj();
			y1=g[1].retj();
			y2=g[2].retj();
			y3=g[3].retj();
			whatreturn=pac.move_ctrl(0);
			if(whatreturn!='\0')
				return whatreturn;
		}
		int ichase=pac.reti(),jchase=pac.retj();
		for(number=0;number<4;++number)
			g[number].gwork(ichase,jchase);
		if(changecolor==1)
		{
			g[0].addcolor(9);
			g[1].addcolor(9);
			g[2].addcolor(9);
			g[3].addcolor(9);
			changecolor=0;
		}
		if(score>=prevscr+10000)
		{ //if you score previous score + 10000, tou get a bonus life
			lives++;
			ctrl_lives();
			prevscr=score-(score%10000);
		}
		if(num_dots==0&&num_pow==0) //when number of dots become 0
		{
			level+=1;
			char number[3];
			delay(1000);
			setcolor(WHITE);
			settextstyle(0,0,0);
			outtextxy(185,266,"LEVEL");
			outtextxy(238,266,itoa(level,number,10));
			delay(1000);
			return 'r';
		}
	}
	return '\0';
}
void assconts(char k[])
{
	setcolor(WHITE);
	settextstyle(0,0,4);
	outtextxy(20,20,"ASSIGN CONTROLS");
	gotoxy(2,25);
	cout<<"           The new controls can be any character except ESCAPE KEY\n"
	    <<"                                                       \n"
	    <<"                                                       ";
	for(int i=0;i<4;i++)
	{
		char x;
		gotoxy(40,10+(i*3));
		cout<<"Enter Here     ";
		setcolor(15);
		rectangle(290,135+(i*48),445,165+(i*48));
		int flag;
		do
		{
			flag=0;
			x='A';
			x=getch();
			gotoxy(59,9+(i*3));
			cout<<"                         ";
			gotoxy(59,10+(i*3));
			cout<<"                   ";
			switch(x)
			{
				case 13:flag=1;
					break;
				default:
				if(x==k[0]||x==k[1]||x==k[2]||x==k[3])
				{
					gotoxy(59,9+(i*3));
					switch(x)
					{
						case 72:char d=30;
							cout<<d;
							break;
						case 77:d=16;
							cout<<d;
							break;
						case 75:d=17;
							cout<<d;
							break;
						case 80:d=31;
							cout<<d;
							break;
						default:cout<<x;
					}
					cout<<" is already assigned";
					gotoxy(59,10+(i*3));
					cout<<"Enter again!";
					flag=1;
				}
				else if(x==27)
				{
					gotoxy(59,9+(i*3));
					cout<<"Esc. is not allowed";
					gotoxy(59,10+(i*3));
					cout<<"Enter again!";
					flag=1;
				}
				else
				{
					gotoxy(40,10+(i*3));
					cout<<"               ";
					gotoxy(45,10+(i*3));
					switch(x)
					{
						case 72:char d=30;
							cout<<d;
							break;
						case 77:d=16;
							cout<<d;
							break;
						case 75:d=17;
							cout<<d;
							break;
						case 80:d=31;
							cout<<d;
							break;
						default:cout<<x;
					}
					gotoxy(59,9+(i*3));
					cout<<"VALID!";
					gotoxy(59,10+(i*3));
					cout<<"Press ENTER to assign";
					char y='\0';
					while(y!=13&&y!=8)
					{
						y=getch();
						if(y!=13&&y!=8)
						{
							gotoxy(59,9+(i*3));
							cout<<"Only 1 entry allowed!";
							gotoxy(59,10+(i*3));
							cout<<"Press ENTER to assign";
						}
						else if(y==8)
						{
							gotoxy(59,10+(i*3));
							cout<<"                         ";
							gotoxy(40,10+(i*3));
							cout<<"               ";
							gotoxy(40,10+(i*3));
							cout<<"Enter Here     ";
							flag=1;
							x='A';
						}
					}
					gotoxy(59,9+(i*3));
					cout<<"                                      ";
					gotoxy(59,10+(i*3));
					cout<<"                         ";
				}
			}
		}while(flag);
		k[i]=x;
		setcolor(0);
		rectangle(290,135+(i*48),445,165+(i*48));
	}
}
void main()
{
	clrscr();
	int mode,driver=DETECT;
	initgraph(&driver,&mode,"C:\\turboc3\\bgi");
	ifstream file("paccont.dat",ios::in|ios::binary);
	file.read((char*)&conts,sizeof(conts));
	if(file.fail())
	{
		file.close();
		ofstream ofile("paccont.dat",ios::out|ios::binary);
		conts.get();
		ofile.close();
	}
	else
	{
		conts.put();
		file.close();
	}
	char whatreturn,return2;
	whatreturn=start();
	while(whatreturn!='Y')
	{
	switch(whatreturn)
	{
		case 's':return2=start();
			break;
		case 'R':restart(1);
			return2=game();
			break;
		case 'r':restart(2);
			return2=game();
			break;
		case 'e':return2=gameends();
			break;
		case 'g':return2=game();
	}
	whatreturn=return2;
	}
	closegraph();
}
char start()
{  //first screen
	while(1)
	{
	cleardevice();
	const int ini=250,two=2,next=25,num=1;
	int j=ini,a=0,mouth=20,inc_dec=-1;
	unsigned long times=1;
	setcolor(1);
	line(0,90,640,90);
	line(0,172,640,172);
	setcolor(WHITE);
	settextstyle(0,0,6);
	outtextxy(145,112,"PA");
	outtextxy(325,112,"MAN");
	settextstyle(2,0,4);
	outtextxy(540,10,version);
	outtextxy(20,460,"UP and DOWN ARROW KEYS to move between the options");
	outtextxy(480,460,"ENTER to select an option");
	setcolor(BLUE);
	setfillstyle(1,BLUE);
	bar(210,ini,420,ini+17);
	setcolor(WHITE);
	settextstyle(0,0,2);
	outtextxy(220,ini+two,"PLAY GAME");
	outtextxy(220,ini+next+two,"INSTRUCTIONS");
	outtextxy(220,ini+two+(2*next),"CONTROLS");
	outtextxy(220,ini+two+(3*next),"HIGH SCORES");
	outtextxy(220,ini+two+(4*next),"ABOUT");
	outtextxy(220,ini+two+(5*next),"EXIT");
	char c;
	setcolor(YELLOW);
	setfillstyle(1,YELLOW);
	pieslice(280,131,0,360,40);
	setcolor(0);
	setfillstyle(1,0);
	pieslice(260,131,0,20,60);
	pieslice(260,131,340,360,60);
	while(times&&a!=1)
	{
		char whatreturn;
		if(times%5000==0)
		{
		if(mouth)
		{
			if(inc_dec==-1)
			{
				setcolor(YELLOW);
				setfillstyle(1,YELLOW);
				pieslice(258,131,mouth-1,mouth+2,60);
				pieslice(258,131,360-mouth-2,361-mouth,60);
			}
			setcolor(0);
			setfillstyle(1,0);
			pieslice(260,131,0,mouth,60);
			pieslice(260,131,360-mouth,360,60);
		}
		if(mouth==20)
			inc_dec=-1;
		else if(mouth==0)
			inc_dec=1;
		mouth+=inc_dec;
		}
		if(kbhit())
		{
			c=getch();
			if(c!=13)
				j=menu(j,next,ini,two,num,c);
			else
			{
				switch(j)
				{
					case ini:return 'R';
					case ini+next:instructions();
							break;
					case ini+(2*next):controls();
							break;
					case ini+(3*next):highscore();
							break;
					case ini+(4*next):about();
							break;
					case ini+(5*next):  whatreturn=Qexit();
						if(whatreturn!='\0')
							return whatreturn;
				}
			a=1;
			}
		}
		times++;
	}
	}
}
int menu(int j,const int next,const int ini,const int two,const int num,char c)
{
	int n;
	switch(num)
	{
		case 1: n=5;
			break;
		case 2: n=4;
			break;
		case 3: n=3;
	}
	settextstyle(0,0,2);
	setcolor(BLACK);
	setfillstyle(1,BLACK);
	bar(210,j,420,j+17);
	switch(c)
	{
		case 72:if(j==ini)
				j=ini+(n*next);
			else
				j-=next;
			break;
		case 80:if(j==ini+(n*next))
				j=ini;
			else
				j+=next;
	}
	setcolor(BLUE);
	setfillstyle(1,BLUE);
	bar(210,j,420,j+17);
	setcolor(WHITE);
	switch(num)
	{
		case 1:	outtextxy(220,ini+two,"PLAY GAME");
			outtextxy(220,ini+next+two,"INSTRUCTIONS");
			outtextxy(220,ini+two+(2*next),"CONTROLS");
			outtextxy(220,ini+two+(3*next),"HIGH SCORES");
			outtextxy(220,ini+two+(4*next),"ABOUT");
			outtextxy(220,ini+two+(5*next),"EXIT");
			break;
		case 2: outtextxy(220,ini+two,"RESUME");
			outtextxy(220,ini+two+next,"RESTART");
			outtextxy(220,ini+two+(2*next),"INSTRUCTIONS");
			outtextxy(220,ini+two+(3*next),"CONTROLS");
			outtextxy(220,ini+two+(4*next),"QUIT GAME");
			break;
		case 3:	outtextxy(220,ini+two,"PLAY AGAIN");
			outtextxy(220,ini+two+next,"MAIN MENU");
			outtextxy(220,ini+two+(2*next),"HIGH SCORES");
			outtextxy(220,ini+two+(3*next),"EXIT");
	}
	return j;
}
char escscrn()
{ //pause/escape screen
	while(1)
	{
	cleardevice();
	const int ini=150,two=2,next=25,num=2;
	int j=ini,a=0;
	setcolor(BLUE);
	setfillstyle(1,BLUE);
	bar(210,ini,420,ini+17);
	setcolor(WHITE);
	settextstyle(2,0,4);
	outtextxy(20,460,"UP and DOWN ARROW KEYS to move between the options");
	outtextxy(480,460,"ENTER to select an option");
	settextstyle(0,0,2);
	outtextxy(220,ini+two,"RESUME");
	outtextxy(220,ini+two+next,"RESTART");
	outtextxy(220,ini+two+(2*next),"INSTRUCTIONS");
	outtextxy(220,ini+two+(3*next),"CONTROLS");
	outtextxy(220,ini+two+(4*next),"QUIT GAME");
	while(a!=1)
	{
		if(kbhit())
		{
			char c;
			c=getch();
			if(c!=13)
				j=menu(j,next,ini,two,num,c);
			else
			{
				switch(j)
				{
					case ini:	return '\0';
					case ini+next:	return 'R';   //restart(1)
					case ini+(2*next):instructions();
							break;
					case ini+(3*next):controls();
							break;
					case ini+(4*next):return 's'; //start();
				}
			a=1;
			}
		}
	}
	}
}
void controls()
{
	cleardevice();
	setcolor(WHITE);
	settextstyle(0,0,4);
	outtextxy(20,20,"CONTROLS");
	for(int i=0;i<4;i++)
	{
		switch(i)
		{
			case 0:gotoxy(20,10);
				cout<<"MOVE UP        -";
				gotoxy(45,10);
				break;
			case 1:gotoxy(20,13);
				cout<<"MOVE DOWN      -";
				gotoxy(45,13);
				break;
			case 2:gotoxy(20,16);
				cout<<"MOVE LEFT      -";
				gotoxy(45,16);
				break;
			case 3:gotoxy(20,19);
				cout<<"MOVE RIGHT     -";
				gotoxy(45,19);
		}
		switch(key[i])
		{
			case 72:char d=30;
				cout<<d;
				break;
			case 77:d=16;
				cout<<d;
				break;
			case 75:d=17;
				cout<<d;
				break;
			case 80:d=31;
				cout<<d;
				break;
			default:cout<<key[i];
		}
	}
	setcolor(WHITE);
	rectangle(140,120,450,320);
	rectangle(136,116,454,324);
	gotoxy(10,25);
	cout<<"                 PRESS\n"
	    <<"                        ->ENTER to change controls\n"
	    <<"                        ->ANY OTHER key to exit";
	char a;
	a=getch();
	if(a==13)
	{
		setcolor(0);
		settextstyle(0,0,4);
		outtextxy(20,20,"CONTROLS");
		char k[4];
		char b='a';
		while(b=='a')
		{
			if(b=='a')
			{
				gotoxy(2,24);
				cout<<"                                         \n"
				    <<"                                                                               \n"
				    <<"                                            \n"
				    <<"                                                          ";
				k[0]='\0';
				k[1]='\0';
				k[2]='\0';
				k[3]='\0';
				gotoxy(40,10);
				cout<<"               ";
				gotoxy(40,13);
				cout<<"               ";
				gotoxy(40,16);
				cout<<"               ";
				gotoxy(40,19);
				cout<<"               ";
				assconts(k);
				gotoxy(2,24);
				cout<<"                                PRESS\n"
				    <<"                    ->ENTER to save controls                                   \n"
				    <<"                    ->'a' to enter again\n"
				    <<"                    ->ANY OTHER key to exit without saving";
				b=getch();
			}
			if(b==13)
			{
				key[0]=k[0];
				key[1]=k[1];
				key[2]=k[2];
				key[3]=k[3];
				ofstream file("paccont.dat",ios::out|ios::binary);
				conts.get();
				file.write((char*)&conts,sizeof(conts));
				file.close();
			}
		}
	}
}
void scorefile()
{  //adds and sorts highscores to score.dat
	data a;
	ifstream file("score.dat",ios::in|ios::binary);
	int found=0;
	file.read((char*)&a,sizeof(a));
	if(file.fail())
	{
		file.close();
		ofstream nfile("score.dat",ios::out|ios::binary);
		a.get();
		nfile.write((char*)&a,sizeof(a));
		nfile.close();
	}
	else
	{
		data h[11];
		int i=0;
		h[0]=a;
		while(!file.eof())
		{
			++i;
			file.read((char*)&h[i],sizeof(h[i]));
		}
		--i;
		file.close();
		if(i==0)
		{
			if(h[i].retscore()<score)
			{
				h[i+1]=h[i];
				h[i].get();
			}
			else
				h[i+1].get();
			++i;
		}
		else
		{
			if(h[i].retscore()<score)
			{
				for(int x=i;x>=0;--x)
				{
					if(h[x].retscore()>=score)
					{
						h[x+1].get();
						found=1;
						break;
					}
					else
						h[x+1]=h[x];
				}
				if(found==0)
					h[0].get();
			}
			else if(i!=9)
				h[i+1].get();
			if(i<9)
				i++;
		}
		ofstream nfile("score.dat",ios::out|ios::binary);
		for(int y=0;y<=i;++y)
			nfile.write((char*)&h[y],sizeof(data));
		nfile.close();
	}
}
void highscore()
{  //screen of highscores
	cleardevice();
	setcolor(15);
	data a;
	setcolor(WHITE);
	settextstyle(0,0,1);
	outtextxy(10,460,"Press any key to EXIT");
	settextstyle(0,0,2);
	ifstream file("score.dat",ios::in|ios::binary);
	file.read((char*)&a,sizeof(a));
	if(file.fail())
	{
		setcolor(WHITE);
		outtextxy(200,150,"No highscores!!!");
		file.close();
		getch();
	}
	else
	{
		int col=0;
		setbkcolor(col);
		int j=60;
		setcolor(WHITE);
		setfillstyle(1,WHITE);
		bar(0,0,640,40);
		setcolor(0);
		setfillstyle(1,0);
		bar(97,10,165,30);
		bar(417,10,505,30);
		setcolor(15);
		outtextxy(100,13,"NAME");
		outtextxy(420,13,"SCORE");
		setcolor(WHITE);
		while(!file.eof())
		{
			if(j<=140)
			{
				setcolor(WHITE);
				setfillstyle(1,WHITE);
				bar(0,j-3,640,j+17);
				setcolor(col);
			}
			else if(j==180)
				setcolor(WHITE);
			a.put(j);
			j+=40;
			file.read((char*)&a,sizeof(a));
		}
		file.close();
		setcolor(15);
		settextstyle(0,0,1);
		outtextxy(370,460,"Press 'd' to Delete High Scores");
		char x=getch();
		if(x==100)
		{
			cleardevice();
			settextstyle(3,0,2);
			outtextxy(220,200,"Are you sure ?(y/n) :");
			do
			{
				x=getch();
				if(x==121)
				{
					remove("score.dat");
					cleardevice();
					outtextxy(220,200,"High Scores Deleted!");
					delay(1500);
				}
			}while(x!=121&&x!=110);
		}
	}
	setbkcolor(BLACK);
}
char gameends()
{  //screen after you lose
	while(1)
	{
	cleardevice();
	const int ini=200,two=2,next=25,num=3;
	int j=ini,a=0;
	setcolor(BLUE);
	setfillstyle(1,BLUE);
	bar(210,ini,420,ini+17);
	setcolor(WHITE);
	settextstyle(2,0,4);
	outtextxy(20,460,"UP and DOWN ARROW KEYS to move between the options");
	outtextxy(548,460,"ENTER to select an option");
	settextstyle(0,0,2);
	outtextxy(220,ini+two,"PLAY AGAIN");
	outtextxy(220,ini+two+next,"MAIN MENU");
	outtextxy(220,ini+two+(2*next),"HIGH SCORES");
	outtextxy(220,ini+two+(3*next),"EXIT");
	while(a!=1)
	{
		char whatreturn;
		if(kbhit())
		{
			char c;
			c=getch();
			if(c!=13)
				j=menu(j,next,ini,two,num,c);
			else
			{
				switch(j)
				{
					case ini:	return 'R';
					case ini+next:	return 's';
					case ini+(2*next):highscore();
							break;
					case ini+(3*next):whatreturn=Qexit();
							if(whatreturn!='\0')
								return whatreturn;
				}
			a=1;
			}
		}
	}
	}
}
void ctrl_lives()     //1=regenerate lives    2=increase lives
{
	setcolor(WHITE);
	settextstyle(0,0,1);
	outtextxy(435,134,"LIVES :");
	setlinestyle(0,1,2);
	setcolor(1);
	line(440,118,630,118);                            //right side
	for(int i=0;i<lives+1;++i)
	{
		setcolor(BLACK);
		setfillstyle(1,BLACK);
		pieslice(510+(i*24),137,0,360,10);
	}
	for(i=0;i<lives;i++)
	{
		setcolor(YELLOW);
		setfillstyle(1,YELLOW);
		pieslice(510+(i*24),137,0,360,10);
		setcolor(0);
		setfillstyle(1,0);
		pieslice(506+(i*24),137,0,30,14);
		pieslice(506+(i*24),137,330,360,14);
	}
}
void info_at_game()
{
	setcolor(15);
	settextstyle(0,0,1);
	outtextxy(435,460,"Press Esc. to PAUSE/EXIT");
	settextstyle(0,0,2);
	outtextxy(463,7,"HIGHSCORE");
	outtextxy(463,70,"SCORE");
	char string[20];
	outtextxy(463,93,itoa(score,string,10));
	if(hg_scr>=score)
	{
		ifstream file("score.dat",ios::in|ios::binary);
		data d;
		file.read((char*)&d,sizeof(d));
		if(file.fail())
		{
			settextstyle(0,0,1);
			outtextxy(463,30,"No Highscore!!!");
		}
		else
		{
			hg_scr=d.retscore();
			settextstyle(0,0,2);
			outtextxy(463,30,itoa(hg_scr,string,10));
		}
		file.close();
	}
	else
		outtextxy(463,30,itoa(score,string,10));
	setcolor(1);
	line(440,60,630,60);
}
void instructions()
{
	cleardevice();
	char hit;
	int poly[]={590,450,590,460,610,460,610,465,620,455,610,445,610,450,590,450};
	for(int i=0;hit!=27&&i<=3;i++)
	{
		hit=1;
		setcolor(WHITE);
		settextstyle(0,0,1);
		drawpoly(8,poly);
		setfillstyle(1,15);
		floodfill(592,452,15);
		outtextxy(20,460,"Press Esc. to EXIT");
		if(i==0)
		{
			setcolor(WHITE);
			settextstyle(0,0,4);
			outtextxy(1,20,"GENERAL INSTRUCTIONS");
			settextstyle(2,0,7);
			outtextxy(30,70,"When the game starts, just sit back and do nothing.");
			outtextxy(60,93,"You win, if the handsome ghosts eat you.");
			outtextxy(60,116,"No problem if the screen says GAME OVER(it is");
			outtextxy(60,139,"due to technical problems), pleasing the ghosts");
			outtextxy(60,162,"is the target of the game.");
			outtextxy(30,185,"Don't dare to eat bigger dots, if you eat it,you lose");
			outtextxy(60,208,"(the ghosts turning blue means you lose).");
			outtextxy(320,443,"Instructions (seriously)");
			settextstyle(2,0,5);
			outtextxy(170,270,"-These general instructions are brought to you by THE GHOSTS.");
		}
		else if(i==1)
		{
			setcolor(WHITE);
			settextstyle(0,0,4);
			outtextxy(30,20,"INTRODUCTION");
			settextstyle(1,0,2);
			outtextxy(30,60,"CHARACTERS :-");
			outtextxy(30,210,"TARGET :-");
			settextstyle(2,0,5);
			outtextxy(175,175,"PACMAN");
			outtextxy(453,175,"GHOST");
			settextstyle(2,0,7);
			outtextxy(30,240,"The target of the player is to EAT UP the WHITE DOTS");
			outtextxy(60,263,"on the MAZE. You have to dodge the GHOSTS as they");
			outtextxy(60,286,"come to eat you.");
			outtextxy(30,320,"When your player gobbles up ALL the DOTS, you are");
			outtextxy(60,343,"PROMOTED to the NEXT LEVEL and THE GAME continues");
			outtextxy(60,366,"FOREVER (most probably).");
			settextstyle(8,0,5);
			outtextxy(510,110,"x4");
			setcolor(YELLOW);
			setfillstyle(1,YELLOW);
			pieslice(200,143,0,360,30);
			setcolor(RED);
			setfillstyle(1,RED);
			pieslice(470,143,0,180,30);
			int poly[20]={440,143,440,173,450,161,460,173,470,161,480,173,490,161,500,173,500,143,440,143};
			drawpoly(10,poly);
			floodfill(446,150,RED);
			setcolor(WHITE);
			setfillstyle(1,WHITE);
			pieslice(455,143,0,360,7);
			pieslice(485,143,0,360,7);
			setcolor(BLACK);
			setfillstyle(1,BLACK);
			pieslice(185,143,0,20,45);
			pieslice(185,143,340,360,45);
			pieslice(455,140,0,360,5);
			pieslice(485,140,0,360,5);
		}
		else if(i==2)
		{
			setcolor(WHITE);
			settextstyle(0,0,4);
			outtextxy(30,20,"MORE");
			settextstyle(2,0,7);
			outtextxy(30,70,"Now! since you know how to move, you should also");
			outtextxy(60,93,"learn how to SURVIVE:");
			outtextxy(30,120,"If the GHOST TOUCHES your player - the PLAYER");
			outtextxy(60,143,"LOSSES one of its 3 LIVES. As simple as that!");
			outtextxy(30,170,"No worries! You are not the only one who can be");
			outtextxy(60,193,"pounded upon. On the maze there also are some");
			outtextxy(60,216,"BIGGER DOTS which are POWER UPS. On eating");
			outtextxy(60,239,"this high protein diet the player ATTAINS a");
			outtextxy(60,262,"TEMPORARY ABILITY to KNOCK OUT the GHOSTS, after");
			outtextxy(60,285,"which the ghosts retreat BACK to their HOME where");
			outtextxy(60,308,"they REGENERATE to their NORMAL FORM.");
		}
		else
		{
			setcolor(BLACK);
			setfillstyle(1,BLACK);
			bar(590,445,620,465);
			setcolor(WHITE);
			settextstyle(0,0,3);
			outtextxy(185,160,"Well then,");
			outtextxy(100,200,"Let's Play PACMAN");
		}
		do
		{

			if(kbhit())
				hit=getch();
		}while(hit!=77&&hit!=27);
		cleardevice();
	}
}
void about()
{
	cleardevice();
	int base=15;
	setcolor(WHITE);
	settextstyle(2,0,4);
	outtextxy(540,10,version);
	outtextxy(10,465,"Press any key to EXIT");
	settextstyle(0,0,2);
	outtextxy(0,170,"PACMAN") ;
	settextstyle(2,0,6);
	outtextxy(95,167,",'a milestone in the journey of video games' recreated by");
	outtextxy(130,360,"Originally created by");
	settextstyle(2,0,8);
	outtextxy(338,354,"Toru Iwatani");
	setcolor(base);
	settextstyle(10,0,6);
	outtextxy(0,160,"HARSHIT GUPTA");
	setfillstyle(2,1);
	floodfill(5,210,base); //H
	setfillstyle(3,2);
	floodfill(67,210,base);//A
	setfillstyle(9,3);
	floodfill(115,210,base); //R
	setfillstyle(7,4);
	floodfill(162,210,base); //S
	setfillstyle(6,5);
	floodfill(216,210,base); //H
	setfillstyle(5,6);
	floodfill(271,210,base);  //I
	setfillstyle(8,7);
	floodfill(310,210,base);  //T
	setfillstyle(4,8);
	floodfill(386,210,base);   //G
	setfillstyle(10,9);
	floodfill(440,210,base);    //U
	setfillstyle(8,14);
	floodfill(486,210,base);    //P
	setfillstyle(7,15);
	floodfill(552,210,base);    //T
	setfillstyle(9,12);
	floodfill(610,210,base);    //A
	setcolor(0);
	outtextxy(0,160,"HARSHIT GUPTA");
	getch();
}
char Qexit()
{
	const int hori=127,ini=130,diff=240,flag=7;
	int i=ini,notyet=1;
	cleardevice();
	setcolor(WHITE);
	settextstyle(2,0,4);
	outtextxy(20,460,"LEFT and RIGHT ARROW KEYS to move between the options");
	outtextxy(480,460,"ENTER to select an option");
	settextstyle(0,0,5);
	outtextxy(70,100,"Are you sure?");
	settextstyle(2,0,8);
	outtextxy(130,260,"Do you realy want to EXIT?");
	setfillstyle(1,BLACK);
	bar3d(i+diff,355,i+diff+hori,385,flag,1);
	bar3d(i,355,i+hori,385,flag,1);
	setfillstyle(1,BLUE);
	bar(i+1,356,i+hori-1,384);
	setcolor(WHITE);
	settextstyle(0,0,3);
	outtextxy(170,360,"No");
	outtextxy(400,360,"Yes");
	while(notyet)
	{
		char hit=0;
		if(kbhit())
		{
			hit=getch();
			switch(hit)
			{
/*right*/			case 77:setfillstyle(1,BLACK);
					bar(i+1,356,i+hori-1,384);
					if(i==ini)
						i+=diff;
					setcolor(WHITE);
					setfillstyle(1,BLUE);
					bar(i+1,356,i+hori-1,384);
					outtextxy(170,360,"No");
					outtextxy(400,360,"Yes");
					break;
				case 75:setfillstyle(1,BLACK);
					bar(i+1,356,i+hori-1,384);
					if(i==ini+diff)
						i-=diff;
					setcolor(WHITE);
					setfillstyle(1,BLUE);
					bar(i+1,356,i+hori-1,384);
					outtextxy(170,360,"No");
					outtextxy(400,360,"Yes");
					break;
				case 13:
					setcolor(BLACK);
					setfillstyle(1,BLACK);
					bar(i,340,i+hori+15,385);
					setfillstyle(1,BLUE);
					setcolor(WHITE);
					bar(i+flag,345,i+hori+flag,375);
					rectangle(i+flag,345,i+hori+flag,375);
					if(i==ini+diff)
					{
						outtextxy(410,350,"Yes");
						delay(200);
						setfillstyle(1,BLACK);
						bar(i+flag,345,i+hori+flag,375);
						setfillstyle(1,BLUE);
						bar3d(i,355,i+hori,385,flag,1);
						outtextxy(400,360,"Yes");
						delay(200);
						closegraph();
						return 'Y';
					}
					else
					{
						outtextxy(180,350,"No");
						delay(200);
						setfillstyle(1,BLACK);
						bar(i+flag,345,i+hori+flag,375);
						setfillstyle(1,BLUE);
						bar3d(i,355,i+hori,385,flag,1);
						outtextxy(170,360,"No");
						delay(200);
						notyet=0;
						return '\0';
					}
			}
		}
	}
	return '\0';
}