/*
 * apartment.c
 *
 *  Created on: 27 ���� 2016
 *      Author: Liron
 */



/*
 *
 * this should be everything
 * whatever I've tested and found to work has " //works" written above it, the splitting function could be improved
 * I've also implemented two helpful functions, their declaration can be seen here, and their implementation at the end
 * everything should be ordered like the header file, and I haven't checked the service file just yet
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "apartment.h"

// helpful functions - implemented at the end of the file

bool checkPath(Apartment apartment, int currentRow, int currentCol, int destinationRow, int destinationCol);

//void print(Apartment apartment);



// works
Apartment apartmentCreate(SquareType** squares, int length, int width, int price)
{
	if(squares == NULL || length <= 0 || width <= 0 || price < 0)
		return NULL;
	Apartment apartment = malloc(sizeof(*apartment));
	if(apartment == NULL)
		return NULL;
	apartment->length = length;
	apartment->width = width;
	apartment->price = price;
	apartment->squares = malloc(length*sizeof(SquareType*));
	if(apartment->squares == NULL)
		return NULL;
	for(int i=0; i<length; i++)
	{
		apartment->squares[i] = malloc(width*sizeof(SquareType));
		if(apartment->squares[i]==NULL)
		{
			apartmentDestroy(apartment);
			return NULL;
		}
		for(int j=0; j<width; j++)
		{
			apartment->squares[i][j] = squares[i][j];
		}
	}
	return apartment;
}

void destroySquares(SquareType*** sq,int length,int width)
{
	for(int i=0;i<length;i++)
	{
		free((*sq)[i]);
	}
	free(*sq);
	return;
}

//does not work
void apartmentDestroy(Apartment apartment)
{
	if(apartment == NULL || apartment->length <= 0 || apartment->width <= 0 || apartment->squares == NULL)
	{
		//free(apartment);	// this keeps fucking me up, this line is probably necessary but the code doesn't run with it
		return;
	}
	for(int i=0; i<apartment->length; i++)
	{
		free(apartment->squares[i]);	// seems to fail here
		apartment->squares[i] = NULL;
	}
	free(apartment->squares);
	apartment->squares = NULL;
	free(apartment);		// this keeps fucking us up, it should probably exist in the code, but hey

}

// works
Apartment apartmentCopy(Apartment apartment)
{
	if(apartment == NULL)
		return NULL;
	Apartment copy = apartmentCreate(apartment->squares, apartment->length, apartment->width, apartment->price);
	return copy;
}

// works
ApartmentResult apartmentIsSameRoom(Apartment apartment, int row1, int col1, int row2, int col2, bool* outResult)
{
	if(apartment == NULL)
		return APARTMENT_NULL_ARG;
	if(row1 >= apartment->length || col1 >= apartment->width
			|| row2 >= apartment->length || col2 >= apartment->width
			|| row1 < 0 || col1 < 0 || row2 < 0 || col2 < 0
			|| apartment->squares[row1][col1] == WALL || apartment->squares[row2][col2] == WALL)
	{
		*outResult = false;
		return APARTMENT_OUT_OF_BOUNDS;
	}
	if(apartment->squares[row1][col1] == WALL || apartment->squares[row2][col2] == WALL)
	{
		*outResult = false;
		return APARTMENT_NO_ROOM;
	}
	*outResult = checkPath(apartment, row1, col1, row2, col2);
	return APARTMENT_SUCCESS;
}

// works
int apartmentTotalArea(Apartment apartment)
{
	int empties = 0;
	for(int i=0; i<apartment->length; i++)
		for(int j=0; j<apartment->width; j++)
			if(apartment->squares[i][j] == EMPTY)
				empties++;
	return empties;
}

// works
ApartmentResult apartmentRoomArea(Apartment apartment, int row, int col, int* outArea)
{
	if(apartment == NULL || outArea == NULL)
		return APARTMENT_NULL_ARG;
	if(row < 0 || row >= apartment->length || col < 0 || col >= apartment->width)
		return APARTMENT_OUT_OF_BOUNDS;	// ��� �� ���� �� ��� ����� ������
	if(apartment->squares[row][col] == WALL)
		return APARTMENT_NO_ROOM;
	*outArea = 0;
	bool path = false;
	for(int i=0; i<apartment->length; i++)
	{
		for(int j=0; j<apartment->width; j++)
		{
			path = checkPath(apartment, i, j, row, col);
			if(path)
				(*outArea)++;
		}
	}
	return APARTMENT_SUCCESS;
}

// works but very long
ApartmentResult apartmentSplit(Apartment apartment, bool splitByRow,
                                int index, Apartment* first, Apartment* second)
{
    if(apartment == NULL)
    	return APARTMENT_NULL_ARG;
    if(splitByRow)
    {

    	if(index < 0 || index > apartment->length)
    	    return APARTMENT_OUT_OF_BOUNDS;
    	for(int i=0; i<apartment->length; i++)
    	    if(apartment->squares[index][i] == EMPTY)
    	    	return APARTMENT_BAD_SPLIT;
    	int price1 = apartment->price*(index+1)/(apartment->length);
    	int price2 = apartment->price*(apartment->length-index)/(apartment->length);

    	SquareType** squares = malloc((apartment->length-index-1)*sizeof(SquareType*));
    	if(squares == NULL)		return APARTMENT_OUT_OF_MEM;
    	for(int i=0; i<apartment->length-index-1; i++)
    	{
    	    squares[i] = malloc(apartment->width*sizeof(SquareType));
    	    if(squares[i] == NULL)	return APARTMENT_OUT_OF_MEM;
    	    for(int j=0; j<apartment->width; j++)
    	    {
    	    	squares[i][j] = apartment->squares[i+index+1][j];
    	    }
    	}

    	*first = apartmentCreate(apartment->squares, index, apartment->width, price1);
    	*second = apartmentCreate(&apartment->squares[index+1], apartment->length-index-1, apartment->width, price2);
    	for(int i=0; i<apartment->length; i++)
       		free(squares[i]);
    	free(squares);
    }
    else
    {
    	if(index < 0 || index > apartment->width)
    		return APARTMENT_OUT_OF_BOUNDS;
    	for(int i=0; i<apartment->length; i++)
    		if(apartment->squares[i][index] == EMPTY)
    			return APARTMENT_BAD_SPLIT;
    	int price1 = (apartment->price)*(index+1)/(apartment->width);
    	int price2 = (apartment->price)*(apartment->width-index-1)/(apartment->width);

    	SquareType** squares = malloc(apartment->length*sizeof(SquareType*));
    	if(squares == NULL)		return APARTMENT_OUT_OF_MEM;
    	for(int i=0; i<apartment->length; i++)
    	{
    		squares[i] = malloc((apartment->width-index-1)*sizeof(SquareType));
    	    if(squares[i] == NULL)	return APARTMENT_OUT_OF_MEM;
    		for(int j=0; j<apartment->width-index-1; j++)
    		{
    			squares[i][j] = apartment->squares[i][j+index+1];
    		}
    	}

    	*first = apartmentCreate(apartment->squares, apartment->length, index, price1);
    	*second = apartmentCreate(squares, apartment->length, apartment->width-index-1, price2);
    	for(int i=0; i<apartment->length; i++)
    		free(squares[i]);
    	free(squares);
    }
    return APARTMENT_SUCCESS;
}

/*
ApartmentResult splitAux(Apartment *apartment, Apartment** first,
		Apartment** second, int index, int lengthOrWidth, int splitByRow)
{
	for(int i=0; i<lengthOrWidth; i++)
		if(apartment->squares[index][i] == EMPTY)
			return APARTMENT_BAD_SPLIT;
	int price1 = apartment->price*(index+1)/(apartment->length);
	int price2 = apartment->price*(apartment->length-index)/(apartment->length);
	SquareType** squares = malloc((apartment->length-index-1)*sizeof(SquareType*));
	if(squares == NULL)
	    return APARTMENT_OUT_OF_MEM;
	for(int i=0; i<apartment->length-index-1; i++) {
		squares[i] = malloc(apartment->width*sizeof(SquareType));
	    if(squares[i] == NULL)
	    	return APARTMENT_OUT_OF_MEM;
	    for(int j=0; j<apartment->width; j++) {
	    	squares[i][j] = apartment->squares[i+index+1][j];
	    }
	}
	*first = apartmentCreate(apartment->squares, index, apartment->width, price1);
	*second = apartmentCreate(&apartment->squares[index+1], apartment->length-index-1, apartment->width, price2);
	for(int i=0; i<apartment->length; i++)
		free(squares[i]);
	free(squares);
	return APARTMENT_SUCCESS;
}
*/

// works
int apartmentNumOfRooms(Apartment apartment)
{
	int roomCount = 0;
	for(int i=0; i<apartment->length; i++)
	{
		for(int j=0; j<apartment->width; j++)
		{
			bool pathExists = false;
			if(apartment->squares[i][j] == WALL)
				continue;
			for(int k = 0; k< i*apartment->width+j; k++)
			{
				apartmentIsSameRoom(apartment, i, j, k/apartment->width, k%apartment->width, &pathExists);
				if(pathExists)
					break;
			}
			if(!pathExists)
				roomCount++;
		}
	}
	return roomCount;
}

// works
ApartmentResult apartmentSetSquare(Apartment apartment, int row, int col,
                                    SquareType value)
{
	if(apartment == NULL || apartment->squares == NULL)
		return APARTMENT_NULL_ARG;
    if(row >= apartment->width || col >= apartment->length)
        return APARTMENT_OUT_OF_BOUNDS;
    if(apartment->squares[row][col] == value)
        return APARTMENT_OLD_VALUE;
    apartment->squares[row][col]=value;
    return APARTMENT_SUCCESS;
}

// works
ApartmentResult apartmentGetSquare(Apartment apartment, int row, int col, SquareType* OutValue)
{
    if(apartment == NULL || apartment->squares == NULL)
        return APARTMENT_NULL_ARG;
	if(row >= apartment->width || col >= apartment->length)
        return APARTMENT_OUT_OF_BOUNDS;
    *OutValue = apartment->squares[row][col];
    return APARTMENT_SUCCESS;
}

// works
ApartmentResult apartmentChangePrice(Apartment apartment, int percent)
{
	if(apartment == NULL)
		return APARTMENT_NULL_ARG;
	if(percent < -100)
		return APARTMENT_PRICE_NOT_IN_RANGE;
	apartment->price *= (100+percent);
	apartment->price /= 100;
	bool round = apartment->price % 100 != 0 && percent < 0;	// HOW U DO DIS????
	if(round)
		apartment->price++;
	return APARTMENT_SUCCESS;
}

// works
int apartmentGetPrice(Apartment apartment)
{
	assert(apartment != NULL);
	return apartment->price;
}

// works
int apartmentGetLength(Apartment apartment)
{
	assert(apartment != NULL);
	return apartment->length;
}

// works
int apartmentGetWidth(Apartment apartment)
{
	assert(apartment != NULL);
	return apartment->width;
}

// works
bool apartmentIsIdentical(Apartment apartment1, Apartment apartment2)
{
	if(apartment1 == NULL && apartment2 == NULL)
		return true;
	if(apartment1 == NULL || apartment2 == NULL)
		return false;
	if(apartment1->price != apartment2->price || apartment1->length != apartment2->length ||
			apartment1->width != apartment2->width)
		return false;
	for(int i=0; i<apartment1->length; i++)
		for(int j=0; j<apartment1->width; j++)
			if(apartment1->squares[i][j] != apartment2->squares[i][j])
				return false;
	return true;
}


// helpful functions implementation

// works
bool checkPath(Apartment apartment, int currentRow, int currentCol, int destinationRow, int destinationCol)
{
	if(currentRow == destinationRow && currentCol == destinationCol)
		return true;

	if(apartment->squares[currentRow][currentCol] == WALL)
		return false;

	bool r1 = false, r2 = false, r3 = false, r4 = false;
	apartment->squares[currentRow][currentCol] = WALL;

	if(currentRow+1 < apartment->length &&
			apartment->squares[currentRow+1][currentCol] == EMPTY)
		r1 = checkPath(apartment, currentRow+1, currentCol, destinationRow, destinationCol);

	if(currentRow-1 >= 0 && apartment->squares[currentRow-1][currentCol] == EMPTY)
		r2 = checkPath(apartment, currentRow-1, currentCol, destinationRow, destinationCol);

	if(currentCol+1 < apartment->width &&
			apartment->squares[currentRow][currentCol+1] == EMPTY)
		r3 = checkPath(apartment, currentRow+1, currentCol+1, destinationRow, destinationCol);

	if(currentCol-1 >= 0 && apartment->squares[currentRow][currentCol-1] == EMPTY)
		r4 = checkPath(apartment, currentRow, currentCol-1, destinationRow, destinationCol);

	apartment->squares[currentRow][currentCol] = EMPTY;

	return r1 || r2 || r3 || r4;
}

// works, might crash if the apartment isn't initialized well
void apartmentPrint(Apartment apartment)
{
	if(apartment == NULL || apartment->length <= 0 || apartment->width <= 0 || apartment->price < 0 || apartment->squares == NULL)
	{
		return;
	}
	printf("length: %d, width: %d, price: %d\n", apartment->length, apartment->width, apartment->price);
	for(int i=0; i<apartment->length; i++)
	{
		//printf("okay now in the loop \n");	// wtf it fails right in the if, why??????
		if(apartment == NULL || apartment->squares == NULL || apartment->squares[i] == NULL)
		{
			printf("NULLLLLLLLLLLLLLLLLLLLLLL %d\n", i);
			return;
		}
		for(int j=0; j<apartment->width; j++)
		{
			if(apartment->squares[i][j]==WALL)
				printf("# ");
			else printf("O ");
		}
		printf("\n");
	}
	printf("and that's it for that apartment\n\n");

}





