/**
* @file sort.h
* @author Melih Altun @2015
**/

#include<string.h>  //for memcpy

#define CPP_BUILD

#if !defined (CPP_BUILD)
#include<stdlib.h>  //for malloc and free
#include<stdbool.h>
#endif

void bSort(double out[], double in[], unsigned int length, bool option); //buble sort
void csSort(double out[], double in[], unsigned int length, bool option); //coctail shaker sort
void mSort(double out[], double in[], unsigned int length, bool option); //merge sort
void qSort(double out[], double in[], unsigned int length, bool option); //quick sort
void cSort(double out[], double in[], unsigned int length, bool option); //comb sort
void iSort(double out[], double in[], unsigned int length, bool option); //insertion sort
void sSort(double out[], double in[], unsigned int length, bool option); //selection sort
void hSort(double out[], double in[], unsigned int length, bool option); //heap sort

#if defined(CPP_BUILD)

void bSort(double inOut[], unsigned int length, bool option);  //in place bubble sort
void csSort(double inOut[], unsigned int length, bool option); //in place coctail shaker
void mSort(double A[], unsigned int length, bool option); //in place merge sort
void qSort(double inOut[], unsigned int length, bool option); //in place quick sort
void cSort(double inOut[], unsigned int length, bool option); //in place comb sort
void iSort(double inOut[], unsigned int length, bool option); //in place insertion sort
void sSort(double inOut[], unsigned int length, bool option); //in place selection sort
void hSort(double inOut[], unsigned int length, bool option); //in place heap sort

#else

void bSortInPlace(double inOut[], unsigned int length, bool option);  //in place bubble sort
void csSortInPlace(double inOut[], unsigned int length, bool option); //in place coctail shaker
void mSortInPlace(double A[], unsigned int length, bool option); //in place merge sort
void qSortInPlace(double inOut[], unsigned int length, bool option); //in place quick sort
void cSortInPlace(double inOut[], unsigned int length, bool option); //in place comb sort
void iSortInPlace(double inOut[], unsigned int length, bool option); //in place insertion sort
void sSortInPlace(double inOut[], unsigned int length, bool option); //in place selection sort
void hSortInPlace(double inOut[], unsigned int length, bool option); //in place heap sort

#endif

double medianQuickSelect(double in[], unsigned int length);   //Quick Select algo to find median of a series
double quickSelect(double in[], unsigned int length, unsigned int n);  //Quick select to find n'th element of a series
