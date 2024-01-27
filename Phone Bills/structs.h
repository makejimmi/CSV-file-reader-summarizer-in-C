#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#define MAXNR 24
#define MAXTIME 20
#define MAXD 30

/*!
 * \brief Struct that suspiciously looks like it might be used for a linked list (struct for cdr).
 */
struct NodeCDR {
    char caller[MAXNR];
    char called[MAXNR];
    float seconds_called;
    char date_and_time[MAXTIME];
    struct NodeCDR* next;
};

/*!
 * \brief Struct that is suited to absorb data from rates files.
 */
struct NodeRate{
    int country_code;
    char destination[MAXD];
    float ppm;
    struct NodeRate *next;
};

/*!
 * \brief A multi-tooled struct that helped the coder a lot! :D
 */
struct onlyOne{
    char caller[MAXNR];
    char called[MAXNR];
    float duration;
    char date_and_time[MAXTIME];
    int amount_of_calls;
    int alreadyprinted;
    struct onlyOne *next;
};



#endif // STRUCTS_H_INCLUDED
