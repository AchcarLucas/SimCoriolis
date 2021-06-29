#ifndef SIMCORIOLIS_H
#define SIMCORIOLIS_H

/*
 * C�digo Desenvolvido por Lucas Campos Achcar para apresenta��o do semin�rio de Mec�nica Cl�ssica
 */

#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <SDL.h>

class simCoriolis {
    public:
        simCoriolis(std::vector<float> init_velocity, std::vector<float> init_position, int sampleTime = 100, float timeSimulation = 10.0f, float fRadius = 1.0f, float wRadians = 1.0f);
        virtual ~simCoriolis();

        // Reinicia a simula��o
        void reset();
        // Faz toda a simula��o
        void simRunning();
        // Fun��o que faz os calculos da acelera��o de coriolis
        std::vector<float> simAccelCoriolis();
        // Fun��o que faz os calculos da acelera��o centrifuga
        std::vector<float> simAccelCentrifuge();

        std::list<std::vector<float>> getListPosition() {
            return listPosition;
        }

        float getStopTimeSimulation() {
            return stopTimeSimulation;
        }

        void drawCircle(SDL_Renderer *m_renderer, std::vector<int>);

    protected:
        int sampleTime;           // Sample para c�lcular dt
        float timeSimulation;     // Tempo de simula��o

        std::vector<float> initVelocity;   // Vetor velocidade inicial
        std::vector<float> initPosition;   // Vetor posi��o inicial

        std::vector<float> vectorVelocity;   // Vetor velocidade inicial
        std::vector<float> vectorPosition;   // Vetor posi��o inicial

        float fRadius;        // raio do circulo (fixo)
        float wRadians;      // velocidade angular medido em rad/s

        std::list<std::vector<float>> listPosition;
        float stopTimeSimulation;
    private:
        float dt;                           // timeDerivated
        std::list<float> derivatedTime;     // time
};

#endif // SIMCORIOLIS_H
