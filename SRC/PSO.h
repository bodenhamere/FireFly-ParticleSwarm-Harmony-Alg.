/**
 * @file PSO.h
 */

/**
 * @author Emily Bodenhamer
 *  CWU ID 41119306
 *  CS 471 Optimization Project 4
 *  Date 5/10/2019
 *
 *  Particle Swarm Optimization header file.
 *  This class implements the methods for performing Particle Swarm Optimization
 *  This algorithm models flocking and schooling patters of birds and fishes.
 *  It was invented by Russell Eberhart and James Kennedy in 1995.
 *
 */

#include "Util.h"
#ifndef PROJECT4_471_PSO_H
#define PROJECT4_471_PSO_H


/**
 * @brief
 *
 * Structure for the PSO algorithm
 */
typedef struct _PSO1 {
    double k; //!< Dampening factor (0.8-1.2)
    double c1; //!< value go towards pBest (0-2)
    double c2; //!< value go towards gBest (0-2)
    double gBest; //!< global best solution of the population
    double *pBest; //!< personal best solution by a specific particle
    double **velocity; //!< velocity of the population
} PSO;

/**
 * @brief
 *
 * Function that reads from the PSO input file to
 * initialize the structure variables for the PSO algorithm
 * @param input file that has the values for the myData structure
 * @param fileOut file that has the values for myPSO structure
 * @param filePop file that prints the population to a csv
 * @param iterations number of iterations to run the algorithm for
 * @param fitnessCallCounter count how many times the fitness function was called
 * @param myData Data structure pointer for initializing the bounds and which function to run
 * @param NS number of solutions for a data type
 * @param DIM number of dimensions for a data type
 */
void readInput(FILE *input, FILE *fileOut, FILE *filePop,int iterations, int fitnessCallCounter,initData *myData, int NS, int DIM);

/**
 * @brief
 *
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
void startPSO(FILE *fileFit, FILE *filePop,int NS, int DIM, int iterations, initData *myData, int fitnessCallCounter, PSO *myPSO);

/**
 * @brief
 *
 * Function that updates the velocity for the PSO algorithm
 * @param myPSO the PSO structure pointer
 * @param myData Data structure pointer for initializing the bounds and which function to run
 * @param DIM number of dimensions for a data type
 * @param j position of the vector from the population matrix
 */
void calcVelocity(PSO *myPSO, initData *myData, int DIM, int j);

/**
 * @brief
 *
 * Function that updates the population of our PSO algorithm
 * @param myPSO the PSO structure pointer
 * @param myData Data structure pointer for initializing the bounds and which function to run
 * @param DIM number of dimensions for a data type
 * @param j position of the vector from the population matrix
 */
void calcPopulation(PSO *myPSO, initData *myData,int DIM,int j);
#endif //PROJECT4_471_PSO_H
