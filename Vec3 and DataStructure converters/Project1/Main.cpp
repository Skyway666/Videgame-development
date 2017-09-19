#include<stdio.h>
#include<iostream>
#include <assert.h>
#include "Array.h"
#include "List.h"
#include "Vec3.h"


int main()
{
	//Vec3 testing
	vec3<int> vector = vec3<int>(2, 5, 7);
	vec3<int> vector1 = vec3<int>(-1, 7, 8);

	printf("Vectors chosen: v1 (%i  %i  %i) and v2 (%i  %i  %i)  \n\n", vector.x, vector.y, vector.z, vector1.x, vector1.y, vector1.z);

	printf("Normalized v1: %f\n\n", vector.get_module());

	vector.zero();

	printf("v1 into 0: v1 (%i  %i  %i)\n\n", vector.x, vector.y, vector.z);
    
	if (vector.is_zero())
	{
		printf("v1 = 0 ?: Yes\n\n");
	}
	else
	{
		printf("v1 = 0 ?: No\n\n");
	}

	printf("Distance from v1 to v2: %f\n\n", vector.distance_to(vector1));

	vector = vector1;

	printf("v1 = v2: v1 (%i  %i  %i)\n\n", vector.x, vector.y, vector.z);

	if (vector == vector1)
	{
		printf("v1 = v2?: Yes\n\n");
	}
	else
	{
		printf("v1 = v2?: No\n\n");
	}

	vec3<int> newvector = vector + vector1;

	printf("newvector = v1+v2: newvector (%i  %i  %i)\n\n", newvector.x, newvector.y, newvector.z);

	vector += newvector;

	printf("v1 + newvector= v1(%i  %i  %i)\n\n", vector.x, vector.y, vector.z);

	vector1 -= newvector;

	printf("v2 - newvector= v2(%i  %i  %i)\n\n", vector1.x, vector1.y, vector1.z);



	//List into DynArray

	List<int> list;

	list.pushFront(1);
	list.pushFront(2);
	list.pushFront(3);
	list.pushFront(4);
	list.pushFront(5);

	list.print();

	DynArray<int> dynarray = list.dyn_array_converter();

	dynarray.print();

	return 0;
}