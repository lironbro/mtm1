/*
 * apartment_service.c
 *
 *  Created on: 28 2016
 *      Author: Liron
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "apartment.h"
#include "apartment_service.h"

#define CHECK_POSITIVE(a, b, c) (a>=0) && (b>=0) && (c>=0)

void quickSort( int a[], int l, int r);

int partition( int a[], int l, int r);



ApartmentService serviceCreate(int maxNumOfApartments)
{
	if(maxNumOfApartments <= 0)
		return NULL;
	ApartmentService service = malloc(sizeof(ApartmentService));
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
	if(apartment == NULL)
		return APARTMENT_SERVICE_NULL_ARG;
	if(id < 0)
		return APARTMENT_SERVICE_OUT_OF_BOUNDS;
	if(service->numOfApartments == service->maxNumOfApartments)
		return APARTMENT_SERVICE_FULL;
	for(int i=0; i<service->numOfApartments; i++)
	{
		if(service->ids[i] == id)
			return APARTMENT_SERVICE_ALREADY_EXISTS;
	}
	service->apartments[service->numOfApartments] = apartment;
	service->ids[service->numOfApartments] = id;
	service->numOfApartments++;
	return APARTMENT_SUCCESS;
}

int serviceNumberOfApatments(ApartmentService service)
{
	return service->numOfApartments;
}

ApartmentServiceResult servicePriceMedian(ApartmentService service,
		int* outResult)
{
	int length = service->numOfApartments;
	int prices[length];
	for(int i=0; i<length; i++)
		prices[i] = apartmentGetPrice(service->apartments[i]);
	quickSort(prices, 0, length-1);
	if(length%2 == 0)
		*outResult = (prices[length/2]+prices[length/2+1])/2;
	else *outResult = prices[length/2+1];
	return APARTMENT_SUCCESS;
}

ApartmentServiceResult serviceAreaMedian(ApartmentService service,
        int* outResult)
{
    if(service->apartments == NULL)
        return APARTMENT_SERVICE_EMPTY;
    int length = service->numOfApartments;
    int area[length];
    for(int i=0; i<length; i++)
        area[i] = (apartmentGetLength(service->apartments[i])) * (apartmentGetWidth(service->apartments[i]));
    quickSort(area, 0, length-1);
    if(length%2 == 0)
		*outResult = (area[length/2]+area[length/2+1])/2;
	else *outResult = area[length/2+1];
    return APARTMENT_SERVICE_SUCCESS;
}

ApartmentServiceResult serviceSearch(ApartmentService service, int area,
        int rooms, int price, Apartment* outApartment)
{	// ziv's function
    int lastLocation=-1;
    if(!CHECK_POSITIVE(area, rooms, price))
        return APARTMENT_SERVICE_OUT_OF_BOUNDS;
    if(service->numOfApartments<=0)
        return APARTMENT_SERVICE_EMPTY;
    int length = service->numOfApartments;
    for(int i=0; i<length; i++)
    {

    }
}

ApartmentServiceResult serviceGetById(ApartmentService service, int id, Apartment* outApartment)
{
	if(id < 0)
		return APARTMENT_SERVICE_OUT_OF_BOUNDS;
	if(service->apartments == NULL || service->numOfApartments == 0)
		return APARTMENT_SERVICE_EMPTY;
	for(int i=0; i< service->numOfApartments; i++)
	{
		if(service->ids[i] == id)
		{
			*outApartment = apartmentCopy(service->apartments[i]);
			return APARTMENT_SERVICE_SUCCESS;
		}
	}
	return APARTMENT_SERVICE_NO_FIT;
}

ApartmentServiceResult serviceDeleteById(ApartmentService service, int id)
{	// freeing might be needed
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
	Apartment* apartments = malloc(service->maxNumOfApartments*sizeof(Apartment));
	if(apartments == NULL)
		return APARTMENT_SERVICE_OUT_OF_MEM;
	for(int i=0, j=0; i<service->numOfApartments; i++)
	{
		if(i != index)
			apartments[j++] = service->apartments[i];
	}
	service->apartments = apartments;
	return APARTMENT_SERVICE_SUCCESS;
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
	free(service->ids);
	for(int i=0; i<service->numOfApartments; i++)
	{
		apartmentDestroy(service->apartments[i]);
		free(service->apartments[i]); 	// might be unnecessary, but won't hurt
	}
	free(service);
}

void quickSort( int a[], int l, int r)
{
	int j;

	if( l < r )
	{
		j = partition( a, l, r);
		quickSort( a, l, j-1);
		quickSort( a, j+1, r);
	}

}

int partition( int a[], int l, int r) {
	int pivot, i, j, t;
	pivot = a[l];
	i = l; j = r+1;

	while( 1)
	{
		do ++i; while( a[i] <= pivot && i <= r );
		do --j; while( a[j] > pivot );
		if( i >= j ) break;
		t = a[i]; a[i] = a[j]; a[j] = t;
	}
	t = a[l]; a[l] = a[j]; a[j] = t;
	return j;
}


