#include "matrix.h"

matrix_t	*create_matrix(int rows, int cols)
{
	matrix_t	*mat;
	int			i;

	if (rows <= 0 || cols <= 0)
		return (NULL);
	mat = (matrix_t *)malloc(sizeof(matrix_t));
	if (!mat)
		return (NULL);
	mat->matrix = (int **)malloc(sizeof(int *) * rows);
	if (!mat->matrix)
	{
		free(mat);
		return (NULL);
	}
	mat->rows = rows;
	mat->cols = cols;
	i = 0;
	while (i < rows)
	{
		mat->matrix[i] = (int *)malloc(sizeof(int) * cols);
		if (!mat->matrix[i])
		{
			while (--i >= 0)
				free(mat->matrix[i]);
			free(mat->matrix);
			free(mat);
			return (NULL);
		}
		i++;
	}
	return (mat);
}
