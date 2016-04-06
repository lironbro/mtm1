#include "aux_macros.h"
#include "apartment_service.h"
#include "apartment.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool service_test_combo() {
	bool final = true;

	ApartmentService service = serviceCreate(10);
	//ApartmentService service2 = serviceCopy(service);
	SquareType square = EMPTY;
	SquareType* squarePtr = &square;
	Apartment apartment = apartmentCreate(&squarePtr, 1, 1, 100);
	int intResult = -1;
	Apartment apartmentRes = NULL;


	int id = 1000;
	TEST_EQUALS(final, APARTMENT_SERVICE_NULL_ARG, serviceAreaMedian(NULL, &intResult));
	TEST_EQUALS(final, APARTMENT_SERVICE_EMPTY, serviceDeleteApartment(service, apartment));
	TEST_EQUALS(final, APARTMENT_SERVICE_SUCCESS, serviceAddApartment(service, apartment, id));
	TEST_EQUALS(final, APARTMENT_SERVICE_SUCCESS, servicePriceMedian(service, &intResult));
	TEST_EQUALS(final, 100, intResult);
	TEST_EQUALS(final, APARTMENT_SERVICE_NO_FIT, serviceSearch(service, 50,50,50, &apartmentRes));
	TEST_EQUALS(final, 1, serviceNumberOfApatments(service));
	TEST_EQUALS(final, APARTMENT_SERVICE_NO_FIT, serviceGetById(service, 2000, &apartmentRes));

	TEST_EQUALS(final, APARTMENT_SERVICE_SUCCESS, serviceDeleteById(service, id));


	// ------------------------------------------------ PASSES THESE ORIGINAL TESTS
	TEST_EQUALS(final, APARTMENT_SERVICE_SUCCESS, serviceAddApartment(service, apartment, id));

	int length = 12, width = 15, price = 3500;
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
	Apartment apt1 = apartmentCreate(squares, length, width, price+77);	// sometimes it has problems adding
	Apartment apt2 = apartmentCreate(squares, length, width, price*3);	// apartments 1&2&3(?), probably
	Apartment apt3 = apartmentCreate(squares, length, width, price*3+1);// something to do with malloc
	Apartment apt4 = apartmentCreate(squares, length, width, price*3+2);// issues, causes crashing and false values
	free(squares);

	printf("printing apartments 1111111111111111111111111111111111111111\n\n\n");
	printf("apartment 1000:\n");
	apartmentPrint(apt);
	printf("apartment 1:\n");
	apartmentPrint(apt1);
	printf("apartment 2:\n");
	apartmentPrint(apt2);
	printf("apartment 3:\n");
	apartmentPrint(apt3);
	printf("apartment 4:\n");
	apartmentPrint(apt4);

	TEST_EQUALS(final, APARTMENT_SERVICE_SUCCESS, serviceAddApartment(service, apt, 1));
	TEST_EQUALS(final, APARTMENT_SERVICE_SUCCESS, serviceAddApartment(service, apt1, 2));
	TEST_EQUALS(final, APARTMENT_SERVICE_SUCCESS, serviceAddApartment(service, apt2, 3));
	TEST_EQUALS(final, APARTMENT_SERVICE_SUCCESS, serviceAddApartment(service, apt3, 4));

	printf("printing apartments 2222222222222222222222222222222222222222222\n\n\n");
	printf("apartment 1000:\n");	apartmentPrint(apt);
	printf("apartment 1:\n");
	apartmentPrint(apt1);
	printf("apartment 2:\n");
	apartmentPrint(apt2);
	printf("apartment 3:\n");
	apartmentPrint(apt3);
	printf("apartment 4:\n");
	apartmentPrint(apt4);

	printf("printing apartments in arrayyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy\n\n\n");
	servicePrint(service);

	int medianPrice;
	for(int i=0; i<service->numOfApartments; i++)
		printf("price of apartment %d is %d\n", service->ids[i], apartmentGetPrice(service->apartments[i]));
	servicePriceMedian(service, &medianPrice);
	printf("median price is: %d\n", medianPrice);
	int medianArea;
	for(int i=0; i<service->numOfApartments; i++)
		printf("area of apartment %d is %d\n", service->ids[i], apartmentTotalArea(service->apartments[i]));
	serviceAreaMedian(service, &medianArea);
	printf("median area is: %d\n", medianArea);


	printf("destroying apartments\n");
	apartmentDestroy(apt);
	printf("destroyed apt\n");
	apartmentDestroy(apt1);
	printf("destroyed apt1\n");
	apartmentDestroy(apt2);
	printf("destroyed apt2\n");
	apartmentDestroy(apt3);
	printf("destroyed apt3\n");
	apartmentDestroy(apt4);
	printf("destroyed apt4\n");
	apartmentDestroy(apartment);	// very strange in here, I don't actually free apartment but doesn't work otherwise
	printf("destroyed apartment\n");	// fails to destroy the service
	serviceDestroy(service);
	printf("destroyed service\n");
	//serviceDestroy(service2);



	/*
	 * 5/4/2016
	 * To whom it may regard,
	 * here's the deal: the classes, as they're written right now, pass the initial tests
	 * but I've had to mess with the delete functions in each class because freeing the struct you're working
	 * on seems to cause some real big issues
	 * plus the serviceDeleteApartment function doesn't exist here
	 * and I haven't really checked the validity of other functions here
	 *
	 *
	 * 6/4/2016
	 * weird thing is, with the this test function it seems to sometimes add the apartments poorly
	 * meaning it messes with the entire apartment structre, erasing the board and chaning the price
	 * and other fields. i tried to find out where this happens, my guess is in the serviceAddApartment
	 * function, but i couldn't locate the bad line because debugging this is a pain in the ass
	 *
	 *
	 * so more work is due
	 *
	 * Yours truly,
	 * Liron
	 *
	 *
	 */
	return final;
}

// pretty strange, the test crashes once in a while, don't know where or why or how frequently it crashes
// seems it crashed once after printing the 4th apartment
// now the 3rd
// now when printing the first apartment, before it actually printed the rows, strange
int majn() {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	RUN_TEST(service_test_combo);
	// TODO: add more tests:
	// RUN_TEST(...);
	return 0;
}


