Simple Constant Amortization System

compile:
    gcc cas.c -lm
usage:
    ./a.out 360 0.0745 710000 test.csv
    parameters:
        - 360     : period in months
        - 0.0745  : interest rate
        - 710000  : principal
        - test.csv: output
