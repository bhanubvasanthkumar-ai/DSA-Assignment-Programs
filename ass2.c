#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[20];
    int emp_id;

    enum { FULL_TIME, CONTRACT } type;

    union {
        float salary;

        struct {
            float hourly_rate;
            int hours_worked;
        } contract_info;
    } pay;

} Employee;

int main() {
    Employee *emp;
    int n, i;
    float total_pay, total_bill = 0;

    printf("Enter the number of employees: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of employees.\n");
        return 1;
    }

    emp = (Employee *)malloc(n * sizeof(Employee));

    if (emp == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    /* Read employee details */
    for (i = 0; i < n; i++) {
        printf("\nEnter details of employee %d\n", i + 1);

        printf("Enter employee name: ");
        scanf(" %19[^\n]", emp[i].name);

        printf("Enter employee ID: ");
        scanf("%d", &emp[i].emp_id);

        printf("Enter employee type (0-Full-time, 1-Contract): ");
        scanf("%d", (int *)&emp[i].type);

        if (emp[i].type == FULL_TIME) {
            printf("Enter monthly salary: ");
            scanf("%f", &emp[i].pay.salary);
        }
        else if (emp[i].type == CONTRACT) {
            printf("Enter hourly rate: ");
            scanf("%f", &emp[i].pay.contract_info.hourly_rate);

            printf("Enter hours worked: ");
            scanf("%d", &emp[i].pay.contract_info.hours_worked);
        }
        else {
            printf("Invalid employee type!\n");
            free(emp);
            return 1;
        }
    }

    /* Print payslips */
    printf("\n========== EMPLOYEE PAYSLIPS ==========\n");

    for (i = 0; i < n; i++) {
        if (emp[i].type == FULL_TIME) {
            total_pay = emp[i].pay.salary;
        }
        else {
            total_pay =
                emp[i].pay.contract_info.hourly_rate *
                emp[i].pay.contract_info.hours_worked;
        }

        printf("\nEmployee ID   : %d\n", emp[i].emp_id);
        printf("Employee Name : %s\n", emp[i].name);

        if (emp[i].type == FULL_TIME) {
            printf("Employee Type : Full-time\n");
        }
        else {
            printf("Employee Type : Contract\n");
        }

        printf("Total Pay     : Rs. %.2f\n", total_pay);

        total_bill += total_pay;
    }

    printf("\n=======================================\n");
    printf("Total Salary Bill: Rs. %.2f\n", total_bill);

    free(emp);

    return 0;
}
