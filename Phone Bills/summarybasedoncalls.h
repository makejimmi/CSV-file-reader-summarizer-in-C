#ifndef SUMMARYBASEDONCALLS_H_INCLUDED
#define SUMMARYBASEDONCALLS_H_INCLUDED

#include "structs.h"

#define MAXNR 24
#define MAXTIME 20

/*!
 * \brief Function to create a node for the "onlyOne"-struct, returning the link of the newly created node. (The function that goes hand in hand with the coder's favourite struct of this project.)
 */
struct onlyOne *create_new_multiples_node(char caller[MAXNR], char called[MAXNR], float duration,int amount_of_calls, int alreadyprinteds, char date_and_time[MAXTIME]){
    struct onlyOne *new_node = malloc(sizeof(struct onlyOne));
    strcpy(new_node->caller, caller);
    strcpy(new_node->called, called);
    new_node->duration = duration;
    new_node->amount_of_calls = amount_of_calls;
    new_node->alreadyprinted = alreadyprinteds;
    strcpy(new_node->date_and_time, date_and_time);
    new_node->next = NULL;
    return new_node;
}

/*!
 * \brief Function that is used in conjunction with the new nodes function for struct "onlyOne", returning the head of a linked list.
 */
struct onlyOne *create_summarybasedoncalls_struct(struct NodeCDR *head){

    struct NodeCDR *currentcdr = head;
    struct NodeCDR *currentcdr1 = head;

    struct onlyOne *occured = NULL;
    struct onlyOne *occured1 = NULL;
    struct onlyOne *headO = NULL;
    struct onlyOne *currentO = NULL;
    struct onlyOne *new_node = NULL;

    int amount_of_calls = 1;
    int alreadyprinted = 0;

    while(currentcdr != NULL){
        while(currentcdr1 != NULL){
            if(strcmp(currentcdr->caller, currentcdr1->caller) == 0){
                if(currentcdr != head){
                    amount_of_calls++;
                }
            }
            currentcdr1 = currentcdr1->next;
        }

        if(headO == NULL){
            headO = create_new_multiples_node(currentcdr->caller, currentcdr->called,currentcdr->seconds_called, amount_of_calls, alreadyprinted, currentcdr->date_and_time);
            currentO = headO;
        } else {
            new_node = create_new_multiples_node(currentcdr->caller, currentcdr->called,currentcdr->seconds_called, amount_of_calls, alreadyprinted, currentcdr->date_and_time);
            currentO->next = new_node;
            currentO = currentO->next;
        }

        amount_of_calls = 0;

        currentcdr1 = head;
        currentcdr = currentcdr->next;
    }

    occured = headO;
    currentcdr = head;
    currentcdr1 = head;
    while(occured != NULL){//goes through the linked list of multiplesCDR
        occured1 = occured;
        if(occured1->next != NULL){//checks if the end of the linked list has been reached
            occured1 = occured1->next;
        } else {break;}
        while(occured1 != NULL){
            if(strcmp(occured1->caller, currentcdr->caller) == 0){
                occured1->alreadyprinted = 1;
            }
            occured1 = occured1->next;
        }
        occured = occured->next;
        occured1 = headO;
        currentcdr = currentcdr->next;
    }

    return headO;
}

#endif // SUMMARYBASEDONCALLS_H_INCLUDED
