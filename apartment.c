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
#include <math.h>
#include "apartment.h"


void checkPath(Apartment apartment, int currentRow,
		int currentCol, int destinationRow, int destinationCol, bool* outResult);


int main()
{
		printf("hello");
	return 0;
}

Apartment apartmentCreate(SquareType** squares, int length, int width, int price)
{
	if(*squares == NULL || length<= 0 || width<= 0 || price< 0)
		return NULL;
	Apartment apartment;
	apartment->length = length;
	apartment->width = width;
	apartment->price = price;
	apartment->squares = malloc(length*sizeof(SquareType*));  // איך אני עושה מערך של סקוואר טייפ?
	for(int i=0; i<length; i++) 	// בהשראת איתמר
		apartment->squares[i] = malloc(width*sizeof(SquareType));	// לא יודע אם זה יעבוד
	return apartment;
}

ApartmentResult apartmentIsSameRoom(Apartment apartment, int row1, int col1,
		 int row2, int col2, bool* outResult)
{
	if(row1>=apartment->width || col1>=apartment->length
			|| row2>=apartment->width || col2>=apartment->length)
		return APARTMENT_OUT_OF_BOUNDS;
	if(apartment->squares[row1][col1] == WALL || apartment->squares[row2][col2] == WALL)
		return APARTMENT_NO_ROOM;
	checkPath(apartment, row1, col1, row2, col2, outResult);
	return APARTMENT_SUCCESS;
}

void checkPath(Apartment apartment, int currentRow, int currentCol, int destinationRow, int destinationCol, bool* outResult)
{
	if(currentRow == destinationRow && currentCol == destinationCol)
	{
		*outResult = true;
		return;
	}
	apartment->squares[currentRow][currentCol] = WALL;

	if(currentRow+1 < apartment->length &&
			apartment->squares[currentRow+1][currentCol] == EMPTY)
		checkPath(apartment, currentRow+1, currentCol, destinationRow, destinationCol, outResult);

	if(currentRow-1 >= 0 && apartment->squares[currentRow-1][currentCol] == EMPTY)
		checkPath(apartment, currentRow-1, currentCol, destinationRow, destinationCol, outResult);

	if(currentCol+1 < apartment->width &&
			apartment->squares[currentRow][currentCol+1] == EMPTY)
		checkPath(apartment, currentRow+1, currentCol, destinationRow, destinationCol, outResult);

	if(currentRow-1 >= 0 && apartment->squares[currentRow][currentCol-1] == EMPTY)
		checkPath(apartment, currentRow-1, currentCol, destinationRow, destinationCol, outResult);

	apartment->squares[currentRow][currentCol] = EMPTY;
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


/*
ApartmentResult apartmentRoomArea(Apartment apartment, int row, int col,
			int* outArea)
{	// אפשר להתחיל בקורדינטה ולהתפשט על כל השטח של החדר
	int squares = 0;
	for(int i=0; i<apartment->length; i++)
	{
		for(int j=0; j<apartment->width; j++)
		{
			if(i!=row || j!=col)
			{
				bool sameRoom = false;
				apartmentIsSameRoom(apartment, row, col, i, j);
			}
		}
	}
	return APARTMENT_SUCCESS;
}
*/

ApartmentResult apartmentSplit(Apartment apartment, bool splitByRow,
                                int index, Apartment* first, Apartment* second)
{
    if(index >= (apartment->length) || index >= (apartment->width))
        return APARTMENT_OUT_OF_BOUNDS;
    if(splitByRow) {
        for( int i=0 ; i < (apartment->width) ; i++ ) {
        	if(apartment->squares[i][index] == EMPTY)
                return APARTMENT_BAD_SPLIT;
        }
    }
    else
        for( int i=0; i < apartment->length; i++)
            if(apartment->squares[index][i]==EMPTY)
                return APARTMENT_BAD_SPLIT;
    if(splitByRow) {
    	first = apartmentCreate(, index, apartment->width,);
    	second = apartmentCreate(, index, apartment->width,);
    	return APARTMENT_SUCCESS;
    }
    first = apartmentCreate(, index, apartment->width,);
    second = apartmentCreate(, index, apartment->width,);
    return APARTMENT_SUCCESS;
    // Continue.
}

int apartmentNumOfRooms(Apartment apartment)
{
    // Continue.
}

ApartmentResult apartmentGetSquare(Apartment apartment, int row, int col, SquareType* OutValue)
{
    if(apartment == NULL)
        return APARTMENT_NULL_ARG;
	if(row >= apartment->width || col >= apartment->length)
        return APARTMENT_OUT_OF_BOUNDS;
    *OutValue = apartment->squares[row][col];
    return APARTMENT_SUCCESS;
}

ApartmentResult apartmentSetSquare(Apartment apartment, int row, int col,
                                    SquareType value)
{
    if(row >= apartment->width || col >= apartment->length)
        return APARTMENT_OUT_OF_BOUNDS;
    if(apartment->squares[row][col] == value)
        return APARTMENT_OLD_VALUE;
    apartment->squares[row][col]=value;
    return APARTMENT_SUCCESS;
}

ApartmentResult apartmentChangePrice(Apartment apartment, int percent)
{
	if(percent < -100)
		return APARTMENT_PRICE_NOT_IN_RANGE;
	double price = apartmentGetPrice(apartment);
	int diff = math.abs(percent/100*price);
	diff = (percent<0) ? -diff : diff;
    apartment->price=price+diff;
    return APARTMENT_SUCCESS
}

int apartmentGetLength(Apartment apartment)
{
	return apartment->length;
}

int apartmentGetWidth(Apartment apartment)
{
	return apartment->width;
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


Apartment apartmentCopy(Apartment apartment)
{
	if(apartment == NULL)
		return NULL;
	Apartment copy = malloc(sizeof(Apartment));
	copy->length = apartment->length;
	copy->width = apartment->width;
	copy->price = apartment->price;
	copy->squares = malloc(copy->length*sizeof(SquareType)); // רצוי לבדוק אם זה נכון
	for(int i=0; i<copy->length; i++)
	{
		copy->squares[i] = malloc(copy->width*sizeof(SquareType));
		for(int j=0; j<copy->width; j++)
			copy->squares[i][j] = apartment->squares[i][j];
	}
	return copy;
}

void apartmentDestroy(Apartment apartment)
{
	if(apartment == NULL)
		return;
	free(apartment->length);
	free(apartment->width);
	free(apartment->price);
	free(apartment->squares);
}







