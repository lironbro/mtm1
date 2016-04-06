#include "aux_macros.h"
#include "apartment.h"
#include "apartment_service.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool apartment_combo_test() {
	bool final = true;
	SquareType square = EMPTY;
	SquareType* squarePtr = &square;
	Apartment apartment = apartmentCreate(&squarePtr, 1, 1, 100);

	/*
	bool result;
	TEST_EQUALS(final, APARTMENT_NULL_ARG, apartmentIsSameRoom(NULL, 0, 1, 0, 1, &result));
	SquareType squareVal;
	TEST_EQUALS(final, APARTMENT_OUT_OF_BOUNDS, apartmentGetSquare(apartment, 0, 2, &squareVal));
	TEST_EQUALS(final, 1, apartmentTotalArea(apartment));
	int area;
	TEST_EQUALS(final, APARTMENT_NO_ROOM, apartmentRoomArea(apartment, 0, 0, &area));
	TEST_EQUALS(final, APARTMENT_SUCCESS, apartmentRoomArea(apartment, 0, 1, &area));
	TEST_EQUALS(final, 1, area);
	Apartment split1 = NULL, split2 = NULL;
	TEST_EQUALS(final, APARTMENT_BAD_SPLIT, apartmentSplit(apartment, false, 1, &split1, &split2));

	TEST_EQUALS(final, 1, apartmentNumOfRooms(apartment));
	TEST_EQUALS(final, APARTMENT_OLD_VALUE, apartmentSetSquare(apartment, 0, 0, WALL));
	TEST_EQUALS(final, 2, apartmentGetWidth(apartment));

	TEST_EQUALS(final, APARTMENT_SUCCESS, apartmentChangePrice(apartment, 10));
	TEST_EQUALS(final, 110, apartmentGetPrice(apartment));

	*/
	Apartment copy = apartmentCopy(apartment);
	TEST_EQUALS(final, true, apartmentIsIdentical(apartment, copy));

	ApartmentService service = serviceCreate(2);

	printf("predestroying\n");
	apartmentPrint(apartment);
	apartmentPrint(copy);

	//apartmentDestroy(apartment);
	//apartmentDestroy(apartment);
	apartmentDestroy(copy);

	printf("postdestroying\n");
	apartmentPrint(apartment);
	apartmentPrint(copy);

	return final;
}

bool lironsTest()
{
	bool final = true;

	int length = 12, width = 15, price = 35;
	SquareType** squares  = malloc(length*sizeof (SquareType*));
	for(int i=0; i<length; i++)
		squares[i] = malloc(width *sizeof(SquareType));
	for(int i=0; i<length; i++)
	{
		for(int j=0; j<width; j++)
		{
			if(i == 0 || i == length-1 || j == 0 || j == width-1 || i == length/2 || j == width/2 || j==width/3 || i ==length/3)
				squares[i][j] = WALL;
			else
				squares[i][j] = EMPTY;
		}
	}
	Apartment apt = apartmentCreate(squares, length, width, price);
	squares[5][6] = WALL;
	Apartment apt1 = apartmentCreate(squares, length, width, price);
	free(squares);

	/*
	final = !apartmentIsIdentical(apt1, apt);

	int rooms = apartmentNumOfRooms(apt);
	final = final && rooms == 9;

	TEST_EQUALS(final, APARTMENT_SUCCESS, apartmentIsSameRoom(apt, 3, 4, 3, 1, &final));

	int roomArea;
	TEST_EQUALS(final, APARTMENT_SUCCESS, apartmentRoomArea(apt, 7, 8, &roomArea));
	final = final && roomArea == 24;

	TEST_EQUALS(final, APARTMENT_SUCCESS, apartmentChangePrice(apt, -50));
	final = final && apt->price == 18;

	*/

	apartmentDestroy(apt);
	apartmentDestroy(apt1);



	return final;
}


/*
int main() {
	RUN_TEST(apartment_combo_test);
	RUN_TEST(lironsTest);
	// RUN_TEST(...);
	return 0;
}
*/

