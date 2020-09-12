/**
 * @file SelectFunctions.h
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

#ifndef INC_471PROJECT_GOFUN_H
#define INC_471PROJECT_GOFUN_H

/**
 * @brief
 * Calls an f(x) function based on if the counter is at a certain number
 * The arr is passed to the function and saved into a single pointer array
 * \param results single pointer array
 * \param arr double pointer array
 * \param row the size of the rows of the array
 * \param col the size of the columns of the array
 * \param counter the case specified
 */
double * getFun(double * results, double **arr, int row, int col,int counter);

/**
 * @brief
 * Calls an f(x) function based on if the counter is at a certain number
 * The arr is passed to the function and saved into a single pointer array
 * \param results a double
 * \param arr single pointer array
 * \param row the size of the rows of the array
 * \param counter the case specified
 */
double getFunSingle(double results, double *arr, int row, int counter);


#endif //INC_471PROJECT_GOFUN_H
