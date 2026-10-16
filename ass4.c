#include <stdio.h>

#define MAX 100

typedef struct
{
    int row, col, value;
} term;

void fast_transpose(term a[], term b[])
{
    int row_terms[MAX] = {0};
    int starting_pos[MAX] = {0};
    int i, j;
    int rows = a[0].row;
    int cols = a[0].col;
    int terms = a[0].value;

    /* Count non-zero elements in each column */
    for (i = 1; i <= terms; i++)
        row_terms[a[i].col]++;

    /* Find starting positions */
    starting_pos[0] = 1;

    for (i = 1; i < cols; i++)
        starting_pos[i] =
            starting_pos[i - 1] + row_terms[i - 1];

    printf("\nRow terms: ");
    for (i = 0; i < cols; i++)
        printf("%d ", row_terms[i]);

    printf("\nStarting positions: ");
    for (i = 0; i < cols; i++)
        printf("%d ", starting_pos[i]);

    /* Header of transposed matrix */
    b[0].row = cols;
    b[0].col = rows;
    b[0].value = terms;

    /* Fast transpose */
    for (i = 1; i <= terms; i++)
    {
        j = a[i].col;

        b[starting_pos[j]].row = a[i].col;
        b[starting_pos[j]].col = a[i].row;
        b[starting_pos[j]].value = a[i].value;

        starting_pos[j]++;
    }
}

int main()
{
    term a[MAX], b[MAX];
    int matrix[MAX][MAX];
    int rows, cols, i, j, k = 1;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    if (rows <= 0 || cols <= 0 ||
        rows >= MAX || cols >= MAX)
    {
        printf("Invalid matrix size.\n");
        return 1;
    }

    printf("Enter matrix elements:\n");

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            scanf("%d", &matrix[i][j]);

            if (matrix[i][j] != 0)
            {
                if (k >= MAX)
                {
                    printf("Too many non-zero elements.\n");
                    return 1;
                }

                a[k].row = i;
                a[k].col = j;
                a[k].value = matrix[i][j];
                k++;
            }
        }
    }

    /* Header of original matrix */
    a[0].row = rows;
    a[0].col = cols;
    a[0].value = k - 1;

    printf("\nOriginal matrix triples:\n");
    printf("Row\tCol\tValue\n");

    for (i = 0; i < k; i++)
        printf("%d\t%d\t%d\n",
               a[i].row, a[i].col, a[i].value);

    fast_transpose(a, b);

    printf("\n\nTransposed matrix triples:\n");
    printf("Row\tCol\tValue\n");

    for (i = 0; i < k; i++)
        printf("%d\t%d\t%d\n",
               b[i].row, b[i].col, b[i].value);

    printf("\nTransposed triples are in row-major order.\n");

    return 0;
}
