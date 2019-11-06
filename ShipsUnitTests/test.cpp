#include "pch.h"
#include "../Ships/GameHelper.h"

//class MockConnection : public Connection
//{
//	public:
//		MOCK_METHOD1(Open, void(string));
//		MOCK_METHOD0(Close, void(void));
//};

struct GameHelperTest : testing::Test
{
	//MockConnection connection;
	//Game* game;
	GameHelper helper;

	//GameHelperTest()
	//{
	//}
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
		StandardizeCoordinatesInputTestCase{ '9', 'J', 9, 9 }
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