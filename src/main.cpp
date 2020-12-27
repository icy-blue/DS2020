/**
  * Created by Huang Jingcheng on 2020/9/20.
  * 201905130198@mail.sdu.edu.cn
*/


#include <GL/glut.h>

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glVertex3f(0.5f, 0.5f, 0.0f);
    glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();
    glFlush();
}


int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(480, 320);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("OpenGL Demo");

    glutDisplayFunc(render);

    glutMainLoop();
    return 0;
}