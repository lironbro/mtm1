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
	// not yet written TEST_EQUALS(final, APARTMENT_SERVICE_EMPTY, serviceDeleteApartment(service, apartment));
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

	apartmentDestroy(apartment);	// very strange in here, I don't actually free apartment but doesn't work otherwise
	serviceDestroy(service);
	serviceDestroy(service2);



	/*
	 * To whom it may regard,
	 * here's the deal: the classes, as they're written right now, pass the initial tests
	 * but I've had to mess with the delete functions in each class because freeing the struct you're working
	 * on seems to cause some real big issues
	 * plus the serviceDeleteApartment function doesn't exist here
	 * and I haven't really checked the validity of other functions here
	 * so more work is due
	 *
	 * Yours truly,
	 * Liron
	 *
	 *
	 */
	return final;
}


int main() {
	RUN_TEST(service_test_combo);
	// TODO: add more tests:
	// RUN_TEST(...);
	return 0;
}


