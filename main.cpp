#include <exception>
#include <string>
#include <iostream>
#include <SDL.h>

#include "simCoriolis.h"

#define WIDTH 640
#define HEIGHT 400

/*
 * Código Desenvolvido por Lucas Campos Achcar para apresentação do seminário de Mecânica Clássica
 */

/*
Simulação do Livro Dinâmica de Particulas
*/

// (a)
/*
#define VELOCITY_X 0.0
#define VELOCITY_Y 1.5
*/

// (b)
/*
#define VELOCITY_X 0.0
#define VELOCITY_Y 0.8
*/

// (c)
/*
#define VELOCITY_X 0.0
#define VELOCITY_Y 0.45
*/

// (d)
/*
#define VELOCITY_X 0.0
#define VELOCITY_Y 0.328
*/

// Lançado a 45º

// (e)
/*
#define VELOCITY_X 0.33234
#define VELOCITY_Y 0.33234
*/

// (f)
/*
#define VELOCITY_X 0.20011
#define VELOCITY_Y 0.20011
*/


#define RADIUS 1.0f
#define OMEGA 1.0f

// A velocidade está multiplicado por um fator de 100 (raio também)
// se for usar 1.5 m/s use 150
std::vector<float> vVelocity = {VELOCITY_X*100.0f, (-1)*VELOCITY_Y*100.0f};
std::vector<float> vPosition = {-(RADIUS * 100.0f / 2.0f), 0.0f};
std::list<std::vector<float>> listPosition;

simCoriolis sCoriolis(vVelocity, vPosition, 10000, 100.0f, RADIUS * 100.0f, (-1)*OMEGA);

class InitError : public std::exception
{
    std::string msg;
public:
    InitError();
    InitError(const std::string &);
    virtual ~InitError() throw();
    virtual const char * what() const throw();
};

InitError::InitError() :
    exception(),
    msg(SDL_GetError())
{
}

InitError::InitError(const std::string & m) :
    exception(),
    msg( m )
{
}

InitError::~InitError() throw()
{
}

const char * InitError::what() const throw()
{
    return msg.c_str();
}

class SDL
{
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
public:
    SDL(Uint32 flags = 0);
    virtual ~SDL();
    void draw();
};

SDL::SDL(Uint32 flags)
{
    if (SDL_Init( flags ) != 0)
        throw InitError();

    if ( SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN,
                                      &m_window, &m_renderer ) != 0)
        throw InitError();
}

SDL::~SDL()
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

void SDL::draw()
{
    // Clear the window with a black background
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);

    // Show the window
    SDL_RenderPresent(m_renderer);

    std::vector<int> pos {(WIDTH/ 2), (HEIGHT / 2)};
    sCoriolis.drawCircle(m_renderer, pos);

    SDL_Rect rectToDraw = {(WIDTH / 2) - 2, (HEIGHT / 2) - 2, 4, 4};
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(m_renderer, &rectToDraw);
    SDL_RenderPresent(m_renderer);

    // Desenha um ponto a cada 5 ms
    for (std::list<std::vector<float>>::iterator it = listPosition.begin(); it != listPosition.end(); ++it) {
        std::vector<float> tmpPoint = *it;

        //std::cout << "Px: " << tmpPoint[0] << "Py: " << tmpPoint[1] << std::endl;

        SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);

        SDL_RenderDrawPoint(m_renderer, (tmpPoint[0] + (WIDTH/ 2)), (tmpPoint[1] + (HEIGHT / 2)));

        SDL_RenderPresent(m_renderer);
        SDL_Delay(5);
    }

    SDL_Delay(5000);
}

int main( int argc, char * argv[] )
{
    sCoriolis.simRunning();
    listPosition = sCoriolis.getListPosition();
    std::cout << "stopTimeSimulation: " << sCoriolis.getStopTimeSimulation() << " s" <<  std::endl;
    std::cout << "Radius: " << RADIUS << " m" << std::endl;
    std::cout << "X Initial Velocity: " << VELOCITY_X << " m/s" << std::endl;
    std::cout << "Y Initial Velocity: " << VELOCITY_Y << " m/s" << std::endl;

    try
    {
        SDL sdl( SDL_INIT_VIDEO | SDL_INIT_TIMER );
        sdl.draw();

        return 0;
    }
    catch ( const InitError & err )
    {
        std::cerr << "Error while initializing SDL:  "
                  << err.what()
                  << std::endl;
    }

    return 1;
}
