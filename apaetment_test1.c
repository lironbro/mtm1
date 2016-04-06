#include "aux_macros.h"
#include "apartment.h"

#include <stdlib.h>

bool apartment_combo_test1() {
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

bool test()
{
	bool final = true;
	SquareType squares0[3] ={EMPTY,WALL,WALL};
	SquareType squares1[3] ={EMPTY,WALL,EMPTY};
	SquareType squares2[3] ={WALL ,WALL ,WALL};
	SquareType squares3[3] ={EMPTY ,WALL ,EMPTY};
	SquareType squares4[3] ={EMPTY ,WALL ,EMPTY};

	SquareType ** squares = malloc(5*sizeof(*squares));
	squares[0] = squares0;
	squares[1] = squares1;
	squares[2] = squares2;
	squares[3] = squares3;
	squares[4] = squares4;

	Apartment ap = apartmentCreate(squares,5,3,100);

	bool result;
	int result1;
	TEST_EQUALS(final, APARTMENT_NULL_ARG, apartmentIsSameRoom(NULL, 0, 1, 0, 1, &result));
	TEST_EQUALS(final, APARTMENT_SUCCESS, apartmentIsSameRoom(ap, 1, 0, 1, 0, &result));
	TEST_EQUALS(final, APARTMENT_NO_ROOM, apartmentIsSameRoom(ap, 0, 0, 0, 1, &result));
	TEST_EQUALS(final, APARTMENT_SUCCESS, apartmentIsSameRoom(ap, 0, 0, 1, 0, &result));
	final = final&&result;
	TEST_EQUALS(final, APARTMENT_SUCCESS, apartmentIsSameRoom(ap, 0, 0, 4, 2, &result));
	final = final&&!result;

	TEST_EQUALS(final,-1,apartmentTotalArea(NULL));
	TEST_EQUALS(final,7,apartmentTotalArea(ap));

	TEST_EQUALS(final,APARTMENT_NULL_ARG,apartmentRoomArea(NULL,1,1,&result1));
	TEST_EQUALS(final,APARTMENT_NO_ROOM,apartmentRoomArea(ap,1,1,&result1));
	TEST_EQUALS(final,APARTMENT_OUT_OF_BOUNDS,apartmentRoomArea(ap,100,1,&result1));
	TEST_EQUALS(final,APARTMENT_OUT_OF_BOUNDS,apartmentRoomArea(ap,-5,1,&result1));
	TEST_EQUALS(final,APARTMENT_SUCCESS,apartmentRoomArea(ap,0,0,&result1));
	final = final&&(result1==2);
	TEST_EQUALS(final,APARTMENT_SUCCESS,apartmentRoomArea(ap,1,2,&result1));
	final = final&&(result1==1);
	TEST_EQUALS(final,APARTMENT_SUCCESS,apartmentRoomArea(ap,4,2,&result1));
	final = final&&(result1==2);

	Apartment ap1,ap2,ap3,ap4;
	TEST_EQUALS(final,APARTMENT_NULL_ARG,apartmentSplit(NULL,true,10,&ap1,&ap2));
	TEST_EQUALS(final,APARTMENT_BAD_SPLIT,apartmentSplit(ap,true,1,&ap1,&ap2));
	TEST_EQUALS(final,APARTMENT_OUT_OF_BOUNDS,apartmentSplit(ap,true,10,&ap1,&ap2));
	TEST_EQUALS(final,APARTMENT_SUCCESS,apartmentSplit(ap,true,2,&ap1,&ap2));
	TEST_EQUALS(final,APARTMENT_SUCCESS,apartmentSplit(ap1,false,1,&ap3,&ap4));

	TEST_EQUALS(final,-1,apartmentNumOfRooms(NULL));
	TEST_EQUALS(final,2,apartmentNumOfRooms(ap2));

	SquareType result2;

	TEST_EQUALS(final,APARTMENT_NULL_ARG,apartmentGetSquare(NULL,0,0,&result2));
	TEST_EQUALS(final,APARTMENT_OUT_OF_BOUNDS,apartmentGetSquare(ap2,5,0,&result2));
	TEST_EQUALS(final,APARTMENT_OUT_OF_BOUNDS,apartmentGetSquare(ap2,-1,0,&result2));
	TEST_EQUALS(final,APARTMENT_SUCCESS,apartmentGetSquare(ap2,0,0,&result2));
	TEST_EQUALS(final,EMPTY,result2);
	TEST_EQUALS(final,APARTMENT_SUCCESS,apartmentGetSquare(ap2,0,1,&result2));
	TEST_EQUALS(final,WALL,result2);

	TEST_EQUALS(final,APARTMENT_NULL_ARG,apartmentSetSquare(NULL,0,0,WALL));
	TEST_EQUALS(final,APARTMENT_OLD_VALUE,apartmentSetSquare(ap2,0,0,EMPTY));
	TEST_EQUALS(final,APARTMENT_SUCCESS,apartmentSetSquare(ap2,0,1,EMPTY));

	TEST_EQUALS(final,APARTMENT_SUCCESS,apartmentIsSameRoom(ap2,0,0,1,2,&result));
	TEST_EQUALS(final,result,true);

	TEST_EQUALS(final,APARTMENT_NULL_ARG,apartmentChangePrice(NULL,100));
	TEST_EQUALS(final,APARTMENT_PRICE_NOT_IN_RANGE,apartmentChangePrice(ap2,-101));
	TEST_EQUALS(final,APARTMENT_SUCCESS,apartmentChangePrice(ap2,100));

	TEST_EQUALS(final,-1,apartmentGetPrice(NULL));
	TEST_EQUALS(final,120,apartmentGetPrice(ap2));

	TEST_EQUALS(final,-1,apartmentGetLength(NULL));
	TEST_EQUALS(final,2,apartmentGetLength(ap2));

	TEST_EQUALS(final,-1,apartmentGetWidth(NULL));
	TEST_EQUALS(final,3,apartmentGetWidth(ap2));

	TEST_EQUALS(final,APARTMENT_SUCCESS,apartmentSetSquare(ap4,0,0,EMPTY));

	TEST_EQUALS(final,true,apartmentIsIdentical(NULL,NULL));
	TEST_EQUALS(final,false,apartmentIsIdentical(ap2,NULL));
	TEST_EQUALS(final,false,apartmentIsIdentical(ap2,ap3));
	TEST_EQUALS(final,true,apartmentIsIdentical(ap3,ap4));


	TEST_EQUALS(final,NULL,apartmentCopy(NULL));
	Apartment ap5 = apartmentCopy(ap2);
	TEST_EQUALS(final,true,apartmentIsIdentical(ap5,ap2));

	apartmentDestroy(ap);

	if(ap->price == -1)
		printf("ok");
	else
		printf("no");
	//apartmentDestroy(ap);

	apartmentDestroy(ap1);
	apartmentDestroy(ap2);
	apartmentDestroy(ap3);
	apartmentDestroy(ap4);
	apartmentDestroy(ap5);
	apartmentDestroy(NULL);

	free(squares);

	return final;

}


int main() {
	RUN_TEST(apartment_combo_test1);
	RUN_TEST(test);
	return true;
}
