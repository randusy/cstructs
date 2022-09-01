# cstructs
IntegerArray, Double Array, StringArray and String2DArray Data Structures For C.

# How to use the library

  //clone the library and put it in your project
  
  //You will need to import the header files
  
  #include "cstructs/array.h"
  
  #include "cstructs/data.h"
  
  #include "cstructs/stats.h"

  // creates a dynamic IntegerArray numbers
  
	struct IntegerArray* numbers = newIntegerArray();
  //adds numbers to the array
  
	addToIntegerArray(numbers, 12);
	addToIntegerArray(numbers, 23);
	addToIntegerArray(numbers, 42);

  //prints the array to the console
  
	printIntegerArray(numbers);

  //gets the value of the array at the given index
  
	const int id = 2;
	const int* i = getIntegerValue(numbers, id);
	printf("Integer value at index 2 is %d\n",*i);

	printf("Setting value 45 at index 2\n");
	setIntegerValue(numbers,45,2);
	printIntegerArray(numbers);

	printf("Reversing the array\n");
	reverseIntegerArray(numbers);
	printIntegerArray(numbers);

  //example 2
  
	struct IntegerArray* numbers2 = newIntegerArray();
  //adds all the numbers provided in the string
  
	addAllToIntegerArray(numbers2,"4,5,7,8,9,0");
	printIntegerArray(numbers2);

  //computes the correlation coefficient
  
	double c =  corrIntegerArray(numbers, numbers2);
	printf("Correlation %.2f\n",c);

  //frees the memory
  
	freeIntegerArray(numbers);
	freeIntegerArray(numbers2);

  //creates a double array
  
	struct DoubleArray* numbers = newDoubleArray();
  //adds the data to the array
  
	addToDoubleArray(numbers, 0.2);
	addToDoubleArray(numbers, 2.8);
	addToDoubleArray(numbers, 3.2);
	addToDoubleArray(numbers,34);
  
  //creates another array
  
	struct DoubleArray* numbers2 = newDoubleArray();
  //adds all the numbers in the array
  
	addAllToDoubleArray(numbers2, "34.3,6,3.5");

	printf("Array 1");
	printDoubleArray(numbers);
	printf("Array 2");
	printDoubleArray(numbers2);

	printf("correlation %.2f\n",corrDoubleArray(numbers, numbers2));
	printf("Sum of two arrays ");
	struct DoubleArray* sum = addDoubleArrays(numbers,numbers2);
	printDoubleArray(sum);

	freeDoubleArray(sum);
	freeDoubleArray(numbers);
	freeDoubleArray(numbers2);

  //imports data from a csv
  
	struct String2DArray* trainData = importData("data.csv",',',5);
  //filters the data with the given index value
  
	struct String2DArray* part = filterString2DArray(trainData, "ID2136364");
  
  //prints thee 2D array
  
	printString2DArray(part);

  //gets a column from the 2D array and returns it as an array
  
	struct StringArray* firstOdds = getColumnStringArray(part, 0);
	printf("First Column\n");
	printStringArray(firstOdds);

	struct DoubleArray* firstOddDouble = getDoubleArray(firstOdds);
	printf("First Column, In double type\n");
	printDoubleArray(firstOddDouble);

	struct StringArray* secondOdds = getColumnStringArray(part, 1);
	printf("Second Column\n");
	printStringArray(secondOdds);

	struct DoubleArray* secondOddDouble = getDoubleArray(secondOdds);
	printf("Second Column, In double type\n");
	printDoubleArray(secondOddDouble);

	printf("Correlation of the two columns %.2f\n",corrDoubleArray(secondOddDouble, firstOddDouble));

	freeStringDArray(firstOdds);
	freeStringDArray(secondOdds);
	freeDoubleArray(firstOddDouble);
	freeDoubleArray(secondOddDouble);
	freePartString2DArray(part);
	freeString2DArray(trainData);


  //creates an array of strings
  
	struct StringArray *s = newStringArray();
  
  //populates the array
  
	addToStringArray(s, "randu");
	addToStringArray(s, "katana");
	addToStringArray(s, "karisa");
	changeStringArray(s, "Daga", 1);
	
  //prints the array
  
	printStringArray(s);
	printf("%d\n",*getStringArraySize(s));
	freeStringArray(s);
