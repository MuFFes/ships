#include "pch.h"
#include "GameHelperTest.h"

struct StandardizeCoordinatesInputTestCase
{
	char x;
	char y;
	int expectedX;
	int expectedY;
};

struct StandardizeCoordinatesInputTest : GameHelperTest, testing::WithParamInterface<StandardizeCoordinatesInputTestCase>
{
	int x;
	int y;
	StandardizeCoordinatesInputTest()
	{
		x = GetParam().x;
		y = GetParam().y;
	}
};

TEST_P(StandardizeCoordinatesInputTest, ValuesAreModifiedCorrectly)
{
	GameHelper::StandardizeCoordinatesInput(&x, &y);
	EXPECT_EQ(x, GetParam().expectedX);
	EXPECT_EQ(y, GetParam().expectedY);
}

INSTANTIATE_TEST_CASE_P(Default, StandardizeCoordinatesInputTest,
	testing::Values(
		StandardizeCoordinatesInputTestCase{ 'A', '0', 0, 0 },
		StandardizeCoordinatesInputTestCase{ '0', 'A', 0, 0 },
		StandardizeCoordinatesInputTestCase{ 'J', '9', 9, 9 },
		StandardizeCoordinatesInputTestCase{ '9', 'J', 9, 9 },
		StandardizeCoordinatesInputTestCase{ 'C', '7', 7, 2 },
		StandardizeCoordinatesInputTestCase{ '7', 'C', 7, 2 }
));
