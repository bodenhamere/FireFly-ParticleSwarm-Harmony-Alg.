/**
 * @file HS.c
 */
/**
 * @author Emily Bodenhamer
 *  CWU ID 41119306
 *  CS 471 Optimization Project 4
 *  Date 5/10/2019
 *
 *  Harmony Search Algorithm header file.
 *  This class implements the methods for performing the Harmony Search Algorithm
 *  This algorithm models the music improvisation process where the musicians
 *  improvise their instruments' pitch by searching for a perfect state of harmony
 *  (Geem et al. 2001)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include <math.h>
#include "Util.h"
#include "HS.h"
#include "ArrayMem.h"
#include "SelectFunction.h"
#include "mt19937ar.h"

/**
 * Function that reads from the HS input file to
 * initialize the structure variables for the HS algorithm
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
readInputHS(FILE *input, FILE *fileOut, FILE *filePop, int iterations, int fitnessCallCounter, initData *myData, int NS,
            int DIM) {
    HS *myHS;
    myHS = (HS *) calloc(1, sizeof(HS));
    FILE *file;
    file = fopen("HSInput.txt", "r");
    if (file == NULL) {
        printf("Error opening HSInput.txt file, make sure the file is in the cmake-build-debug folder\n");
        exit(-1);
    }
    // go through file till the end
    while (!feof(file) && !feof(input)) {
        // read values and save them to the struct
        fscanf(file, "%lf %lf %lf",
               &myHS->HMCR, &myHS->PAR,
               &myHS->BW);

        // read values and save them to the data struct
        fscanf(input, "%lf %lf %d",
               &myData->min, &myData->max,
               &myData->functionNumber);

        if (myData->max == 314) {
            myData->max = M_PI;
        }

        /*  initialize all the variables  */
        myData->population = fillIn(myData->population, DIM, NS, myData->min, myData->max);
        myData->fitness = getFun(myData->fitness, myData->population, DIM, NS, myData->functionNumber);
        myHS->HSVector = singleArray(DIM);
        myHS->HSfitness = 0.0;
        fitnessCallCounter = 0;

        double *holdb = singleArray(NS);
        double *holdw = singleArray(NS);
        double *replace = singleArray(DIM);

        /* return the initialize variables */
            startHS(myHS, fileOut, filePop, NS, DIM, iterations, myData, fitnessCallCounter,holdb,holdw,replace);
    }
    fclose(file);
    fclose(input);
}


/**
 * Function that runs the HS algorithm
 * @param fileOut file that prints the best solution to a csv
 * @param filePop file that prints the population to a csv
 * @param NS number of solutions for a data type
 * @param DIM number of dimensions for a data type
 * @param iterations number of iterations to run the algorithm for
 * @param myData Data structure pointer for initializing the bounds and which function to run
 * @param fitnessCallCounter count how many times the fitness function was called
 * @param holdb, holds the best solutions
 * @param holdw holds the worst solutions
 * @param replace variable to hold a new arrays elements
 */
void
startHS(HS *myHS, FILE *fileOut, FILE *filePop, const int NS, const int DIM, const int iterations, initData *myData,
        int fitnessCallCounter,double* holdb,double *holdw,double *replace) {
    sortAscendingOrder(myData, NS, DIM, replace);
    // start the clock
    clock_t start;
    start = clock();
    for (int i = 0; i < iterations; ++i) {

        for (int k = 0; k < DIM; ++k) {
            if (genrand_real1() < myHS->HMCR) {
                // take value from population
                int rand = genrand_real1() * (NS - 1);
                myHS->HSVector[k] = myData->population[rand][k];

                // check how to tune the number in the vector
                if (genrand_real1() < myHS->PAR) {
                    updateWithPAR(myHS, myData, k);
                }
            } else {
                myHS->HSVector[k] = (myData->max - (myData->min)) * (genrand_real1()) + myData->min;
            }
        }
        myHS->HSfitness = getFunSingle(myHS->HSfitness, myHS->HSVector, DIM, myData->functionNumber);
        fitnessCallCounter++;

        updateHM(myHS, NS, DIM, myData);

        sortAscendingOrder(myData, NS, DIM, replace);

        holdb[i] = myData->fitness[0];
        holdw[i] = myData->fitness[NS - 1];
    }
    printSingle(fileOut, holdb, NS);
    printSingle(fileOut, holdw, NS);
    start = (((clock() - start)));
    fprintf(fileOut, "Experiment for %d took, %lf, Counter, %d\n",
            myData->functionNumber, ((((double) start) / CLOCKS_PER_SEC) * 1000), fitnessCallCounter);
}


/**
 * Function that updates the values from HS vector
 * @param myHS the HS structure pointer
 * @param myData Data structure pointer for initializing the bounds and which function to run
 * @param k position of the HS vector
 */
void updateWithPAR(HS *myHS, initData *myData, int k) {
    if (genrand_real1() > 0.5) {
        myHS->HSVector[k] += genrand_real1() * myHS->BW;
        checkBounds(k, myData, myHS);
    } else {
        myHS->HSVector[k] -= genrand_real1() * myHS->BW;
        checkBounds(k, myData, myHS);
    }
}

/**
 * Function that checks the values within
 * the vector to see if it within the f(x) bounds
 * @param k position of the HS vector
 * @param myHS the HS structure pointer
 * @param myData Data structure pointer for initializing the bounds and which function to run
 */
void checkBounds(int k, initData *myData, HS *myHS) {
    if (myHS->HSVector[k] < myData->min) {
        myHS->HSVector[k] = myData->min;
    }
    if (myHS->HSVector[k] > myData->max) {
        myHS->HSVector[k] = myData->max;
    }
}

/**
 * Function that updates the population if the vector
 * is better than the worst vector in the population
 * @param myHS the HS structure pointer
 * @param DIM number of dimensions
 * @param myData Data structure pointer for initializing the bounds and which function to run
 */
void updateHM(HS *myHS, int NS, int DIM, initData *myData) {
    if (myHS->HSfitness < myData->fitness[NS - 1]) {
        for (int i = 0; i < DIM; ++i) {
            myData->population[NS - 1][i] = myHS->HSVector[i];
        }
        myData->fitness[NS - 1] = myHS->HSfitness;
    }
}

