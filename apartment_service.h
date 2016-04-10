#ifndef APARTMENT_SERVICE_H
#define APARTMENT_SERVICE_H

#include "apartment.h"

typedef struct apartment_service_t* ApartmentService;

struct apartment_service_t
{
	int numOfApartments;
	int maxNumOfApartments;
	Apartment* apartments;
	int* ids;
};

typedef enum {
	APARTMENT_SERVICE_SUCCESS,
	APARTMENT_SERVICE_OUT_OF_MEM,
	APARTMENT_SERVICE_NULL_ARG,
	APARTMENT_SERVICE_FULL,
	APARTMENT_SERVICE_NO_FIT,
	APARTMENT_SERVICE_OUT_OF_BOUNDS,
	APARTMENT_SERVICE_EMPTY,
	APARTMENT_SERVICE_ALREADY_EXISTS
} ApartmentServiceResult;


/*
 * Creates a new service.
 * The maximum number of apartments the service can hold is given
 * by maxNumOfApartments.
 *
 * @return
 * 	A new allocated service.
 * 	If maxNumOfApartments is not positive or in a case of a memory allocation
 * 	failure - return NULL.
 */
ApartmentService serviceCreate(int maxNumOfApartments);

/*
 * Creates a newly allocated copy of a given service.
 *
 * @return
 * 	A newly allocated copy of the original service.
 * 	NULL if the service is NULL.
 * 	NULL in any case of memory allocation failure(inside serviceCreate()).
 */
ApartmentService serviceCopy(ApartmentService service);

/*
 * Frees all memory allocated for the given service and the apartments
 * inside it.
 * This function can receive NULL.
 */
void serviceDestroy(ApartmentService service);

/*
 *@return
 * The number of apartments in the service(can be identical apartments).
 * This function asserts (service != NULL).
 */
int serviceNumberOfApatments(ApartmentService service);

/*
 * Adds a given apartment to the service.
 * The apartment's unique ID number is given by id.
 *
 * @return
 * 	NULL if the service is NULL.
 * 	APARTMENT_SERVICE_OUT_OF_BOUNDS if id < 0.
 * 	If the service is full(numOfApartments equals to maxNumOfApartments)
 * 	 - return APARTMENT_SERVICE_FULL.
 * 	If an apartment with the same ID exists
 * 	 - return APARTMENT_SERVICE_ALREADY_EXISTS.
 * 	APARTMENT_SERVICE_SUCCESS otherwise.
 */
ApartmentServiceResult serviceAddApartment(ApartmentService service, 									   
										   Apartment apartment, int id);

/*
 * Calculates the median price out of all the apartments in the given service.
 * Result should be stored in outResult.
 *
 * @return
 *  APARTMENT_SERVICE_NULL_ARG if the the service is NULL.
 *  APARTMENT_SERVICE_EMPTY if there are no apartments in the service.
 *  APARTMENT_SUCCESS otherwise.
 *
 */
ApartmentServiceResult servicePriceMedian(ApartmentService service,
										  int* outResult);

/*
 * Calculates the median area out of all the apartments in the given service.
 * Result should be stored in outResult.
 */
ApartmentServiceResult serviceAreaMedian(ApartmentService service, 
										 int* outResult);

ApartmentServiceResult serviceDeleteApartment(ApartmentService service,
											  Apartment apartment);

ApartmentServiceResult serviceDeleteById(ApartmentService service, int id);

ApartmentServiceResult serviceGetById(ApartmentService service, int id,
									  Apartment* outApartment);

ApartmentServiceResult serviceSearch(ApartmentService service, int area,
									 int rooms, int price, 
									 Apartment* outApartment);

#endif /* APARTMENT_SERVICE_H */
