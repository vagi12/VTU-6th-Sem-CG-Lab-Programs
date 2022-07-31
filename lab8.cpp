#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#define PI 3.1416
float theta=0;
struct point{
        GLfloat x,y,z;
};
int factorial(int n){
        if(n<=1)
                return(1);
        else
                n=n*factorial(n-1);
        return n;
}
void computeNcR(int n, int *ncr){
        int r;
        for(r=0;r<=n;r++){
                ncr[r]=factorial(n)/(factorial(n-r)*factorial(r));
        }
}
void computeBezierPoints(float t, point *bp,int cp,point *a,int *ncr){
        int i,n=cp-1;
        float poly;
        bp ->x=0;
        bp ->y=0;
        bp ->z=0;
        for(i=0;i<cp;i++){
                poly=ncr[i]*pow(t,i)*pow(1-t,n-i);
                bp->x+=poly*a[i].x;
                bp->y+=poly*a[i].y;
                bp->z+=poly*a[i].z;
        }
}
void Bezier(point *a,int cp,int nbp){
        point bp;
        float t;
        int *ncr,i;
        ncr=new int[cp];//to hold  the nCr values
        computeNcR(cp-1,ncr);//calculate Ncr values
        glBegin(GL_LINE_STRIP);
        for(i=0;i<=nbp;i++){
                t=float(i)/float(nbp);
                computeBezierPoints(t,&bp,cp,a,ncr);
                glVertex2f(bp.x,bp.y);
        }
        glEnd();
        delete[]ncr;
}
void display(){
        glClear(GL_COLOR_BUFFER_BIT);
        int cp=4,nbp=20;
        point a[4]={
                {100,400,0},
                {150,450,0},
                {250,350,0},
                {300,400,0}
        };
        a[1].x+=50*sin(theta*PI/180.0); //for animating the flag
        a[1].y+=25*sin(theta*PI/180.0);

        a[2].x-=50*sin((theta+30)*PI/180.0);
        a[2].y-=50*sin((theta+30)*PI/180.0);

        a[3].x-=25*sin((theta-30)*PI/180.0);
        a[3].y+=sin((theta-30)*PI/180.0);
        
        theta+=2;//animating speed
        glPushMatrix();
        glPointSize(5); //for plotting the point

        glColor3f(1,0.4,0.2); //Indian flag:saffron code
        for(int i=0;i<50;i++){
                glTranslatef(0,-0.8,0);
                Bezier(a,cp,nbp);
        }

        glColor3f(1,1,1);
        for(int i=0;i<50;i++)//Indian flag:white code
        {
                 glTranslatef(0,-0.8,0);
                 Bezier(a,cp,nbp);
        }

        glColor3f(0,1,0);
        for(int i=0;i<50;i++)//Indian flag:green code
        {
                 glTranslatef(0,-0.8,0);
                 Bezier(a,cp,nbp);
        }
        glPopMatrix();
        
        glLineWidth(5);
        glColor3f(0.7,0.5,0.3); //pole colour
        glBegin(GL_LINES);
        glVertex2f(100,400);
        glVertex2f(100,40);
        glEnd();
        glutPostRedisplay(); //call display again
        glutSwapBuffers(); //show the output
}
void init(){
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0,500,0,500);
}
int main(int argc,char **argv){
        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
        glutInitWindowPosition(0,0);
        glutInitWindowSize(500,500);
        glutCreateWindow("Flag Animation");
        init();
        glutDisplayFunc(display);
        glutMainLoop();
}