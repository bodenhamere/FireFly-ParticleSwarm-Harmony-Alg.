/**
 * @file PSO.c
 */

/**
 * @author Emily Bodenhamer
 *  CWU ID 41119306
 *  CS 471 Optimization Project 4
 *  Date 5/10/2019
 *
 *  Particle Swarm Optimization class file.
 *  This class implements the methods for performing Particle Swarm Optimization
 *  This algorithm models flocking and schooling patters of birds and fishes.
 *  It was invented by Russell Eberhart and James Kennedy in 1995.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include <math.h>
#include "ArrayMem.h"
#include "PSO.h"
#include "Util.h"
#include "SelectFunction.h"
#include "mt19937ar.h"

/**
 * Function that reads from the PSO input file to
 * initialize the structure variables for the PSO algorithm
 * @param input file that has the values for the myData structure
 * @param fileOut file that prints the best solution to a csv
 * @param filePop file that prints the population to a csv
 * @param iterations number of iterations to run the algorithm for
 * @param fitnessCallCounter count how many times the fitness function was called
 * @param myData Data structure pointer for initializing the bounds and which function to run
 * @param NS number of solutions for a data type
 * @param DIM number of dimensions for a data type
 */
void readInput(FILE *input, FILE *fileOut, FILE *filePop, int iterations, int fitnessCallCounter, initData *myData, int NS, int DIM) {
    PSO *myPSO;
    myPSO = (PSO *) calloc(1, sizeof(PSO));
    FILE *file;
    file = fopen("PSOInput.txt", "r");
    if (file == NULL) {
        printf("Error opening userInput.txt file, make sure the file is in the cmake-build-debug folder\n");
        exit(-1);
    }
    // go through file till the end
    while (!feof(file) && !feof(input)) {
        // read values and save them to the struct
        fscanf(file, "%lf %lf %lf",
               &myPSO->k, &myPSO->c1,
               &myPSO->c2);

        // read values and save them to the data struct
        fscanf(input, "%lf %lf %d",
               &myData->min, &myData->max,
               &myData->functionNumber);

        if (myData->max == 314) {
            myData->max = M_PI;
        }
            /*  initialize all the variables  */
            double best = DBL_MAX;
            myData->population = fillIn(myData->population, DIM, NS, myData->min, myData->max);
            myData->fitness = getFun(myData->fitness, myData->population, DIM, NS, myData->functionNumber);
            myPSO->pBest = singleArray(NS);
            myPSO->pBest = getFun(myPSO->pBest, myData->population, DIM, NS, myData->functionNumber);
            myPSO->velocity = createDblArray(NS, DIM);
            for (int i = 0; i < NS; ++i) {
                for (int j = 0; j < DIM; ++j) {
                    myPSO->velocity[i][j] = ((0.5 * (myData->max - myData->min)) - 0) * (genrand_real1());
                }
            }
            for (int i = 0; i < NS; ++i) {
                if (myPSO->pBest[i] < best) {
                    best = myPSO->pBest[i];
                }
            }
            myPSO->gBest = best;
            fitnessCallCounter = 0;
            /* return the initialize variables */
            startPSO(fileOut,filePop, NS, DIM, iterations, myData, fitnessCallCounter, myPSO);
    }
    fclose(file);
    fclose(input);
}


/**
 * Function that runs the PSO algorithm
 * @param fileOut output file for the fitness of the population
 * @param filePop file that prints the population to a csv
 * @param NS number of solutions for a data type
 * @param DIM number of dimensions for a data type
 * @param iterations number of iterations to run the algorithm for
 * @param myData Data structure pointer for initializing the bounds and which function to run
 * @param fitnessCallCounter count how many times the fitness function was called
 * @param myPSO the PSO structure
*/
void startPSO(FILE *fileOut, FILE *filePop, int NS, int DIM, int iterations, initData *myData, int fitnessCallCounter, PSO *myPSO) {
    fprintf(fileOut, "gBest\n");

    // start the clock
    clock_t start;
    start = clock();
    for (int t = 1; t < iterations; ++t) {
        for (int j = 0; j < NS; ++j) {
            calcVelocity(myPSO, myData, DIM, j);
            calcPopulation(myPSO, myData, DIM, j);

            myData->fitness[j] = getFunSingle(myData->fitness[j], myData->population[j], DIM, myData->functionNumber);
            fitnessCallCounter++;

            if (myData->fitness[j] < myPSO->pBest[j]) {
                myPSO->pBest[j] = myData->fitness[j];
            }
            if (myPSO->pBest[j] < myPSO->gBest) {
                myPSO->gBest = myPSO->pBest[j];
            }
        }
        fprintf(fileOut, "%lf, ", myPSO->gBest);
    }
    start = (((clock() - start)));
    fprintf(fileOut, "\nExperiment for %d took, %lf, Counter, %d\n",
            myData->functionNumber, ((((double) start) / CLOCKS_PER_SEC) * 1000), fitnessCallCounter);
}


/**
 * Function that updates the velocity for the PSO algorithm
 * @param myPSO the PSO structure pointer
 * @param myData Data structure pointer for initializing the bounds and which function to run
 * @param DIM number of dimensions for a data type
 * @param j position of the vector from the population matrix
 */
void calcVelocity(PSO *myPSO, initData *myData, int DIM, int j) {
    double rand = genrand_real1();
    double rand2 = genrand_real1();
    for (int i = 0; i < DIM; ++i) {
        myPSO->velocity[j][i] = myPSO->k * (myPSO->velocity[j][i] +
                                            myPSO->c1 * rand * (myPSO->pBest[j] - myData->population[j][i]) +
                                            myPSO->c2 * rand2 * (myPSO->gBest - myData->population[j][i]));
    }
}


/**
 * Function that updates the population of our PSO algorithm
 * @param myPSO the PSO structure pointer
 * @param myData Data structure pointer for initializing the bounds and which function to run
 * @param DIM number of dimensions for a data type
 * @param j position of the vector from the population matrix
 */
void calcPopulation(PSO *myPSO, initData *myData, int DIM, int j) {
    double newValue;
    for (int i = 0; i < DIM; ++i) {
        newValue = myData->population[j][i] + myPSO->velocity[j][i];
        if (newValue < myData->min) {
            newValue = myData->min;
        }
        if (newValue > myData->max) {
            newValue = myData->max;
        }
        myData->population[j][i] = newValue;
    }
}
