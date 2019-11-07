#include "pch.h"
#include "GameHelperTest.h"

struct ValidateCoordinatesInputTestCase
{
	string str;
	bool expectedResult;
};

struct ValidateCoordinatesInputTest : GameHelperTest, testing::WithParamInterface<ValidateCoordinatesInputTestCase>
{
	string str;
	bool expectedResult;

	ValidateCoordinatesInputTest()
	{
		str = GetParam().str;
		expectedResult = GetParam().expectedResult;
	}
};

TEST_P(ValidateCoordinatesInputTest, ValuesAreValidatedCorrectly)
{
	
	EXPECT_EQ(GameHelper::ValidateCoordinatesInput(str), expectedResult);
}

INSTANTIATE_TEST_CASE_P(LengthTest, ValidateCoordinatesInputTest,
	testing::Values(
		ValidateCoordinatesInputTestCase{ "", false },
		ValidateCoordinatesInputTestCase{ "A112", false },
		ValidateCoordinatesInputTestCase{ "A1", true }
));

//INSTANTIATE_TEST_CASE_P(SampleValuesTest, ValidateCoordinatesInputTest,
//	testing::Values(
//		ValidateCoordinatesInputTestCase{ 'C', '7', 7, 2 },
//		ValidateCoordinatesInputTestCase{ '7', 'C', 7, 2 }
//));
