/*

 * ckae.c
 *
 *  Created on: 29 במרץ 2016
 *      Author: Liron
 */

#include <stdio.h>
#include <stdlib.h>
#include "apartment.h"
#include "apartment_service.h"

/*
int main()
{

	ApartmentService service = serviceCreate(2);
	ApartmentService service2 = serviceCopy(service);
	SquareType square = EMPTY;
	SquareType* squarePtr = &square;
	Apartment apartment = apartmentCreate(&squarePtr, 1, 1, 100);
	serviceAddApartment(service, apartment, 1337);
	apartmentDestroy(apartment);
	printf("apartment with id %d\n",service->ids[0]);
	print(service->apartments[0]);
	serviceDeleteById(service, 1337);
	print(apartment);


	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

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
	printf("hello\n");
	Apartment apt = apartmentCreate(squares, length, width, price);
	squares[5][6] = WALL;
	Apartment apt1 = apartmentCreate(squares, length, width, price);
	free(squares);

	printf("apt:\n");
	print(apt);
	printf("apt1:\n");
	print(apt1);

	bool identical = apartmentIsIdentical(apt1, apt);
	if(identical)
		printf("apartments identical\n");
	else printf("apartments not identical\n");

	printf("number of rooms in apt is %d\n",apartmentNumOfRooms(apt));
	printf("number of rooms in apt1 is %d\n",apartmentNumOfRooms(apt1));

	bool sameRoom;
	apartmentIsSameRoom(apt, 3, 4, 3, 1, &sameRoom);
	if(sameRoom)
		printf("same room\n");
	else printf("not same room\n");

	printf("total area of apt is %d\n",apartmentTotalArea(apt));

	int roomArea;
	apartmentRoomArea(apt, 7, 8, &roomArea);
	printf("room area is %d\n",roomArea);

	Apartment apt2 = NULL, apt3 = NULL;
	apartmentSplit(apt1, false, 7, &apt2, &apt3);
	printf("apt2:\n");
	print(apt2);
	printf("apt3:\n");
	print(apt3);

	apartmentChangePrice(apt, -50);
	printf("apt updated price is %d\n", apartmentGetPrice(apt));

	apartmentDestroy(apt);
	apartmentDestroy(apt1);
	apartmentDestroy(apt2);
	apartmentDestroy(apt3);
	printf("destroyed");

	return 0;
}

*/

