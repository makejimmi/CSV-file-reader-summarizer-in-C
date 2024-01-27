#ifndef CDR_READER_H_INCLUDED
#define CDR_READER_H_INCLUDED

#include "structs.h"

#define MAXARR 255
#define MAXNR 24
#define MAXTIME 20
#define MAXD 30
/*!
 * The header file: "readers_and_createnodes" does as the name already states... it reads and creates nodes (csv files!).
 */

/*!
 * \brief This function takes in a total of four arguments to create a node for the cdr-file in the "NODECDR"-struct. Returns the new node.
 */
struct NodeCDR *create_node(char nr1[MAXNR], char nr2[MAXNR], float callTime, char when[MAXTIME]) {
    struct NodeCDR* new_node = (struct NodeCDR *)malloc(sizeof(struct NodeCDR));
    strcpy(new_node->caller, nr1);
    strcpy(new_node->called, nr2);
    new_node->seconds_called = callTime;
    when[MAXTIME] = '\0';
    strcpy(new_node->date_and_time, when);
    new_node->next = NULL;
    return new_node;
}


/*!
 * \brief This particular function creates, just like its predecessor, a node for the rates (in the NodeRate struct) and takes in three arguments. Return: link to the new struct.
 */
struct NodeRate *create_ratenode(int ccode, char destin[MAXD], float price){
    struct NodeRate *new_ratenode = (struct NodeRate *)malloc(sizeof(struct NodeRate));
    new_ratenode->country_code = ccode;
    strcpy(new_ratenode->destination, destin);
    new_ratenode->ppm = price;
    new_ratenode->next = NULL;
    return new_ratenode;
}

/*!
 * \brief The "longest_matching_string" function takes a number, the duration of a call and the HEAD(!) of NodeRate to return the matching country code for the given number.
 *
 */
float longest_matching_substring(char nr[MAXNR], float call_duration, struct NodeRate *head){
    struct NodeRate *current = head;
    int countrycode;
    char *countrycodeArr = calloc(15, sizeof(char));
    int length;
    int current_match = 0, highest_match = 0;
    float matching_rate_price;

    while(current != NULL){

        //gets the length of the currently looked at node's country code
        countrycode = current->country_code;
        sprintf(countrycodeArr, "%d", countrycode);
        length = strlen(countrycodeArr);

        char digits[length];
        strncpy(digits, nr, length);
        digits[length] = '\0';

        if(strncmp(nr, countrycodeArr, length) == 0){
            current_match = length;
        }
        if(current_match > highest_match){
            highest_match = current_match;
            matching_rate_price = current->ppm;
        }
        current = current->next;
    }
    free(countrycodeArr);
    return matching_rate_price;
}


/*!
 * \brief Having the return value of "head", the "rates_read"-function takes the rates file as argument and returns the head of the newly constructed linked list.
 */
struct NodeRate *rates_read(FILE *rates){

    char arr[MAXARR]; char *token;

//read rates into a linked list
    struct NodeRate *current = NULL;
    struct NodeRate *head = NULL;
    struct NodeRate *temp = NULL;
    int countrycode; char destin[MAXD]; float priceperm;

    while(fgets(arr, MAXARR, rates) != NULL){

        token = strtok(arr,",");
        countrycode = atoi(token);

        token = strtok(NULL,",");
        strcpy(destin, token);

        token = strtok(NULL,",");
        priceperm = strtof(token, NULL);

        if(head == NULL){
            current = create_ratenode(countrycode, destin, priceperm);
            head = current;
        } else {
            temp = create_ratenode(countrycode, destin, priceperm);
            current->next = temp;
            current = current->next;
        }
    }
    return head;
}


/*!
 * \brief Similar to "read_rates", this function returns the head of a new linked list that contains data of the read cdr file.
 */
struct NodeCDR *cdr_read(FILE *csv){

    char arr[MAXARR]; char *token;

    struct NodeCDR *current = NULL;
    struct NodeCDR *head = NULL;
    struct NodeCDR *temp = NULL;

    char phoner[MAXNR], pickupper[MAXNR], time_and_date[MAXTIME];
    float seconds_Called;

    while(fgets(arr, MAXARR, csv) != NULL){

        token = strtok(arr,",");
        strcpy(phoner, token);

        token = strtok(NULL,",");
        strcpy(pickupper, token);

        token = strtok(NULL,",");
        seconds_Called = strtof(token, NULL);

        token = strtok(NULL,"\n");
        strcpy(time_and_date, token);


        if(head == NULL){
            current = create_node(phoner, pickupper, seconds_Called, time_and_date);
            head = current;
        } else {
            temp = create_node(phoner, pickupper, seconds_Called, time_and_date); //gives char * phoner (the address)
            current->next = temp;
            current = current->next;
        }
    }
    return head;
}

#endif // CDR_READER_H_INCLUDED
