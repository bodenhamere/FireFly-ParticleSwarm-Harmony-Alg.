/**
 * @file FA.h
 */
/**
 * @author Emily Bodenhamer
 *  CWU ID 41119306
 *  CS 471 Optimization Project 4
 *  Date 5/10/2019
 *
 *  Firefly Algorithm header file.
 *  This class implements the methods for performing the Firefly Algorithm
 *  This algorithm models the social behavior of fireflies based on the flashing
 *  and attraction characteristics of fireflies.
 *  It was developed by Yang in 2010.
 *
 */

#ifndef PROJECT4_471_FA_H
#define PROJECT4_471_FA_H
#include "Util.h"

/**
 * @brief
 *
 * Structure for the FA algorithm
 */
typedef struct _FA1 {
    double alpha; //!< constant parameter (0.5)
    double betaMin; //!< constant parameter(0.2)
    double gamma; //!< light absorption coefficient (.01-100)
    double beta; //!< attractiveness of a firefly
    double r; //!< the distance from one firefly to another
    double *intensity; //!< the intensity from one firefly to another
    double *newXi; //!< new vector for the population
    int index; //!< keeps track of the worst fitness' index
    double *tempFitness; //!< temporary fitness for the copied population
    double newXiFitness; //!<  fitness for the new vector for the population
    double **tempPopulation; //!< temporary population copy
    double *I0; //! initial light intensity
} FA;


/**
 * @brief
 *
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
void readInputFA(FILE *input, FILE *fileOut, FILE *filePop, int iterations, int fitnessCallCounter, initData *myData, int NS, int DIM);

/**
 * @brief
 *
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
void startFA(FA *myFA, FILE *fileOut, FILE *filePop, int NS, int DIM, int iterations, initData *myData, int fitnessCallCounter);

/**
 * @brief
 *
 * Function that updates Beta
 * @param myFA the FA structure pointer
 * @return Beta
 */
double Eqn2(FA *myFA);

/**
 * @brief
 *
 * Function that finds the distance between two fireflies
 * @param xi firefly vector at i
 * @param xj firefly vector at j
 * @param DIM number of dimensions for a data type
 * @param myFA the PSO structure pointer
 */
void Eqn3(const double * xi, const double *xj, int DIM, FA *myFA);

/**
 * @brief
 *
 * Function that creates a new firefly vector,
 * checks if the vector is better than the worst firefly in the population
 * @param xi firefly vector at i
 * @param xj firefly vector at j
 * @param DIM number of dimensions for a data type
 * @param myFA the PSO structure pointer
 * @param myData Data structure pointer for initializing the bounds and which function to run
 */
void Eqn4(const double *xi, const double *xj, int DIM, FA *myFA, initData *myData);

/**
 * @brief
 *
 * Function that updates the intensity of the fireflies
 * @param xi firefly vector at i
 * @param xj firefly vector at j
 * @param DIM number of dimensions for a data type
 * @param myFA the PSO structure pointer
 * @param myData Data structure pointer for initializing the bounds and which function to run
 */
double updateIntensity(FA *myFA,int j);

#endif //PROJECT4_471_FA_H
