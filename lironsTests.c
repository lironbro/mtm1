/*
 * lironsTests.c
 *
 *  Created on: 8 באפר׳ 2016
 *      Author: Liron
 */


#include "aux_macros.h"
#include "apartment_service.h"

#include <stdlib.h>

void initializeSquares(SquareType** squares, int length, int width)
{
	for(int i=0; i<length; i++)
			squares[i] = malloc(width *sizeof(SquareType));
	for(int i=0; i<length; i++)
	{
		for(int j=0; j<width; j++)
		{
			if(i == 0 || i == length-1 || j == 0 || j == width-1 ||
					i == length/2 || j == width/2 || j==width/3 || i ==length/3)
				squares[i][j] = WALL;
			else
				squares[i][j] = EMPTY;
		}
	}
}

bool lironsTests()
{
	bool final = true;


	// Apartment -----------------------------------------------------------------

	int length = 12, width = 15, price = 3500;
	SquareType** squares  = malloc(length*sizeof (SquareType*));

	initializeSquares(squares, length, width);

	// apartmentCreate
	Apartment apt = apartmentCreate(NULL, length, width, price);
	TEST_EQUALS(final, NULL, apt);
	apartmentDestroy(apt);
	apt = apartmentCreate(squares, 0, width, price);
	TEST_EQUALS(final, NULL, apt);
	apartmentDestroy(apt);
	apt = apartmentCreate(squares, length, 0, price);
	TEST_EQUALS(final, NULL, apt);
	apartmentDestroy(apt);
	apt = apartmentCreate(squares, length, width, -1);
	TEST_EQUALS(final, NULL, apt);
	apartmentDestroy(apt);

	apt = apartmentCreate(squares, length, width, price);
	squares[5][6] = WALL;
	Apartment apt1 = apartmentCreate(squares, length, width, price);
	squares[1][8] = WALL;
	squares[2][8] = WALL;
	Apartment apt2 = apartmentCreate(squares, length, width, price*3);
	squares[7][6] = WALL;
	squares[8][6] = WALL;
	squares[9][6] = WALL;
	squares[10][6] = WALL;
	Apartment apt3 = apartmentCreate(squares, length, width, price*3+1);
	squares[9][14] = EMPTY;
	squares[10][14] = EMPTY;
	Apartment apt4 = apartmentCreate(squares, length, width, price*3+2);
	for(int i=0; i<length; i++) {
			free(squares[i]);
		}
	free(squares);

	TEST_EQUALS(final, NULL, apartmentCopy(NULL));	// apartmentCopy

	bool outResult;	// apartmentIsSameRoom
	TEST_EQUALS(final, APARTMENT_NULL_ARG, apartmentIsSameRoom(NULL, 0, 0, 1, 1, &outResult));
	TEST_EQUALS(final, APARTMENT_OUT_OF_BOUNDS , apartmentIsSameRoom(apt, -1, 0, 1, 1, &outResult));
	TEST_EQUALS(final, APARTMENT_OUT_OF_BOUNDS , apartmentIsSameRoom(apt, 0, -1, 1, 1, &outResult));
	TEST_EQUALS(final, APARTMENT_OUT_OF_BOUNDS , apartmentIsSameRoom(apt, 0, 0, length, 1, &outResult));
	TEST_EQUALS(final, APARTMENT_OUT_OF_BOUNDS , apartmentIsSameRoom(apt, 0, 0, 1, width, &outResult));
	TEST_EQUALS(final, APARTMENT_NO_ROOM , apartmentIsSameRoom(apt, 0, 0, 1, 1, &outResult));
	TEST_EQUALS(final, APARTMENT_SUCCESS , apartmentIsSameRoom(apt, 1, 1, 5, 6, &outResult));
	TEST_EQUALS(final, false, outResult);
	TEST_EQUALS(final, APARTMENT_SUCCESS , apartmentIsSameRoom(apt, 1, 1, 3, 4, &outResult));
	TEST_EQUALS(final, true, outResult);
	TEST_EQUALS(final, true, outResult);

	TEST_EQUALS(final, -1, apartmentTotalArea(NULL));	// apartmentTotalArea
	TEST_EQUALS(final, 88, apartmentTotalArea(apt));

	int area;	// apartmentRoomArea
	TEST_EQUALS(final, APARTMENT_NULL_ARG, apartmentRoomArea(NULL, 0, 0, &area));
	TEST_EQUALS(final, APARTMENT_OUT_OF_BOUNDS, apartmentRoomArea(apt, -1, 0, &area));
	TEST_EQUALS(final, APARTMENT_OUT_OF_BOUNDS, apartmentRoomArea(apt, 0, width+1, &area));
	TEST_EQUALS(final, APARTMENT_NO_ROOM, apartmentRoomArea(apt, 0, 0, &area));
	TEST_EQUALS(final, APARTMENT_SUCCESS, apartmentRoomArea(apt, 7, 9, &area));
	TEST_EQUALS(final, 24, area);

	// apartmentSplt

	// apartmentNumOfRooms - this might take a while so don't freak out
	TEST_EQUALS(final, -1, apartmentNumOfRooms(NULL));
	TEST_EQUALS(final, 9, apartmentNumOfRooms(apt));
	TEST_EQUALS(final, 8, apartmentNumOfRooms(apt1));

	// apartmentGetSquare
	SquareType square;
	TEST_EQUALS(final, APARTMENT_NULL_ARG, apartmentGetSquare(NULL, 0, 0, &square));
	TEST_EQUALS(final, APARTMENT_OUT_OF_BOUNDS, apartmentGetSquare(apt, -1, 0, &square));
	TEST_EQUALS(final, APARTMENT_OUT_OF_BOUNDS, apartmentGetSquare(apt, 1, width, &square));
	TEST_EQUALS(final, APARTMENT_SUCCESS, apartmentGetSquare(apt, 6, 5, &square));
	TEST_EQUALS(final, WALL, square);
	TEST_EQUALS(final, APARTMENT_SUCCESS, apartmentGetSquare(apt, 1, 1, &square));
	TEST_EQUALS(final, EMPTY, square);

	// apartmentSetSquare
	TEST_EQUALS(final, APARTMENT_NULL_ARG, apartmentSetSquare(NULL, 0, 0, WALL));
	TEST_EQUALS(final, APARTMENT_OUT_OF_BOUNDS, apartmentSetSquare(apt, length, 0, WALL));
	TEST_EQUALS(final, APARTMENT_OUT_OF_BOUNDS, apartmentSetSquare(apt, 0, -1, WALL));
	TEST_EQUALS(final, APARTMENT_OLD_VALUE, apartmentSetSquare(apt, 6, 5, WALL));
	TEST_EQUALS(final, APARTMENT_SUCCESS, apartmentSetSquare(apt, 6, 5, EMPTY));
	TEST_EQUALS(final, APARTMENT_SUCCESS, apartmentSetSquare(apt, 6, 5, WALL));

	// apartmentChangePrice
	TEST_EQUALS(final, APARTMENT_NULL_ARG, apartmentChangePrice(NULL, 10));
	TEST_EQUALS(final, APARTMENT_PRICE_NOT_IN_RANGE, apartmentChangePrice(apt, -1000));
	TEST_EQUALS(final, APARTMENT_SUCCESS, apartmentChangePrice(apt, 100));
	TEST_EQUALS(final, APARTMENT_SUCCESS, apartmentChangePrice(apt, -50));

	// apartmentGetPrice
	TEST_EQUALS(final, -1, apartmentGetPrice(NULL));
	TEST_EQUALS(final, price, apartmentGetPrice(apt));

	// apartmentGetLength
	TEST_EQUALS(final, -1, apartmentGetLength(NULL));
	TEST_EQUALS(final, length, apartmentGetLength(apt));

	// apartmentGetWidth
	TEST_EQUALS(final, -1, apartmentGetWidth(NULL));
	TEST_EQUALS(final, width, apartmentGetWidth(apt));

	// apartmentIsIdentical
	TEST_EQUALS(final, true, apartmentIsIdentical(NULL, NULL));
	TEST_EQUALS(final, false, apartmentIsIdentical(NULL, apt));
	TEST_EQUALS(final, false, apartmentIsIdentical(apt, apt1));
	apartmentSetSquare(apt, 5, 6, WALL);
	TEST_EQUALS(final, true, apartmentIsIdentical(apt, apt1));
	apartmentSetSquare(apt, 5, 6, EMPTY);



	// ApartmentService -----------------------------------------------------------------

	int maxApartments = 5;
	ApartmentService service = serviceCreate(maxApartments),
			service2 = serviceCreate(maxApartments);

	// serviceAddApartment
	TEST_EQUALS(final, APARTMENT_SERVICE_NULL_ARG,
			serviceAddApartment(service, NULL, 1));
	TEST_EQUALS(final, APARTMENT_SERVICE_NULL_ARG,
			serviceAddApartment(NULL, apt, 1));
	TEST_EQUALS(final, APARTMENT_SERVICE_OUT_OF_BOUNDS,
			serviceAddApartment(service, apt, -1));
	TEST_EQUALS(final, APARTMENT_SERVICE_SUCCESS,
				serviceAddApartment(service, apt, 10));
	TEST_EQUALS(final, APARTMENT_SERVICE_ALREADY_EXISTS,
						serviceAddApartment(service, apt1, 10));
	TEST_EQUALS(final, APARTMENT_SERVICE_SUCCESS,
					serviceAddApartment(service, apt1, 20));
	TEST_EQUALS(final, APARTMENT_SERVICE_SUCCESS,
					serviceAddApartment(service, apt3, 40));
	TEST_EQUALS(final, APARTMENT_SERVICE_SUCCESS,
					serviceAddApartment(service, apt4, 50));
	TEST_EQUALS(final, APARTMENT_SERVICE_SUCCESS,
					serviceAddApartment(service, apt2, 30));
	TEST_EQUALS(final, APARTMENT_SERVICE_FULL,
				serviceAddApartment(service, apt4, 50));

	// serviceNumberOfApatments
	TEST_EQUALS(final, -1, serviceNumberOfApatments(NULL));
	TEST_EQUALS(final, 5, serviceNumberOfApatments(service));
	TEST_EQUALS(final, 0, serviceNumberOfApatments(service2));	// fails

	// servicePriceMedian
	int medianPrice;
	TEST_EQUALS(final, APARTMENT_SERVICE_NULL_ARG,
			servicePriceMedian(NULL, &medianPrice));
	TEST_EQUALS(final, APARTMENT_SERVICE_EMPTY,
		servicePriceMedian(service2, &medianPrice));
	TEST_EQUALS(final, APARTMENT_SERVICE_SUCCESS,
		servicePriceMedian(service, &medianPrice));
	TEST_EQUALS(final, 10500, medianPrice);



	// serviceAreaMedian
	int medianArea;
	TEST_EQUALS(final, APARTMENT_SERVICE_NULL_ARG,
			serviceAreaMedian(NULL, &medianArea));
	TEST_EQUALS(final, APARTMENT_SERVICE_EMPTY,
			serviceAreaMedian(service2, &medianArea));
	TEST_EQUALS(final, APARTMENT_SERVICE_SUCCESS,
			serviceAreaMedian(service, &medianArea));
	TEST_EQUALS(final, 85, medianArea);	//fails

	// serviceSearch - takes a long time, don't freak out
	Apartment resultApt;
	TEST_EQUALS(final, APARTMENT_SERVICE_NULL_ARG,
			serviceSearch(NULL, 1, 1, 1, &resultApt));
	TEST_EQUALS(final, APARTMENT_SERVICE_OUT_OF_BOUNDS,
			serviceSearch(service, -1, 1, 1, &resultApt));
	TEST_EQUALS(final, APARTMENT_SERVICE_OUT_OF_BOUNDS,
				serviceSearch(service, 1, -1, 1, &resultApt));
	TEST_EQUALS(final, APARTMENT_SERVICE_OUT_OF_BOUNDS,
				serviceSearch(service, 1, 1, -1, &resultApt));
	TEST_EQUALS(final, APARTMENT_SERVICE_EMPTY,
				serviceSearch(service2, 1, 1, 1, &resultApt));
	TEST_EQUALS(final, APARTMENT_SERVICE_NO_FIT,
				serviceSearch(service, 1, 1, 1, &resultApt));
	TEST_EQUALS(final, APARTMENT_SERVICE_SUCCESS,
				serviceSearch(service, 88, 9, 15000, &resultApt));
	TEST_EQUALS(final, true, apartmentIsIdentical(apt, resultApt));

	// serviceGetById
	TEST_EQUALS(final, APARTMENT_SERVICE_NULL_ARG,
				serviceGetById(NULL, 10, &resultApt));
	TEST_EQUALS(final, APARTMENT_SERVICE_OUT_OF_BOUNDS,
				serviceGetById(service, -5, &resultApt));
	TEST_EQUALS(final, APARTMENT_SERVICE_EMPTY,
				serviceGetById(service2, 5, &resultApt));
	TEST_EQUALS(final, APARTMENT_SERVICE_NO_FIT,
				serviceGetById(service, 15, &resultApt));
	TEST_EQUALS(final, APARTMENT_SERVICE_SUCCESS,
				serviceGetById(service, 20, &resultApt));
	TEST_EQUALS(final, true, apartmentIsIdentical(resultApt, apt1));

	// serviceDeleteApartment
	TEST_EQUALS(final, APARTMENT_SERVICE_NULL_ARG,
				serviceDeleteApartment(NULL, apt));
	TEST_EQUALS(final, APARTMENT_SERVICE_NULL_ARG,
				serviceDeleteApartment(service, NULL));
	TEST_EQUALS(final, APARTMENT_SERVICE_EMPTY,
				serviceDeleteApartment(service2, apt));
	resultApt->price = 0;
	TEST_EQUALS(final, APARTMENT_SERVICE_NO_FIT,
				serviceDeleteApartment(service, resultApt));
	resultApt->price = apt1->price;
	TEST_EQUALS(final, APARTMENT_SERVICE_SUCCESS,
				serviceDeleteApartment(service, resultApt));
	TEST_EQUALS(final, APARTMENT_SERVICE_NO_FIT,
				serviceDeleteApartment(service, resultApt));

	// serviceDeleteById
	TEST_EQUALS(final, APARTMENT_SERVICE_NULL_ARG,
			serviceDeleteById(NULL, 1));
	TEST_EQUALS(final, APARTMENT_SERVICE_OUT_OF_BOUNDS,
			serviceDeleteById(service2, -1));
	TEST_EQUALS(final, APARTMENT_SERVICE_EMPTY,
			serviceDeleteById(service2, 1));
	TEST_EQUALS(final, APARTMENT_SERVICE_NO_FIT,
			serviceDeleteById(service, 1));
	TEST_EQUALS(final, APARTMENT_SERVICE_SUCCESS,
			serviceDeleteById(service, 40));
	TEST_EQUALS(final, APARTMENT_SERVICE_NO_FIT,	// fails
			serviceDeleteById(service, 40));

	// serviceCopy
	TEST_EQUALS(final, NULL, serviceCopy(NULL));
	ApartmentService copy = serviceCopy(service);
	TEST_EQUALS(final, true, ((service->numOfApartments == copy->numOfApartments)
			&& (service->maxNumOfApartments == copy->maxNumOfApartments)));
	for(int i=0; i<copy->numOfApartments; i++)
	{
		TEST_EQUALS(final, true,
		apartmentIsIdentical(service->apartments[i], copy->apartments[i]));
	}

	// destroying -----------------------------------------------------------------


	apartmentDestroy(apt);
	apartmentDestroy(apt1);
	apartmentDestroy(apt2);
	apartmentDestroy(apt3);
	apartmentDestroy(apt4);
	serviceDestroy(service);
	serviceDestroy(service2);


	return final;
}






int main()
{
	RUN_TEST(lironsTests);
	return 0;
}


