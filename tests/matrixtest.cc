


// trivial but error-prone case
TEST(MatrixTest, Square1x1) {	
	Matrix<int> A(std::vector<std::vector<int>>({{6,},}));
	Matrix<int> B(std::vector<std::vector<int>>({{-4,},}));
	Matrix<int> AxB(std::vector<std::vector<int>>({{-24,},}));
	EXPECT_EQ( A*B, AxB);
}


TEST(MatrixTest, Square3x3) {	
	Matrix<int> A(
		{
			{1,2,3},
			{4,5,6},
			{7,8,9}
		});


	Matrix<int> B(
		{
			{10,-11,12},
			{13,-14,15},
			{-17,18,19}
		});

	Matrix<int> AxB(
			{{-15, 15, 99}, {3, -6, 237}, {21, -27, 375}}
			); // precalculated using Wolfram

	EXPECT_EQ( A*B, AxB);
}

