/*
 ================================================================================
 Name        : data.h
 Author      : Randu Karisa
 Version     :
 Copyright   : Your copyright notice
 Description : Set of functions to get and manipulate data
 ================================================================================
 */
#ifndef DATA_H
#define DATA_H

#include <string.h>
#include <ctype.h>
#include "array.h"

#define FALSE 0
#define TRUE 1

/**
 *isNumber function, Finds out whether the string provided is a number
 *@param string, The number represented in a string
 *@return integer, Holding either zero for false or 1 for true
 */
int isNumber(const char* string)
{
	int hasPoint = FALSE;
	for (int i = 0; i < strlen(string); ++i) {
		if(isdigit(string[i]) == FALSE){
			if((char) string[i] == '.'){
				if(hasPoint == TRUE)
					return FALSE;
			}else
				return FALSE;
		}
		if((char) string[i] == '.') hasPoint = TRUE;
	}
	return TRUE;
}
/**
 * stringSplit function, Splits a string with the given char
 * @param string, the string to split
 * @param splitter, the character splitter
 * @return pointer to StringArray structure in heap
 */
struct StringArray* stringSplit(const char* string,const char splitter)
{
	char temp[1000];
	int j = 0;
	int k = 0;
	struct StringArray* str = newStringArray();
	for(size_t i = 0; i < strlen(string); ++i){
		if(string[i] == splitter || string[i] == '\n')
		{
			temp[j] = '\0';
			addToStringArray(str,temp);
			k++;
			j=0;
			temp[0] = '\0';
		}else if(i == strlen(string)-1)
		{
			temp[j] = string[i];
			temp[j+1] = '\0';
			addToStringArray(str,temp);
		}
		else
		{
			temp[j] = string[i];
			j++;
		}
	}
	return str;
}
/**
 * stringIsIn function, checks if a string is present in a
 * 		given array
 * @param array, an array of strings
 * @param string, the string to check
 * @return integer 0 for false or 1 for true
 */
int stringIsIn(const struct StringArray* array,const char* string)
{
	for(int i = 0; i < array->size; ++i)
		if(strcmp(*(array->array+i),string) == 0)
			return TRUE;
	return FALSE;
}
/**
 * integerIsIn function, checks if a integer is present in a
 * 		given array
 * @param array, an array of integers
 * @param value, the integer to check
 * @return integer 0 for false or 1 for true
 */
int integerIsIn(const struct IntegerArray* array,const int value)
{
	for(int i = 0; i < array->size; ++i)
		if(*(array->array+i) == value)
			return TRUE;
	return FALSE;
}
/**
 * doubleIsIn function, checks if a double is present in a
 * 		given array
 * @param array, an array of double
 * @param value, the double to check
 * @return integer 0 for false or 1 for true
 */
int doubleIsIn(struct DoubleArray* array, double value)
{
	for(int i = 0; i < array->size; ++i)
		if(*(array->array+i) == value)
			return TRUE;
	return FALSE;
}

/**
 *setOfStringArray function, gets a set of strings in an array
 *		i.e removes duplicates
 *@param array, the array to get a set from
 *@return arrayset, a pointer to a stringArray struct in heap
 */
struct StringArray* setOfStringArray(struct StringArray* array)
{
	struct StringArray* set = newStringArray();
	for (int i = 0; i < array->size; ++i)
		if(stringIsIn(set,*(array->array+i)) == 0)
			addToStringArray(set, *(array->array+i));
	return set;
}
/**
 *stringCat function, Concatenates a string with an integer
 *@param string, reference to a pointer of characters
 *@param value, The integer to concatenate
 */
void stringCat(char **string, int value)
{
	int len = (int) log10(value) + 3;
	char num[len];
	char str[len+strlen(*string)];

	strcpy(str,*string);

	sprintf(num,"%ld",value);
	strcat(str,num);
	*string = (char*) str;
}

/**
 * importData function, Imports the data from a text file
 * @param filename, string representing the file name to open
 * @param spliterChar, the character used as a separator in the text file
 * @param indexColumn, Column from which index keys will be generated in
 * 		order to have fast data retrieval.
 * @return a pointer to a String2DArray data structure in heap
 */
struct String2DArray* importData(const char* filename,const char spliterChar,const int indexColumn)
{
	FILE *file = fopen(filename,"r");
	if(!file)
	{
		printf("File '%s' failed to open\n",filename);
		exit(1);
	}
	char* line = "";
	size_t size = 0;
	int i = 0;

	struct String2DArray* data = newString2DArray();
	while(-1 != getline(&line,&size,file))
	{
		struct StringArray* row = stringSplit(line,spliterChar);

			addToString2DArray(data,row,indexColumn);
		i++;
	}
	free(line);
	fclose(file);
	return data;
}
/**
 *getIntegerArray function, Converts an string array to an integer array
 *@param array, The string array
 *@return array, A converted integer array
 */
struct IntegerArray* getIntegerArray(const struct StringArray* array)
{
	struct IntegerArray* intArray = newIntegerArray();
	for (int i = 0; i < array->size; ++i) {
		const char* str = getString(array, i);
		if(isNumber(str))
			addToIntegerArray(intArray, atoi(str));
		else
		{
			printf("StringArray Contains Non-Integer Values\n");
			exit(1);
		}
	}
	return intArray;
}

/**
 *getDoubleArray function, Converts the string array to a double array
 *@param array, The string array to convert
 *@return array, The double array
 */
struct DoubleArray* getDoubleArray(const struct StringArray* array)
{
	struct DoubleArray* doubleArray = newDoubleArray();
	for (int i = 0; i < array->size; ++i) {
		const char* str = getString(array, i);
		if(isNumber(str))
			addToDoubleArray(doubleArray, atof(str));
		else
		{
			printf("StringArray Contains Non-Double Values\n");
			exit(1);
		}
	}
	return doubleArray;
}
/**
 *getColumnStringArray function, Gets a column from a 2D array as an array
 *@param array, The 2D array to get the column
 *@return array, A column from the 2D array
 */
struct StringArray* getColumnStringArray(const struct String2DArray* array,const int columnIndex)
{
	if(array->size < 0)
	{
		printf("Array is Empty\n");exit(1);
	}
	if(columnIndex < (*array->stringArray)->size && columnIndex > -1 )
	{
		struct StringArray* column = newStringArray();
		for (int i = 0; i < array->size; ++i) {
			addToStringArray(column, getString(*(array->stringArray+i), columnIndex));
		}
		return column;
	}
	printf("RuntimeError: Index %d is Out of Array Bounds, Size of Array %d\n",columnIndex,getStringArraySize(*array->stringArray)-1);
	exit(1);
}
/**
 *filterString2DArray function, filters row of a 2D array by the given column value
 *@param array, The 2D array to filter
 *@param columnValue, The value to use as a filter
 *Note: The index column will be used to apply this filter
 */
struct String2DArray* filterString2DArray(const struct String2DArray* array,const char* columnValue)
{
	struct String2DArray* arrayPart = newString2DArray();
		int start = 0;
		int stop = 0;
		for (int i = 0; i < array->setsSize; ++i) {
			struct String* str = *(array->sets+i);
			struct StringArray* s = stringSplit(str->string, ',');
				if(strcmp( (char*) getString(s,0), columnValue) == 0)
				{
					start = atoi(getString(s, 1));
					if(s->size > 2)
						stop = atoi(getString(s, 2));
					else
						stop = array->size;
					freeStringArray(s);
					break;
				}
			freeStringArray(s);
		}
		for (int i = start; i < stop; ++i)
			addToString2DArray(arrayPart, *(array->stringArray+i),array->indexColumn);

	return arrayPart;
}
/**
 *firstRowString2DArray function, Does the same as filterString2DArray function, but this
 *		returns only one single row(the first) rather than every row filters
 *@param array, The 2D array to filter
 *@param columnValue, The values to be used as the filter
 */
struct String2DArray* firstRowString2DArray(struct String2DArray* array, char* columnValue)
{
	struct String2DArray* arrayPart = newString2DArray();
		int start = 0;
		int stop = 0;
		for (int i = 0; i < array->setsSize; ++i) {
			struct String* str = *(array->sets+i);
			struct StringArray* s = stringSplit(str->string, ',');
				if(strcmp( (char*) getString(s,0), columnValue) == 0)
				{
					start = atoi(getString(s, 1));
					if(s->size > 2)
						stop = atoi(getString(s, 2));
					else
						stop = array->size;
					freeStringArray(s);
					break;
				}
			freeStringArray(s);
		}
		for (int i = start; i < stop; ++i)
		{
			addToString2DArray(arrayPart, *(array->stringArray+i),array->indexColumn);
			break;
		}
	return arrayPart;
}
/**
 *getIndexKey function, Gets the keys for a specified index from a 2D array
 *@param array, The 2D array
 *@param index, The index of the data
 */
char* getIndexKey(const struct String2DArray* array,const int index)
{
	struct String* set = *(array->sets+index);
	struct StringArray* s = stringSplit(set->string, ',');
	char* key = malloc((strlen(*s->array)+1) * sizeof(char));
	strcpy(key,*s->array);
	freeStringArray(s);
	return key;
}

/**
 *addAllToIntegerArray function, Adds all the numbers from the array of
 *	numbers represented as a string
 *@param array, The array to add the numbers
 *@param stringIntegerArray, The numbers in a string
 */
void addAllToIntegerArray(struct IntegerArray* array,const char* stringIntegerArray)
{
	struct StringArray* stringArray = stringSplit(stringIntegerArray, ',');
	struct IntegerArray* intArray = getIntegerArray(stringArray);
	for (int i = 0; i < intArray->size; ++i)
		addToIntegerArray(array, *getIntegerValue(intArray, i));
	freeStringArray(stringArray);
	freeIntegerArray(intArray);
}
/**
 *addAllToIntegerArray function, Adds all the numbers from the array of
 *	numbers represented as a string
 *@param array, The array to add the numbers
 *@param stringIntegerArray, The numbers in a string
 */
void addAllToDoubleArray(struct DoubleArray* array,const char* stringDoubleArray)
{
	struct StringArray* stringArray = stringSplit(stringDoubleArray, ',');
	struct DoubleArray* dubArray = getDoubleArray(stringArray);
	for (int i = 0; i < dubArray->size; ++i)
		addToDoubleArray(array, *getDoubleValue(dubArray, i));
	freeStringArray(stringArray);
	freeDoubleArray(dubArray);
}
#endif

