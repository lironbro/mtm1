#include "aux_macros.h"
#include "apartment_service.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool service_test_combo() {
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
	//TEST_EQUALS(final, APARTMENT_SERVICE_EMPTY, serviceDeleteApartment(service, apartment));
	TEST_EQUALS(final, APARTMENT_SERVICE_SUCCESS, serviceAddApartment(service, apartment, id));
	TEST_EQUALS(final, APARTMENT_SERVICE_SUCCESS, servicePriceMedian(service, &intResult));
	TEST_EQUALS(final, 100, intResult);
	TEST_EQUALS(final, APARTMENT_SERVICE_NO_FIT, serviceSearch(service, 50,50,50, &apartmentRes));
	TEST_EQUALS(final, 1, serviceNumberOfApatments(service));
	TEST_EQUALS(final, APARTMENT_SERVICE_NO_FIT, serviceGetById(service, 2000, &apartmentRes));
	TEST_EQUALS(final, APARTMENT_SERVICE_SUCCESS, serviceDeleteById(service, id));

	/*
	Apartment* apt;
	serviceGetById(service, 1000, apt);
	final = final && *apt == apartment;
	*/


	apartmentDestroy(apartment);

	serviceDestroy(service);
	serviceDestroy(service2);
	return final;
}

/*
int main() {
	RUN_TEST(service_test_combo);
	// TODO: add more tests:
	// RUN_TEST(...);
	return 0;
}

*/
