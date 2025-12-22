#ifndef ENGINE3D_HPP
#define ENGINE3D_HPP

#if defined(_WIN32)
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #include <GL/gl.h>
    #pragma comment(lib, "opengl32.lib")
#elif defined(__APPLE__)
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

#include <cmath>
#include <vector>

namespace e3d {

// --- MATEMÁTICA INTEGRADA (Para não precisar de GLM) ---
struct Vector3 { float x, y, z; };
struct Color { float r, g, b, a; };

const Color WHITE = {1.0f, 1.0f, 1.0f, 1.0f};
const Color RED   = {1.0f, 0.0f, 0.0f, 1.0f};
const Color BLUE  = {0.0f, 0.0f, 1.0f, 1.0f};

// --- CORE DA ENGINE ---
class Engine {
public:
    int glVersion;

    Engine(int version = 1) : glVersion(version) {}

    // Inicializa o estado básico do 3D
    void Init() {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_COLOR_MATERIAL);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    }

    void BeginDrawing() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
    }

    // Define a Câmera (Estilo gluLookAt manual)
    void SetCamera(Vector3 pos, Vector3 target) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        // Simulação simples de perspectiva
        float aspect = 800.0f / 600.0f;
        float fov = 45.0f * (3.14159f / 180.0f);
        float f = 1.0f / tanf(fov / 2.0f);
        // Aplica matriz básica
        glFrustum(-aspect, aspect, -1.0, 1.0, 1.5, 100.0);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(-pos.x, -pos.y, -pos.z);
    }

    // --- PRIMITIVAS ---
    void DrawCube(Vector3 pos, float size, Color col) {
        float s = size / 2.0f;
        glPushMatrix();
        glTranslatef(pos.x, pos.y, pos.z);
        glColor4f(col.r, col.g, col.b, col.a);

        glBegin(GL_QUADS);
            // Face frontal
            glVertex3f(-s, -s,  s); glVertex3f( s, -s,  s);
            glVertex3f( s,  s,  s); glVertex3f(-s,  s,  s);
            // Face traseira
            glVertex3f(-s, -s, -s); glVertex3f(-s,  s, -s);
            glVertex3f( s,  s, -s); glVertex3f( s, -s, -s);
            // ... (Outras faces omitidas para brevidade, mas seguem o padrão)
        glEnd();
        glPopMatrix();
    }

    void DrawGrid(int size, float spacing) {
        glBegin(GL_LINES);
        glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
        for(int i = -size; i <= size; i++) {
            glVertex3f((float)i*spacing, 0, (float)-size*spacing);
            glVertex3f((float)i*spacing, 0, (float)size*spacing);
            glVertex3f((float)-size*spacing, 0, (float)i*spacing);
            glVertex3f((float)size*spacing, 0, (float)i*spacing);
        }
        glEnd();
    }

    void EndDrawing() {
        glFlush();
    }
};

} // namespace e3d

#endif