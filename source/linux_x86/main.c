/*
 * SNEK - port SNAKE II dla systemów GNU/Linux x86
 *
 * Przeportowany przez J. "Krecika" K. - na licencji MIT
 * Biblioteki użyte do tego portu:
 * - GTK+ 2  [libgtk2.0-dev]
 * - freeglut [freeglut3, freeglut3-dev]
 * - GLUT i GLEW [libglew-dev, libglu1-mesa-dev]
 * NOTE: przy kompilacji użyj -std=c99
 */
/** Port z windowsowego SNEK'a na łono Linuxowe :) **/

#include <gtk/gtk.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define PADDING 0.025
#define KROKX 0.025
#define KROKY 0.045

#define X_MIN -2.5
#define X_MAX 2.5

// na środek ekranu
#define DEFAULT_X 0.5
#define DEFAULT_Y 0.5

#define MAX_SEGMENTS 256
#define TIMER_SET 350 //[milisekund]
#define limit 0.025


int global_argc;
char **global_argv;

float SegmentWeza[MAX_SEGMENTS][2];
float DotX = DEFAULT_X, DotY = DEFAULT_Y;
float KierunekX = KROKX; // Początkowy kierunek ruchu w poziomie
float KierunekY = 0.0;   // Początkowy kierunek ruchu w pionie
float FoodX;    //bez jedzenia nigdy się nie odbędzie.
float FoodY;

bool snakeMoved = false;
bool debugMode = false;

int PointCount, LiczbaSegmentow = 1;
int show_xy;

char MITLicense[] = "SNEK - Snake II dla systemow rodziny GNU/Linux x86\nProjekt Prywatny - Napisany przez J. 'Krecika' K.\nPROJEKT NIE JEST WYSYŁANY POD PUBLIKE, PODLEGA NA LICENCJI MIT:\n\nCopyright 2024 ApplehatDoesStuff\nPermission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ,,Software''), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:\n\nThe above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.\n\nTHE SOFTWARE IS PROVIDED,,AS IS'', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.";


// dla ułatwienia robocizny, funkcja tworząca messagebox w GTK+
// GTK_MessageBox("tytuł", "opis");
int GTK_MessageBox(const char *TITLE, const char *TEXT)
{
    GtkWidget *dialog;

    //zanim użyjesz funkcji zdefiniuj globalne argc i argv!
    gtk_init(&global_argc, &global_argv);
    dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "%s", TEXT);
    gtk_window_set_title(GTK_WINDOW(dialog), TITLE);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}


// ^ wiem, wygląda nieprzyjemnie

/** JEDZENIE **/

void RysujJedzenie(){
    glColor3f(0.5f, 0.5f, 0.5f);
    glPointSize(7.0);
    glBegin(GL_POINTS);
        glVertex2f(FoodX * glutGet(GLUT_WINDOW_WIDTH), FoodY * glutGet(GLUT_WINDOW_HEIGHT));
    glEnd();
}

void GenerateFood() {
    // Zakres dla FoodX i FoodY
    float minX = 0.050;
    float maxX = 0.950;
    float minY = 0.050;
    float maxY = 0.950;

    // Obliczenie zakresów do generowania losowej współrzędnej
    float rangeX = maxX - minX;
    float rangeY = maxY - minY;

    // Generowanie losowych współrzędnych w odpowiednim zakresie
    FoodX = minX + ((float)rand() / RAND_MAX) * rangeX;
    FoodY = minY + ((float)rand() / RAND_MAX) * rangeY;
}

void RysujBoczneLinie(){
    /*
    rysuje boczne linie, tak jak to jest
    w oryginalnej wersji SNAKE II
     */
    glColor3f(0.0f, 0.0f, 0.0f);

    // Pobieranie szerokości i wysokości okna
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    // Przeskalowanie PADDING do przestrzeni okna
    float paddingX = PADDING * width;
    float paddingY = PADDING * height;

    // Rysowanie linii
    glBegin(GL_LINES);
        // Lewa linia
        glVertex2f(paddingX, paddingY);
        glVertex2f(paddingX, height - paddingY);

        // Prawa linia
        glVertex2f(width - paddingX, paddingY);
        glVertex2f(width - paddingX, height - paddingY);

        // Dolna linia
        glVertex2f(paddingX, paddingY);
        glVertex2f(width - paddingX, paddingY);

        // Górna linia
        glVertex2f(paddingX, height - paddingY);
        glVertex2f(width - paddingX, height - paddingY);
    glEnd();
}

/**RYSUJE FRAGMENT (JEDEN KWADRACIK) WEZA O WSPÓŁRZĘDNYCH X I Y**/
void RysujFragmentWeza(float x, float y){

    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    // skalowanie piksela do okna
    float pixelX = x * width;
    float pixelY = y * height;

    glPointSize(7.0);  // Ustawienie rozmiaru punktu
    glBegin(GL_POINTS);
        glVertex2f(pixelX, pixelY);   // Rysowanie punktu na terenie ekranu
    glEnd();
}

void DodajSegmentWeza(float x, float y) {
    // Przesuń każdy segment węża na miejsce poprzedniego segmentu
    for (int i = LiczbaSegmentow - 1; i > 0; --i) {
        SegmentWeza[i][0] = SegmentWeza[i-1][0];
        SegmentWeza[i][1] = SegmentWeza[i-1][1];
    }

    // Ustaw nową głowę węża na podane współrzędne
    SegmentWeza[0][0] = x;
    SegmentWeza[0][1] = y;

    // Zwiększ liczbę segmentów węża, jeśli nie przekracza MAX_SEGMENTS
    if (LiczbaSegmentow < MAX_SEGMENTS) {
        LiczbaSegmentow++;
    }
}

/** LOGIKA KOLIZJI WEZA**/
bool KolizjaWeza(float x, float y){
    for (int i = 0; i < LiczbaSegmentow; i++) {
        if (DotX < 0.050 - KROKX || DotY < 0.050 - KROKY){
            return true;
        } else if (DotX > 0.950 + KROKX || DotY > 0.950 + KROKY){
            return true;
        }
    }
    return false;
}

/** kontrolowanie weza przez klawiature **/
void Kontrol(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
            KierunekX = 0.0;
            KierunekY = KROKY;
            break;

        case GLUT_KEY_DOWN:
            KierunekX = 0.0;
            KierunekY = -KROKY;
            break;

        case GLUT_KEY_LEFT:
            KierunekX = -KROKX;
            KierunekY = 0.0;
            break;

        case GLUT_KEY_RIGHT:
            KierunekX = KROKX;
            KierunekY = 0.0;
            break;
        case GLUT_KEY_F1:
            GTK_MessageBox("o programie", MITLicense);
            break;

    }
}
// nie byłoby innej opcji niż ciągle stawiać argc i argv do funkcji?
void Timer(int value) {
    float oldDotX = DotX;
    float oldDotY = DotY;

    // Zapisz poprzednią pozycję głowy węża
    float prevX = DotX;
    float prevY = DotY;

    // Przesuń głowę węża zgodnie z aktualnym kierunkiem
    DotX += KierunekX;
    DotY += KierunekY;

    // Sprawdź kolizję z wężem
    if (KolizjaWeza(DotX, DotY)) {
        GTK_MessageBox("Przegrana... a to pech!", "Wykryto kolizje ze ścianą - przegrałeś! ( a to pech :[ )");
        exit(0);
    }

    // Sprawdź kolizję z jedzeniem i dodaj nowy segment
    if (fabs(DotX - FoodX) <= limit && fabs(DotY - FoodY) <= limit) {
        DodajSegmentWeza(prevX, prevY);  // Dodaj nowy segment na poprzedniej pozycji głowy
        GenerateFood();  // Wygeneruj nowe jedzenie
    }

    // Przesuń każdy segment węża na miejsce poprzedniego
    for (int i = LiczbaSegmentow - 1; i > 0; --i) {
        SegmentWeza[i][0] = SegmentWeza[i-1][0];
        SegmentWeza[i][1] = SegmentWeza[i-1][1];
    }

    // Ustaw nową pozycję głowy węża na początku tablicy segmentów
    SegmentWeza[0][0] = DotX;
    SegmentWeza[0][1] = DotY;

    glutPostRedisplay();  // Odśwież ekran
    glutTimerFunc(TIMER_SET, Timer, 0);  // Ustaw ponownie timer
}

/*** STREFA FUNKCJI GRAFICZNYCH - UWAŻAJ ***/
/* w porównaniu do kodu dla Win32, reshape był
 przedostatnią funkcją... a tu robię inaczej. */

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(X_MIN, X_MAX, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutReshapeWindow(336, 192);
}



void display() {

    glClearColor(153.0f/255.0f, 194.0f/255.0f, 2.0f/255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Tutaj są inne funkcje rysowania

    RysujBoczneLinie();
    RysujFragmentWeza(DotX, DotY);
    //RysujJedzenie();

    for (int i = 1; i < LiczbaSegmentow; ++i) {
        RysujFragmentWeza(SegmentWeza[i][0], SegmentWeza[i][1]);
    }

    RysujJedzenie();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glutSwapBuffers();
}



int main(int argc, char *argv[])
{
    global_argc = argc;
    global_argv = argv;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(336, 192);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("SNEK - Snake II dla Linux x86");

    // Inicjalizacja OpenGL
    glEnable(GL_COLOR_MATERIAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutDisplayFunc(display);
    glutReshapeFunc(NULL);
    glutSpecialFunc(Kontrol);

    GenerateFood();
    glutTimerFunc(TIMER_SET, Timer, 0);
    glutMainLoop();
    return 0;
}
