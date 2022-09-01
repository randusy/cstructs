/*
 ================================================================================
 Name        : data.h
 Author      : Randu Karisa
 Version     :
 Copyright   : Your copyright notice
 Description : Set of functions to compute data on a data structure
 ================================================================================
 */
#ifndef STATS_H
#define STATS_H

#include <stdlib.h>
#include <stdio.h>
#include "array.h"
#include "data.h"
#include <math.h>
/******************************************************************************************
 * FUNCTIONS FOR INTEGER ARRAY
 ******************************************************************************************/
/**
 *addIntegerArrays function, Adds two integer arrays
 *@param array1, The array to be added to the other
 *@param array2, The array to be added to the other
 *@return sum, An array, the sum of the two arrays
 *Note: if arrays are of different size, The longer one will be trimmed
 */
 struct IntegerArray* addIntegerArrays(const struct IntegerArray* array1,const struct IntegerArray* array2)
{
	struct IntegerArray* ints = newIntegerArray();
	int diff;
	if(*getIntegerArraySize(array1) < *getIntegerArraySize(array2))
	{
		diff =  (*getIntegerArraySize(array2)) - (*getIntegerArraySize(array1));
		for (int i = 0; i < array1->size; ++i)
				addToIntegerArray(ints, (*getIntegerValue(array1, i))+(*getIntegerValue(array2, i+diff)));
	}
	else
	{
		diff =  (*getIntegerArraySize(array1)) - (*getIntegerArraySize(array2));
		for (int i = 0; i < (array2)->size; ++i)
				addToIntegerArray(ints,(* getIntegerValue(array1, i+diff))+(*getIntegerValue(array2, i)));
	}
	return ints;
}
/**
 *diffIntegerArrays function, Finds the difference of two arrays
 *@param array1, The array to find the difference from
 *@param array2, The array to find the difference to
 *@return array, An array the difference of the two arrays
 *Note: if arrays are of different size, The longer one will be trimmed
 */
 struct IntegerArray* diffIntegerArrays(const struct IntegerArray* array1,const struct IntegerArray* array2)
{
	struct IntegerArray* ints = newIntegerArray();
	int diff;
	if(*getIntegerArraySize(array1) < *getIntegerArraySize(array2))
	{
		diff =  *getIntegerArraySize(array2) - *getIntegerArraySize(array1);
		for (int i = 0; i < (array1)->size; ++i)
				addToIntegerArray(ints, *getIntegerValue(array1, i)- *getIntegerValue(array2, i+diff));
	}
	else
	{
		diff =  *getIntegerArraySize(array1) - *getIntegerArraySize(array2);
		for (int i = 0; i < (array2)->size; ++i)
				addToIntegerArray(ints, *getIntegerValue(array1, i+diff)- *getIntegerValue(array2, i));
	}
	return ints;
}
/**
 *prodIntegerArrays function, calculate the product of two arrays
 *@param array1, Array to calculate the product
 *@param array2, Array to calculate the product
 *@return array, Array, The product of the two
 *Note: if arrays are of different size, The longer one will be trimmed
 */
 struct IntegerArray* prodIntegerArrays(const struct IntegerArray* array1,const struct IntegerArray* array2)
{
	struct IntegerArray* ints = newIntegerArray();
	int diff;
	if(*getIntegerArraySize(array1) < *getIntegerArraySize(array2))
	{
		diff =  *getIntegerArraySize(array2) - *getIntegerArraySize(array1);
		for (int i = 0; i < (array1)->size; ++i)
				addToIntegerArray(ints, (*getIntegerValue(array1, i))*(*getIntegerValue(array2, i+diff)));
	}
	else
	{
		diff =  *getIntegerArraySize(array1) - *getIntegerArraySize(array2);
		for (int i = 0; i < (array2)->size; ++i)
				addToIntegerArray(ints, (*getIntegerValue(array1, i+diff))*(*getIntegerValue(array2, i)));
	}
	return ints;
}

/**
 *sumIntegerArray function, Calculated the sum of all the values in an array
 *@param array, The array holding the values
 *@return sum, Integer the sum of all the values
 */
const int sumIntegerArray(const struct IntegerArray* array)
{
	int sum = 0;
	for (int i = 0; i < array->size; ++i)
		sum = sum + (*getIntegerValue(array, i));
	return sum;
}
/**
 *sumAbsIntegerArray function, Calculate the absolute sum of all the values in the array
 *@param array, The array holding the values
 *@return sum
 */
int sumAbsIntegerArray(const struct IntegerArray* array)
{
	int sum = 0;
	for (int i = 0; i < array->size; ++i)
		sum = sum + abs(*getIntegerValue(array, i));
	return sum;
}
/**
 *meanIntegerArray function, Calculates the mean of the array
 *@return mean of the array
 */
double meanIntegerArray(const struct IntegerArray* array)
{
	return (double) sumIntegerArray(array)/array->size;
}
/**
 *scalarDiffIntegerArrays function, Calculate the difference of the array using a scalar value
 *@param array, The array to find its difference
 *@param scalar, The value to subtract
 *@return array, The resulting array
 */
struct IntegerArray* scalarDiffIntegerArrays(const struct IntegerArray* array1,const int scalar)
{
	struct IntegerArray* doubles = newIntegerArray();
	for(int i = 0; i < (array1)->size; ++i)
			addToIntegerArray(doubles, *getIntegerValue(array1,i) - scalar);
	return doubles;
}
/**
 *corrIntegerArray function, Calculates the correlation between two arrays
 *@param array1, The X array
 *@param array3, The Y array
 *@return double, The correlation coefficient
 *Note: if arrays are of different size, The longer one will be trimmed
 */
double corrIntegerArray(const struct IntegerArray* array1,const struct IntegerArray* array2)
{
	struct IntegerArray* diffx = (scalarDiffIntegerArrays(array1, meanIntegerArray(array1)));
	struct IntegerArray* diffy = (scalarDiffIntegerArrays(array2, meanIntegerArray(array2)));

	struct IntegerArray* prod = prodIntegerArrays(diffx,diffy);
	int prodUpper = sumIntegerArray(prod);

	struct IntegerArray* prodx = prodIntegerArrays(diffx,diffx);
	struct IntegerArray* prody = prodIntegerArrays(diffy,diffy);

	int sumx = sumIntegerArray(prodx);
	int sumy = sumIntegerArray(prody);

	freeIntegerArray(prod);
	freeIntegerArray(prodx);
	freeIntegerArray(prody);
	freeIntegerArray(diffx);
	freeIntegerArray(diffy);

	double prodLower = sqrt(sumx*sumy);
	return (prodUpper/prodLower);
}
/******************************************************************************************
 * FUNCTIONS FOR DOUBLE ARRAY
 ******************************************************************************************/
/**
 *addDoubleArrays function, adds two arrays
 *@param array1, The first array
 *@param array2, The second array
 *@param array, The sum of the two arrays
 *Note: if arrays are of different size, The longer one will be trimmed
 */
struct DoubleArray* addDoubleArrays(const struct DoubleArray* array1,const struct DoubleArray* array2)
{
	struct DoubleArray* doubles = newDoubleArray();
	double diff;
	if(*getDoubleArraySize(array1) < *getDoubleArraySize(array2))
	{
		diff =  *getDoubleArraySize(array2) - *getDoubleArraySize(array1);
		for (int i = 0; i < *getDoubleArraySize(array1); ++i)
				addToDoubleArray(doubles, (*getDoubleValue(array1, i))+(*getDoubleValue(array2, i+diff)));
	}
	else
	{
		diff =  *getDoubleArraySize(array1) - *getDoubleArraySize(array2);
		for (int i = 0; i < *getDoubleArraySize(array2); ++i)
				addToDoubleArray(doubles, (*getDoubleValue(array1, i+diff))+(*getDoubleValue(array2, i)));
	}
	return doubles;
}
/**
 *diffDoubleArrays function, Finds the difference between two arrays
 *@param array1, The first array
 *@param array2, The second array
 *@return array, The difference between the two
 *Note: if arrays are of different size, The longer one will be trimmed
 */
struct DoubleArray* diffDoubleArrays(const struct DoubleArray* array1,const struct DoubleArray* array2)
{
	struct DoubleArray* doubles = newDoubleArray();
	double diff;
	if(*getDoubleArraySize(array1) < *getDoubleArraySize(array2))
	{
		diff =  *getDoubleArraySize(array2) - *getDoubleArraySize(array1);
		for (int i = 0; i < *getDoubleArraySize(array1); ++i)
				addToDoubleArray(doubles, (*getDoubleValue(array1, i))-(*getDoubleValue(array2, i+diff)));
	}
	else
	{
		diff =  *getDoubleArraySize(array1) - *getDoubleArraySize(array2);
		for (int i = 0; i < *getDoubleArraySize(array2); ++i)
				addToDoubleArray(doubles, (*getDoubleValue(array1, i+diff))-(*getDoubleValue(array2, i)));
	}
	return doubles;
}
/**
 *prodDoubleArrays function, Finds the product of the two arrays
 *@param array1, The first array
 *@param array2, The second array
 *@return array, The resulting array
 *Note: if arrays are of different size, The longer one will be trimmed
 */
struct DoubleArray* prodDoubleArrays(const struct DoubleArray* array1,const struct DoubleArray* array2)
{
	struct DoubleArray* doubles = newDoubleArray();
	double diff;
	if(*getDoubleArraySize(array1) < *getDoubleArraySize(array2))
	{
		diff =  *getDoubleArraySize(array2) - *getDoubleArraySize(array1);
		for (int i = 0; i < *getDoubleArraySize(array1); ++i)
				addToDoubleArray(doubles, (*getDoubleValue(array1, i))*(*getDoubleValue(array2, i+diff)));
	}
	else
	{
		diff =  *getDoubleArraySize(array1) - *getDoubleArraySize(array2);
		for (int i = 0; i < *getDoubleArraySize(array2); ++i)
				addToDoubleArray(doubles, (*getDoubleValue(array1, i+diff))*(*getDoubleValue(array2, i)));
	}
	return doubles;
}
/**
 *sumDoubleArray function, Finds the sum of the array
 *@param array, The array to find the sum of its values
 *@return sum, Double value representing the sum
 */
double sumDoubleArray(const struct DoubleArray* array)
{
	double sum = 0.0;
	for (int i = 0; i < array->size; ++i)
		sum = sum + (*getDoubleValue(array, i));
	return sum;
}
/**
 *sumAbsDoubleArray function, Finds the absolute sum of the array
 *@param array, The array to find the sum of its values
 *@return sum, Double value representing the absolute sum
 */
double sumAbsDoubleArray(const struct DoubleArray* array)
{
	double sum = 0.0;
	for (int i = 0; i < array->size; ++i)
		sum = sum + fabs(*getDoubleValue(array, i));
	return sum;
}
/**
 *meanDoubleArray function, Finds the mean of the array
 *@param array, The array to find the mean of its values
 *@return mean, Double value representing the sum
 */
double meanDoubleArray(const struct DoubleArray* array)
{
	if(*getDoubleArraySize(array) > 0)
		return (double) sumDoubleArray(array)/(*getDoubleArraySize(array));
	else
		return 0.0;
}
/**
 *scalarDiffDoubleArrays function, Finds the difference of the array with a scalar value
 *@param array, The array to subtract the scalar
 *@param scalar, The value to subtract from the array
 *@return array, The resulting array
 */
struct DoubleArray* scalarDiffDoubleArrays(const struct DoubleArray* array,const double scalar)
{
	struct DoubleArray* doubles = newDoubleArray();
	for(int i = 0; i < *getDoubleArraySize(array); ++i)
			addToDoubleArray(doubles, *getDoubleValue(array,i) - scalar);
	return doubles;
}
/**
 *corrDoubleArray function, Finds the correlation of the arrays
 *@param array1, The X array
 *@param array2, The Y array
 *@return correlation, The correlation coefficient
 */
double corrDoubleArray(const struct DoubleArray* array1,const struct DoubleArray* array2)
{
	struct DoubleArray* diffx = (scalarDiffDoubleArrays(array1, meanDoubleArray(array1)));
	struct DoubleArray* diffy = (scalarDiffDoubleArrays(array2, meanDoubleArray(array2)));

	struct DoubleArray* prod = prodDoubleArrays(diffx,diffy);
	double prodUpper = sumDoubleArray(prod);

	struct DoubleArray* prodx = prodDoubleArrays(diffx,diffx);
	struct DoubleArray* prody = prodDoubleArrays(diffy,diffy);

	double sumx = sumDoubleArray(prodx);
	double sumy = sumDoubleArray(prody);

	freeDoubleArray(prod);
	freeDoubleArray(prodx);
	freeDoubleArray(prody);
	freeDoubleArray(diffx);
	freeDoubleArray(diffy);

	double prodLower = sqrt(sumx*sumy);
	return (prodUpper/prodLower);
}
#endif
