/**
* @file sort.cpp
* @author Melih Altun @2015
**/
#include "sort.h"

/* Contains implementations of bubble sort, coctail shaker sort, merge sort, quick sort, comb sort, insertion sort and selection sort.
* Bubble sort is the simplest but a slow sort algorithm
* Coctail shaker is slightly more complex and faster. Both have the smallest memory usage.
* Merge sort is very fast but it also uses the most amount of memory.
* Quick sort is faster than merge sort for the average case. It doesn't handle reverse sorted lists well but it uses less memory.
* Comb sort is simple to implement, very fast and very efficient in terms of memory.
* Insertion sort is just like bubble sort. Small code space, small memory usage but inefficient for large sizes of data.
* Selection sort is simple but inefficient in all possible cases. Should be used only for experimentation.
* Heap sort is similar to Merge and Quick sort in terms of performance. It does better on reverse sorted lists compared to quicksort.

* Median Quick Select and Quick select algorithms are also implemented here.
* Although they only partially sort the series, they are based on quick sort and they share sub routines with it.*/


//Swap function - It does what it says.
void swap(double *a, double *b)
{
	double temp = *a;
	*a = *b;
	*b = temp;
}

/*bubble sort - best: O(n), avg: O(n^2), worst: (n^2), space: O(1) -> (in place)
parameters: output array, input array, # of elements, descending / ascending option */
void bSort(double out[], double in[], unsigned int length, bool descend)
{
	//for (i = 0; i < length; i++) out[i] = in[i];
	memcpy(out, in, length*sizeof(double));  // copy input
#if defined(CPP_BUILD)
	bSort(out, length, descend);  // call in place sort
#else
	bSortInPlace(out, length, descend);  // call in place sort
#endif
}

//bubble sort that sorts in place
#if defined(CPP_BUILD)
void bSort(double inOut[], unsigned int length, bool descend)
#else
void bSortInPlace(double inOut[], unsigned int length, bool descend)  //no function overloading in c :(
#endif
{
	unsigned int endIndx = length, i;
	bool sorted = false;

	if (descend) { //sort descending
		while (!sorted) {
			sorted = true;
			for (i = 1; i < endIndx; i++) {
				if (inOut[i - 1] < inOut[i]) {
					swap(&inOut[i], &inOut[i - 1]);
					sorted = false;
				}
			}
			endIndx--;
		}
	} else { //sort ascending
		while (!sorted) {
			sorted = true;
			for (i = 1; i < endIndx; i++) {
				if (inOut[i - 1] > inOut[i]) {
					swap(&inOut[i], &inOut[i - 1]);
					sorted = false;
				}
			}
			endIndx--;
		}
	}
}

/*coctail shaker sort -> slightly faster version of bubble sort
best: O(n), avg: O(n^2), worst: (n^2), space: O(1) -> (in place)
parameters: output array, input array, # of elements, descending / ascending option */
void csSort(double out[], double in[], unsigned int length, bool descend)
{
	//for (i = 0; i < length; i++) out[i] = in[i];
	memcpy(out, in, length*sizeof(double));  //copy input
#if defined(CPP_BUILD)
	csSort(out, length, descend);  // call in place sort
#else
	csSortInPlace(out, length, descend);  // call in place sort
#endif
}

//coctail shaker that sorts in place
#if defined(CPP_BUILD)
void csSort(double inOut[],  unsigned int length, bool descend)
#else
void csSortInPlace(double inOut[], unsigned int length, bool descend)
#endif
{
	unsigned int endIndx = length, i, startIndx = 1;
	bool sorted = false;
	bool goUpwards = true;

	while (!sorted) {
		sorted = true;
		if (goUpwards) {
			if (descend) {  //sort descending
				for (i = startIndx; i < endIndx; i++) {
					if (inOut[i - 1] < inOut[i]) {
						swap(&inOut[i], &inOut[i - 1]);
						sorted = false;
					}
				}
			} else { //sort ascending
				for (i = startIndx; i < endIndx; i++) {
					if (inOut[i - 1] > inOut[i]) {
						swap(&inOut[i], &inOut[i - 1]);
						sorted = false;
					}
				}
			}
			goUpwards = false;
			endIndx--;
		} else {
			if (descend) {  //sort descending
				for (i = endIndx; i >= startIndx; i--) {
					if (inOut[i - 1] < inOut[i]) {
						swap(&inOut[i], &inOut[i - 1]);
						sorted = false;
					}
				}
			} else { //sort ascending
				for (i = endIndx; i >= startIndx; i--) {
					if (inOut[i - 1] > inOut[i]) {
						swap(&inOut[i], &inOut[i - 1]);
						sorted = false;
					}
				}
			}
			goUpwards = true;
			startIndx++;
		}
		if (startIndx >= endIndx)
			break;
	}
}

//subroutine for merge sort
void mergeParts(double B[], double A[], unsigned int iLeft, unsigned int iRight, unsigned int iEnd, bool descend)
{
	unsigned int i1 = iLeft, i2 = iRight, j;
	if (descend) { //sort descending
		for (j = iLeft; j < iEnd; j++) {
			if (i1 < iRight && (i2 >= iEnd || A[i1] >= A[i2])) {
				B[j] = A[i1];
				i1++;
			} else {
				B[j] = A[i2];
				i2++;
			}
		}
	} else { //sort ascending
		for (j = iLeft; j < iEnd; j++) {
			if (i1 < iRight && (i2 >= iEnd || A[i1] <= A[i2])) {
				B[j] = A[i1];
				i1++;
			} else {
				B[j] = A[i2];
				i2++;
			}
		}
	}
}

/*merge sort - best: O(n log n), avg: O(n log n), worst: (n log n), space: O(n)
parameters: output array, input array, # of elements, descending/ascending option */
void mSort(double out[], double in[], unsigned int length, bool descend)
{
	memcpy(out, in, length*sizeof(double));  //copy input
#if defined(CPP_BUILD)
	mSort(out, length, descend);  // call in place sort
#else
	mSortInPlace(out, length, descend);  // call in place sort
#endif
}

// in place merge sort
#if defined(CPP_BUILD)
void mSort(double A[], unsigned int length, bool descend)
#else
void mSortInPlace(double A[], unsigned int length, bool descend)
#endif
{
	double *B;
#if defined(CPP_BUILD)
	B = new double[length];
#else
	B = (double*)malloc(length*sizeof(double));
#endif
	unsigned int width, runs = 0, i, iRight, iEnd;
	for (width = 1; width < length; width *= 2) {
		runs++;
		for (i = 0; i < length; i += 2 * width) {
			iRight = (i + width < length - 1) ? i + width : length - 1;
			iEnd = (i + 2 * width < length) ? i + 2 * width : length;
			if (runs % 2 == 1) //Alternate between sorting A into B and B into A. Otherwise, B needs to be copied into A at each iteration.
				mergeParts(B, A, i, iRight, iEnd, descend);
			else
				mergeParts(A, B, i, iRight, iEnd, descend);
		}
	}
	if (runs % 2 == 1) //copy B to A if array is sorted into B at the end
		memcpy(A, B, length*sizeof(double));
#if defined(CPP_BUILD)
	delete[] B;
#else
	free(B);
#endif
	B = NULL;
}

//subroutine for quicksort
unsigned int medianOfThree(double A[], unsigned int low, unsigned int high)
{
	if (high - low > 1) {
		unsigned int middle = (low + high) / 2;
		if (A[low] < A[middle]) {
			if (A[low] >= A[high])
				return low;
			else if (A[middle]<A[high])
				return middle;
		} else {
			if (A[low] < A[high])
				return low;
			else if (A[middle] >= A[high])
				return middle;
		}
	}
	return high;
}

//subroutine for quicksort
unsigned int partition(double A[], unsigned int low, unsigned int high, bool descend)
{
	unsigned int pivotIndex = medianOfThree(A, low, high), storeIndex = low, i;
	double pivotValue = A[pivotIndex];

	if (pivotIndex != high)
		swap(&A[high], &A[pivotIndex]);

	if (!descend) {
		for (i = low; i < high; i++) {
			if (A[i] < pivotValue) {
				swap(&A[i], &A[storeIndex]);
				storeIndex++;
			}
		}
	} else {
		for (i = low; i < high; i++) {
			for (i = low; i < high; i++) {
				if (A[i] > pivotValue) {
					swap(&A[i], &A[storeIndex]);
					storeIndex++;
				}
			}
		}
	}
	swap(&A[high], &A[storeIndex]);
	return storeIndex;
}

//recursive quicksort base function
void quickSort(double A[], unsigned int low, unsigned int high, bool descend)
{
	const unsigned int maxInterval = 1000;  //stop recursion when partitions are smaller than this number; should be around 30 if insertion sort is used
	if (high - low > maxInterval) {
		int pivot = partition(A, low, high, descend);
		quickSort(A, low, pivot - 1, descend);
		quickSort(A, pivot, high, descend);
	}
	else if (low < high)  //insertion sort optimization
#if defined (CPP_BUILD)
		cSort(&A[low], high - low + 1, descend);  //using comb sort with larger interval instead of insertion sort
#else
		cSortInPlace(&A[low], high - low + 1, descend);  //using comb sort with larger interval instead of insertion sort
#endif
}

/* Quick sort - best: O(n log n), avg: O(n log n), worst: (n^2), space: O(log n)
parameters: output array, input array, # of elements, descending/ascending option */
void qSort(double out[], double in[], unsigned int length, bool descend)
{
	memcpy(out, in, length*sizeof(double));  // copy input
	quickSort(out, 0, length - 1, descend);
}

// Quick sort (in place)
#if defined(CPP_BUILD)
void qSort(double inOut[], unsigned int length, bool descend)
#else
void qSortInPlace(double inOut[], unsigned int length, bool descend)
#endif
{
	quickSort(inOut, 0, length - 1, descend);
}


/* Comb sort - best: O(n), avg: O(n log n), worst: (n^2), space: O(1)
parameters: output array, input array, # of elements, descending/ascending option */
void cSort(double out[], double in[], unsigned int length, bool descend)
{
	memcpy(out, in, length*sizeof(double));  //copy input
#if defined(CPP_BUILD)
	cSort(out, length, descend);  // call in place sort
#else
	cSortInPlace(out, length, descend);  // call in place sort
#endif
}

//In place comb sort
#if defined(CPP_BUILD)
void cSort(double inOut[], unsigned int length, bool descend)
#else
void cSortInPlace(double inOut[], unsigned int length, bool descend)
#endif
{
	const double shrinkFactor = 1.3;  // 1.3 is selected empirically. http://cs.clackamas.cc.or.us/molatore/cs260Spr03/combsort.htm
	unsigned int gap = length, i1, i2;
	bool sorted = false;

	if (!descend){ //sort ascending
		while (!sorted || gap > 1) {
			sorted = true;
			if (gap > 1)
				gap = (unsigned int)((double)gap / shrinkFactor);
			for (i1 = 0, i2 = i1 + gap; i2 < length; i1++, i2++)
			{
				if (inOut[i1]>inOut[i2]) {
					swap(&inOut[i1], &inOut[i2]);
					sorted = false;
				}
			}
		}
	} else { //sort descending
		while (!sorted || gap > 1) {
			sorted = true;
			if (gap > 1)
				gap = (unsigned int)((double)gap / shrinkFactor);
			for (i1 = 0, i2 = i1 + gap; i2 < length; i1++, i2++)
			{
				if (inOut[i1]<inOut[i2]) {
					swap(&inOut[i1], &inOut[i2]);
					sorted = false;
				}
			}
		}
	}
}

/*insertion sort - best: O(n), avg: O(n^2), worst: (n^2), space: O(1) -> (in place)
parameters: output array, input array, # of elements, descending / ascending option */
void iSort(double out[], double in[], unsigned int length, bool descend)
{
	memcpy(out, in, length*sizeof(double)); //copy input
#if defined(CPP_BUILD)
	iSort(out, length, descend); // call in place sort
#else
	iSortInPlace(out, length, descend); // call in place sort
#endif
}

//insertion sort in place
#if defined(CPP_BUILD)
void iSort(double inOut[], unsigned int length, bool descend)
#else
void iSortInPlace(double inOut[], unsigned int length, bool descend)
#endif
{
	unsigned int i, j;
	if (!descend){ //sort ascending
		for (i = 1, j = i; i < length; i++, j = i) {
			while (j>0 && inOut[j - 1] > inOut[j]) {
				swap(&inOut[j], &inOut[j - 1]);
				j--;
			}
		}
	} else {
		for (i = 1, j = i; i < length; i++, j = i) {
			while (j>0 && inOut[j - 1] < inOut[j]) {
				swap(&inOut[j], &inOut[j - 1]);
				j--;
			}
		}
	}
}

/*selection sort - best: O(n^2), avg: O(n^2), worst: (n^2), space: O(1) -> (in place)
parameters: output array, input array, # of elements, descending / ascending option */
void sSort(double out[], double in[], unsigned int length, bool descend)
{
	memcpy(out, in, length*sizeof(double)); //copy input
#if defined(CPP_BUILD)
	sSort(out, length, descend); // call in place sort
#else
	sSortInPlace(out, length, descend); // call in place sort
#endif
}

//in place selection sort
#if defined(CPP_BUILD)
void sSort(double inOut[], unsigned int length, bool descend)
#else
void sSortInPlace(double inOut[], unsigned int length, bool descend)
#endif
{
	unsigned int i, j, iMin, iMax;
	if (!descend) {
		for (j = 0; j < length - 1; j++) {
			iMin = j;
			for (i = j + 1; i < length; i++) {
				if (inOut[i] < inOut[iMin]) {
					iMin = i;
				}
			}
			swap(&inOut[j], &inOut[iMin]);
		}
	} else {
		for (j = 0; j < length - 1; j++) {
			iMax = j;
			for (i = j + 1; i < length; i++) {
				if (inOut[i] > inOut[iMax]) {
					iMax = i;
				}
			}
			swap(&inOut[j], &inOut[iMax]);
		}
	}
}

//heap sort subroutine for fixing heap tree when heap property is broken
void siftDown(double A[], unsigned int startIndex, unsigned int endIndex, bool descend)
{
	unsigned int root = startIndex, child, other;
	if (!descend) {
		while (2 * root + 1 <= endIndex) {
			child = 2 * root + 1;
			other = root;
			if (A[other] < A[child])
				other = child;
			if (child + 1 <= endIndex && A[other] < A[child + 1])
				other = child + 1;
			if (other == root)
				return;
			else {
				swap(&A[root], &A[other]);
				root = other;
			}
		}
	} else {
		while (2 * root + 1 <= endIndex) {
			child = 2 * root + 1;
			other = root;
			if (A[other] > A[child])
				other = child;
			if (child + 1 <= endIndex && A[other] > A[child + 1])
				other = child + 1;
			if (other == root)
				return;
			else {
				swap(&A[root], &A[other]);
				root = other;
			}
		}
	}
}

//heap sort sub routine for building the heap
void heapify(double A[], unsigned int size, bool descend)
{
	unsigned int startIndex = (unsigned int)((size - 2) / 2), i;
	for (i = startIndex; i >= 0 && i<=startIndex; i--)
		siftDown(A, i, size - 1, descend);
}

/*heap sort - best: O(n log n), avg: O(n log n), worst: (n log n), space: O(1) -> (in place)
parameters: output array, input array, # of elements, descending / ascending option */
void hSort(double out[], double in[], unsigned int length, bool descend)
{
	memcpy(out, in, length*sizeof(double)); //copy input
#if defined(CPP_BUILD)
	hSort(out, length, descend); // call in place sort
#else
	hSortInPlace(out, length, descend); // call in place sort
#endif
}

//heap sort in place
#if defined(CPP_BUILD)
void hSort(double inOut[], unsigned int length, bool descend)
#else
void hSortInPlace(double inOut[], unsigned int length, bool descend)
#endif
{
	unsigned int i;
	heapify(inOut, length, descend);
	for (i = length - 1; i > 0; i--) {
		swap(&inOut[i], &inOut[0]);
		siftDown(inOut, 0, i-1, descend);
	}
}

// Sub-routine for quick select
double qSelect(double in[], unsigned int low, unsigned int high, unsigned int n)
{
	unsigned int pivotIndex;
	if (low == high)
		return in[low];
	pivotIndex = partition(in, low, high, false);
	if (n == pivotIndex)
		return in[n];
	else if (n < pivotIndex)
		return qSelect(in, low, pivotIndex - 1, n);
	else
		return  qSelect(in, pivotIndex + 1, high, n);
}

/*Median Quick Select - best: O(n), avg: O(n), worst: (n^2), space: O(n)
This is a selection algorithm. However, it works similar to quick sort and shares sub-routines with it.
parameters: input array, # of elements
returns: median of a series */
double medianQuickSelect(double in[], unsigned int length)
{
	double *A, result = 0;  //A[] is used as a temp array, so that in[] is not sorted in place 
	A = NULL;
	if (length == 0)
		return 0;
	else if (length == 1)
		return in[0];  //trivial cases

#if defined(CPP_BUILD)
	A = new double[length];
#else
	A = (double*)malloc(length*sizeof(double));
#endif
	memcpy(A, in, length*sizeof(double));  // copy input

	if (length % 2 == 1)
		result = qSelect(in, 0, length-1, (length - 1) / 2);
	else
		result = qSelect(in, 0, length - 1, length / 2) / 2 + qSelect(in, 0, length - 1, length / 2 - 1) /2 ;

	if (A != NULL) {
#if defined(CPP_BUILD)
		delete[] A;
#else
		free(A);
#endif
		A = NULL;
	}
	return result;
}


/*Quick Select - best: O(n), avg: O(n), worst: (n^2), space: O(n)
This is a selection algorithm. However, it works similar to quick sort and shares sub-routines with it.
parameters: input array, # of elements, n indicates n_th smallest element in the unordered list.
returns: n_th smallest element in the series */
double quickSelect(double in[], unsigned int length, unsigned int n)
{
	double *A, result = 0;  //A[] is used as a temp array, so that in[] is not sorted in place 
	A = NULL;
	if (length == 0 || n>length)
		return 0;
	else if (length == 1)
		return in[0];  //trivial cases
#if defined(CPP_BUILD)
	A = new double[length];
#else
	A = (double*)malloc(length*sizeof(double));
#endif
	memcpy(A, in, length*sizeof(double));  // copy input

	result = qSelect(A, 0, length - 1, --n);

	if (A != NULL) {
#if defined(CPP_BUILD)
		delete[] A;
#else
		free(A);
#endif
		A = NULL;
	}
	return result;
}