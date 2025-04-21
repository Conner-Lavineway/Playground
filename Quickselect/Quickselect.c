/**
 * Things that make a quick select algorithim:
 * Quicksort to find data
 * only sorts where value would be
 */

#include <stdlib.h>
#include <stdio.h>



#define MAX_INPUT 10
#define MAX_LENGTH 10
#define MAX_NUM 1000
#define MIN_NUM 1


int quickSelect(int val, int arr[], int low, int high);
void swap(int* a, int* b);
void printArray(int arr[], int start, int end);

//calls everything else
void main()
{
    srand(time(NULL));

    int numList[MAX_LENGTH];

    for(int i = 0; i < MAX_LENGTH; i++)
    {
        numList[i] = rand() % MAX_NUM + MIN_NUM;
    }

    printf("A list of 500 random integers from 1 to 1000 has been made\n");
    printf("Now give me a number if it is in the list I will tell you where it is\n");

    char input[MAX_INPUT];
    int val;
    int validInput = -1;

    while(validInput == -1)
    {
        if(fgets(input, MAX_INPUT, stdin) != NULL)
        {
            char* end;
    
            val = strtol(input, &end, 10);
    
            if(!isspace(*end) && end != 0)
                printf("Not a valid input\n");
            else
                validInput = 1;

            if(validInput == 1 && val > MAX_NUM)
                printf("Your number isn't in the list but I'll check anyways\n");
        }
    }
    int pos = quickSelect(val, numList, 0, MAX_LENGTH-1);
    printf("Your value is located at %d\n", pos);
    printArray(numList, 0, MAX_LENGTH);

}


void printArray(int arr[], int start, int end)
{
    for(int i = start; i < end; i++)
        printf("%d, ", arr[i]);
        printf("\n");
}
/**
 * We need to first partition the array around a chosen pivot, this will be 
 * pos max (the last element of the array). Then we need to check if our value is not
 * our current pivot.
 * 
 * Then we repeat with whichever side our value would be on.
 */


 //TODO: Figure out how to return -1 if not in list
int quickSelect(int val, int arr[], int low, int high)
{
    if(arr[low] == val)
    {
        printArray(arr, low, high);  
        return low;
    }

    int pivot = arr[high];

    int p = low;

    for(int i = low; i < high; i++)
    {
        if(arr[i] < pivot)
        {
            if(i == p)
            {
                p++;
                break;
            }
            swap(&arr[i], &arr[p]);
            printArray(arr, low, high);
            p++;
        }
    }
    
    printArray(arr, low, high);
    swap(&arr[p], &arr[high]);
    printArray(arr, low, high);
    
    if(arr[p] == val)
        return p;
    else if(arr[p] > val)
        return quickSelect(val, arr, low, p-1);
    else
        return quickSelect(val, arr, p+1, high);

}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}