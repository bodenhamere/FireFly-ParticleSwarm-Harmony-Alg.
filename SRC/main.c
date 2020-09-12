/**
 * @file main.c
 */
/**
 * @author Emily Bodenhamer
 *  CWU ID 41119306
 *  CS 471 Optimization Project 4
 *  Date 5/10/2019
 *
 *  This project implements three meta-heuristic optimization algorithms.
 *  Particle Swarm Optimization (PSO), Firefly Algorithm (FA), and Harmony Search Algorithm (HS).
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "ArrayMem.h"
#include "SelectFunction.h"
#include "Util.h"
#include "mt19937ar.h"
#include "PSO.h"
#include "FA.h"
#include "HS.h"

/**
 * main method that performs PSO, FA, and HS
 * \return 0
 */
int main() {
    init_genrand(time(0));
    int NS = 500; //!< number of solutions
    int DIM = 30; //!< number of dimensions
    int iterations = 500; //!< number of iterations
    int fitnessCallCounter = 0; //!< function call counter
    // create structure object
    initData *myData;
    myData = (initData *) calloc(1, sizeof(initData));

    // create file to read and write to
    FILE *file;
    FILE *PSOfileOUT;
    FILE *FAfileOUT;
    FILE *HSfileOUT;
    FILE *PSOfilePOP;
    FILE *FAfilePOP;
    FILE *HSfilePOP;
    file = fopen("mainInput.txt", "r");
    PSOfileOUT = fopen("PSOFit.csv", "w+");
    FAfileOUT = fopen("FAFit.csv", "w+");
    HSfileOUT = fopen("HSFit2.csv", "w+");
    PSOfilePOP = fopen("PSOPop.csv", "w+");
    FAfilePOP = fopen("FAPop.csv", "w+");
    HSfilePOP = fopen("HSPop.csv", "w+");

    // check if inputs.txt exists
    if (file == NULL) {
        printf("Error opening inputs.txt file, make sure the file is in the cmake-build-debug folder\n");
        exit(1);
    }
    myData->population = createDblArray(NS, DIM);
    myData->fitness = singleArray(NS);

    // start PSO
    readInput(file, PSOfileOUT, PSOfilePOP, iterations, fitnessCallCounter, myData, NS, DIM);

    // start FA
    readInputFA(file, FAfileOUT, FAfilePOP, iterations, fitnessCallCounter, myData, NS, DIM);

    // start HS
    readInputHS(file, HSfileOUT, HSfilePOP, iterations, fitnessCallCounter, myData, NS, DIM);

    // free memory from matrix and result
    freeMem(NS, myData->population);
    free(myData->fitness);

}