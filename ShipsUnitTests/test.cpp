#include "pch.h"
#include "../Ships/GameHelper.h"


struct GameHelperTest : testing::Test
{
	GameHelper helper;
};

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
	helper.StandardizeCoordinatesInput(&x, &y);
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

TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	ASSERT_TRUE(true);
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}