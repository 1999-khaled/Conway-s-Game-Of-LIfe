#include<GL/glut.h>
#include <stdio.h>
#include<string.h>
int phyWidth= 700;
int phyHeight= 700;
int logWidth=100;
int logHeight=100;
int centerX=logWidth/2;
int centerY=logHeight/2;
int mouseXX,mouseYY;
int stat=0;
int s=0;
int **status;
int **statusNew;
int size=51;
bool clear = false;
bool randomize=false;
int nCount=0;
int liveCells=0;
bool secpage=false;
void drawGrid();
void cellAlive(int x,int y);




void FPS(int val){
	glutPostRedisplay();
	glutTimerFunc(300, FPS, 0); // 1sec = 1000, 60fps = 1000/60 = ~17
}



int randomNum(){//random number between 1 and N-1
  int num=rand()%(size-2);
  num+=1;
  return num;
}
void drawCellsInitial(){//intially spawns a few cells to grid

	for(int cellX=0;cellX<size;cellX++){
			for(int cellY=0;cellY<size;cellY++){
				statusNew[cellX][cellY]=0;
				if((rand()%2)==1){//if a live cell found then draw it
					status[cellX][cellY]=0;
				}
				else{
					status[cellX][cellY]=1;
				}
			}
	}
}
void drawGrid(){
	glPointSize(1.0);
	glColor3f(0,0,0);
	glBegin(GL_LINES);
		for(int i=0;i<size;i++){
				glVertex2f(0,i+1);
				glVertex2f(size,i+1);
				glVertex2f(i+1,0);
				glVertex2f(i+1,size);
		}
	glEnd();

	}

int checkNeighbours(int nCount,int cellX, int cellY){
	nCount=0;
	if(status[cellX-1][cellY]==1){nCount++;}
	if(status[cellX+1][cellY]==1){nCount++;}
	if(status[cellX][cellY-1]==1){nCount++;}
	if(status[cellX][cellY+1]==1){nCount++;}
	if(status[cellX-1][cellY+1]==1){nCount++;}
	if(status[cellX+1][cellY+1]==1){nCount++;}
	if(status[cellX-1][cellY-1]==1){nCount++;}
	if(status[cellX+1][cellY-1]==1){nCount++;}

	return nCount;
}


void cellAlive(int x,int y){
		glBegin(GL_POLYGON);
		glColor3f(0,0,1);
		glVertex2f(x,y);
		glVertex2f(x+1,y);
		glVertex2f(x+1,y+1);
		glVertex2f(x,y+1);
		glEnd();

}


void clearBoard(){
	for(int cellX=0;cellX<size;cellX++){
		for(int cellY=0;cellY<size;cellY++){
			status[cellX][cellY]=0;
			statusNew[cellX][cellY]=0;
		}
	}
}



void drawCells(){
		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				if((status[i][j])==1){
					cellAlive(i,j);
				}
			}
		}
}



void rules(){

		for(int cellX=1;cellX<size-1;cellX++){
			for(int cellY=1;cellY<size-1;cellY++){
				int n=checkNeighbours(nCount,cellX,cellY);
				if(n==3 && (status[cellX][cellY]==0)){
					statusNew[cellX][cellY]=1;
					liveCells++;
				}else if( (n==2 && (status[cellX][cellY]==1)) || (n==3 && (status[cellX][cellY]==1)) ){
					statusNew[cellX][cellY]=1;
				}else if(n<2 && (status[cellX][cellY]==1)){
					statusNew[cellX][cellY]=0;
					liveCells--;
				}else if(n>3 && (status[cellX][cellY]==1)){
					statusNew[cellX][cellY]=0;
					liveCells--;
				}
			}
		}

		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				status[i][j]=statusNew[i][j];
			}
		}
}















void printSome(char *str,int x,int y) {
glColor3f (1.0, 1.0, 1.0);
glRasterPos2d(38,75);
for (int i=0;i<strlen(str);i++)
glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
glFlush();
}

void printSomeplay(char *str,int x,int y) {
glColor3f (0.3, 0.4, 0.6);
glRasterPos2d(46,57);
for (int i=0;i<strlen(str);i++)
glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
glFlush();
}

void printSomequit(char *str,int x,int y) {
glColor3f (0.3, 0.4, 0.6);
glRasterPos2d(46,27);
for (int i=0;i<strlen(str);i++)
glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
glFlush();
}


void init2D()
{

glClearColor( 0.8, 0.8, 1.0, 1.0); // COLOR
glMatrixMode( GL_PROJECTION);
gluOrtho2D( 0.0, logWidth, 0.0, logHeight);

}




void Display(){

glClearColor(1,1,1,1);
glClear(GL_COLOR_BUFFER_BIT);
drawGrid();
rules();


glutSwapBuffers();

glFlush();

}





void startDisplay()
{

    if(stat==0){
             init2D();

glClear( GL_COLOR_BUFFER_BIT);

glColor3f(1.0, 1.0, 1.0);
glBegin(GL_QUADS);

glVertex2i(40,63);
glVertex2i(57,63);
glVertex2i(57,53);
glVertex2i(40,53);

glEnd();

glBegin(GL_QUADS);

glVertex2i(40,33);
glVertex2i(57,33);
glVertex2i(57,23);
glVertex2i(40,23);

glEnd();

glColor3f (0.3, 0.4, 0.6);
glBegin(GL_LINE_LOOP);
glVertex2i(40,33);
glVertex2i(57,33);
glVertex2i(57,23);
glVertex2i(40,23);

glEnd();

glBegin(GL_LINE_LOOP);
glVertex2i(40,63);
glVertex2i(57,63);
glVertex2i(57,53);
glVertex2i(40,53);

glEnd();


printSome("Conway's game of life",centerX,centerY);

glColor3f(1.0, 1.0, 0);
printSomeplay("Play",centerX,centerY);
printSomequit("Quit",centerX,centerY);
// ...................................
}
else if(stat==1){
glutDisplayFunc(Display);
secpage=true;
glEnd();

}
else if(stat==2){
    exit(1);
    glEnd();

}
glutSwapBuffers();
glFlush();

}
void keyb(int key, int x, int y)
{
    if(key ==GLUT_KEY_UP){
clear=false;
printf("start.." );
drawCellsInitial();
glClearColor(1,1,1,0);
glClear(GL_COLOR_BUFFER_BIT);
drawCells();
drawGrid();
glFlush();

    }
    if(key == GLUT_KEY_RIGHT){

printf("right.." );
rules();


    }
    if(key ==GLUT_KEY_F1){
        printf("clear..");
        clear=true;

    }
    if(key==GLUT_KEY_F2){
      glutDisplayFunc(startDisplay);
secpage=false;

    }


}
void keys(unsigned char key,int x,int y){

if(key=='x'){
glutDisplayFunc(Display);

}
glutPostRedisplay();

}
void mouseClick(int btn, int state, int x, int y)
{if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
{ mouseXX = x;
mouseXX=0.5+1.0*mouseXX*logWidth/phyWidth;
mouseYY = phyHeight - y;
mouseYY=0.5+1.0*mouseYY*logHeight/phyHeight;
if( mouseXX>=(40) && mouseXX<=(57) && mouseYY >=(53) && mouseYY <=(63))
{
stat=1;
}
if( mouseXX>=(40) && mouseXX<=(57) && mouseYY >=(23) && mouseYY <=(33))
{
stat=2;
}

glutPostRedisplay();
}
}
int main( int argc, char ** argv)
{

    printf("\n%s\n","     	    Welcome!" );
	printf("\n%s\n","---Press F1 to clear the screen\n" );
	printf("%s\n","---Press up key to place initial cells\n" );
	printf("%s\n","---Press right key to move to next generation\n" );
	printf("%s\n","---Press F2 to go back to menu" );
	status = (int **)malloc(size*sizeof(int *));
	statusNew = (int **)malloc(size*sizeof(int *));
	for(int i=0;i<size;i++){
		status[i] = (int *)malloc(size*sizeof(int));
		statusNew[i] = (int *)malloc(size*sizeof(int));
	}
glutInit( &argc, argv);
glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
glutInitWindowPosition( 500, 100);
glutInitWindowSize(phyWidth, phyHeight);
glutCreateWindow( "Conway's game of life");
glutSpecialFunc(keyb);
glutDisplayFunc(startDisplay);
glutKeyboardFunc(keys);
glutMouseFunc(mouseClick);
glutMainLoop();
}
