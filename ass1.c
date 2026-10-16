#include <stdio.h>
#include <stdlib.h>

struct Student
{
    int roll_no;
    char name[20];
    float marks;
};

int main()
{
    struct Student *ptr;
    int n, i, choice;
    float sum = 0, average;
    struct Student *topper;

    // Read number of students
    printf("Enter number of students: ");
    scanf("%d", &n);

    // Dynamically allocate memory using malloc
    ptr = (struct Student *)malloc(n * sizeof(struct Student));

    if (ptr == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Read student records
    for (i = 0; i < n; i++)
    {
        printf("Enter roll, name, marks: ");
        scanf("%d %19s %f",
              &(ptr + i)->roll_no,
              (ptr + i)->name,
              &(ptr + i)->marks);
    }

    // Find average marks and topper using pointer arithmetic
    topper = ptr;

    for (i = 0; i < n; i++)
    {
        sum += (ptr + i)->marks;

        if ((ptr + i)->marks > topper->marks)
        {
            topper = ptr + i;
        }
    }

    average = sum / n;

    printf("\nAverage marks: %.2f\n", average);
    printf("Topper: %s (Roll %d, Marks %.2f)\n",
           topper->name, topper->roll_no, topper->marks);

    // Ask whether to add two more students
    printf("\nAdd 2 more students? (1 = Yes, 0 = No): ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        // Increase array size using realloc
        struct Student *temp;

        temp = (struct Student *)realloc(
            ptr, (n + 2) * sizeof(struct Student));

        if (temp == NULL)
        {
            printf("Memory reallocation failed!\n");
            free(ptr);
            return 1;
        }

        ptr = temp;

        // Read two additional student records
        for (i = n; i < n + 2; i++)
        {
            printf("Enter roll, name, marks: ");
            scanf("%d %19s %f",
                  &(ptr + i)->roll_no,
                  (ptr + i)->name,
                  &(ptr + i)->marks);
        }

        n = n + 2;

        // Recalculate average and topper
        sum = 0;
        topper = ptr;

        for (i = 0; i < n; i++)
        {
            sum += (ptr + i)->marks;

            if ((ptr + i)->marks > topper->marks)
            {
                topper = ptr + i;
            }
        }

        average = sum / n;

        printf("\nUpdated average marks: %.2f\n", average);
        printf("Topper: %s (Roll %d, Marks %.2f)\n",
               topper->name, topper->roll_no, topper->marks);
    }

    // Release dynamically allocated memory
    free(ptr);
    ptr = NULL;

    return 0;
}
