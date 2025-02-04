#include <stdio.h>
#include <stdlib.h>

#define MAX_DAYS 5
#define MONTHS_FOR_14TH_SALARY 12

const char *daysOfWeek[MAX_DAYS] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

// Function to get a valid number of employees
int getNumberOfEmployees() {
    int employees;
    do {
        printf("Enter the number of employees: ");
        scanf("%d", &employees);
        // check if the number of employees is valid
        if (employees <= 0) {
            printf("Invalid number of employees! Please enter a correct number.\n");
        }

    } while (employees <= 0 );
    return employees;
}

// Function to get salary rates for each employee
void getSalaryRates(int employees, float salaryRates[]) {
    for (int i = 0; i < employees; i++) {
        do {
            printf("Enter hourly salary rate for Employee %d: ", i + 1);
            scanf("%f", &salaryRates[i]);
            // check if the salary rate is valid
            if (salaryRates[i] <= 0) {
                printf("Invalid rate! Please enter a positive number.\n");
            }
        } while (salaryRates[i] <= 0);
    }
}

// Function to get hours worked for each employee
void getHoursWorked(int employees, float hours[employees][MAX_DAYS]) {
    for (int i = 0; i < employees; i++) {
        printf("\nEnter hours worked by Employee %d:\n", i + 1);
        for (int j = 0; j < MAX_DAYS; j++) {
            // Get hours worked for each day
            do {
                printf("%s: ", daysOfWeek[j]);
                scanf("%f", &hours[i][j]);
                if (hours[i][j] < 0 || hours[i][j] > 24) {
                    printf("Invalid input! Hours must be between 0 and 24.\n");
                }
            } while (hours[i][j] < 0 || hours[i][j] > 24);
        }
    }
}

// Function to calculate employee stats
void calculateEmployeeStats(int employees, float hours[employees][MAX_DAYS], int *minEmployee, int *maxEmployee) {
    int minHours = 1000, maxHours = 0;
    float globalHigh = 0.0, globalLow = 24.0;

    for (int i = 0; i < employees; i++) {
        int totalHours = 0;
        float highest = hours[i][0], lowest = hours[i][0];

        for (int j = 0; j < MAX_DAYS; j++) {
            totalHours += hours[i][j];
            if (hours[i][j] > highest) highest = hours[i][j];
            if (hours[i][j] < lowest) lowest = hours[i][j];
            if (hours[i][j] > globalHigh) globalHigh = hours[i][j];
            if (hours[i][j] < globalLow) globalLow = hours[i][j];
        }

        printf("\nEmployee %d - Total: %d hours, Average: %.2f, Highest: %.2f, Lowest: %.2f\n",
               i + 1, totalHours, (float)totalHours / MAX_DAYS, highest, lowest);

        if (totalHours < minHours) {
            minHours = totalHours;
            *minEmployee = i;
        }
        if (totalHours > maxHours) {
            maxHours = totalHours;
            *maxEmployee = i;
        }
    }

    printf("\nOverall Statistics:\n");
    printf("Employee with Lowest Weekly Hours: Employee %d with %d hours\n", *minEmployee + 1, minHours);
    printf("Employee with Highest Weekly Hours: Employee %d with %d hours\n", *maxEmployee + 1, maxHours);
    printf("Global Highest Hours Worked in a Day: %.2f\n", globalHigh);
    printf("Global Lowest Hours Worked in a Day: %.2f\n", globalLow);
}

// Function to calculate daily stats
void calculateDailyStats(int employees, float hours[employees][MAX_DAYS]) {
    printf("\nDaily Statistics:\n");
    for (int j = 0; j < MAX_DAYS; j++) {
        float dailyHigh = 0.0, dailyLow = 24.0;
        for (int i = 0; i < employees; i++) {
            if (hours[i][j] > dailyHigh) dailyHigh = hours[i][j];
            if (hours[i][j] < dailyLow) dailyLow = hours[i][j];
        }
        printf("%s: Highest = %.2f, Lowest = %.2f\n", daysOfWeek[j], dailyHigh, dailyLow);
    }
}

// Function to calculate tax payable
void calculateTax(float annualSalary, int dependents, int employeeNum) {
    float deduction = 0;
    if (dependents == 1) deduction = 110000;
    else if (dependents == 2) deduction = 190000;
    else if (dependents == 3) deduction = 275000;
    else if (dependents >= 4) deduction = 355000;
    
    float taxableIncome = annualSalary - deduction;
    float tax = 0;

    if (taxableIncome > 390000) tax += (taxableIncome - 390000) * 0.10;
    if (taxableIncome > 430000) tax += (taxableIncome - 430000) * 0.12;
    if (taxableIncome > 730000) tax += (taxableIncome - 730000) * 0.14;
    if (taxableIncome > 1130000) tax += (taxableIncome - 1130000) * 0.16;
    if (taxableIncome > 1630000) tax += (taxableIncome - 1630000) * 0.18;
    if (taxableIncome > 2130000) tax += (taxableIncome - 2130000) * 0.20;
    
    if (tax < 0) tax = 0;
    
    printf("Employee %d - Annual Salary: Rs %.2f, Deduction: Rs %.2f, Taxable Income: Rs %.2f, Tax Payable: Rs %.2f\n", employeeNum, annualSalary, deduction, taxableIncome, tax);
}

// Function to calculate salaries and 14th-month salary eligibility
void calculateSalaries(int employees, float hours[employees][MAX_DAYS], float salaryRates[]) {
    printf("\n--- Salary Report & 14th-Month Salary Eligibility ---\n");

    for (int i = 0; i < employees; i++) {
        float totalHours = 0, weeklySalary = 0, monthlySalary = 0, annualSalary = 0;

        // Calculate total hours worked per week
        for (int j = 0; j < MAX_DAYS; j++) {
            totalHours += hours[i][j];
        }

        // Compute weekly and monthly salary
        weeklySalary = totalHours * salaryRates[i];
        monthlySalary = weeklySalary * 4;  // 4 weeks in a month
        annualSalary = monthlySalary * 12; // 12 months in a year

        // Display salary information
        printf("\nEmployee %d:\n", i + 1);
        printf("Total Hours Worked Weekly: %.2f\n", totalHours);
        printf("Weekly Salary: Rs %.2f\n", weeklySalary);
        printf("Monthly Salary: Rs %.2f\n", monthlySalary);
        printf("Annual Salary: Rs %.2f\n", annualSalary);

        // Check eligibility for the 14th-month salary
        int monthsWorked;
        do {
            printf("Enter number of months Employee %d has worked: ", i + 1);
            scanf("%d", &monthsWorked);
            if (monthsWorked < 0) {
                printf("Invalid input! Months worked cannot be negative.\n");
            }
        } while (monthsWorked < 0);

        // Determine if the employee qualifies
        if (monthsWorked >= MONTHS_FOR_14TH_SALARY) {
            printf("Eligible for 14th-month salary! Bonus: Rs %.2f\n", monthlySalary);
        } else {
            printf("Not eligible for 14th-month salary. (%d months worked)\n", monthsWorked);
        }

        // Calculate tax
        int dependents;
        printf("Enter the number of dependents for Employee %d: ", i + 1);
        scanf("%d", &dependents);
        calculateTax(annualSalary, dependents, i + 1);
    }
}



int main() {
    // Get the number of employees
    int employees = getNumberOfEmployees();
    float hours[employees][MAX_DAYS]; // Store daily hours worked
    float salaryRates[employees];     // Store hourly rates

    // Get hourly salary rates
    getSalaryRates(employees, salaryRates);
    
    // Get hours worked for each employee
    getHoursWorked(employees, hours);

    // Compute and display min/max work hours stats
    int minEmployee = -1, maxEmployee = -1;
    calculateEmployeeStats(employees, hours, &minEmployee, &maxEmployee);
    
    // Compute and display daily work stats
    calculateDailyStats(employees, hours);
    
    // Compute salaries and eligibility
    calculateSalaries(employees, hours, salaryRates);
    return 0;
}
