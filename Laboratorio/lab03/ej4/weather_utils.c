#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"
#include "weather.h"
#include "weather_utils.h"

int min_tempR(WeatherTable a) 
{
    int min_temp = a[0][0][0]._min_temp;

    for (unsigned int year = 0; year < YEARS; year++) 
    {
        for (unsigned int month = 0; month < MONTHS; month++) 
        {
            for (unsigned int day = 1; day < DAYS; day++) 
            {
                if (min_temp > a[year][month][day]._min_temp) 
                {
                    min_temp = a[year][month][day]._min_temp;
                                  
                }
            }
        } 
    }  

    return min_temp;
}

void max_temp_per_year (WeatherTable array, int maxTempArray[YEARS])
{
    int max_temp_of_that_year;
    for (unsigned int year = 0; year < YEARS; year++)
    {
        max_temp_of_that_year = array[year][0][0]._max_temp;
        for (unsigned int month = 0; month < MONTHS; month++)
        {
            for (unsigned int day = 0; day < DAYS; day++)
            {
                if (max_temp_of_that_year < array[year][month][day]._max_temp)
                {
                    max_temp_of_that_year = array[year][month][day]._max_temp;
                }
            }
        }

        maxTempArray[year] = max_temp_of_that_year;
    }  
}

void month_max_prec_per_year(WeatherTable a, int output[YEARS])
{
    unsigned int max_prec_month;
    unsigned int actual_prec;
    for (unsigned int year = 0; year < YEARS; year++)
    {
        max_prec_month = 0;
        for (int month = 0; month < MONTHS; month++)
        {
            actual_prec = 0;
            for (unsigned int day = 0; day < DAYS; day++)
            {
                actual_prec = actual_prec + a[year][month][day]._rainfall;
        
            }
            if (actual_prec > max_prec_month)
            {
                max_prec_month = actual_prec;
                output[year] = month;
            }

        }
    }
}
