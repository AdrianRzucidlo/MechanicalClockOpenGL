/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "myCube.h"
#include "myTeapot.h"
#include <torus.h>
#include <cube.h>

float speed_x=0;
float speed_y=0;
float aspectRatio=1;

ShaderProgram *sp;



//Odkomentuj, żeby rysować kostkę
//float* vertices = myCubeVertices;
//float* normals = myCubeNormals;
//float* texCoords = myCubeTexCoords;
//float* colors = myCubeColors;
//int vertexCount = myCubeVertexCount;


//Odkomentuj, żeby rysować czajnik
//float* vertices = torus.vertices;
//float* normals = torus.normals;
//float* texCoords = torus.texCoords;
//float* colors = torus.colors;
//int vertexCount = torus.vertexCount;

GLuint tex0;
GLuint tex1;
GLuint tex2;

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}
//draw torus
void drawtorus(glm::mat4 Mt1, Models::Torus mytorus)
{
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(Mt1));

	glEnableVertexAttribArray(sp->a("vertex"));  //Włącz przesyłanie danych do atrybutu vertex
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, mytorus.vertices); //Wskaż tablicę z danymi dla atrybutu vertex

	glEnableVertexAttribArray(sp->a("color"));  //Włącz przesyłanie danych do atrybutu color
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, mytorus.colors); //Wskaż tablicę z danymi dla atrybutu color

	glEnableVertexAttribArray(sp->a("normal"));  //Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, mytorus.normals); //Wskaż tablicę z danymi dla atrybutu normal

	glEnableVertexAttribArray(sp->a("texCoord0"));  //Włącz przesyłanie danych do atrybutu texCoord
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, mytorus.texCoords); //Wskaż tablicę z danymi dla atrybutu texCoord

	glUniform1i(sp->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex0);

	glUniform1i(sp->u("textureMap1"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex1);

	glDrawArrays(GL_TRIANGLES, 0, mytorus.vertexCount); //Narysuj obiekt

	glDisableVertexAttribArray(sp->a("vertex"));  //Wyłącz przesyłanie danych do atrybutu vertex
	glDisableVertexAttribArray(sp->a("color"));  //Wyłącz przesyłanie danych do atrybutu color
	glDisableVertexAttribArray(sp->a("normal"));  //Wyłącz przesyłanie danych do atrybutu normal
	glDisableVertexAttribArray(sp->a("texCoord0"));  //Wyłącz przesyłanie danych do atrybutu texCoord0
}

void draw_wood_cube(glm::mat4 Mt1, Models::Cube mytorus)
{
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(Mt1));

	glEnableVertexAttribArray(sp->a("vertex"));  //Włącz przesyłanie danych do atrybutu vertex
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, mytorus.vertices); //Wskaż tablicę z danymi dla atrybutu vertex

	glEnableVertexAttribArray(sp->a("color"));  //Włącz przesyłanie danych do atrybutu color
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, mytorus.colors); //Wskaż tablicę z danymi dla atrybutu color

	glEnableVertexAttribArray(sp->a("normal"));  //Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, mytorus.normals); //Wskaż tablicę z danymi dla atrybutu normal

	glEnableVertexAttribArray(sp->a("texCoord0"));  //Włącz przesyłanie danych do atrybutu texCoord
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, mytorus.texCoords); //Wskaż tablicę z danymi dla atrybutu texCoord

	glUniform1i(sp->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex2);

	glUniform1i(sp->u("textureMap1"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex1);

	glDrawArrays(GL_TRIANGLES, 0, mytorus.vertexCount); //Narysuj obiekt

	glDisableVertexAttribArray(sp->a("vertex"));  //Wyłącz przesyłanie danych do atrybutu vertex
	glDisableVertexAttribArray(sp->a("color"));  //Wyłącz przesyłanie danych do atrybutu color
	glDisableVertexAttribArray(sp->a("normal"));  //Wyłącz przesyłanie danych do atrybutu normal
	glDisableVertexAttribArray(sp->a("texCoord0"));  //Wyłącz przesyłanie danych do atrybutu texCoord0
}

void drawcube(glm::mat4 Mt1, Models::Cube mytorus)
{
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(Mt1));

	glEnableVertexAttribArray(sp->a("vertex"));  //Włącz przesyłanie danych do atrybutu vertex
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, mytorus.vertices); //Wskaż tablicę z danymi dla atrybutu vertex

	glEnableVertexAttribArray(sp->a("color"));  //Włącz przesyłanie danych do atrybutu color
	glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, mytorus.colors); //Wskaż tablicę z danymi dla atrybutu color

	glEnableVertexAttribArray(sp->a("normal"));  //Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, mytorus.normals); //Wskaż tablicę z danymi dla atrybutu normal

	glEnableVertexAttribArray(sp->a("texCoord0"));  //Włącz przesyłanie danych do atrybutu texCoord
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, mytorus.texCoords); //Wskaż tablicę z danymi dla atrybutu texCoord

	glUniform1i(sp->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex0);

	glUniform1i(sp->u("textureMap1"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex1);

	glDrawArrays(GL_TRIANGLES, 0, mytorus.vertexCount); //Narysuj obiekt

	glDisableVertexAttribArray(sp->a("vertex"));  //Wyłącz przesyłanie danych do atrybutu vertex
	glDisableVertexAttribArray(sp->a("color"));  //Wyłącz przesyłanie danych do atrybutu color
	glDisableVertexAttribArray(sp->a("normal"));  //Wyłącz przesyłanie danych do atrybutu normal
	glDisableVertexAttribArray(sp->a("texCoord0"));  //Wyłącz przesyłanie danych do atrybutu texCoord0
}

void keyCallback(GLFWwindow* window,int key,int scancode,int action,int mods) {
    if (action==GLFW_PRESS) {
        if (key==GLFW_KEY_LEFT) speed_x=-PI/2;
        if (key==GLFW_KEY_RIGHT) speed_x=PI/2;
        if (key==GLFW_KEY_UP) speed_y=PI/2;
        if (key==GLFW_KEY_DOWN) speed_y=-PI/2;
    }
    if (action==GLFW_RELEASE) {
        if (key==GLFW_KEY_LEFT) speed_x=0;
        if (key==GLFW_KEY_RIGHT) speed_x=0;
        if (key==GLFW_KEY_UP) speed_y=0;
        if (key==GLFW_KEY_DOWN) speed_y=0;
    }
}

void windowResizeCallback(GLFWwindow* window,int width,int height) {
    if (height==0) return;
    aspectRatio=(float)width/(float)height;
    glViewport(0,0,width,height);
}


GLuint readTexture(const char* filename) {
    GLuint tex;
    glActiveTexture(GL_TEXTURE0);

    //Wczytanie do pamięci komputera
    std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
    unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
    //Wczytaj obrazek
    unsigned error = lodepng::decode(image, width, height, filename);

    //Import do pamięci karty graficznej
    glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
    glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
    //Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return tex;
}


//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);
	glfwSetWindowSizeCallback(window,windowResizeCallback);
	glfwSetKeyCallback(window,keyCallback);

	sp=new ShaderProgram("v_simplest.glsl",NULL,"f_simplest.glsl");
	tex0 = readTexture("metal3.png");
	tex1 = readTexture("sky.png");
	tex2 = readTexture("wood_jpg.png");
}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
    //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************

    delete sp;
}

/// nasze funkcje
void drawKostka(glm::mat4 M, float a, float b, float c) {
	glm::mat4 Mk = glm::scale(M, glm::vec3(a / 2, b / 2, c / 2));
	Models::Cube mycube;
	drawcube(Mk, mycube);
}
void zebatka(glm::mat4 M, float angle, float x, float y, float z, float angleDelta, float a, float b, float c, float zw, float w)
//angle nie ruszac, x y z(0,0,0) - przesuniecie zebatki, angle delta(0) - rotate kostek wokol torusa, a b c(1,1,1) - skalowanie torusa,
// zw w(0.9,0.3) - promien zewnetrzny i wewnetrzny torusa, prawolewo 
// w nawiasach defaultowe wartosci zeby mialo sens na poczatku i potem mozna zmieniac
{
	Models::Torus mytorus(zw, w, 36, 36);
	//glm::mat4 I = glm::mat4(1.0f);
	glm::mat4 Mt1 = glm::translate(M, glm::vec3(x, y, z)); //Macierz torusa to najpierw przesunięcie do odpowiedniej pozycji... + Relatywnie do macierzy M żeby się rotowało wokół osi x i y
	Mt1 = glm::rotate(Mt1, angle, glm::vec3(0.0f, 0.0f, 1.0f)); //... potem obrót żeby nasz "tryb" był odpowiednio obrócony
	Mt1 = glm::scale(Mt1, glm::vec3(a, b, c));
	drawtorus(Mt1, mytorus);

	//W pętli narysuj 12 kostek.
	for (int k = 0; k < 12; k++) {
		//Macierz kostki to obrót, żeby wybrać kierunek wokół torusa...
		glm::mat4 Mk = glm::rotate(Mt1, glm::radians(k * 30.0f + angleDelta), glm::vec3(0.0f, 0.0f, 1.0f));
		//...przesunięcie żeby dotrzeć na obrzeże torusa...
		Mk = glm::translate(Mk, glm::vec3(zw + w, 0.0f, 0.0f));
		//...i skalowanie żeby pomniejszyć kostkę do porządanych rozmiarów
		Mk = glm::scale(Mk, glm::vec3(0.1f, 0.1f, 0.1f));
		Models::Cube mycube;
		drawcube(Mk, mycube);
	}
}
void zebatka_inner(glm::mat4 Mt1, float angleDelta, float zw, float w, float a, float b, float c)
{
	Models::Torus mytorus(zw, w, 36, 36);
	drawtorus(Mt1, mytorus);

	//glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(Mt1));
	//glUniform4f(spLambert->u("color"), 0, 1, 0, 1);
	//mytorus.drawSolid();

	//W pętli narysuj 12 kostek.
	int limit = int(PI * a * zw / 0.2);
	float delta = angleDelta ? 360.0f/2*limit : 0.0f;
	for (int k = 0; k < limit; k++) {
		//Macierz kostki to obrót, żeby wybrać kierunek wokół torusa...
		glm::mat4 Mk = glm::rotate(Mt1, glm::radians(k * 360.0f / limit + delta ), glm::vec3(0.0f, 0.0f, 1.0f));
		//...przesunięcie żeby dotrzeć na obrzeże torusa...
		Mk = glm::translate(Mk, glm::vec3(zw + w, 0.0f, 0.0f));
		//...i skalowanie żeby pomniejszyć kostkę do porządanych rozmiarów
		Mk = glm::scale(Mk, glm::vec3(0.1f / a, 0.1f / b, 0.1f / c));
		Models::Cube mycube;
		drawcube(Mk, mycube);
	}

	//wnetrze zebatki
	for (int k = 0; k < 3; k++) {
		glm::mat4 Mk = glm::rotate(Mt1, glm::radians(k * 120.0f + angleDelta), glm::vec3(0.0f, 0.0f, 1.0f));
		Mk = glm::translate(Mk, glm::vec3(zw / 2, 0.0f, 0.0f));
		Mk = glm::scale(Mk, glm::vec3(zw / 2, 0.06f, 0.06f));
		Models::Cube mycube;
		drawcube(Mk, mycube);
	}

}
void glowna_zebatka(glm::mat4 M, float angle, float x, float y, float z, float angleDelta, float a, float b, float c, float zw, float w)
//angle nie ruszac, x y z(0,0,0) - przesuniecie zebatki, angle delta(0) - rotate kostek wokol torusa, a b c(1,1,1) - skalowanie torusa,
// zw w(0.9,0.3) - promien zewnetrzny i wewnetrzny torusa, prawolewo 
// w nawiasach defaultowe wartosci zeby mialo sens na poczatku i potem mozna zmieniac
{
	Models::Torus mytorus(zw, w, 36, 36);
	//glm::mat4 I = glm::mat4(1.0f);
	glm::mat4 Mt1 = glm::translate(M, glm::vec3(x, y, z)); //Macierz torusa to najpierw przesunięcie do odpowiedniej pozycji... + Relatywnie do macierzy M żeby się rotowało wokół osi x i y
	Mt1 = glm::rotate(Mt1, angle, glm::vec3(0.0f, 0.0f, 1.0f)); //... potem obrót żeby nasz "tryb" był odpowiednio obrócony
	Mt1 = glm::scale(Mt1, glm::vec3(a, b, c));
	drawtorus(Mt1, mytorus);

	zebatka_inner(Mt1, angleDelta, zw, w, a, b, c);

	//kijek od zebatki
	glm::mat4 Mk = glm::translate(Mt1, glm::vec3(0.0f, 0.0f, -0.3f));
	Mk = glm::scale(Mk, glm::vec3(0.2f, 0.2f, 0.6f));
	Models::Cube mycube;
	drawcube(Mk, mycube);
	// krótsza wskazówka zegara
	glm::mat4 Mk2 = glm::translate(Mt1, glm::vec3(0.0f, 0.8f, -0.5f));
	Mk2 = glm::scale(Mk2, glm::vec3(0.15f, 2.2f, 0.15f));
	Models::Cube mycube1;
	draw_wood_cube(Mk2, mycube1);
}



void gorna_zebatka(glm::mat4 M, float angle, float x, float y, float z, float angleDelta, float a, float b, float c, float zw, float w)
{
	//przednia gorna zebatka
	Models::Torus mytorus(zw, w, 36, 36);
	glm::mat4 Mt1 = glm::translate(M, glm::vec3(x, y, z)); //Macierz torusa to najpierw przesunięcie do odpowiedniej pozycji... + Relatywnie do macierzy M żeby się rotowało wokół osi x i y
	Mt1 = glm::rotate(Mt1, angle, glm::vec3(0.0f, 0.0f, 1.0f)); //... potem obrót żeby nasz "tryb" był odpowiednio obrócony
	Mt1 = glm::scale(Mt1, glm::vec3(1.2*a, 1.2*b, 1.2*c));
	zebatka_inner(Mt1, 1, zw, w,1.2*a,1.2*b,1.2*c);
	//kijek od zebatki
	glm::mat4 Mk = glm::rotate(Mt1, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Mk = glm::translate(Mk, glm::vec3(-2.5f, 0.0f, 0.0f));
	Mk = glm::scale(Mk, glm::vec3(2.5f, 0.1f, 0.1f));
	Models::Cube mycube;
	drawcube(Mk, mycube);
	//tylnia gorna zebatka
	glm::mat4 Mt2 = glm::translate(M, glm::vec3(x, y, 6.25)); //Macierz torusa to najpierw przesunięcie do odpowiedniej pozycji... + Relatywnie do macierzy M żeby się rotowało wokół osi x i y
	Mt2 = glm::rotate(Mt2, angle, glm::vec3(0.0f, 0.0f, 1.0f)); //... potem obrót żeby nasz "tryb" był odpowiednio obrócony
	Mt2 = glm::scale(Mt2, glm::vec3(2.2 * a, 2.2 * b, 2.2 * c));
	zebatka_inner(Mt2, 0, zw, w,2.2*a,2.2*b,2.2*c);
	//tylnia dolna zebatka
	glm::mat4 Mt3 = glm::translate(M, glm::vec3(x, 0, 6.25)); //Macierz torusa to najpierw przesunięcie do odpowiedniej pozycji... + Relatywnie do macierzy M żeby się rotowało wokół osi x i y
	Mt3 = glm::rotate(Mt3, -angle, glm::vec3(0.0f, 0.0f, 1.0f)); //... potem obrót żeby nasz "tryb" był odpowiednio obrócony
	Mt3 = glm::scale(Mt3, glm::vec3(1.8 * a, 1.8 * b, 1.8 * c));
	zebatka_inner(Mt3, 1, zw, w,1.8*a, 1.8 *b, 1.8*c);
	//kijek
	glm::mat4 Mk2 = glm::translate(Mt3, glm::vec3(0.0f, 0.0f, -2.2f));
	Mk2 = glm::scale(Mk2, glm::vec3(0.06f, 0.06f, 2.2f));
	Models::Cube mycube1;
	drawcube(Mk2, mycube1);
	//szybsza wskazowka zegara
	glm::mat4 Mk3 = glm::translate(Mt3, glm::vec3(0.0f, 1.5f, -4.4f));
	Mk3 = glm::scale(Mk3, glm::vec3(0.1f, 3.0f, 0.1f));
	Models::Cube mycube2;
	draw_wood_cube(Mk3, mycube2);


}

//rysowanie pojdynczego ramienia
void drawArm(glm::mat4 M)
{
	glm::mat4 Mf = glm::rotate(M, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	Mf = glm::translate(Mf, glm::vec3(0.0f, 1.25f, 0.0f));
	drawKostka(Mf, 0.3, 2.5, 0.3);
	Mf = glm::translate(Mf, glm::vec3(0.5f, 1.10f, 0.0f));
	drawKostka(Mf, 1, 0.3, 0.3);
}

//rysowanie dwoch ramion jedno odwrocone o 180deg
void twoArms(glm::mat4 M) {
	glm::mat4 Mf = glm::rotate(M, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	drawArm(Mf);
	Mf = glm::rotate(Mf, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	drawArm(Mf);
}
//rysowanie wahadła
void drawWing(glm::mat4 M) {
	glm::mat4 Mf = glm::translate(M, glm::vec3(0, -2.0, 0));
	drawKostka(Mf, 0.2, 4.0, 0.2);
	Mf = glm::translate(Mf, glm::vec3(0, -2.5, 0));
	Models::Torus myTorus(0.5, 0.2, 36, 36);
	drawtorus(Mf, myTorus);

}
//złączenie wszystkich kompnentów
void drawPendulum(glm::mat4 M, float angle2)
{
	glm::mat4 Mf = glm::mat4(1.0f);
	Mf = glm::rotate(M, angle2, glm::vec3(0, 0, 1));
	drawWing(Mf);
	Mf = glm::rotate(Mf, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	drawKostka(Mf, 0.8, 0.8, 0.8);
	twoArms(Mf);
}
//


//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window, float angle_x, float angle_y, float pendulum_angle, float angle) {
	//************Tutaj umieszczaj kod rysujący obraz******************l
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glm::mat4 M = glm::mat4(1.0f); //Zainicjuj macierz modelu macierzą jednostkową
	////////////////////////////////////////////////////////////////////////

	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f); //Wyliczenie macierzy rzutowania
	glm::mat4 V = glm::lookAt(glm::vec3(0.0f, 0.0f, -25.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	
	M = glm::rotate(M, angle_y, glm::vec3(1.0f, 0.0f, 0.0f)); //rotacja wokół osi y
	M = glm::rotate(M, angle_x, glm::vec3(0.0f, 1.0f, 0.0f)); //rotacja wokół osi y
	M = glm::translate(M, glm::vec3(-4.0, 0, 0));
    sp->use();//Aktywacja programu cieniującego
    //Przeslij parametry programu cieniującego do karty graficznej
    glUniformMatrix4fv(sp->u("P"),1,false,glm::value_ptr(P));
    glUniformMatrix4fv(sp->u("V"),1,false,glm::value_ptr(V));

	drawPendulum(M, pendulum_angle); // rysowanie wahadła
	zebatka(M, angle/20, 4.5, 0, 0, 0, 1.5, 1.5, 1.5, 1.2, 0.1);
	glowna_zebatka(M, -angle/3600, 9.3, 0, 0, 15.0, 1.5, 1.5, 1.5, 1.7, 0.1);
	gorna_zebatka(M, angle/30, 9.3, 3.90, 0.0, 15.0, 1.5, 1.5, 1.5, 0.6, 0.05);
	//Testowanie żródeł światła na kostce 7x7
	//glm:: mat4 Mk2 = glm::translate(M, glm::vec3(4, 0, 0)); 
	//Mk2 = glm::scale(Mk2, glm::vec3(7.0f, 7.0f, 7.0f));
	//Models::Cube mycube1;
	//draw_wood_cube(Mk2, mycube1);

    glfwSwapBuffers(window); //Przerzuć tylny bufor na przedni
}


int main(void)
{
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące

//Główna pętla
	float angle_x = 0; //zadeklaruj zmienną przechowującą aktualny kąt obrotu
	float angle_y = 0; //zadeklaruj zmienną przechowującą aktualny kąt obrotu
	glfwSetTime(0); //Wyzeruj licznik czasu
	float angle = 0; //Aktualny kąt obrotu obiektu
	float pendulum_angle = 0;
	int right = 0, left = 1;
	glfwSetTime(0); //Wyzeruj timer
	//Główna pętla
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		angle += -PI * glfwGetTime(); //Oblicz przyrost kąta po obrocie

		angle_x += speed_x * glfwGetTime(); //Add angle by which the object was rotated in the previous iteration
		angle_y += speed_y * glfwGetTime(); //Add angle by which the object was rotated in the previous iteration
		//angle2 += speed * glfwGetTime();
		if (pendulum_angle > glm::radians(20.0f))
		{
			left = 0;
			right = 1;
		}
		else if (pendulum_angle < (-1) * glm::radians(20.0f)) {
			left = 1;
			right = 0;
		}
		if (right) {
			pendulum_angle -= PI / 2 * glfwGetTime();
		}
		if (left) {
			pendulum_angle += PI / 2 * glfwGetTime();
		}
		glfwSetTime(0); //Wyzeruj timer
		drawScene(window, angle_x, angle_y, pendulum_angle, angle); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
