/*
 ================================================================================
 Name        : array.h
 Author      : Randu Karisa
 Version     :
 Copyright   : Your copyright notice
 Description : Set of functions to create, populate and print an array.
 	 	 	 : Contains structures IntegerArray, DoubleArray, StringArray,
 	 	 	 : String2DArray
 ================================================================================
 */
#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define ARRAY_LENGTH 100 //The block of memory allocate to the array
#define FALSE 0
#define TRUE 1


/***************************************************************************************
 * AN ARRAY OF INTEGERS
 * ************************************************************************************/
/**
 *IntegerArray Structure
 *@attrib size, Pointer to an integer holding the size of the array
 *@attrib length, Pointer to an integer holding the allocated
 *				  memory size in heap.
 *@attrib array, Pointer to an integer holding the array of integers
 */
struct IntegerArray{
	int size;
	int length;
	int* array;
};
/**
 * getIntegerArraySize function, gets the size of the array of an
 * 	holding integers
 * @param array, the array to determine its size
 * @return size, the size of the array
 */
const int* getIntegerArraySize(const struct IntegerArray* array)
{
	return &(array->size);
}
/**
 * getIntegerValue function, Gets the integer of the array at the
 * 	given index
 *@param index, the index of the integer
 *@return pointer to integer value in the array
 *Note: The application exits if the index is out of range
 */
const int* getIntegerValue(const struct IntegerArray* array,const int index)
{
	if(index > -1 && index < array->size)
		return (array->array+(index));
	else
	{
		printf("RuntimeError: Array Index %d is out of bounds, Accepted indices 0-%d\n",index,array->size-1);
		exit(1);
	}
}
/**
 *setIntegerValue function, Sets the value at the given index of the array
 *@param array, The array to set the value at the given index
 *@param index, The value to set in the array
 */
void setIntegerValue(struct IntegerArray* array,const int value, const int index)
{
	if(index < array->size)
		*(array->array+index) = value;
}
/**
 *reverseIntegerArray function, Reverses the array
 *@param array, the array to reverse
 */
void reverseIntegerArray(struct IntegerArray* array)
{
	int end = array->size;
	for (int i = 0; i < end; ++i) {
		int temp = *getIntegerValue(array, i);
		setIntegerValue(array, *getIntegerValue(array, end-1),i);
		setIntegerValue(array, temp,end-1);
		end--;
	}
}
/**
 * newIntegerArray function, create a new array of integers and allocates
 * 	memory in the heap
 * 	@return array, an array of integers
 */
struct IntegerArray *newIntegerArray()
{
	struct IntegerArray *array =(struct IntegerArray*) malloc(sizeof(struct IntegerArray));
	array->array = malloc(sizeof(int)*ARRAY_LENGTH);
	array->length = ARRAY_LENGTH;
	array->size = 0;
	return array;
}
/**
 *addToIntegerArray function, Adds an integer value to an array
 *@param array, the array to and the value at the end
 *@param value, the integer value to store in the array
 */
void addToIntegerArray(struct IntegerArray* array,const int value)
{
	if(array->size == array->length)
	{
		int length = array->length;
		int* newPointer = malloc(sizeof(int)* (length+ARRAY_LENGTH));
		for(int i=0; i<array->size; i++)
			*(newPointer+i) = *(array->array+i);
		free(array->array);
		array->array = newPointer;
		array->length = length+ARRAY_LENGTH;
	}
	int size = array->size;
	*(array->array+size) = value;
	array->size = (size + 1);
}
/**
 *printIntegerArray function, Prints the array to the console
 *@param array, The array to traverse and print its contents
 */
void printIntegerArray(const struct IntegerArray* array)
{
	printf("[");
	for (int i = 0; i < array->size; ++i) {
		if(i == 20 && array->size > 100){
			i = (array->size) - 20;
			printf("... ");
		}
		printf("%d",*(array->array+i));
		if(i != array->size-1)
			printf(", ");
	}
	printf("]\n");
}
/**
 * freeIntegerArray function, Frees the memory to an array of integers
 *@param array, The array to free its memory
 */
void freeIntegerArray(struct IntegerArray* array)
{
	free(array->array);
	free(array);
}
/***************************************************************************************
 * AN ARRAY OF DOUBLES
 * ************************************************************************************/

/**
 *DoubleArray structure, A structure to hold the array and its attributes
 *@attrib size, Stores the size of the array
 *@attrib length, Stores the allocated block length in heap
 *@attrib array, A pointer to an array of doubles
 */
struct DoubleArray{
	int size;
	int length;
	double* array;
};

/**
 *getDoubleArraySize function, gets the size of the array
 *@param array, The array to get its size
 */
const int* getDoubleArraySize(const struct DoubleArray* array)
{
	return &array->size;
}
/*
 *getDoubleValue function, Gets the value at the given index
 *@param array, The array to get the value from
 *@param index, The index of the value
 */
const double* getDoubleValue(const struct DoubleArray* array, const int index)
{
	if(index > -1 && index < array->size)
		return (array->array+index);
	else
	{
		printf("RuntimeError: Array Index %d is out of bounds, Accepted indices 0-%d\n",index,array->size-1);
		exit(1);
	}
}
/**
 *setDoubleValue function, sets the value in the array at the given index
 *@param array, The array to set its value
 *@param index, The index to set the value in the array
 *@param value, The value to be set
 */
void setDoubleValue(struct DoubleArray* array,const double value,const int index)
{
	if(index > -1 && index < array->size)
		*(array->array+index) = value;
	else
	{
		printf("RuntimeError: Array Index %d is out of bounds, Accepted indices 0-%d\n",index,array->size-1);
		exit(1);
	}
}
/**
 *reverseDoubleArray function, Reverses the array
 *@param array, The array to reverse
 */
void reverseDoubleArray(struct DoubleArray* array)
{
	int end = array->size;
	for (int i = 0; i < end; ++i) {
		double temp = *getDoubleValue(array, i);
		setDoubleValue(array, i, *getDoubleValue(array, end-1));
		setDoubleValue(array, end-1, temp);
		end--;
	}
}
/**
 *newDoubleArray function, Creates a new array
 *@return array, Pointer to the newly created array of doubles
 */
struct DoubleArray *newDoubleArray()
{
	struct DoubleArray *array =(struct DoubleArray*) malloc(sizeof(struct DoubleArray));
	array->array = malloc(sizeof(double)*ARRAY_LENGTH);
	array->length = ARRAY_LENGTH;
	array->size = 0;
	return array;
}
/**
 *addToDoubleArray function, Adds a value to the array
 *@param array, The array to add values
 *@param value, The value to be added
 */
void addToDoubleArray(struct DoubleArray* array,const double value)
{
	if(array->size == array->length)
	{
		int length = array->length;
		double* newPointer = malloc(sizeof(double)* (length+ARRAY_LENGTH));
		for(int i=0; i<array->size; i++)
			*(newPointer+i) = *(array->array+i);
		free(array->array);
		array->array = newPointer;
		array->length = length+ARRAY_LENGTH;
	}
	int size = array->size;
	*(array->array+size) = value;
	array->size = (size + 1);
}
/**
 *printDoubleArray function, Prints the array to the console
 *@param array, The array to print its contents
 */
void printDoubleArray(const struct DoubleArray* array)
{
	printf("[");
	for (int i = 0; i < array->size; ++i) {
		if(i == 20 && array->size > 100){
			i = (array->size) - 20;
			printf("... ");
		}
		printf("%.2f",*(array->array+i));
		if(i != array->size-1)
			printf(", ");
	}
	printf("]\n");
}
/**
 *freeDoubleArray function, Frees memory allocated to the array in heap
 */
void freeDoubleArray(struct DoubleArray* array)
{
	free(array->array);
	free(array);
}

/***************************************************************************************
 * AN ARRAY OF CHARACTERS ==> <String>
 * ************************************************************************************/
/**
 * String structure, A structure representing a string
 *Attrib size,The length of the string
 *Attrib string, Pointer to an array of chars
 */
struct String{
	int size;
	char* string;
};
/**
 *newString function, Creates a new string and allocate memory in heap
 *@param stringLiteral, Pointer to characters to create  the string from
 *@return string, Pointer to the string
 */
struct String* newString(char* stringLiteral)
{
	char* string = malloc(sizeof(char)*(strlen(stringLiteral)+1));
	struct String* str = (struct String*) malloc( sizeof(struct String));
	str->size = strlen(stringLiteral);
	strcpy(string,stringLiteral);
	str->string = string;
	return str;
}
/**
 *changeString function, Changes the string contents to the newly provides
 *@param string, The string to change
 *@param stringLiteral, The string to change too
 */
void changeString(struct String* string,const char* stringLiteral)
{
	char* str = malloc(sizeof(char)*(strlen(stringLiteral)+1));
	free(string->string);
	strcpy(str,stringLiteral);
	string->string = str;
	string->size = strlen(stringLiteral);
}
/**
 *freeString function, The string to free its memory
 */
void freeString(struct String* string)
{
	free(string->string);
	free(string);
}
/***************************************************************************************
 * AN ARRAY OF STRINGS ==> ArrayList<String>
 * ************************************************************************************/
/**
 *StringArray structure, represents an array of strings
 *@Attrib size, The size of the array
 *@Attrib length, The allocated block of memory in heap
 *@Attrib array, The array of strings
 */
struct StringArray{
	int size;
	int length;
	char** array;
};

/**
 *getStringArraySize function, Gets the size of the array
 *@param array, The array to get its size
 *@return size, Reference to the size
 */
const int *getStringArraySize(const struct StringArray* array)
{
	return &array->size;
}

/*
 *getString function, Gets the string at the specified index
 *@param array, The array to get its the string from
 *@param index, The location where the string is
 *@return string, Pointer to the string
 *Note: Application exits with a message if index is out of bounds
 */
const char* getString(const struct StringArray *array,const int index)
{
	if(index > -1 && index < array->size)
		return *(array->array+index);
	else
	{
		printf("RuntimeError: Array Index %d is out of bounds, Accepted indices 0-%d\n",index,array->size-1);
		exit(1);
	}
}
/**
 *changeStringArray function, Changes the value of the array at a given index
 *@param array, The array to change its value
 *@param stringLiteral, The value to change
 *@param index, The location to change the string
 */
void changeStringArray(struct StringArray* array,const char* stringLiteral,const int index)
{
	if(index > -1 && index < array->size){
		free(*(array->array+index));
		char* string = malloc(sizeof(char)*(strlen(stringLiteral)+1));
		strcpy(string,stringLiteral);
		*(array->array+index) = string;
	}else
	{
		printf("RuntimeError: Array Index %d is out of bounds, Accepted indices 0-%d\n",index,array->size-1);
		exit(1);
	}
}
/**
 * reverseStringArray function, Reverses the array
 */
void reverseStringArray(struct StringArray* array)
{
	int end = array->size;
	for (int i = 0; i < end; ++i) {
		const char* temp = getString(array, i);
		changeStringArray(array, getString(array, end-1),i);
		changeStringArray(array,temp, end-1);
		end--;
	}
}
/**
 *newStringArray function, Create a new array and allocate memory in heap
 *@return array, The newly created array
 */
struct StringArray *newStringArray()
{
	struct StringArray *array =(struct StringArray*) malloc(sizeof(struct StringArray));
	array->array = malloc(sizeof(char*)*ARRAY_LENGTH);
	array->length = ARRAY_LENGTH;
	array->size = 0;
	return array;
}
/**
 *addToStringArray function, Adds a string to the array
 *@param array, The array to populate
 *@param string, The string to be added
 */
void addToStringArray(struct StringArray* array,const char* string)
{
	if(array->size == array->length)
	{
		int length = array->length;
		char** newPointer = malloc(sizeof(char*)* (length+ARRAY_LENGTH));
		for(int i=0; i<array->size; i++)
			*(newPointer+i) = *(array->array+i);
		free(array->array);
		array->array = newPointer;
		array->length = length+ARRAY_LENGTH;
	}
	int size = array->size;
	char* s = malloc(sizeof(char)*strlen(string)+1);
	strcpy(s,string);
	*(array->array+size) = s;
	array->size = (size + 1);
}

/**
 *printStringArray function, Prints the array to the console
 *@param array, The array to print
 */
void printStringArray(const struct StringArray* array)
{
	printf("[");
	for (int i = 0; i < array->size; ++i) {
		if(i == 20 && array->size > 100){
				i = (array->size) - 20;
				printf("... ");
			}
		printf("%s",*(array->array+i));
		if(i != array->size-1)
			printf(", ");
	}
	printf("]\n");
}
/**
 *freeStringArray function, Frees the array in memory
 *@param array, The array to free its memory
 */
void freeStringArray(struct StringArray* array)
{
	for (int i = 0; i < array->size; ++i)
		free(*(array->array+i));
	free(array->array);
	free(array);
}
/***************************************************
 * STRING 2D ARRAY
 **************************************************/
/**
 *String2DArray structure, Represents a two dimensional array of strings
 *@Attrib length, The block length of the memory allocation in heap
 *@Attrib size, The size of the array i.e size of rows
 *@Attrib sets, A string representing a set of data belonging to an index
 *@Attrib setSize, The size of the blocks/sets of the array
 *@Attrib indexColumn, The column to create the block from
 */
struct String2DArray{
	struct StringArray** stringArray;
	int length;
	int size;
	struct String** sets;
	int setsSize;
	int indexColumn;
};

/**
 *newString2DArray function, Creates a new two dimensional array and allocate
 *	memory in heap
 *@return array, The two dimensional array
 */
struct String2DArray *newString2DArray()
{
	struct String2DArray *array =(struct String2DArray*) malloc(sizeof(struct String2DArray));
	array->stringArray = (struct StringArray**) malloc(sizeof(struct StringArray*)*ARRAY_LENGTH);
	array->sets = (struct String**) malloc(sizeof(char*)*ARRAY_LENGTH);
	array->length = ARRAY_LENGTH;
	array->size = 0;
	array->setsSize = 0;
	array->indexColumn = 0;
	return array;
}

/**
 *addToString2DArray function, Adds an array of strings to the 2D array
 *@param array, The 2D array
 *@param pointer, The one dimension array
 *@param indexColumn, Specifies the column to be used as index,
 *					Important for fast retrieval of data.
 */
void addToString2DArray(struct String2DArray* array, struct StringArray* pointer,const int indexColumn)
{
	if(array->size == array->length)
	{
		int length = array->length;
		struct StringArray** newPointer = (struct StringArray**) malloc(sizeof(struct StringArray*)* (length+ARRAY_LENGTH));
		for(int i=0; i<array->size; i++)
		{
			*(newPointer+i) = *(array->stringArray+i);
		}
		free(array->stringArray);
		array->stringArray = newPointer;
		array->length = length+ARRAY_LENGTH;
		struct String** newStringPointer = (struct String**) malloc(sizeof(struct String*)* (array->length));
		for (int i = 0; i < array->setsSize; ++i) {
			*(newStringPointer+i) = *(array->sets+i);
		}
		free(array->sets);
		array->sets = newStringPointer;
	}

	int size = array->size;
	*(array->stringArray+size) = pointer;

	int setsSize = array->setsSize;

	if(size == 0){
		if(indexColumn >= pointer->size || indexColumn < 0)
		{
			printf("The index column %d is out of  Column Bounds, Highest index is %d\n",indexColumn,(pointer->size-1));
			exit(1);
		}
		array->indexColumn = indexColumn;
		int length = strlen(getString(pointer, array->indexColumn)) + 3;
		char start[length];
		strcpy(start,getString(pointer, array->indexColumn));
		strcat(start,",0");

		*(array->sets+setsSize) = newString(start);
		array->setsSize++;
	}
	else
	{
		if(strcmp(getString(pointer, indexColumn),getString(*(array->stringArray+size-1), indexColumn)) != 0){

			int len = (int) log10(array->size) + 3;
			char indice[len];

			struct String* s = *(array->sets+setsSize-1);
			char currentKeys[len+s->size];

			strcpy(currentKeys,s->string);

			sprintf(indice,",%ld",array->size);
			strcat(currentKeys,indice);
			struct String* ns = *(array->sets+setsSize-1);
			changeString(ns, currentKeys);

			char next[len];
			sprintf(next,",%ld",array->size);

			int length = strlen(getString(pointer, array->indexColumn)) + len;
			char start[length];
			strcpy(start,getString(pointer, array->indexColumn));
			strcat(start,next);
			*(array->sets+array->setsSize) = newString(start);
			array->setsSize++;

		}
	}
	array->size++;
}
/**
 *printString2DArray function, Prints the 2D array
 *@param array, The 2D array to print
 */
void printString2DArray(const struct String2DArray* data)
{
	for (int i = 0; i < data->size; ++i) {
	if(i == 20 && data->size > 100){
		i = (data->size) - 20;
		printf("\n");
	}
		printf("%-10d",i);
		struct StringArray* innerArray = *(data->stringArray+i);
		 for( int j=0; j<innerArray->size; j++)
			 printf("%-10s ", *(innerArray->array+j) );
		printf("\n");
	}
}
/**
 *freeString2DArray function, Frees the memory for the array
 *@param data, The 2D array to free its memory
 */
void freeString2DArray(struct String2DArray* data)
{
	for (int i = 0; i < data->size; ++i)
		 freeStringArray(*(data->stringArray+i));
	for (int i = 0; i < data->setsSize; ++i)
		freeString( (struct String*) *(data->sets+i));
	free(data->sets);
	free(data->stringArray);
	free(data);
}
/**
 *freePartString2DArray function, Frees a part of the 2D array since some
 * of its data points to the parent array
 * @param data, The array to free its memory
 */
void freePartString2DArray(struct String2DArray* data)
{
	for (int i = 0; i < data->setsSize; ++i) {
			freeString( (struct String*) *(data->sets+i));
	}
	free(data->stringArray);
	free(data->sets);
	free(data);
}
#endif
