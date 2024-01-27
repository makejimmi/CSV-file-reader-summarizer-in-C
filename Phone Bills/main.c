#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "readers_and_createnodes.h"
#include "structs.h"
#include "summarybasedoncalls.h"
#include "summarybasedonmonths.h"

#define MAXARR 255

/*!
 * \file main.c
 *
 *
 * \author Jimmi Bacher
 * \date 11.01.2023
 *
 * This file contains the first, second, third and fourth task of project "Phone Billing System".
 * This whole project has been written in the IDE of Codeblocks on Windows!
 */


int main()
{
    char arr[MAXARR];
    printf("Which cdr-file do you want me to read and summarize for you? (without .csv added): ");
    scanf("%s", arr);
    strcat(arr, ".csv");
    FILE *numbers = fopen(arr, "r");
    if(numbers == NULL){
        perror("Error: ");
        return 1;
    }

    printf("Now give me a rates-file: ");
    scanf("%s", arr);
    strcat(arr, ".csv");
    FILE *ratesplan = fopen(arr, "r");
    if(ratesplan == NULL){
        perror("Error: ");
        return 1;
    }

    //TASK 1 ----------------------------------------------------------------
    struct NodeCDR *head_of_cdr = cdr_read(numbers);
    struct NodeCDR *currentcdr = head_of_cdr;
    int totCount = 0;
    float overallminutes;
    float hours = 0.0;
    float seconds;

    while(currentcdr!= NULL){
        totCount++;
        seconds += currentcdr->seconds_called;
        currentcdr = currentcdr->next;
    }
    overallminutes = seconds/60;
    while(overallminutes > 60.0){
        overallminutes -= 60.0;;
        hours++;
    }
    printf("\nSum of all Calls: %d\nMinutes overall: %02.0f:%02.0f:%02.0f\nTotal Price: %.2f EUR\n\n", totCount ,hours, overallminutes, fmod(seconds, 60), overallminutes*0.05);

    printf("\n\n");
    //TASK 2 ----------------------------------------------------------------
    struct NodeRate *head_of_rates = rates_read(ratesplan);
    currentcdr = head_of_cdr;
    float matching_rate;
    while(currentcdr != NULL){
        matching_rate = longest_matching_substring(currentcdr->caller, currentcdr->seconds_called, head_of_rates);
        printf("Subscriber: %s needs to pay %.2f EUR\n", currentcdr->caller, matching_rate*currentcdr->seconds_called);
        currentcdr = currentcdr->next;
    }

    printf("\n\n");
    //TASK 3 ----------------------------------------------------------------
    struct onlyOne *headO = create_summarybasedoncalls_struct(head_of_cdr);
    struct onlyOne *currentO = headO;
    currentcdr = head_of_cdr;
    while(currentO != NULL){
        if(currentO->alreadyprinted == 0){
            printf("Subscriber: %s called %s\nCalls: %d; Duration: %.0f; Date/Time: %s\n\n", currentO->caller, currentcdr->called,currentO->amount_of_calls, currentcdr->seconds_called, currentcdr->date_and_time);
        }
        currentO = currentO->next;
        currentcdr = currentcdr->next;
    }

    printf("\n\n");
    //TASK 4 ----------------------------------------------------------------
    FILE *fp = NULL;
    fp = summarymonths(head_of_cdr, headO, fp);
    if(fp == NULL){
        perror("Error: ");
        return 1;
    }
    printf("--------------------------------------- ");
    printf("Check out the .txt-file that has been created for you!");
    printf("\n\n");

    fclose(numbers);
    fclose(ratesplan);

    return 0;
}
