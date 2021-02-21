//======== Copyright (c) 2020, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     FILIP JANUSKA  <xjanus11@stud.fit.vutbr.cz>
// $Date:       $2020-19-02
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author FILIP JANUSKA
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

class Matica : public ::testing::Test
{
	protected:
		Matrix Matica_1;
		Matrix Matica_3 = Matrix(3,3);
		Matrix Matica_10 = Matrix(10,10);
		Matrix Matica_large = Matrix(1024, 1024);
		Matrix Matica_rect = Matrix(42, 68);

		Matrix Matica_5_f = Matrix(5,5);
		
		virtual void SetUp()
		{
			std::vector<std::vector<double>> values = {{0,1,2,3,4},
			       				           {5,6,7,8,9},
								   {1, 2, 1.3, 1.4, 5},
								   {42,42,42,68,42},
								   {-5,4, -6, -10, 68}};
			Matica_5_f.set(values);
		}
};


//Test Konstruktoru
TEST(Initial, construct)
{
	EXPECT_ANY_THROW(Matrix Matica_1(0,0));
	EXPECT_ANY_THROW(Matrix Matica_2(-5, -2));
		
	EXPECT_NO_THROW(Matrix Matica_3 (4.2, 5.4));
	EXPECT_NO_THROW(Matrix Matica_4(2,2));
	EXPECT_NO_THROW(Matrix Matica_5(2048, 1024));
}

//Test funkce Matrix::set
TEST_F(Matica,set)
{
	
	EXPECT_FALSE(Matica_3.set(10,10, 42));
	EXPECT_FALSE(Matica_3.set(-4 , -1, 68));
	
	EXPECT_TRUE(Matica_3.set(0, 0, 10.24));
	EXPECT_TRUE(Matica_3.set(2, 2, 42));
}

//Test funkce Matrix::set(vector)
TEST_F(Matica, set_vector)
{
	std::vector<std::vector<double>> values_f = {
						    { 1, 2, 3},
						    {4.5, -4.2}};

	EXPECT_FALSE(Matica_3.set(values_f));

	std::vector<std::vector<double>> values_low = {{12}, {54, 42}};
	EXPECT_FALSE(Matica_3.set(values_low));
					

	std::vector<std::vector<double>> values_t = {
					{1, 2, 4},
	       				{-5, -65.2, 32},
					{42, 95, 5}};
	EXPECT_TRUE(Matica_3.set(values_t));
}

//Test funkce Matrix::get
TEST_F(Matica, get)
{

	EXPECT_ANY_THROW(Matica_3.get(5,5));
	EXPECT_ANY_THROW(Matica_3.get(-2, -1));
	EXPECT_ANY_THROW(Matica_large.get(2048, 5));

	EXPECT_NO_THROW(Matica_large.get(1023, 1023));
	EXPECT_NO_THROW(Matica_3.get(1,2));
}

//Test operatoru ==
TEST_F(Matica, compare)
{
	EXPECT_ANY_THROW(Matica_3 == Matica_10);
	EXPECT_ANY_THROW(Matica_3 == Matica_large);
	EXPECT_ANY_THROW(Matica_large == Matrix (2048, 2048));

	ASSERT_NO_THROW(Matica_3  == Matica_3);
	EXPECT_TRUE(Matica_3 == Matica_3);

	Matrix Matica_5(5,5);
	ASSERT_NO_THROW(Matica_5_f == Matica_5);
	EXPECT_FALSE(Matica_5_f == Matica_5);
	
	ASSERT_NO_THROW(Matrix(2048, 1024) == Matrix(2048, 1024));
	EXPECT_TRUE(Matrix(2048, 1024) == Matrix(2048, 1024));
}

//Test operatoru +
TEST_F(Matica, add)
{

	EXPECT_ANY_THROW(Matica_3 + Matica_10);
	EXPECT_ANY_THROW(Matica_large + Matica_1);

	EXPECT_NO_THROW(Matica_rect + Matica_rect);
	EXPECT_NO_THROW(Matica_5_f + Matrix(5,5));
	EXPECT_NO_THROW(Matica_3 + Matica_3);
}

//Test operatoru * matici
TEST_F(Matica, multiply_matrix)
{
	EXPECT_ANY_THROW(Matica_3 * Matica_10);
	EXPECT_ANY_THROW(Matica_rect * Matica_rect);
	EXPECT_ANY_THROW(Matrix(52, 52) * Matica_rect);

	EXPECT_NO_THROW(Matica_3 * Matica_3);
	EXPECT_NO_THROW(Matrix(42, 42) * Matrix(42, 42));
}

//Test operatoru * skalarem
TEST_F(Matica, multiply_scalar)
{
	EXPECT_NO_THROW(Matica_3 * 5);
	EXPECT_NO_THROW(Matica_3 * 4.2);
	EXPECT_NO_THROW(Matica_large * 14);
	EXPECT_NO_THROW(Matica_5_f * -5);	
}

//Test reseni soustavy
TEST_F(Matica, solve)
{
	Matrix Matica_3_f(3,3);
	Matica_3_f.set({
			{1, 1, 1},
			{1, -1, 1},
			{1, 1, -1}});
	std::vector <double> vector = {4, 2, 2};
	std::vector<double> results = Matica_3_f.solveEquation(vector);
	ASSERT_NO_THROW(Matica_3_f.solveEquation(vector));

	
	std::vector <double> expected = {2, 1, 1};
	EXPECT_EQ(expected , results);

 	//Pocet prvku se nerovna poctu radku matice	
	EXPECT_ANY_THROW(Matica_3_f.solveEquation({1, 2, 4, 2}));
	
	//Matice neni ctvercova
	Matrix Matica_rect_fill (4, 2);
	Matica_rect_fill.set({
			{1, 2},
			{3, 4},
			{5, 6},
			{4, 2}});

	EXPECT_ANY_THROW(Matica_rect_fill.solveEquation({4, 2}));
	
	//Matice je singularni

	Matrix Matica_sing(3, 3);

	Matica_sing.set({
			{1, 1, 1},
			{2, 3, 4},
			{1, 1, 1}});
	EXPECT_ANY_THROW(Matica_sing.solveEquation({1, 2, 3}));

	//Matica velkosti 1
	Matica_1.set(0, 0, 1);
	EXPECT_NO_THROW(Matica_1.solveEquation({2}));

	//Matica velkosti 2
	Matrix Matica_2(2, 2);
	Matica_2.set({
		     {1, 2},
		     {3, 1}});
	EXPECT_NO_THROW(Matica_2.solveEquation({2, 3}));

	//Matica velkosti 5
	EXPECT_NO_THROW(Matica_5_f.solveEquation({1, 2, 3, 4, 5}));
}




//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

/*** Konec souboru white_box_tests.cpp ***/
