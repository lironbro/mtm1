/*
 * apartment.c
 *
 *  Created on: 27 במרץ 2016
 *      Author: Liron
 */



/*
 * Dear Ziv,
 * I wrote the functions I've completed as declarations at the beginning of the project, please do the same
 * I left you the weird splitting question which seemed quite annoying,
 * as well as some easy functions, I could try to do them if you want
 * I'm sure you'll handle this
 * try to do it early on, this'll save us a lot of headaches
 *
 * Yours truly,
 * Liron
 *
 * P.S. you forgot enum bool Bool
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "apartment.h"


void checkPath(Apartment apartment, int currentRow,
		int currentCol, int destinationRow, int destinationCol, bool* outResult);

void print(Apartment apartment);


Apartment apartmentCreate(SquareType** squares, int length, int width, int price)
{
	if(squares == NULL || length <= 0 || width <= 0 || price < 0)
		return NULL;
	Apartment apartment = malloc(sizeof(Apartment));
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
			apartment->squares[i][j] = squares[i][j];	// המפה של הדירה נקלטת בסדר, אולי יש בעיה בשמירה
		}
	}
	return apartment;
}

void apartmentDestroy(Apartment apartment)
{
	if(apartment == NULL)
		return;
	for(int i=0; i<apartment->length; i++)
	{
		free(apartment->squares[i]);
	}
	free(apartment->squares);
	free(apartment);
}

Apartment apartmentCopy(Apartment apartment)
{
	if(apartment == NULL)
		return NULL;
	Apartment copy = apartmentCreate(apartment->squares, apartment->length, apartment->width, apartment->price);
	return copy;
}

// doesn't work
ApartmentResult apartmentIsSameRoom(Apartment apartment, int row1, int col1, int row2, int col2, bool* outResult)
{
	if(row1 >= apartment->length || col1 >= apartment->width
			|| row2 >= apartment->length || col2 >= apartment->width
			|| row1 < 0 || col1 < 0 || row2 < 0 || col2 < 0)
	{
		*outResult = false;
		return APARTMENT_OUT_OF_BOUNDS;
	}
	if(apartment->squares[row1][col1] == WALL || apartment->squares[row2][col2] == WALL)
	{
		*outResult = false;
		return APARTMENT_NO_ROOM;
	}
	printf("ookay i didn't fail till the pathfinding\n");
	checkPath(apartment, row1, col1, row2, col2, outResult);
	return APARTMENT_SUCCESS;
}

void checkPath(Apartment apartment, int currentRow, int currentCol, int destinationRow, int destinationCol, bool* outResult)
{

	if(currentRow == destinationRow && currentCol == destinationCol)

		*outResult = true;
	// the problem is with returning the answer here, don't know why I'm having trouble
	if(*outResult)
			return;

	apartment->squares[currentRow][currentCol] = WALL;

	if(currentRow+1 < apartment->length &&
			apartment->squares[currentRow+1][currentCol] == EMPTY)
		checkPath(apartment, currentRow+1, currentCol, destinationRow, destinationCol, outResult);
	printf("test1\n");
	if(currentRow-1 >= 0 && apartment->squares[currentRow-1][currentCol] == EMPTY)
		checkPath(apartment, currentRow-1, currentCol, destinationRow, destinationCol, outResult);
	printf("test2\n");
	if(currentCol+1 < apartment->width &&
			apartment->squares[currentRow][currentCol+1] == EMPTY)
		checkPath(apartment, currentRow+1, currentCol, destinationRow, destinationCol, outResult);
	printf("test3\n");
	if(currentRow-1 >= 0 && apartment->squares[currentRow][currentCol-1] == EMPTY)
		checkPath(apartment, currentRow-1, currentCol, destinationRow, destinationCol, outResult);
	printf("test4\n");
	apartment->squares[currentRow][currentCol] = EMPTY;

	*outResult = false;
	return;
}

int apartmentTotalArea(Apartment apartment)
{
	int empties = 0;
	for(int i=0; i<apartment->length; i++)
		for(int j=0; j<apartment->width; j++)
			if(apartment->squares[i][j] == EMPTY)
				empties++;
	return empties;
}

ApartmentResult apartmentRoomArea(Apartment apartment, int row, int col, int* outArea)
{
	if(row < 0 || row >= apartment->length || col < 0 || col >= apartment->width)
		return APARTMENT_OUT_OF_BOUNDS;	// אני לא סגור אם זאת הטעות הנכונה
	*outArea = 0;
	bool path = false;
	for(int i=0; i<apartment->length; i++)
	{
		for(int j=0; j<apartment->width; j++)
		{
			checkPath(apartment, i, j, row, col, &path);
			if(path)
				(*outArea)++;
		}
	}
	return APARTMENT_SUCCESS;
}

/*
ApartmentResult apartmentSplit(Apartment apartment, bool splitByRow,
								int index, Apartment* first,
								Apartment* second);
*/

//
int apartmentNumOfRooms(Apartment apartment)
{
	int roomCount = 0;
	bool inCountedRoom = false;
	for(int i=0; i<apartment->length; i++)
	{
		for(int j=0; j<apartment->width; j++)
		{
			inCountedRoom = false;
			for(int ii = 0; ii< i; ii++)
			{
				for(int jj = 0; jj<j; jj++)
				{
					apartmentIsSameRoom(apartment, i, j, ii, jj, &inCountedRoom);
					if(inCountedRoom)
						break;
				}
				if(inCountedRoom)
					break;
			}
			if(!inCountedRoom)
				roomCount++;
		}
	}
	return roomCount;
}

bool apartmentIsIdentical(Apartment apartment1, Apartment apartment2)
{
	if(apartment1 == NULL && apartment2 == NULL)
		return true;
	if(apartment1 == NULL || apartment2 == NULL)
		return false;
	if(apartment1->price != apartment2->price || apartment1->length != apartment2->length ||
			apartment1->width!= apartment2->width)
		return false;
	for(int i=0; i<apartment1->length; i++)
		for(int j=0; j<apartment1->width; j++)
			if(apartment1->squares[i][j] != apartment2->squares[i][j])
				return false;
	return true;
}

int apartmentGetPrice(Apartment apartment)
{
	return apartment->price;
}



void print(Apartment apartment)
{
	printf("length: %d, width: %d, price: %d\n", apartment->length, apartment->width, apartment->price);
		for(int i=0; i<apartment->length; i++)
		{
			for(int j=0; j<apartment->width; j++)
			{
				if(apartment->squares[i][j]==WALL)
					printf("W ");
				else printf("E ");
			}
			printf("\n");
		}
}





