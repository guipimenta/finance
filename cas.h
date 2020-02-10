#ifndef __CAS__
#define __CAS__

#define MAX_PATH_SIZE 500
#define MAX_FILE_LINES 10000

typedef struct AMORTIZATION_CALC_INPUT {
    int period;
    double rate;
    double notional;
    int export_to_csv;
    char csv_file[MAX_PATH_SIZE];
} AMORT_CALC_INPUT;



typedef struct AMORTIZATION_TABLE_OUTPUT {
    int month;
    double principal_amort;
    double interest;
    double month_payment;
    double principal_left;
} AMORT_TABLE_OUTPUT;

typedef struct AMORTIZATION_CALC_OUTPUT {
    int n_lines;
    AMORT_TABLE_OUTPUT table[MAX_FILE_LINES];
} AMORT_CALC_OUTPUT;

void print_input(AMORT_CALC_INPUT input);

AMORT_CALC_OUTPUT create_payment_table(AMORT_CALC_INPUT input);

void export_to_csv(AMORT_CALC_INPUT input, AMORT_CALC_OUTPUT output);

AMORT_CALC_INPUT process_inputs(int argc, char** argv);

#endif