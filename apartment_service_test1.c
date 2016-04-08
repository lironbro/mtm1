#include "aux_macros.h"
#include "apartment_service.h"

#include <stdlib.h>

bool service_test_combo1() {
	bool final = true;

	ApartmentService service = serviceCreate(2);
	ApartmentService service2 = serviceCopy(service);
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


	apartmentDestroy(apartment);
	serviceDestroy(service);
	serviceDestroy(service2);

	return final;
}

bool Test()
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

	int result;

	Apartment ap = apartmentCreate(squares,5,3,100);
	Apartment ap1,ap2;
	apartmentSplit(ap,true,2,&ap1,&ap2);

	ApartmentService ser = serviceCreate(4);
	ApartmentService ser1 = serviceCreate(4);

	TEST_EQUALS(final,NULL,serviceCreate(-1));
	TEST_EQUALS(final,NULL,serviceCreate(0));

	TEST_EQUALS(final,APARTMENT_SERVICE_NULL_ARG,serviceAddApartment(NULL,ap,5));
	TEST_EQUALS(final,APARTMENT_SERVICE_NULL_ARG,serviceAddApartment(ser,NULL,5));
	TEST_EQUALS(final,APARTMENT_SERVICE_OUT_OF_BOUNDS,serviceAddApartment(ser,ap,-1));
	TEST_EQUALS(final,APARTMENT_SERVICE_SUCCESS,serviceAddApartment(ser,ap,1));
	TEST_EQUALS(final,APARTMENT_SERVICE_ALREADY_EXISTS,serviceAddApartment(ser,ap,1));
	TEST_EQUALS(final,APARTMENT_SERVICE_SUCCESS,serviceAddApartment(ser,ap1,2));
	TEST_EQUALS(final,APARTMENT_SERVICE_SUCCESS,serviceAddApartment(ser,ap2,3));
	TEST_EQUALS(final,APARTMENT_SERVICE_SUCCESS,serviceAddApartment(ser,ap,4));
	TEST_EQUALS(final,APARTMENT_SERVICE_FULL,serviceAddApartment(ser,ap,5));

	TEST_EQUALS(final,-1,serviceNumberOfApatments(NULL));
	TEST_EQUALS(final,4,serviceNumberOfApatments(ser));

	TEST_EQUALS(final,APARTMENT_SERVICE_NULL_ARG,servicePriceMedian(NULL,&result));
	TEST_EQUALS(final,APARTMENT_SERVICE_EMPTY,servicePriceMedian(ser1,&result));
	TEST_EQUALS(final,APARTMENT_SERVICE_SUCCESS,servicePriceMedian(ser,&result));

	TEST_EQUALS(final,80,result);


	TEST_EQUALS(final,APARTMENT_SERVICE_NULL_ARG,serviceAreaMedian(NULL,&result));
	TEST_EQUALS(final,APARTMENT_SERVICE_EMPTY,serviceAreaMedian(ser1,&result));
	TEST_EQUALS(final,APARTMENT_SERVICE_SUCCESS,serviceAreaMedian(ser,&result));
	TEST_EQUALS(final,5,result);


	Apartment ap3,ap4;

	TEST_EQUALS(final,APARTMENT_SERVICE_NULL_ARG,serviceSearch(NULL,5,4,2,&ap3));

	TEST_EQUALS(final,APARTMENT_SERVICE_OUT_OF_BOUNDS,serviceSearch(ser,-1,4,2,&ap3));

	TEST_EQUALS(final,APARTMENT_SERVICE_OUT_OF_BOUNDS,serviceSearch(ser,1,-4,2,&ap3));
	TEST_EQUALS(final,APARTMENT_SERVICE_OUT_OF_BOUNDS,serviceSearch(ser,1,4,-1,&ap3));

	TEST_EQUALS(final,APARTMENT_SERVICE_EMPTY,serviceSearch(ser1,1,4,2,&ap3));
	TEST_EQUALS(final,APARTMENT_SERVICE_SUCCESS,serviceSearch(ser,2,3,200,&ap3));
	TEST_EQUALS(final,APARTMENT_SERVICE_NO_FIT,serviceSearch(ser,2,3,10,&ap3));



	TEST_EQUALS(final,APARTMENT_SERVICE_NULL_ARG,serviceGetById(NULL,5,&ap4));
	TEST_EQUALS(final,APARTMENT_SERVICE_OUT_OF_BOUNDS,serviceGetById(ser,-1,&ap4));
	TEST_EQUALS(final,APARTMENT_SERVICE_NO_FIT,serviceGetById(ser,7,&ap4));
	TEST_EQUALS(final,APARTMENT_SERVICE_EMPTY,serviceGetById(ser1,2,&ap4));
	TEST_EQUALS(final,APARTMENT_SERVICE_SUCCESS,serviceGetById(ser,1,&ap4));

	TEST_EQUALS(final,APARTMENT_SERVICE_NULL_ARG,serviceDeleteApartment(NULL,ap1));
	TEST_EQUALS(final,APARTMENT_SERVICE_NULL_ARG,serviceDeleteApartment(ser,NULL));
	TEST_EQUALS(final,APARTMENT_SERVICE_EMPTY,serviceDeleteApartment(ser1,ap1));
	TEST_EQUALS(final,APARTMENT_SERVICE_SUCCESS,serviceDeleteApartment(ser,ap2));
	TEST_EQUALS(final,APARTMENT_SERVICE_NO_FIT,serviceDeleteApartment(ser,ap2));


	TEST_EQUALS(final,APARTMENT_SERVICE_NULL_ARG,serviceDeleteById(NULL,1));
	TEST_EQUALS(final,APARTMENT_SERVICE_OUT_OF_BOUNDS,serviceDeleteById(ser,-1));
	TEST_EQUALS(final,APARTMENT_SERVICE_EMPTY,serviceDeleteById(ser1,2));
	TEST_EQUALS(final,APARTMENT_SERVICE_NO_FIT,serviceDeleteById(ser,7));
	TEST_EQUALS(final,APARTMENT_SERVICE_SUCCESS,serviceDeleteById(ser,1));


	TEST_EQUALS(final,NULL,serviceCopy(NULL));


	serviceDestroy(NULL);
	serviceDestroy(ser);
	serviceDestroy(ser1);
	apartmentDestroy(ap);
	apartmentDestroy(ap1);
	apartmentDestroy(ap2);
	apartmentDestroy(ap3);
	apartmentDestroy(ap4);
//fds


	free(squares);
	return final;
}
int maj2n() {
	setvbuf(stdout, NULL, _IONBF, 0);	// strangely enough, these 2 lines need to be included for
	setvbuf(stderr, NULL, _IONBF, 0);	// the code not to crash
	RUN_TEST(service_test_combo1);
	RUN_TEST(Test);
	return 0;
}
