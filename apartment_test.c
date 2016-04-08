#include "aux_macros.h"
#include "apartment.h"

#include <stdlib.h>

bool apartment_combo_test() {
	bool final = true;

	SquareType square[2] = { WALL, EMPTY };
	SquareType* squarePtr = square;

	Apartment apartment = apartmentCreate(&squarePtr, 1, 2, 100);

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

	Apartment copy = apartmentCopy(apartment);
	TEST_EQUALS(final, true, apartmentIsIdentical(apartment, copy));

	apartmentDestroy(apartment);
	apartmentDestroy(copy);

	return final;
}

bool test1() {
	bool final = true;

	SquareType squares0[5] ={WALL,WALL,WALL,WALL,EMPTY};
	SquareType squares1[5] ={WALL,WALL,WALL,WALL,EMPTY};
	SquareType squares2[5] ={WALL,WALL,WALL,WALL,WALL};
	SquareType squares3[5] ={EMPTY,EMPTY,WALL,WALL,EMPTY};
	SquareType squares4[5] ={EMPTY,WALL,WALL,WALL,EMPTY};

	SquareType ** squares = malloc(5*sizeof(*squares));

	squares[0] = squares0;
	squares[1] = squares1;
	squares[2] = squares2;
	squares[3] = squares3;
	squares[4] = squares4;
	Apartment apr = apartmentCreate(squares,5,5,1500);

	Apartment apr1,apr2,apr3,apr4;
	bool outResult;
	TEST_EQUALS(final, APARTMENT_SUCCESS, apartmentSplit(apr,true,2,&apr1,&apr2));
	TEST_EQUALS(final, APARTMENT_SUCCESS, apartmentSplit(apr2,false,3,&apr3,&apr4));
	TEST_EQUALS(final, APARTMENT_NO_ROOM, apartmentIsSameRoom(apr1,0,0,0,4,&outResult));
	TEST_EQUALS(final, false, outResult);
	//TEST_EQUALS(final, APARTMENT_BAD_SPLIT, apartmentSplit(apr1,false,2,&apr5,&apr6));

	apartmentDestroy(apr);
	apartmentDestroy(apr1);
	apartmentDestroy(apr2);
	apartmentDestroy(apr3);
	apartmentDestroy(apr4);
	free(squares);

	return final;
}

int main() {
	RUN_TEST(apartment_combo_test);
	RUN_TEST(test1);
	// TODO: add more tests:
	// RUN_TEST(...);
	return true;
}
