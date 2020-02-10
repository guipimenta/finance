#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include "cas.h"

void print_input(AMORT_CALC_INPUT input) {
    printf("Input parameters ç\n");
    printf("==================\n");
    printf("  period:      %d\n", input.period);
    printf("    rate:      %f\n", input.rate);
    printf("notional:      %f\n", input.notional);
    printf("\n\n");
}

AMORT_CALC_OUTPUT create_payment_table(AMORT_CALC_INPUT input) {
    double principal_payments = input.notional / input.period;
    double exp = 1.0 / 12.0;
    double base = 1.0 + input.rate;
    double rate_per_month = pow(base, exp) - 1.0;
    double remaning_debt = input.notional;
    AMORT_CALC_OUTPUT calc_ouput;
    calc_ouput.n_lines = input.period;
    for(int i = 0; i < input.period; i++) {
        double interest = rate_per_month * remaning_debt;
        remaning_debt -= principal_payments;
        AMORT_TABLE_OUTPUT table_output;
        table_output.month = i;
        table_output.principal_amort = principal_payments;
        table_output.interest = interest;
        table_output.month_payment = interest + principal_payments;
        table_output.principal_left = remaning_debt;
        calc_ouput.table[i] = table_output;
    }
    return calc_ouput;
}

void export_to_csv(AMORT_CALC_INPUT input, AMORT_CALC_OUTPUT output) {
    FILE *f = fopen(input.csv_file, "w");
    if(f == NULL) {
        fprintf(stderr, "Can't open input file in.list!\n");
        exit(1);
    }
    printf("Exporting to csv file: %s", input.csv_file);
    fprintf(f, "month,payment,interest,total_payment,remaning_debth\n");
    for(int i = 0; i < input.period; i++) {
        AMORT_TABLE_OUTPUT table_output = output.table[i];
        fprintf(f, "%d,%f,%f,%f,%f\n", i+1, table_output.principal_amort, table_output.interest, table_output.interest + table_output.principal_amort, table_output.principal_left);
    }
    fclose(f);
}

AMORT_CALC_INPUT process_inputs(int argc, char** argv) {
    int period;
    double rate;
    double notional;
    sscanf(argv[1], "%d", &period);
    sscanf(argv[2], "%lf", &rate);
    sscanf(argv[3], "%lf", &notional);
    

    AMORT_CALC_INPUT input;
    input.period = period;
    input.rate = rate;
    input.notional = notional;

    if(argc == 5) {
        sscanf(argv[4], "%s", input.csv_file);
        input.export_to_csv = 1;
    }

    return input;
}


int main(int argc, char** argv) {
    if(argc < 3) {
        printf("Missing inputs\n");
        return -1;
    }

    AMORT_CALC_INPUT input = process_inputs(argc, argv);

    print_input(input);

    AMORT_CALC_OUTPUT output = create_payment_table(input);
    export_to_csv(input, output);
    return 0;
}
