#ifndef CREATECSV_H_INCLUDED
#define CREATECSV_H_INCLUDED


#define MAXNR 24

FILE *createcsv(struct NodeCDR *head_of_cdr, struct onlyOne *headO, char name[MAXNR]){
    struct NodeCDR *currentcdr = head_of_cdr;
    struct onlyOne *currentO = headO;
    struct onlyOne *tempOo = NULL;
    struct NodeCDR *tempCDR = NULL;
    int intmonth; char *month;

    float overallminutes;
    float hours;

    char name1[MAXNR];
    strcpy(name1, name);
    strcat(name1, ".csv");

    FILE *fp = NULL;
    fp = fopen(name1, "w");

    while(currentO != NULL || currentcdr != NULL){

        if(currentO->amount_of_calls > 1){
            overallminutes = currentcdr->seconds_called/60.0;
            hours = 0;
            while(overallminutes > 60.0){
                overallminutes -= 60.0;;
                hours++;}

            month = strtok(currentcdr->date_and_time, "-");
            month = strtok(NULL, "-");

            intmonth = atoi(month);

            switch(intmonth){
                case 1: month = "January"; break;
                case 2: month = "February"; break;
                case 3: month = "March"; break;
                case 4: month = "April"; break;
                case 5: month = "May"; break;
                case 6: month = "June"; break;
                case 7: month = "July"; break;
                case 8: month = "August"; break;
                case 9: month = "September"; break;
                case 10: month = "October"; break;
                case 11: month = "November"; break;
                case 12: month = "December"; break;
            }
            strcpy(currentO->month, month);
            fprintf(fp, "\nSubscriber %s\nCalls: %d\nInvoice for %s - Duration: %02.0f:%02.0f:%02.0f\n",currentO->caller, currentO->amount_of_calls, currentO->month, hours, overallminutes, fmod(currentcdr->seconds_called, 60));
            tempOo = currentO->next; tempCDR = currentcdr;

            while(tempOo != NULL){

                if(strcmp(currentO->caller, tempOo->caller) == 0){
                    tempOo->amount_of_calls = 0;
                    overallminutes = tempCDR->seconds_called/60.0;
                    hours = 0;
                    while(overallminutes > 60.0){
                        overallminutes -= 60.0;;
                        hours++;}
                    month = strtok(tempOo->date_and_time, "-");
                    month = strtok(NULL, "-");

                    intmonth = atoi(month);

                    switch(intmonth){
                        case 1: month = "January"; break;
                        case 2: month = "February"; break;
                        case 3: month = "March"; break;
                        case 4: month = "April"; break;
                        case 5: month = "May"; break;
                        case 6: month = "June"; break;
                        case 7: month = "July"; break;
                        case 8: month = "August"; break;
                        case 9: month = "September"; break;
                        case 10: month = "October"; break;
                        case 11: month = "November"; break;
                        case 12: month = "December"; break;
                    }
                    strcpy(currentO->month, month);
                    fprintf(fp, "Invoice for %s - Duration: %02.0f:%02.0f:%02.0f\n",tempOo->month, hours, overallminutes, fmod(tempCDR->seconds_called, 60));
                }
                tempCDR = tempCDR->next;
                tempOo = tempOo->next;
            }
        } else if (currentO->amount_of_calls == 1){
            overallminutes = currentcdr->seconds_called/60.0;
            hours = 0;
            while(overallminutes > 60.0){
                overallminutes -= 60.0;;
                hours++;
            }
            month = strtok(currentcdr->date_and_time, "-");
            month = strtok(NULL, "-");

            intmonth = atoi(month);

            switch(intmonth){
                case 1: month = "January"; break;
                case 2: month = "February"; break;
                case 3: month = "March"; break;
                case 4: month = "April"; break;
                case 5: month = "May"; break;
                case 6: month = "June"; break;
                case 7: month = "July"; break;
                case 8: month = "August"; break;
                case 9: month = "September"; break;
                case 10: month = "October"; break;
                case 11: month = "November"; break;
                case 12: month = "December"; break;
            }
            strcpy(currentO->month, month);
            fprintf(fp, "\nSubscriber %s\nCalls: %d\nInvoice for %s - Duration: %02.0f:%02.0f:%02.0f\n",currentO->caller, currentO->amount_of_calls, currentO->month, hours, overallminutes, fmod(currentcdr->seconds_called, 60));
        }
        currentcdr = currentcdr->next;
        currentO = currentO->next;
    }

    return fp;
}


#endif // CREATECSV_H_INCLUDED
