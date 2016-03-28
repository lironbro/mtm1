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

typedef enum {EMPTY, WALL} SquareType;
typedef enum {APARTMENT_NULL_ARG, APARTMENT_OUT_OF_MEM, APARTMENT_SUCCESS,
				APARTMENT_OUT_OF_BOUNDS, APARTMENT_NO_ROOM} ApartmenmtResult;
typedef struct apartment_t Apartment;

struct apartment_t{
	SquareType** squares;
	int width;
	int length;
	int price;
};

Apartment apartmentCreate(SquareType** squares, int length, int width, int price);

ApartmenmtResult apartmentIsSameRoom(Apartment apartment, int row1, int col1,
		 int row2, int col2, bool* outResult);

int apartmentTotalArea(Apartment apartment);

ApartmenmtResult apartmentRoomArea(Apartment apartment, int row, int col,
			int* outArea);

bool apartmentIsIdentical(Apartment apartment1, Apartment apartment2);

int apartmentGetPrice(Apartment apartment);

Apartment apartmentCopy(Apartment apartment);

void apartmentDestroy(Apartment apartment);




Apartment apartmentCreate(SquareType** squares, int length, int width, int price)
{
	if(*squares == NULL || length<= 0 || width<= 0 || price< 0)
		return NULL;
	Apartment apt;
	apt.length = length;
	apt.width = width;
	apt.price = price;
	apt.squares = squares;
	return apt;
}

ApartmenmtResult apartmentIsSameRoom(Apartment apartment, int row1, int col1,
		 int row2, int col2, bool* outResult)
{
	if(row1>=apartment.width || col1>=apartment.length
			|| row2>=apartment.width || col2>=apartment.length)
		return APARTMENT_OUT_OF_BOUNDS;
	if(apartment.squares[row1][col1] == WALL || apartment.squares[row2][col2] == WALL)
		return APARTMENT_NO_ROOM;
	checkPath(apartment, row1, col1, row2, col2, outResult);
	return APARTMENT_SUCCESS;
}

void checkPath(Apartment apartment, int currentRow, int currentCol, // צריך לבדוק, נראה לי שיעבוד
		int destinationRow, int destinationCol, bool* outResult)
{
	if(currentRow == destinationRow && currentCol == destinationCol)
	{
		*outResult = true;
		return;
	}
	apartment.squares[currentRow][currentCol] = WALL;

	if(currentRow+1 < apartment.length &&
			apartment.squares[currentRow+1][currentCol] == EMPTY)
		checkPath(apartment, currentRow+1, currentCol, destinationRow, destinationCol, outResult);

	if(currentRow-1 >= 0 && apartment.squares[currentRow-1][currentCol] == EMPTY)
		checkPath(apartment, currentRow-1, currentCol, destinationRow, destinationCol, outResult);

	if(currentCol+1 < apartment.width &&
			apartment.squares[currentRow][currentCol+1] == EMPTY)
		checkPath(apartment, currentRow+1, currentCol, destinationRow, destinationCol, outResult);

	if(currentRow-1 >= 0 && apartment.squares[currentRow][currentCol-1] == EMPTY)
		checkPath(apartment, currentRow-1, currentCol, destinationRow, destinationCol, outResult);

	apartment.squares[currentRow][currentCol] = EMPTY;
}

int apartmentTotalArea(Apartment apartment)
{
	int empties = 0;
	for(int i=0; i<apartment.length; i++)
		for(int j=0; j<apartment.width; j++)
			if(apartment.squares[i][j] == EMPTY)
				empties++;
	return empties;
}

ApartmenmtResult apartmentRoomArea(Apartment apartment, int row, int col,
			int* outArea)
{	// אפשר להתחיל בקורדינטה ולהתפשט על כל השטח של החדר
	int squares = 0;
	for(int i=0; i<apartment.length; i++)
	{
		for(int j=0; j<apartment.width; j++)
		{
			if(i!=row || j!=col)
			{
				bool sameRoom = false;
				apartmentIsSameRoom(apartment, row, col, i, j)
			}
		}
	}
}

bool apartmentIsIdentical(Apartment apartment1, Apartment apartment2)
{
	if(apartment1 == NULL && apartment2 == NULL)
		return true;
	if(apartment1 == NULL || apartment2 == NULL)
		return false;
	if(apartment1.price != apartment2.price || apartment1.length != apartment2.length ||
			apartment1.width!= apartment2.width)
		return false;
	for(int i=0; i<apartment1.length; i++)
		for(int j=0; j<apartment1.width; j++)
			if(apartment1.squares[i][j] != apartment2.squares[i][j])
				return false;
	return true;
}

int apartmentGetPrice(Apartment apartment)
{
	return apartment.price;
}


Apartment apartmentCopy(Apartment apartment)
{
	if(apartment == NULL)
		return NULL;
	Apartment copy = malloc(sizeof(Apartment));
	copy.length = apartment.length;
	copy.width = apartment.width;
	copy.price = apartment.price;
	copy.squares = malloc(copy.length*copy.width*sizeof(SquareType)); // רצוי לבדוק אם זה נכון
	for(int i=0; i<copy.length; i++)
		for(int j=0; j<copy.width; j++)
			copy.squares[i][j] = apartment.squares[i][j];
	return copy;
}

void apartmentDestroy(Apartment apartment)
{
	if(apartment == NULL)
		return;
	free(apartment.length);
	free(apartment.width);
	free(apartment.price);
	free(apartment.squares);
}







