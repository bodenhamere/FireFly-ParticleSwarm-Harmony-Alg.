/**
 * @file FA.c
 */

/**
 * @author Emily Bodenhamer
 *  CWU ID 41119306
 *  CS 471 Optimization Project 4
 *  Date 5/10/2019
 *
 *  Firefly Algorithm class file.
 *  This class implements the methods for performing the Firefly Algorithm
 *  This algorithm models the social behavior of fireflies based on the flashing
 *  and attraction characteristics of fireflies.
 *  It was developed by Yang in 2010.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <time.h>
#include "Util.h"
#include "FA.h"
#include "ArrayMem.h"
#include "SelectFunction.h"
#include "mt19937ar.h"

/**
 * Function that reads from the FA input file to
 * initialize the structure variables for the FA algorithm
 * @param input file that has the values for the myData structure
 * @param fileOut file that prints the best solution to a csv
 * @param filePop file that prints the population to a csv
 * @param iterations number of iterations to run the algorithm for
 * @param fitnessCallCounter count how many times the fitness function was called
 * @param myData Data structure pointer for initializing the bounds and which function to run
 * @param NS number of solutions for a data type
 * @param DIM number of dimensions for a data type
 */
void
readInputFA(FILE *input, FILE *fileOut, FILE *filePop,int iterations, int fitnessCallCounter, initData *myData, int NS, int DIM) {
    FA *myFA;
    myFA = (FA *) calloc(1, sizeof(FA));
    FILE *file;
    file = fopen("FAInput.txt", "r");
    if (file == NULL) {
        printf("Error opening FAInput.txt file, make sure the file is in the cmake-build-debug folder\n");
        exit(-1);
    }
    // go through file till the end
    while (!feof(file) && !feof(input)) {
        // read values and save them to the struct
        fscanf(file, "%lf %lf %lf",
               &myFA->alpha, &myFA->betaMin,
               &myFA->gamma);
        // read values and save them to the data struct
        fscanf(input, "%lf %lf %d",
               &myData->min, &myData->max,
               &myData->functionNumber);

        if (myData->max == 314) {
            myData->max = M_PI;
        }

        /*  initialize all the variables  */
        myFA->beta = 0.0;
        myFA->newXiFitness = 0.0;
        myFA->intensity = singleArray(NS);
        myFA->newXi = singleArray(DIM);
        myFA->tempPopulation = createDblArray(NS, DIM);
        myFA->tempFitness = singleArray(NS);
        myData->population = fillIn(myData->population, DIM, NS, myData->min, myData->max);
        myData->fitness = getFun(myData->fitness, myData->population, DIM, NS, myData->functionNumber);
        myFA->intensity = getFun(myFA->intensity, myData->population, DIM, NS, myData->functionNumber);
        myFA->I0 = singleArray(NS);
        myFA->I0 = getFun(myFA->I0, myData->population, DIM, NS, myData->functionNumber);
        /* return the initialize variables */
            startFA(myFA, fileOut, filePop, NS, DIM, iterations, myData, fitnessCallCounter);
            fitnessCallCounter = 0;
    }
    fclose(file);
    fclose(input);
}

/**
 * Function that runs the FA algorithm
 * @param fileOut file that prints the best solution to a csv
 * @param filePop file that prints the population to a csv
 * @param NS number of solutions for a data type
 * @param DIM number of dimensions for a data type
 * @param iterations number of iterations to run the algorithm for
 * @param myData Data structure pointer for initializing the bounds and which function to run
 * @param fitnessCallCounter count how many times the fitness function was called
 * @param myFA the FA structure
*/
void startFA(FA *myFA, FILE *fileOut, FILE *filePop, const int NS, const int DIM, const int iterations, initData *myData,
             int fitnessCallCounter) {
    double *replace = singleArray(DIM);
    sortAscendingOrder(myData, NS, DIM, replace);
    copyDbl(myFA->tempPopulation, myData->population, NS, DIM);
    myFA->tempFitness = getFun(myFA->tempFitness, myFA->tempPopulation, DIM, NS, myData->functionNumber);

    // start the clock
    clock_t start;
    start = clock();
    for (int t = 1; t < iterations; ++t) {

        // sort and copy population to temporary
        myFA->index = NS - 1;
        for (int i = 0; i < NS; ++i) {
            for (int j = 0; j < NS; ++j) {
                if (myFA->intensity[j] < myFA->intensity[i]) {
                    /* move firefly j towards firefly i; EQN. 3 */
                    Eqn3(myData->population[i], myData->population[j], DIM, myFA);
                    /* Attractiveness varies with distance r via exp[-gamma*r]; EQN. 2 */
                    myFA->beta = Eqn2(myFA);
                    /* Evaluate and update the worst firefly in the population; EQN. 4 */
                    Eqn4(myData->population[i], myData->population[j], DIM, myFA, myData);
                    myFA->intensity[j] = updateIntensity(myFA, j);
                    fitnessCallCounter++;
                }
            }
        }
        fprintf(fileOut, "%lf, ", findBest(myFA->tempFitness, NS));

        copyDbl(myData->population, myFA->tempPopulation, NS, DIM);
        copySingle(myData->fitness, myFA->tempFitness, DIM);
        sortAscendingOrder(myData, NS, DIM, replace);
    }
    start = (((clock() - start)));
    fprintf(fileOut, "\nExperiment for %d took, %lf, Counter, %d\n",
            myData->functionNumber, ((((double) start) / CLOCKS_PER_SEC) * 1000), fitnessCallCounter);
}

/**
 * function that moves firefly j towards firefly i; EQN. 3
 * @param xi firefly vector at i
 * @param xj firefly vector at j
 * @param DIM number of dimensions for a data type
 * @param myFA the PSO structure pointer
 */
void Eqn3(const double *xi, const double *xj, int DIM, FA *myFA) {
    //distance r between ij
    myFA->r = 0.0;
    for (int i = 0; i < DIM; ++i) {
        myFA->r += pow(xi[i] - xj[i], 2);
    }
    myFA->r = sqrt(myFA->r);
}


/**
 * Function that updates Beta
 * @param myFA the FA structure pointer
 * @return Beta
 */
double Eqn2(FA *myFA) {
    double myBeta = (myFA->betaMin * exp(-(myFA->gamma * pow(myFA->r, 2))));
    return myBeta;
}


/**
 * Evaluate and update the worst firefly in the population;  EQN. 4
 * @param xi firefly vector at i
 * @param xj firefly vector at j
 * @param DIM number of dimensions for a data type
 * @param myFA the PSO structure pointer
 * @param myData Data structure pointer for initializing the bounds and which function to run
 */
void Eqn4(const double *xi, const double *xj, const int DIM, FA *myFA, initData *myData) {
    double epsilon = (genrand_real1() - 0.5) * (myData->max - myData->min);

    // create new vector
    for (int i = 0; i < DIM; ++i) {
        myFA->newXi[i] =
                xi[i] + myFA->beta * (xj[i] - xi[i])
                + myFA->alpha * epsilon;
        if (myFA->newXi[i] < myData->min) {
            myFA->newXi[i] = myData->min;
        }
        if (myFA->newXi[i] > myData->max) {
            myFA->newXi[i] = myData->max;
        }
    }

    // calculate new vectors fitness
    myFA->newXiFitness = getFunSingle(myFA->newXiFitness, myFA->newXi, DIM, myData->functionNumber);

    // determine if the new vectors fitness is better than the worst in the population

    if (myFA->newXiFitness < myFA->tempFitness[myFA->index]) {
        myFA->tempFitness[myFA->index] = myFA->newXiFitness;
        myFA->tempPopulation[myFA->index] = myFA->newXi;
        myFA->index--;
    }

}


/**
 * Function that updates the intensity of the fireflies
 * @param xi firefly vector at i
 * @param xj firefly vector at j
 * @param DIM number of dimensions for a data type
 * @param myFA the PSO structure pointer
 * @param myData Data structure pointer for initializing the bounds and which function to run
 */
double updateIntensity(FA *myFA, int j) {
    double intense = (myFA->intensity[j] * exp(-(myFA->gamma * pow(myFA->r, 2))));
    return intense;
}