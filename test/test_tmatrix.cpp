#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m(5);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			m[i][j] = i + j;
		}
	}
	TDynamicMatrix<int> z(m);
	EXPECT_EQ(1, z == m);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(5);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			m[i][j] = i + j;
		}
	}
	TDynamicMatrix<int> m1(m);
	m1[0][0] = 5;
	EXPECT_EQ(0, m == m1);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(5);
	EXPECT_EQ(5, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 6;
	EXPECT_EQ(6, m[0][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(2);
	ASSERT_ANY_THROW(m.at(-2,2));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(2);
	ASSERT_ANY_THROW(m.at(3,2));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(3);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m[i][j] = i + j;
		}
	}
	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(3);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m[i][j] = i + j;
		}
	}
	ASSERT_NO_THROW(m1 = m);
	EXPECT_EQ(1, m == m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(1);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m[i][j] = i + j;
		}
	}
	ASSERT_NO_THROW(m1 = m);
	EXPECT_EQ(m.size(), m1.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(1);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m[i][j] = i + j;
		}
	}
	ASSERT_NO_THROW(m1 = m);
	EXPECT_EQ(m[0][0], m1[0][0]);
	EXPECT_EQ(m[0][1], m1[0][1]);
	EXPECT_EQ(m[1][0], m1[1][0]);
	EXPECT_EQ(m[1][1], m1[1][1]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(2);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m[i][j] = i + j;
			m1[i][j] = i + j;
		}
	}
	EXPECT_EQ(1, m == m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(2);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m[i][j] = i + j;
		}
	}
	EXPECT_EQ(1, m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m(2), m1(4);
	EXPECT_EQ(0, m == m1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(2), m1(2), mr(2);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m[i][j] = i + j;
			m1[i][j] = i + j + 1;
		}
	}
	ASSERT_NO_THROW(mr = m + m1);
	EXPECT_EQ(mr[0][0], 1);
	EXPECT_EQ(mr[0][1], 3);
	EXPECT_EQ(mr[1][0], 3);
	EXPECT_EQ(mr[1][1], 5);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(2), m1(4);
	ASSERT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(2), m1(2), mr(2);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m[i][j] = i + j;
			m1[i][j] = i + j + 1;
		}
	}
	ASSERT_NO_THROW(mr = m - m1);
	EXPECT_EQ(mr[0][0], -1);
	EXPECT_EQ(mr[0][1], -1);
	EXPECT_EQ(mr[1][0], -1);
	EXPECT_EQ(mr[1][1], -1);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m(2), m1(4);
	ASSERT_ANY_THROW(m - m1);
}

