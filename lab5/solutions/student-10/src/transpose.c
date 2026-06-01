#include "matrix.h"

matrix_t	*transpose(matrix_t *A)
{
	matrix_t	*result;
	int			i;
	int			j;

	if (!A || !A->matrix)
		return (NULL);
	result = create_matrix(A->cols, A->rows);
	if (!result)
		return (NULL);
	i = 0;
	while (i < A->rows)
	{
		j = 0;
		while (j < A->cols)
		{
			result->matrix[j][i] = A->matrix[i][j];
			j++;
		}
		i++;
	}
	return (result);
}
