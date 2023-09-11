#ifndef WEATHER_UTILS
#define weather_utils
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"
#include "weather.h"

int min_tempR(WeatherTable a);
void max_temp_per_year(WeatherTable a, int output[YEARS]);
void month_max_prec_per_year(WeatherTable a, int output[YEARS]);
#endif
