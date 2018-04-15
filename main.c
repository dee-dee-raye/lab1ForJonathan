//
//  main.c
//  lab1
//
//

#include <stdio.h>
#include <stdbool.h>
#include "omp.h"

int Find_bin(float data, float bin_maxes[], int bin_count, int min_meas);
void quickSort(float arr[], float low, float high);
float getMaxForBinNum(int b, float arr[], int count);

int main(int argc, const char * argv[]) {
    
    const int data_count = 20;
    float data[]  = {1.3,2.9,0.4,0.3,1.3,4.4,1.7,0.4,3.2,0.3,4.9,2.4,3.1,4.4,3.9,0.4,4.2,4.5,4.9,0.9};
    
    int min_meas = 1;
    int max_meas = 5;
    const int bin_count = 5;
    float bin_maxes[] = {1,2,3,4,5};
    int bin_counts[] = {0,0,0,0,0};
    
    //sort my data
    quickSort(data, 0, 19);
    
    //get the wideth of each bin
    float bin_width = data_count / bin_count;
    
    for(int b = 0; b<bin_count; b++)
    {
        //get the max value found in each bin
        bin_maxes[b] = getMaxForBinNum(b, data, data_count);
    }
    
 
    int bin = 0;
    #pragma omp parallel for reduction(+:bin_counts)
    for(int i = 0; i<data_count; i++)
    {
        //figure out what bin the data would be in
        bin = Find_bin(data[i], bin_maxes, bin_count, min_meas);
        //increment bin count accordingly
        bin_counts[bin]++;
    }
    
    //print out of results
    for(int y = 0; y < bin_count; y++)
    {
        printf("%f\n",bin_maxes[y]);
        printf("%i\n",bin_counts[y]);
    }
    
    
    return 0;
}


//used by quicksort
float partition (float arr[], int low, int high)
{

    float pivot = arr[high];
    
    int i = (low - 1);
    
    for (int j = low; j <= high- 1; j++)
    {
        
        if (arr[j] <= pivot)
        {
            i++;
            float temp = arr[i];
            arr[i] = arr[j];
            arr[j]=temp;
        }
    }
    float temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high]=temp;
    return (i + 1);
}

void quickSort(float arr[], float low, float high)
{
    
    if (low < high)
    {
         float pi = partition(arr, low, high);
        
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

//this finds what bin the data would be in
int Find_bin(float data, float bin_maxes[], int bin_count, int min_meas)
{
    bool notFound = true;
    int spot = 0;
    for (int x =0; x <bin_count && notFound; x++)
    {
        if(x == 0)
        {
            if(data <= bin_maxes[x])
            {
                spot = x;
                notFound=false;
            }
        }
        else
        {
            if(data >= bin_maxes[x-1] && data <= bin_maxes[x])
            {
                notFound = false;
                spot = x;
            }
            
        }
    }
    
    return spot;
}

//this gets the max for each bin
float getMaxForBinNum(int b, float arr[], int count)
{
    
    //                |     |     |     |     |     |
    //                |     |     |     |     |     |
    //                |     |     |     |     |     |
    //                -------------------------------
    //bins look like: 0     1     2     3     4     5
    
    float max = 0.0;
    int lastTemp =0;
    bool notDone = true;
    //switch for which bin we're looking at
    switch (b) {
        case 0:
            for(int x =0; x<count && notDone; x++)
            {
                lastTemp = x-1;
                if(arr[x] > 1)
                {
                    notDone = false;
                }
            }
            max = arr[lastTemp];
            break;
        case 1:
            for(int x =0; x<count && notDone; x++)
            {
                lastTemp = x-1;
                if(arr[x] > 2)
                {
                    notDone = false;
                }
            }
            max = arr[lastTemp];
            break;
        case 2:
            for(int x =0; x<count && notDone; x++)
            {
                lastTemp = x-1;
                if(arr[x] > 3)
                {
                    notDone = false;
                }
            }
            max = arr[lastTemp];
            break;
        case 3:
            for(int x =0; x<count && notDone; x++)
            {
                lastTemp = x-1;
                if(arr[x] > 4)
                {
                    notDone = false;
                }
            }
            max = arr[lastTemp];
            break;
        case 4:
            for(int x =0; x<count && notDone; x++)
            {
                lastTemp = x-1;
                if(arr[x] > 5)
                {
                    notDone = false;
                }
            }
            max = arr[lastTemp];
            break;
        default:
            break;
    }
    return max;
}

