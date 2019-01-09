//
//  linear.cpp
//  Homework 3
//
//  Created by Anthony on 2/10/17.
//  Copyright © 2017 CS32. All rights reserved.
//

//bool somePredicate(int x){
//    return x >= 0; // include zero for testing purposes
//}

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const double a[], int n)
{
    // If any of the parameters n, n1, or n2 is negative, act as if it were zero.
    if (n < 0){
        return true;
    } else if (n == 0){
        return true;
    }
    
    if (somePredicate(a[0]) == false){
        return false;
    }
    
    if (n <= 1){
        return true;
    }
    
    return allTrue(a + 1, n - 1);

//    int mid = (n - 1) / 2;
//    if (mid == 0){
//        if (somePredicate(a[mid]) == false){
//            return false;
//        }
//        return true;
//    } else {
//        return allTrue(a, mid);
//    }
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const double a[], int n)
{
    // If any of the parameters n, n1, or n2 is negative, act as if it were zero.
    if (n < 0){
        return 0;
    } else if (n == 0){
        return 0;
    }
    
    int i = 0;
    
    if (somePredicate(a[0]) == false){ // mark it
        return 1 + countFalse(a + 1, n - 1);
    } else {
    	return countFalse(a + 1, n - 1);
    }
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const double a[], int n)
{
    if (n < 0){
        return -1;
    } else if (n == 0){
        return -1;
    }
    
    if (somePredicate(a[0]) == false){ // mark
        return 0;
    }
    
    if (firstFalse(a + 1, n - 1) == -1) { // mark it wrong
        return -1;
    } else {
        return 1 + firstFalse(a + 1, n - 1);
    }
}

// Return the subscript of the smallest double in the array (i.e.,
// the one whose value is <= the value of all elements).  If more
// than one element has the same smallest value, return the smallest
// subscript of such an element.  If the array has no elements to
// examine, return -1.
int indexOfMin(const double a[], int n)
{
    if (n < 0){
        return -1;
    } else if (n == 0){
        return -1;
    } else if (n == 1){
        return 0;
    }
    
    int min;
    
//    if (indexOfMin(a + 1, n - 1) == -1){
//        min = -1;
//    } else {
//        min = 1 + indexOfMin(a + 1, n - 1);
//    }
    if (indexOfMin(a, n - 1) == -1){
        return -1;
    }
    if (a[n - 1] < a[indexOfMin(a, n - 1)]){
        return n - 1;
    } else {
        return indexOfMin(a, n - 1);
    //    return min;
    }
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2){
    if (n1 < 0 || n2 < 0){ // if either array's number that we are expected is below zero, a2 is not found in a1
        return false;
    } else if (n1 == 0 && n2 == 0){ // if a1 and a2 run out at the same time, they are equal
        return true;
    } else if (n1 == 0 && n2 != 0){
        return false;
    } else if (n1 != 0 && n2 == 0){
        return true;
    }
	
    if (a1[0] == a2[0]){ // if a1 and a2 match
        return includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1); // increment both of them
    } else {
        return includes(a1 + 1, n1 - 1, a2, n2); // increment only a1
    }
}
