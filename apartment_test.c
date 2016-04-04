#include "aux_macros.h"
#include "apartment.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool apartment_combo_test() {
	bool final = true;
	printf("testing1");
	SquareType square[2] = { WALL, EMPTY };
	SquareType* squarePtr = square;

	printf("testing1");
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


int main() {
	RUN_TEST(apartment_combo_test);
	// TODO: add more tests:
	// RUN_TEST(...);
	return 0;
}

