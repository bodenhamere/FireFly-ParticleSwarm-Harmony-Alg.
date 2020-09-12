/**
 * @file HS.h
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

#ifndef PROJECT4_471_HS_H
#define PROJECT4_471_HS_H

#include "Util.h"

/**
 * @brief
 *
 * Structure for the HS algorithm
 */
typedef struct _HS1 {
    double HMCR; //!< Harmony Memory Considering Rate; (0.7-0.95)
    double PAR; //!< Pitch Adjusting Rate; (0.1-0.5)
    double BW; //!< Bandwidth; (0.2)
    double *HSVector; //!< a new harmony vector
    double HSfitness; //!< new harmony fitness vector
} HS;

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
void readInputHS(FILE *input, FILE *fileOut, FILE *filePop, int iterations, int fitnessCallCounter,initData *myData, int NS, int DIM);

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
void startHS(HS *myHS, FILE *fileOut, FILE *filePop, int NS, int DIM, int iterations, initData *myData, int fitnessCallCounter,double* holdb,double *holdw,double *replace);

/**
 * Function that updates the values from HS vector
 * @param myHS the HS structure pointer
 * @param myData Data structure pointer for initializing the bounds and which function to run
 * @param k position of the HS vector
 */
void updateWithPAR(HS *myHS, initData *myData, int k);

/**
 * Function that checks the values within
 * the vector to see if it within the f(x) bounds
 * @param k position of the HS vector
 * @param myHS the HS structure pointer
 * @param myData Data structure pointer for initializing the bounds and which function to run
 */
void checkBounds(int k, initData *myData, HS *myHS);

/**
 * Function that updates the population if the vector
 * is better than the worst vector in the population
 * @param myHS the HS structure pointer
 * @param DIM number of dimensions
 * @param myData Data structure pointer for initializing the bounds and which function to run
 */
void updateHM(HS *myHS, int NS, int DIM, initData *myData);

#endif //PROJECT4_471_HS_H
