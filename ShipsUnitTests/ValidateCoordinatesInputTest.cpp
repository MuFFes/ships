#include "pch.h"
#include "GameHelperTest.h"

using namespace std;

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

INSTANTIATE_TEST_CASE_P(EdgeCaseTest, ValidateCoordinatesInputTest,
	testing::Values(
		ValidateCoordinatesInputTestCase{ "A0", true },
		ValidateCoordinatesInputTestCase{ "0A", true },
		ValidateCoordinatesInputTestCase{ "0a", true },
		ValidateCoordinatesInputTestCase{ "a0", true },
		ValidateCoordinatesInputTestCase{ "J9", true },
		ValidateCoordinatesInputTestCase{ "j9", true },
		ValidateCoordinatesInputTestCase{ "9J", true },
		ValidateCoordinatesInputTestCase{ "9j", true }
));

INSTANTIATE_TEST_CASE_P(InvalidValuesTest, ValidateCoordinatesInputTest,
	testing::Values(
		ValidateCoordinatesInputTestCase{ "\a", false },
		ValidateCoordinatesInputTestCase{ "\\a", false },
		ValidateCoordinatesInputTestCase{ "/-", false },
		ValidateCoordinatesInputTestCase{ "-a", false },
		ValidateCoordinatesInputTestCase{ "??", false },
		ValidateCoordinatesInputTestCase{ "%*", false },
		ValidateCoordinatesInputTestCase{ "  ", false },
		ValidateCoordinatesInputTestCase{ "``", false }
));
