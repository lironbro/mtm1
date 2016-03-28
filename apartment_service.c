/*
 * apartment_service.c
 *
 *  Created on: 28 ���� 2016
 *      Author: Liron
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <apartment.c>



typedef struct apartment_service_t* ApartmentService;
typedef enum {APARTMENT_SERVICE_NULL_ARG, APARTMENT_SERVICE_OUT_OF_MEM,
		APARTMENT_SERVICE_SUCCESS, APARTMENT_SERVICE_OUT_OF_BOUNDS,
		APARTMENT_SERVICE_FULL, APARTMENT_SERVICE_ALREADY_EXISTS,
		APARTMENT_SERVICE_EMPTY, } ApartmentServiceResult;

struct apartment_service_t
{
			int numOfApartments;
			int maxNumOfApartments;
			Apartment apartments[];
			int ids[];
};

ApartmentService serviceCreate(int maxNumOfApartments);

ApartmentServiceResult serviceAddApartment(ApartmentService service,
			Apartment apartment, int id);

int serviceNumberOfApatments(ApartmentService service);

ApartmentServiceResult servicePriceMedian(ApartmentService service,
		int* outResult);



ApartmentService serviceCreate(int maxNumOfApartments)
{	// �� �� ����� ����� ������ ������ ��� �� ����� �� ��, �����
	if(maxNumOfApartments <= 0)
		return NULL;
	ApartmentService service;  // �� ��� ���� ��������
	service->maxNumOfApartments = maxNumOfApartments;
	service->numOfApartments = 0;
	service->apartments[maxNumOfApartments];
	service->ids[maxNumOfApartments];
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
		prices[i] = service->apartments[i].price;
	quickSort(prices, 0, length-1);
	if(length%2 == 0)
		*outResult = (prices[length/2]+prices[length/2+1])/2;
	else *outResult = prices[length/2+1];
	return APARTMENT_SUCCESS;
}


// �� ��� ��������� ����� ������ ���������, ���� ����� �� �� ����
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


