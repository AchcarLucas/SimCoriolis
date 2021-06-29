#include "simCoriolis.h"

/*
 * Código Desenvolvido por Lucas Campos Achcar para apresentação do seminário de Mecânica Clássica
 */

simCoriolis::simCoriolis(std::vector<float> initVelocity, std::vector<float> initPosition, int sampleTime, float timeSimulation, float fRadius, float wRadians) {
    this->initVelocity = initVelocity;
    this->initPosition = initPosition;

    this->sampleTime = sampleTime;
    this->timeSimulation = timeSimulation;

    this->fRadius = fRadius;
    this->wRadians = wRadians;

    reset();
}

simCoriolis::~simCoriolis() {
    //dtor
}

void simCoriolis::reset() {
    this->dt = this->timeSimulation / this->sampleTime;

    for (int i = 0; i <= sampleTime; ++i) {
        std::list<float>::iterator it = this->derivatedTime.end();
        ++it;
        this->derivatedTime.push_back(dt * i);
    }

    this->vectorPosition = this->initPosition;
    this->vectorVelocity = this->initVelocity;

    this->listPosition.clear();
    this->listPosition.push_back(this->vectorPosition);

    this->stopTimeSimulation = 0.0f;
}

void simCoriolis::simRunning() {

    std::cout << "Starting simRunning" << std::endl;

    for (std::list<float>::iterator it = this->derivatedTime.begin(); it != this->derivatedTime.end(); ++it) {
        //std::cout << "Time Running: " << *it << std::endl;
        std::vector<float> accelCoriolis = this->simAccelCoriolis();
        std::vector<float> accelCentrifuge = this->simAccelCentrifuge();

        // accelFF = -W vector product (W vector product R) - 2*(W vector product V);
        std::vector<float> accelFF = {  accelCoriolis[0] + accelCentrifuge[0],
                                        accelCoriolis[1] + accelCentrifuge[1]};

        //std::cout << "Ax: " << accelFF[0] << " Ay: " << accelFF[1] << std::endl;

        // integra a aceleração em relação a dt
        std::vector<float> velocFF = {  accelFF[0]*this->dt + this->vectorVelocity[0],
                                        accelFF[1]*this->dt + this->vectorVelocity[1]};


        //std::cout << "Vx: " << velocFF[0] << " Vy: " << velocFF[1] << std::endl;

        // atualiza a velocidade
        this->vectorVelocity = velocFF;

        // Integra a velocidade em relação a dt
        std::vector<float> PositFF = {     velocFF[0]*this->dt + this->vectorPosition[0],
                                            velocFF[1]*this->dt + this->vectorPosition[1]};

        // atualiza a posição
        this->vectorPosition = PositFF;

        // Verifica se o raio é maior, se for, pausa a simulação
        float r = sqrt(this->vectorPosition[0]*this->vectorPosition[0] + this->vectorPosition[1]*this->vectorPosition[1]);

        if(r > this->fRadius)
            break;

        //std::cout << "Rx: " << PositFF[0] << " Ry: " << PositFF[1] << std::endl;

        this->listPosition.push_back(this->vectorPosition);

        this->stopTimeSimulation += this->dt;
    }
}

std::vector<float> simCoriolis::simAccelCoriolis() {
    // -2 * (W) prod vector (Velocity) = ((+1)*2*W*Vy, (-1)*2*W*Vx), sendo Vx e Vy as velocidades iniciais (movimento uniforme)

    std::vector<float> accelCoriolis = {    (+2) * this->wRadians * this->vectorVelocity[1],
                                            (-2) * this->wRadians * this->vectorVelocity[0]};

    return accelCoriolis;
}

std::vector<float> simCoriolis::simAccelCentrifuge() {
    // - (W prod vector (W prod vector R)) = (+[W^2 * Rx], +[W^2 * Ry]), sendo Ry e Rx as posições atualizadas no tempo

    float powRadians = this->wRadians * this->wRadians;
    std::vector<float> accelCentrifuge = {  (+1) * powRadians * (this->vectorPosition[0]),
                                            (+1) * powRadians * this->vectorPosition[1]};
    return accelCentrifuge;

}

void simCoriolis::drawCircle(SDL_Renderer *m_renderer, std::vector<int> pos) {
    float angle = (2 * M_PI) / 360;

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

    for(double theta = 0; theta < 2 * M_PI; theta += angle) {
        SDL_RenderDrawPoint( m_renderer,
                            pos[0] + this->fRadius*std::cos(theta),
                            pos[1] + this->fRadius*std::sin(theta)
                            );
    }

    SDL_RenderPresent(m_renderer);


}

