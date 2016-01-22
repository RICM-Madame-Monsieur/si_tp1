#include <iostream>
#include <shader.hpp> // Help to load shaders from files
// Include GLEW : Always include it before glfw.h et gl.h :)
#include <GL/glew.h> // OpenGL Extension Wrangler Library : http://glew.sourceforge.net/ 
#include <GL/glfw.h> // Window, keyboard, mouse : http://www.glfw.org/
#include <glm/glm.hpp> // OpenGL Mathematics : www.http://glm.g-truc.net/0.9.5/index.html

using namespace glm;
using namespace std;

int main()
{

    cout << "Debut du programme..." << endl;

    // Initialisation de GLFW
	if( !glfwInit() )
	{
		cout << "Echec de l'initialisation de GLFW" << endl;
		exit(EXIT_FAILURE);
	}

    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4); // Anti Aliasing
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2); // OpenGL 2.1
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);

    // Ouverture d'une fenêtre en 1024x768
    // et creation d'un contexte OpenGL
	if( !glfwOpenWindow( 768, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) )
	{
		cout << "Echec de l'ouverture de fenetre OpenGL" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
    }

    // Definition du titre de la fenêtre
	glfwSetWindowTitle( "Polytech RICM 4 - TP1" );

    // Autorise GLFW a recevoir les appuis de touche
	glfwEnable( GLFW_STICKY_KEYS );

    // Initialisation de  GLEW
	if (glewInit() != GLEW_OK) {
		cout << "Echec de l'initialisation de GLEW" << endl;
		exit(EXIT_FAILURE);
	}

    // Verification des donnees du contexte OpenGL
    const GLubyte* renderer = glGetString (GL_RENDERER);
    cout << "Carte Graphique : " << renderer << endl;

    const GLubyte* version = glGetString (GL_VERSION);
    cout << "Driver OpenGL : " << version << endl;



    //==================================================
    // ToDo : Initialiser
    //==================================================

    // Compilation du shader program et generation de l'ID du Shader
    GLuint programID = LoadShaders("../shader/vertex_triangle.glsl", "../shader/fragment.glsl");

    // Definition d'un vecteur
    vec3 v1(-0.5f, -0.5f, 0.0f);
    vec3 v2( 0.5f, -0.5f, 0.0f);
    vec3 v3( 0.0f,  0.5f, 0.0f);

    // Definition d'un tableau de vecteurs
    vec3 vertex[3];
    vertex[0] = v1;
    vertex[1] = v2;
    vertex[2] = v3;

    /*vec2 vertex2[3];
    vertex2[0] = v1;
    vertesx2[1] = v3;
    vertex2[2] = v4;*/

    // Obtention de l'ID de l'attribut "vertex_position" dans programID
    GLuint vertexPositionID = glGetAttribLocation(programID, "vertex_position");

    // Creation d'un VBO et recuperation de son ID
    GLuint vboID;
    glGenBuffers(1, &vboID);

    // Definition de notre VBO comme le buffer courant
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    // Copie de donnees vers le VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertex2), vertex2, GL_STATIC_DRAW);

    cout << "Initialisations..." << endl;

    // Definition de la couleur du fond
    glClearColor(0.0, 0.5, 0.5, 0.0);


    cout << "Debut de la boucle principale..." << endl;
    unsigned int i = 0;
    // Boucle de dessin
	do{

        // Nettoyage de la zone de dessin
		glClear( GL_COLOR_BUFFER_BIT );

        //==================================================
        // ToDo : Dessiner
        //==================================================

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // On dit a OpenGL d'utiliser programID
        glUseProgram(programID);

        // On active l'attribut vertexPositionID
        glEnableVertexAttribArray(vertexPositionID);

        // On definit notre VBO comme le VBO courant
        glBindBuffer(GL_ARRAY_BUFFER, vboID);

        // On lui indique OpenGL comment lire les donnees
        glVertexAttribPointer(
            vertexPositionID,       // ID de l'attribut contenant les positions
            3,                      // nombre de composante par position (x, y, z);
            GL_FLOAT,               // Type des composantes
            GL_FALSE,               // Normalisation des composantes
            0,                      // Decalage des composantes (stride)
            (void*)0                // Decalage initial des composantes (offset)
            );

        // On dit a OpenGL de dessiner le contenu du buffer courant
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        // On desactive l'attribut vertexPositionID
        glDisableVertexAttribArray(vertexPositionID);

        //glColor3f(1.0f, 0.0f, 0.0f);

		// carré en utilisant GL_TRIANGLES
		// On dessine un premier triangle pour former un carré
        glBegin(GL_TRIANGLES);
            glVertex3f(-0.75f,  0.5f, 0.0f);
            glVertex3f(-0.25f, 0.5f, 0.0f);
            glVertex3f(-0.25f, 0.0f, 0.0f);
        glEnd();
        
        // On dessine le deuxième triangle pour former un carré
        glBegin(GL_TRIANGLES);
            glVertex3f(-0.75f,  0.5f, 0.0f);
            glVertex3f(-0.75f, 0.0f, 0.0f);
            glVertex3f(-0.25f, 0.0f, 0.0f);
        glEnd();

		// Echange des zones de dessin buffers
		glfwSwapBuffers();

        cout << "Compteur : " << i++ << "\r";
        cout.flush();

    } // Execution de la boucle...
    while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&  // ... jusqu'a appui sur la touche ESC
           glfwGetWindowParam( GLFW_OPENED )        );  // ... ou fermeture de la fenetre

    cout << endl;

    // Ferme GLFW et OpenGL
	glfwTerminate();



    //==================================================
    // ToDo : Nettoyer la memoire
    //==================================================

    glDeleteBuffers(1, &vboID);

    cout << "Fin du programme..." << endl;

	return EXIT_SUCCESS;
}

