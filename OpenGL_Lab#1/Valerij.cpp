#include <stdio.h>
#include <GL/glew.h>  // Подключаем заголовок GLEW
#include <GL/freeglut.h>
#include "Valerij_header.h"

GLuint VBO;  // Глобальной переменной для хранения указателя на буфер вершин.

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);  // Очистка буфера кадра

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  // Параметр GL_ARRAY_BUFFER означает, что буфер будет хранить массив вершин.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);  // Этот вызов говорит конвейеру как воспринимать данные внутри буфера.

    glDrawArrays(GL_TRIANGLES, 0, 3);  // Массив содержит 3 вершины. Функция для отрисовки.

    glDisableVertexAttribArray(0);  // Отключить каждый атрибут вершины, как только отпадает необходимость в нем.

    glutSwapBuffers();  // Просит GLUT поменять фоновый буфер и буфер кадра местами.
}


static void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderSceneCB); //  Отрисовывает 1 кадр. 
}

static void CreateVertexBuffer()  // Создаем массив из одного экземпляра структуры Vector3f. Так задается точка в середине экрана.
{
    Vector3f Vertices[3];  // Массив содержит 3 вершины.
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
    Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);  // GL_STATIC_DRAW - Изменения значений буфера запрещено.
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);  // Инициализируем GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);  // GLUT_DOUBLE включает двойную буферизацию. И Буфер цвета.
    glutInitWindowSize(1024, 768);  // Параметры окна 
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Valerij Baturin");  // Загаловок окна.

    InitializeGlutCallbacks();

     GLenum res = glewInit();  // Инициализируем GLEW и проверяем на ошибки.
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    // Цвет имеет 4 канала (красный, зелёный, синий, альфа-канал) 
    // и принимает значения от 0.0 и до 1.0.
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // Вызов выше   устанавливает цвет, который будет 
    // использован во время очистки буфера кадра

    CreateVertexBuffer();

    glutMainLoop();  // Этот вызов передаёт контроль GLUT'у, 
    // который теперь начнёт свой собственный цикл (Вызывает функцию RenderSceneCB

    return 0;
}