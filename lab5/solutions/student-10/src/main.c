/*
 * Лабораторная работа №5
 * Студент: номер 10
 * Вариант: 2 (Умножение матрицы на число и транспонирование)
 */

#include "matrix.h"

static void	fill_matrix(matrix_t *A)
{
	A->matrix[0][0] = 1;
	A->matrix[0][1] = 2;
	A->matrix[0][2] = 3;
	A->matrix[1][0] = 4;
	A->matrix[1][1] = 5;
	A->matrix[1][2] = 6;
}

int	main(void)
{
	matrix_t	*A;
	matrix_t	*B;
	matrix_t	*T;

	ft_putendl_fd("\n=== Matrix Operations Demo ===", 1);
	ft_putendl_fd("Variant 2: Multiplication by number and Transpose", 1);
	A = create_matrix(2, 3);
	if (!A)
	{
		ft_putendl_fd("Failed to create matrix", 2);
		return (1);
	}
	fill_matrix(A);
	ft_putendl_fd("\nOriginal matrix A:", 1);
	print_matrix(A);
	B = mult_number(A, 2);
	if (!B)
	{
		ft_putendl_fd("Failed to multiply matrix", 2);
		remove_matrix(A);
		return (1);
	}
	ft_putendl_fd("\nMatrix A multiplied by 2:", 1);
	print_matrix(B);
	T = transpose(A);
	if (!T)
	{
		ft_putendl_fd("Failed to transpose matrix", 2);
		remove_matrix(A);
		remove_matrix(B);
		return (1);
	}
	ft_putendl_fd("\nTransposed matrix A (A^T):", 1);
	print_matrix(T);
	remove_matrix(A);
	remove_matrix(B);
	remove_matrix(T);
	ft_putendl_fd("\nAll memory freed successfully.", 1);
	return (0);
}
