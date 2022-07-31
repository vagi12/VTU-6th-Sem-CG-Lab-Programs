#include<GL/glut.h>
#include<stdio.h>
int x1,y1,x2,y2;
void draw_pixel(int x , int y){
        glColor3f(1.0, 0.0, 0.0);
	glPointSize(4);
	glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
}
void bresenhams_line_draw(int x1, int y1, int x2, int y2){
        int dx = x2 - x1;
        int dy = y2 - y1;
        int slope = dy / dx;
        if(slope < 1){
                int dp = 2*dy - dx;
                int x = x1;
                int y = y1;
                if(dx < 0){
                        x = x2;
                        y = y2;
                        x2 = x1;
                }
                draw_pixel(x, y);
                while(x < x2){
                	if(dp >= 0){
                		x = x + 1;
                                y = y + 1;
                                dp = dp + 2*dy - 2*dx;
                        }
                        else{
                                x = x + 1;
                                y = y;
                                dp = dp + 2*dy;
                        }
                        draw_pixel(x, y);
                }
        }
        else if(slope > 1){
                int dp = 2*dx - dy;
                int x = x1;
                int y = y1;
                if(dy < 0){
                        x = x2;
                        y = y2;
                        y2 = y1;
                }
                draw_pixel(x, y);
                while(y < y2){
                        if(dp >= 0){
                                x = x+1;
                                y = y + 1;
                                dp = dp + 2*dx - 2*dy;
			}
                        else{
                                y = y + 1;
                                x = x;
                                dp = dp + 2*dx;
                        }
                        draw_pixel(x, y);
                }
        }
        else if(slope == 1){
                int x = x1;
                int y = y1;
                draw_pixel(x,y);
                while(x < x2){
                        x = x+1;
                        y = y+1;
                        draw_pixel(x,y);
                }
        }
}
void init(){
        glClearColor(1,1,1,1);
        gluOrtho2D(0.0,500.0,0.0,500.0);
}
void display(){
        glClear(GL_COLOR_BUFFER_BIT);
        bresenhams_line_draw(x1, y1, x2, y2);
        glFlush();
}
int main(int argc, char **argv){       
	printf("Enter the X1, Y1 values");
        scanf("%d %d", &x1, &y1);
        printf("Enter the end points ");
        scanf("%d %d", &x2, &y2);
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowPosition(220, 200);
        glutInitWindowSize(500, 500);
        glutCreateWindow("4SO19CS170");
        init();
        glutDisplayFunc(display);
        glutMainLoop();
}