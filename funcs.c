#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "funcs.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* simple code to convert string to lowercase */
void to_lower_str(char *s)
{
    while (*s) {
        *s = (char)tolower((unsigned char)*s);
        s++;
    }
}

/* convert the resistor colour to digit 0-9 or -1 if invalid */
int colour_to_digit(char *colour)
{
    to_lower_str(colour);

    if(strcmp(colour, "black") == 0)  return 0;
    if(strcmp(colour, "brown") == 0)  return 1;
    if(strcmp(colour, "red") == 0)  return 2;
    if(strcmp(colour, "orange") == 0)  return 3;
    if(strcmp(colour, "yellow") == 0)  return 4;
    if(strcmp(colour, "green") == 0)  return 5;
    if(strcmp(colour, "blue") == 0)  return 6;
    if(strcmp(colour, "violet") == 0 ||
    strcmp(colour, "purple") == 0) return 7;
    if(strcmp(colour, "grey") == 0  ||
    strcmp(colour, "gray") == 0) return 8;
    if(strcmp(colour, "white") == 0)  return 9;

    return -1;
}

/* print the resistances nicely with prefixes */
void print_resistance_with_prefix(double R)
{
    if (R < 1e3) {
        printf("Resistance: %.2f Ohms\n", R);
    } else if (R < 1e6) {
        printf("Resistance: %.3f kOhms\n", R / 1e3);
    } else {
        printf("Resistance: %.3f MOhms\n", R / 1e6);
    }
}

/* cleans any left over characters left on the input line */
void flush_line(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

/* below is the code for menu item 1 */
/*Resistor Colour Code Decoder*/

void menu_item_1(void)
{
    char band1[16], band2[16], band3[16];
    int d1, d2, mult_pow;
    double resistance;

    printf("\n>> Resistor Colour Code Decoder (3-band)\n");
    printf("Enter colours as words (e.g. red, brown, yellow).\n\n");

    printf("First band colour: ");
    if(scanf("%15s", band1) !=1) return;

    printf("Second band colour: ");
    if(scanf("%15s", band2) !=1) return;

    printf("Third band (multiplier) colour: ");
    if(scanf("%15s", band3) !=1) return;

    d1      = colour_to_digit(band1);
    d2      = colour_to_digit(band2);
    mult_pow = colour_to_digit(band3);

    if (d1 < 0 || d2 < 0 || mult_pow < 0) {
        printf("\nOne or more colours were invalid.\n");
        flush_line();
        return;
    }

    resistance = (d1 * 10 + d2) * pow(10.0, mult_pow);

    printf("\nDecoded value:\n");
    printf(" Digits: %d %d\n", d1, d2);
    printf(" Multiplier: 10^%d\n", mult_pow);
    print_resistance_with_prefix(resistance);

    flush_line();
}

/* below is the code for menu item 2 */
/*Series / Parallel Resistor Calculator*/

void menu_item_2(void)
{
    int mode, n, i;
    double R, total = 0.0, inv_sum = 0.0;
    double supply_voltage, total_current;

    printf("\n>> Series / Parallel Resistor Calculator\n");
    printf("1. Series combination\n");
    printf("2. Parallel combination\n");
    printf("Choose mode (1 or 2): ");

    if (scanf("%d", &mode) != 1) {
        flush_line();
        return;
    }
    if (mode != 1 && mode != 2) {
        printf("Invalid mode:\n");
        flush_line();
        return;
    }

    printf("How many resistors? (2-10): ");
    if (scanf("%d", &n) !=1) {
        flush_line();
        return;
    }
    if (n < 2 || n > 10) {
        printf("Invalid number of resistors.\n");
        flush_line();
        return;
    }
    /* series */
    if (mode == 1) 
    {
        total = 0.0;
        printf("\nEnter each resistor in Ohms:\n");
        for (i = 0; i < n; i++) {
            printf("R%d (Ohms): ", i + 1);
            if (scanf("%lf", &R) != 1){
                flush_line();
                return;
            }
            total += R;
        }
        printf("\nSeries combination:\n");
        print_resistance_with_prefix(total);
    } else {      /* parallel */
        inv_sum = 0.0;
        printf("\nEnter each resistor in Ohms:\n");
        for (i = 0; i < n; i++) {
            printf("R%d (Ohms): ", i + 1);
            if (scanf("%lf", &R) != 1) {
                flush_line();
                return;
            }
            if (R <= 0) {
                printf("Resistance must be > 0.\n");
                flush_line();
                return;
            }
            inv_sum += 1.0 / R;
        }
        if (inv_sum == 0.0){
            printf("Cannot compute parallel resistance.\n");
            flush_line();
            return;
        }
        total = 1.0 / inv_sum;
        printf("\nParallel combination:\n");
        print_resistance_with_prefix(total);
    }

    printf("\nOptional: Ohm's Law current (I = V / R_total)\n");
    printf("Enter supply voltage in Volts: ");
    if (scanf("%lf", &supply_voltage) != 1) {
        flush_line();
        return;
    }

    if (total <= 0.0) {
        printf("Total resistance is non-positive, cannot compute current.\n");
    } else {
        total_current = supply_voltage / total;
        printf("Total current: %.6f A\n", total_current);
    }

    flush_line();
}

/* below is the code for menu item 3 */
/*RC Circuit Helper*/
void menu_item_3(void) 
{
    int choice, k;
    double R, C, tau, Vin, t, Vt;

    printf("\n>> RC Circuit Helper\n");
    printf("1. Calculate time constant τ = R * C\n");
    printf("2. Charging voltage at a time t\n");
    printf("Choose option (1 or 2): ");

    if(scanf("%d", &choice) != 1) {
        flush_line();
        return;
    }
    if (choice != 1 && choice != 2) {
        printf("Invalid option.\n");
        flush_line();
        return;
    }
    printf("Enter resistance R in Ohms: ");
    if (scanf("%lf", &R) != 1) {
        flush_line();
        return;
    }
    printf("Enter capacitance C in Farads: ");
    if (scanf("%lf", &C) != 1) {
        flush_line();
        return;
    }
    tau = R * C;
    printf("\nTime constant:\n");
    printf(" τ = R * C = %.6e seconds\n", tau);

    printf("\nRule-of-thumb charging levels:\n");
    for (k = 1; k <= 5; k++) {
        double frac = 1.0 - exp(-(double)k);
        printf(" t = %d τ -> %.1f %% of final voltage\n", k, frac * 100.0);
    }

    if (choice ==2) {
        printf("\nEnter input voltage Vin in Volts: ");
        if (scanf("%lf", &Vin) != 1) {
            flush_line();
            return;
        }
        printf("Enter time t in seconds: ");
        if (scanf("%lf", &t) != 1) {
            flush_line();
            return;
        }
        if (tau <= 0.0) {
            printf("Invalid τ, cannot compute V(t).\n");
            flush_line();
            return;
        }
        Vt = Vin * (1.0 - exp(-t / tau));

        printf("\nCharging capacitor (from 0 V): \n");
        printf(" V(t) = Vin * (1 - e^(-t/τ))\n");
        printf(" For Vin = %.3f V, t = %.3f s: \n", Vin, t);
        printf(" V(t) = %.6f v\n", Vt);
    }
    flush_line();
}

/* below is the code for menu item 4 */
/*Unit Converter */
void menu_item_4(void) 
{
    int choice;
    double x, result;

    printf("\n>> Unit Converter \n");
    printf("1. Hz -> rad/s\n");
    printf("2. rad/s -> Hz\n");
    printf("3. Ohms -> kOhms / MOhms\n");
    printf("4. kOhms / MOhms -> Ohms \n");
    printf("5. mW -> dBm\n");
    printf("6. dBm -> mW\n");
    printf("Choose option (1-6): ");

    if (scanf("%d", &choice) != 1){
        flush_line();
        return;
    }
    if (choice ==1) {
        printf("Enter frquency in Hz: ");
        if (scanf("%lf", &x) != 1) { flush_line(); return;}
        result = 2.0 * M_PI * x;
        printf("\nUsing ω = 2πf:\n");
        printf(" f = %.6f Hz\n", x);
        printf(" ω = %.6f rad/s\n", result);
    }
    else if (choice == 2) {
        printf("Enter angular frequency ω in rad/s: ");
        if (scanf("%lf", &x) != 1) {flush_line(); return;}
        result = x / (2.0 * M_PI);
        printf("\nUsing f = ω / (2π):\n");
        printf(" ω = %.6f rad/s\n", x);
        printf(" f = %.6f Hz\n", result);
    }
    else if (choice == 3) {
        printf("Enter resistance in ohms: ");
        if (scanf("%lf", &x) != 1) {
            flush_line();
            return;
        }
        printf("\nScaling resistance:\n");
        printf(" %.6f Ohms = %.6f kOhms\n", x, x / 1000.0);
        printf(" %.6f Ohms = %.6f MOhms\n", x, x / 1000000.0);
        printf("\nExplanation:\n");
        printf(" - kOhms = Ohms / 1000\n");
        printf(" - MOhms = Ohms / 1000000\n");
    }
    else if (choice == 4) {
        int sub;
        printf("Enter value: ");
        if (scanf("%lf", &x) != 1) {flush_line(); return;}
        printf("Is this (1) kOhms or (2) MOHms? ");
        if (scanf("%d", &sub) != 1) { flush_line(); return; }

        if (sub == 1) {
            result = x * 1e3;
            printf("\n%.6f kOhms = %.6f Ohms\n", x, result);
        } else if (sub == 2) {
            result = x * 1e6;
            printf("\n%.6f MOhms = %.6f Ohms\n", x, result);
        } else {
            printf("Invalid option.\n");
        }
        printf("Explanations: multiply by 1000 k, 1000000 for M.\n");
    }
    else if (choice == 5) {
        printf("Enter power in mW: ");
        if (scanf("%lf", &x) != 1) { flush_line(); return; }
        if (x <= 0.0) {
            printf("Power must be > 0 for dBm.\n");
            flush_line();
            return;
        }
        result = 10.0 * log10(x);
        printf("\nUsing dBm = 10 * log10(P_mW):\n");
        printf(" P = %.6f mW\n", x);
        printf(" dBm = %.6f dBm\n", result);
    }
    else if (choice == 6) {
        printf("Enter power in dBm: ");
        if (scanf("%lf", &x) != 1) {flush_line(); return;}
        result = pow(10.0, x / 10.0);
        printf("\nUsing P_mW = 10^(dBm/10):\n");
        printf(" dBm = %.6f dBm\n", x);
        printf(" P = %.6f mW\n", result);
    }
    else {
        printf("Invalid option.\n");
    }
    flush_line();
}