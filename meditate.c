/* meditate.c - causes computer to meditate */
/* By Sean Clay - Version 1.0 - May 11, 1991 */
/* Rev. 1.1 - June 28, 1991 - fix timing problem on some machines */


#include <graphics.h>
#include <timer.h>
#include <dos.h>
#include <bioslib.h>

int maxx, maxy, mode, driver, gerror,
    left, top, right, bottom;
int repeat = 2;


main(int argc, int *argv[])
{
	driver = CGA;
	mode = CGAC0;
	initgraph(&driver, &mode,"");
	gerror = graphresult();
	maxx = getmaxx();
	maxy = getmaxy();
	left = top = 0;
	right = maxx;
	bottom = maxy;

	if ( argc > 1 )
		repeat = atoi(argv[1]);		/* # of repeats */
		{
		gscreen();  	/* use graphics version */
		}
	beg();			/* beg for money */

} /* end main */

 /*********************************************************************
  *  delayx -- provide a machine independent delay of ** aproximately **
  *  the specified duration.
  *
  *  Sysnopsis:
		    void delayx(d)
		    float d;

  *  Description:
  *  The delayx() function loops to waste the specified number
  *  of seconds and fractional seconds.  The delay has a practical
  *  resolution of about .06 seconds.  - Gary Kendrick
  */

 void delayx(float d)

 {
      long ticks, then;
      extern long getticks();

      /* converts duration into PC clock ticks */
      ticks = d * TICKRATE;

      /* delay for specified interval */
         then = getticks() + ticks;
         while(1)
               if (getticks() >= then)
               break;
 }
/*
 *       getticks -- get the current bios to clock ticks value
 */

 long getticks()
 {
         long count;
         union REGS inregs, outregs;

 /* get BIOS time of day as Number of ticks since midnight */
         inregs.h.ah = 0;
         int86(TOD, &inregs, &outregs);

         /* correct for change of day or midnite passed */
         count = (outregs.h.al != 0) ? 0x01800B0L : 0;

	/* add current day ticks */
         count += (outregs.x.dx + (outregs.x.cx << 16));

         return (count);
 }
/**********************************************************************/

 gscreen()
{
	setcolor(1);
	rectangle(left, top, right, bottom);
	rectangle(left+3, top+3, right-3, bottom-3);
	face1();
	delayx(2.00);
	eyes_close();
	meditate();
	eyes_open();
	face2();
	delayx(4.00);
	closegraph();
} /* end gscreen */

face1()		/* draw face */
{
	int x = maxx/2;
	int y = maxy/2;
	setcolor(3);
	circle(x, y, y-10);
	setfillstyle(1,3);
	floodfill(x, y, 3);
	setcolor(0);
	setfillstyle(1,0);
	circle(x-25, y-15, 20);
	circle(x+25, y-15, 20);
	floodfill(x-25, y-15, 0);
	floodfill(x+25, y-15, 0);
	line(x-25,y+30,x+25,y+30);
	setcolor(1);
	circle(x-25, y-15, 5);
	circle(x+25, y-15, 5);
	setfillstyle(1,1);
	floodfill(x+25, y-15, 1);
	floodfill(x-25, y-15, 1);
} /* end face1 */

face2()		/* draw smiling face */
{
	int x = maxx/2;
	int y = maxy/2;
	setcolor(3);
	circle(x, y, y-10);
	setfillstyle(1,3);
	floodfill(x, y, 3);
	setcolor(0);
	setfillstyle(1,0);
	circle(x-25, y-15, 20);
	circle(x+25, y-15, 20);
	floodfill(x-25, y-15, 0);
	floodfill(x+25, y-15, 0);
	arc(x,y+5,225,315,50);
	setcolor(1);
	circle(x-25, y-15, 5);
	circle(x+25, y-15, 5);
	setfillstyle(1,1);
	floodfill(x+25, y-15, 1);
	floodfill(x-25, y-15, 1);
} /* end face2 */

eyes_close()	/* close the eyes */
{
	int i;
	int x = maxx/2;
	int y = maxy/2;
	setcolor(3);
	setfillstyle(1,3);
	for (i=y-30; i < y-15; i++)  {
	    circle(x+25, i, 20);
	    circle(x-25, i, 20);
	    floodfill(x-25, i, 3);
	    floodfill(x+25, i, 3);
	    delayx(0.10);
	}
} /* end eyes_close() */

meditate()	/* move mouth & chant */
{
	int j,i;
	int x = maxx/2;
	int y = maxy/2;
	for(i=0; i<repeat; i++)  {
	   setcolor(0);
	   ellipse(x,y+30,0,360,25,10);
	   setfillstyle(1,0);
	   floodfill(x,y+32,0);
	   floodfill(x,y+28,0);
	   sound(50);
	   delayx(0.80);
	   for (j=50; j<75; j++)   {
	      delayx(0.10);
	      sound(j);
	   }
	   setfillstyle(1,3);
	   floodfill(x,y+30,3);
	   setcolor(0);
	   line(x-25,y+30,x+25,y+30);
	   delayx(0.40);
	   nosound();
	   floodfill(x,y+30,3);
	} /* end repeat */
} /* end meditate */

eyes_open()	/* wake up! */
{
	int i;
	int x = maxx/2;
	int y = maxy/2;
	for (i=0; i < 3; i++)  {
	   setcolor(3);
	   setfillstyle(1,3);
	   circle(x+25, y-15, 20);
	   circle(x-25, y-15, 20);
	   floodfill(x-25, y-15, 3);
	   floodfill(x+25, y-15, 3);
	   setcolor(0);
	   setfillstyle(1,0);
	   circle(x-25, y-15, 20);
	   circle(x+25, y-15, 20);
	   floodfill(x-25, y-15, 0);
	   floodfill(x+25, y-15, 0);
	   setcolor(1);
	   circle(x-25, y-15, 5);
	   circle(x+25, y-15, 5);
	   setfillstyle(1,1);
	   floodfill(x+25, y-15, 1);
	   floodfill(x-25, y-15, 1);
	}
} /* end eyes_open */

beg()      	/* beg for money for this program */
{
	clrscr();
	box(5,1,75,4);
	gotoxy(26,2);
	printf("Computer Meditation Program");
	gotoxy(28,3);
	printf("Copyright 1991 - CLAYCO");
	gotoxy(10,7);
	printf("You may copy this program and share it with your friends.");
	gotoxy(10,8);
	printf("If you make use of this software, you are expected to");
	gotoxy(10,9);
	printf("pay a one time registration fee.  Please send $10 to:");
	gotoxy(30,11);
	printf("     CLAYCO");
	gotoxy(30,12);
	printf("2572 Yucca Mesa Road");
	gotoxy(30,13);
	printf("Yucca Valley, Ca. 92284");
	gotoxy(30,14);
	printf(" (619) 365-9385");
	box(10,17,70,21);
	gotoxy(13,18);
	printf("Upon receipt of your registration fee, you will receive");
	gotoxy(13,19);
	printf("a diskette with the latest version of the software");
	gotoxy(13,20);
	printf("and source code in C.");
	gotoxy(0,23);
} /* end beg */

/* box.c - draws a box per users request */
box(x1,y1,x2,y2)
  int x1,y1,x2,y2;
  {
  int i;
  gotoxy(x1,y1);
  printf("\xC9");
  gotoxy(x1,y2);
  printf("\xC8");
  for (i=x1+1; i<x2; i++)
    {
    gotoxy(i,y1);
    printf("\xCD");
    gotoxy(i,y2);
    printf("\xCD");
    }
  gotoxy(x2,y1);
  printf("\xBB");
  gotoxy(x2,y2);
  printf("\xBC");
  for (i=y1+1; i<y2; i++)
    {
    gotoxy(x1,i);
    printf("\xBA");
    gotoxy(x2,i);
    printf("\xBA");
    }
  } /* end box */