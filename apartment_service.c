/*
 * apartment_service.c
 *
 *  Created on: 28 2016
 *      Author: Liron
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "apartment.h"
#include "apartment_service.h"

#define CHECK_POSITIVE(a, b, c) ((a>0) && (b>0) && (c>=0))


void maxSort(int* a, int n);

void swap(int* a, int* b);

int indexOfMax(int* a, int m);

ApartmentServiceResult removeApartment(ApartmentService service, int index);

ApartmentService serviceCreate(int maxNumOfApartments)
{
	if(maxNumOfApartments <= 0)
		return NULL;
	ApartmentService service = malloc(sizeof(*service));
	if(service == NULL)
		return NULL;
	service->maxNumOfApartments = maxNumOfApartments;
	service->numOfApartments = 0;
	service->apartments = malloc(maxNumOfApartments *sizeof(Apartment));
	if(service->apartments == NULL)
		return NULL;
	service->ids = malloc(maxNumOfApartments *sizeof(int));
	if(service->ids == NULL)
		return NULL;
	return service;
}

ApartmentServiceResult serviceAddApartment(ApartmentService service,
			Apartment apartment, int id)
{
	if(apartment == NULL || service == NULL)
		return APARTMENT_SERVICE_NULL_ARG;
	if(id < 0)
		return APARTMENT_SERVICE_OUT_OF_BOUNDS;
	if(service->numOfApartments == service->maxNumOfApartments)
		return APARTMENT_SERVICE_FULL;
	for(int i=0; i<service->numOfApartments; i++)
	{
		if(service->ids[i] == id)
		{
			return APARTMENT_SERVICE_ALREADY_EXISTS;
		}
	}


	service->apartments[service->numOfApartments] = apartmentCopy(apartment);
	//int oPrice = apartment->price, oLength = apartment->length, oWidth = apartment->width;
	//int cPrice = service->apartments[service->numOfApartments]->price, cLength = service->apartments[service->numOfApartments]->length, cWidth = service->apartments[service->numOfApartments]->width;
	service->ids[service->numOfApartments] = id;
	(service->numOfApartments)++;
	return APARTMENT_SERVICE_SUCCESS;
}

int serviceNumberOfApatments(ApartmentService service)
{
	if(service==NULL)
		return -1;
	return service->numOfApartments;
}

ApartmentServiceResult servicePriceMedian(ApartmentService service, int* outResult)
{
	if (service == NULL)
		return APARTMENT_SERVICE_NULL_ARG;
	if(service->apartments == NULL || service->numOfApartments == 0)
	    return APARTMENT_SERVICE_EMPTY;
	int length = service->numOfApartments;
	int* prices = malloc(length*sizeof(int));
	for(int i=0; i<length; i++)
	{
		prices[i] = apartmentGetPrice(service->apartments[i]);
	}
	maxSort(prices, length);
	if(length%2 == 0)
		*outResult = (prices[length/2]+prices[length/2-1])/2;
	else *outResult = prices[length/2];
	free(prices);
	return APARTMENT_SUCCESS;
}

ApartmentServiceResult serviceAreaMedian(ApartmentService service,
        int* outResult)
{
	if (service == NULL)
			return APARTMENT_SERVICE_NULL_ARG;
    if(service->apartments == NULL || service->numOfApartments == 0)
        return APARTMENT_SERVICE_EMPTY;
    int length = service->numOfApartments;
    int* area = malloc(length*sizeof(int));
    for(int i=0; i<length; i++)
        area[i] = apartmentTotalArea(service->apartments[i]);
    maxSort(area, length);
    if(length%2 == 0)
		*outResult = (area[length/2]+area[length/2-1])/2;
	else *outResult = area[length/2];
    free(area);
    return APARTMENT_SERVICE_SUCCESS;
}

ApartmentServiceResult serviceSearch(ApartmentService service, int area,
        int rooms, int price, Apartment* outApartment)
{	// ziv's function
	if(service == NULL)
		return APARTMENT_SERVICE_NULL_ARG;
	int lastLocation=-1, currPrice;
	if(!CHECK_POSITIVE(area, rooms, price))
		return APARTMENT_SERVICE_OUT_OF_BOUNDS;
	if((service->numOfApartments)<=0)
		return APARTMENT_SERVICE_EMPTY;
	int length = service->numOfApartments;
	for(int i=0; i<length; i++) {
		int currArea = apartmentTotalArea(service->apartments[i]);
		int currRooms = apartmentNumOfRooms(service->apartments[i]);
		currPrice = apartmentGetPrice(service->apartments[i]);
		if(currArea>=area && currRooms>=rooms && currPrice<=price)
			lastLocation=i;
	}
	if(lastLocation==-1)
		return APARTMENT_SERVICE_NO_FIT;
	*outApartment = apartmentCreate(service->apartments[lastLocation]->squares,
		apartmentGetLength(service->apartments[lastLocation]),
		apartmentGetWidth(service->apartments[lastLocation]), currPrice);
	return APARTMENT_SERVICE_SUCCESS;
}

ApartmentServiceResult serviceGetById(ApartmentService service, int id, Apartment* outApartment)
{
	if (service == NULL)
		return APARTMENT_SERVICE_NULL_ARG;
	if(id < 0)
		return APARTMENT_SERVICE_OUT_OF_BOUNDS;
	if(service->apartments == NULL || service->numOfApartments == 0)
		return APARTMENT_SERVICE_EMPTY;
	for(int i=0; i< service->numOfApartments; i++)
	{
		if(service->ids[i] == id)
		{
			outApartment = apartmentCopy(service->apartments[i]);
			return APARTMENT_SERVICE_SUCCESS;
		}
	}
	return APARTMENT_SERVICE_NO_FIT;
}

ApartmentServiceResult removeApartment(ApartmentService service, int index)
{
	if(service == NULL)
		return APARTMENT_SERVICE_NULL_ARG;
	if(service->apartments == NULL || service->numOfApartments == 0)
		return APARTMENT_SERVICE_EMPTY;
	if(index < 0 || index > service->numOfApartments)
		return APARTMENT_SERVICE_NO_FIT;
	service->numOfApartments--;
	apartmentDestroy(service->apartments[index]);	// this might work, not sure yet
	for(int i=index; i<service->maxNumOfApartments-1; i++)
	{
		service->apartments[i] = service->apartments[i+1];
	}
	service->apartments[service->maxNumOfApartments-1] = NULL;
	return APARTMENT_SUCCESS;
}

ApartmentServiceResult serviceDeleteApartment(ApartmentService service, Apartment apartment)
{
	if(service == NULL||apartment == NULL)
		return APARTMENT_SERVICE_NULL_ARG;
	if(service->apartments == NULL || service->numOfApartments == 0)
			return APARTMENT_SERVICE_EMPTY;
	int index = -1;
	for(int i = service->numOfApartments-1; i >= 0; i--)
	{
		if(apartmentIsIdentical(service->apartments[i], apartment))
		{
			index = i;
			break;
		}
	}
	if( index == -1)
		return APARTMENT_SERVICE_NO_FIT;
	removeApartment(service, index);
	return APARTMENT_SUCCESS;
}

ApartmentServiceResult serviceDeleteById(ApartmentService service, int id)
{	// freeing might be needed
	if (service == NULL)
		return APARTMENT_SERVICE_NULL_ARG;
	if(id < 0)
		return APARTMENT_SERVICE_OUT_OF_BOUNDS;
	if(service->apartments == NULL || service->numOfApartments == 0)
		return APARTMENT_SERVICE_EMPTY;
	int index = -1;
	for(int i=0; i<service->numOfApartments; i++)
	{
		if(service->ids[i] == id)
		{
			index = i;
			break;
		}
	}
	if(index == -1)
		return APARTMENT_SERVICE_NO_FIT;
	removeApartment(service, index);
	return APARTMENT_SUCCESS;
}

ApartmentService serviceCopy(ApartmentService service)
{
	if(service == NULL)
		return NULL;
	ApartmentService copy = serviceCreate(service->maxNumOfApartments);
	if(copy == NULL)
		return NULL;
	copy->numOfApartments = service->numOfApartments;
	for(int i=0; i<copy->numOfApartments; i++)
	{
		copy->ids[i] = service->ids[i];
		copy->apartments[i] = apartmentCopy(service->apartments[i]);
	}
	return copy;
}

void serviceDestroy(ApartmentService service)
{
	if(service == NULL)
		return;
	free(service->ids);
	for(int i=0; i<service->numOfApartments; i++)
	{
		apartmentDestroy(service->apartments[i]);
		//free(service->apartments[i]); 	// this causes problems here, as well as apartmentDestroy, but I think that atleast one is necessary
	}
	free(service->apartments);
	//free(service);
}

/* Helper function: finds the index of maximal element */
int indexOfMax(int* a, int m)
{
	int i, i_max = 0;
	for ( i = 1; i < m; i++ )
		if ( a[i_max] <= a[i] )
			i_max = i;
	return i_max;
}
void maxSort(int* a, int n)
{
	int length;
	for ( length = n; length > 1; length-- ) {
		int i_max = indexOfMax(a, length);
	swap(&a[i_max], &a[length-1]);
	}
}

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


void servicePrint(ApartmentService service)
{
	if(service == NULL || service->apartments == NULL || service->numOfApartments <= 0)
		return;
	printf("max apartments: %d\ncurrent apartments: %d\n", service->maxNumOfApartments, service->numOfApartments);
	for(int i=0; i<service->numOfApartments; i++)
	{
		printf("apartment at id %d is:\n", service->ids[i]);
		apartmentPrint(service->apartments[i]);
	}
	printf("Done printing apartments ------------------\n");
}
