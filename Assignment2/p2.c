/*
* In this problem you are given the values of t market index through time. Compute:
*   - First day with max value. Print both day and max
*   - First day with min value. Print both day and min
*   - Average value overall
*   - Number of days with higher than average value
*
* Input:
*   - N, the number of days which we are getting values
*   - N values for a given day, starting with day 1
*
* Output:
*   - First line of output print the day with maximum value and max, separated with a space
*   - Second line, pint the day with min value and min value, separate with space
*   - Third line, print the average value to 2 decimal places
*   - Fouth line print the number of days with a value higher than average
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(){

    int numDays, index, dayMin, dayMax, daysGreaterThanAverage;
    float min = INT_MAX, max = INT_MIN, totalValue, average;
    float *values;

    scanf("%d", &numDays);
    values = (float *) malloc(sizeof(float) * numDays);
    totalValue = 0;

    for(index = 0; index < numDays; index++){
        scanf("%f", &values[index]);

        totalValue += values[index];

        if(values[index] < min){
            min = values[index];
            dayMin = index+1;
        }

        if(values[index] > max){
            max = values[index];
            dayMax = index+1;
        }
    }

    average = totalValue / numDays;
    daysGreaterThanAverage = 0;
    for(index = 0; index < numDays; index++){
        if(values[index] > average) daysGreaterThanAverage++;
    }

    printf("%d %.2f\n", dayMax, max);
    printf("%d %.2f\n", dayMin, min);
    printf("%0.2f\n", average);
    printf("%d\n", daysGreaterThanAverage);

    free(values);
    return 0;
}
