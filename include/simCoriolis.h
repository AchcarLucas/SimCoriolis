#ifndef SIMCORIOLIS_H
#define SIMCORIOLIS_H

/*
 * Código Desenvolvido por Lucas Campos Achcar para apresentação do seminário de Mecânica Clássica
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

        // Reinicia a simulação
        void reset();
        // Faz toda a simulação
        void simRunning();
        // Função que faz os calculos da aceleração de coriolis
        std::vector<float> simAccelCoriolis();
        // Função que faz os calculos da aceleração centrifuga
        std::vector<float> simAccelCentrifuge();

        std::list<std::vector<float>> getListPosition() {
            return listPosition;
        }

        float getStopTimeSimulation() {
            return stopTimeSimulation;
        }

        void drawCircle(SDL_Renderer *m_renderer, std::vector<int>);

    protected:
        int sampleTime;           // Sample para cálcular dt
        float timeSimulation;     // Tempo de simulação

        std::vector<float> initVelocity;   // Vetor velocidade inicial
        std::vector<float> initPosition;   // Vetor posição inicial

        std::vector<float> vectorVelocity;   // Vetor velocidade inicial
        std::vector<float> vectorPosition;   // Vetor posição inicial

        float fRadius;        // raio do circulo (fixo)
        float wRadians;      // velocidade angular medido em rad/s

        std::list<std::vector<float>> listPosition;
        float stopTimeSimulation;
    private:
        float dt;                           // timeDerivated
        std::list<float> derivatedTime;     // time
};

#endif // SIMCORIOLIS_H
