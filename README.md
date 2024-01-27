# Phone Billing Summarizer

## Project Overview
This project involves a C program that reads, processes, and summarizes phone billing data from CSV files. It is specifically designed to handle phone billing records, calculating costs based on call duration and destination. The program efficiently manages data using a custom implementation of linked lists.

## Key Features

- **CSV File Reading**: Capable of reading two types of CSV files:
  - **Billing Data**: Contains detailed records of phone calls, including caller, callee, call duration, and date/time.
  - **Rate Information**: Lists the calling rates for various countries, categorized by the starting digits of the phone number.

- **Linked List Data Structure**: Implemented a linked list from scratch to manage and process data dynamically.

- **Cost Calculation**: Determines the cost of calls by matching the country rates with the caller's number prefix.

- **Summarization**: Provides a summary of total costs and other relevant aggregated data from the billing records.

## Technical Details

- **Language**: The program is written in C, utilizing standard libraries for file handling and data processing.

- **Data Structures**:
  - Custom linked lists are used for efficient data storage and manipulation.
  - Structs are employed to represent individual records and rate information.

- **Algorithm**:
  - Parses CSV files to extract relevant data.
  - Uses linked lists to store and iterate over records and rates.
  - Matches call destinations with rates using the prefix of the caller number.
  - Calculates the total cost for each call and aggregates the data for summarization.

## Usage

1. **Prepare CSV Files**:
   - Ensure the phone billing CSV file contains columns for caller, callee, duration, and date/time.
   - Prepare a separate CSV file with rate information, including country prefixes and corresponding rates.

2. **Run the Program**: Execute the program with the paths to the billing and rate CSV files as inputs.

3. **View Summary**: The program outputs a summarized report of the total costs and other relevant statistics.

## Future Enhancements

- **User Interface**: Develop a user-friendly interface for easier interaction and file management.
- **Extended Compatibility**: Enhance the program to support different CSV formats and additional billing details.
- **Performance Optimization**: Implement advanced data structures and algorithms for handling large datasets more efficiently.
