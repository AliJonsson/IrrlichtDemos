#include <iostream>
#include <irrlicht.h>
#include <math.h>
#include <list>
#include <time.h>


using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Chromosome
{
private:
    float angle;
    double power;
    double fitness;
    float ftime;

    double xaxis(double x0, double v0, float angle, double t);
    double yaxis(double y0, double v0, float angle, double t);
    double toRadians(double angle);
    double getDistance(double x1,double y1, double x2, double y2);


public:
    Chromosome(float nangle, double npower);
    double calculateFitness(double distanceFromTarget);
    float getFitnessTime();
    double getFitness();
    double getPower();
    float getAngle();
    void setValues(float nangle, double npower);
    irr::core::stringc toString();
};

class Genetic
{
private:
    float crossoverRate;
    float mutationRate;

    std::list<Chromosome*> population;
    std::list<Chromosome*>::iterator it;
    bool compareChromosomes(Chromosome *first,Chromosome *second);

    struct SortProcess : public std::binary_function<Chromosome*, Chromosome*, bool>
    {
        bool operator()(Chromosome *first,Chromosome *second)
        {
            return first->getFitness()<second->getFitness();
        }
    };

    void printPopulation();
    void calculateFitness(double distance);
    void sortPopulation();
    void generatePopulation(int size);
    std::list<Chromosome*> select(int rate);
    Chromosome* getChromosome(int index);
    Chromosome* getRandomChromosome();

    double frand(double low, double high);

    void crossover(Chromosome* c1,Chromosome* c2);
    void mutation(std::list<Chromosome*> l);

    /**
Fun��o ALGORITMO-GEN�TICO(popula��o, FN-FITNESS) retorna um indiv�duo
Entradas: popula��o, um conjunto de indiv�duos
FN_FITNESS, uma fun��o que mede a adapta��o de um indiv�duo
Repita
nova_popula��o <- conjunto vazio
para i<-1 at� TAMANHO(popula��o) fa�a
x <- SELE��O-ALEAT�RIA(popula��o, FN-FITNESS)
y <- SELE��O-ALEAT�RIA(popula��o, FN-FITNESS)
filho <- REPRODUZ(x,y)
se (pequena probabilidade aleat�ria)
ent�o filho <- MUTA��O(filho)
adicionar filho � nova popula��o
At� algum crit�rio de parada
Retornar o melhor indiv�duo da popula��o, de acordo com FN-FITNESS
    */

public:
    Genetic(float crossRate,float mutRate);
    void redefineRates(float crossRate,float mutRate);
    Chromosome* execute(double distanceFromTarget,int populationSize,int totalGenerations, bool show);
};
