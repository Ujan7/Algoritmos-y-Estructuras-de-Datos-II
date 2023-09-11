/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"

/**
* @brief returns true when reach last line in flight file
* @return True when is the last line of the file, False otherwise
*/
static bool is_last_line(unsigned int hour, unsigned int type) {
  return  hour == HOURS - 1u && type == TYPE - 1u;
}

void array_dump(DelayTable a) {
  for (unsigned int type = 0u; type < TYPE; ++type) {
    for (unsigned int hour = 0u; hour < HOURS; ++hour) {
      Flight f = a[type][hour];
      fprintf(stdout, "%c: %s flight with %u passengers arrived at %u:00, with %u delay",f.code,f.type == 0 ? "last_mile" : "layover",f.passengers_amount,f.hour - 1,f.delay);
      if (!is_last_line(hour, type))
      {
        fprintf(stdout, "\n");
      }
    }
  }
}

unsigned int compensation_cost (DelayTable a)
{
    unsigned int compensationCost = 0u;
    unsigned int delay_lastMile = 0u;
    unsigned int delay_layOver = 0u;
    
    for (unsigned int hour = 0u; hour < HOURS; hour++)
    {
        if (a[last_mile][hour].hour <= 18) 
        {
            if (a[last_mile][hour].delay > MAX_LM_DELAY_ALLOWED)
            {
              delay_lastMile = delay_lastMile + (a[last_mile][hour].delay - MAX_LM_DELAY_ALLOWED) * a[last_mile][hour].passengers_amount;
            }
        }
            
        if (a[layover][hour].hour <= 18)
        {
            if (a[layover][hour].delay > MAX_LAYOVER_DELAY_ALLOWED)
            {
              delay_layOver = delay_layOver + (a[layover][hour].delay - MAX_LAYOVER_DELAY_ALLOWED) * a[layover][hour].passengers_amount;
            }
        }   
    }

    return compensationCost = (COMPENSATION_PER_MINUTE * delay_lastMile) + (COMPENSATION_PER_MINUTE * delay_layOver);
}

void array_from_file(DelayTable array, const char *filepath) 
{
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) 
  {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  int i = 0;
  while (i < HOURS && !feof(file)) 
  {
    Flight last_mile_info = flight_from_file(file);
    Flight layover_info = flight_from_file(file);
    int res = fscanf(file,"#%c#",&code);
    
    if (res != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }

    array[last_mile][i] = last_mile_info;
    array[layover][i] = layover_info;
    
    array[last_mile][i].type = last_mile;
    array[layover][i].type = layover;
    
    array[layover][i].code = code;
    array[last_mile][i].code = code;
    
    i ++;
  
  }
  
  fclose(file);
}