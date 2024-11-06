#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_set_and_get_infix_expression)
{
	TPostfix p;
	p.SetInfix("a + b");
	EXPECT_EQ(p.GetInfix(), "a + b");
}

TEST(TPostfix, can_convert_to_postfix)
{
	TPostfix p;
	p.SetInfix("a + b * c");
	EXPECT_EQ(p.ToPostfix(), "abc*+");
}

TEST(TPostfix, can_calculate_postfix_expression)
{
	TPostfix p;
	p.SetInfix("2 + 3 * 4");
	p.ToPostfix();
	EXPECT_NEAR(p.Calculate(), 14.0, 0.001);
}

TEST(TPostfix, throws_on_division_by_zero)
{
	TPostfix p;
	p.SetInfix("8 / 0");
	p.ToPostfix();
	EXPECT_THROW(p.Calculate(), std::runtime_error);
}
