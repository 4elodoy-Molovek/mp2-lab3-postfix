// test_tstack.cpp
#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, throws_when_creating_stack_with_invalid_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-1));
}

TEST(TStack, can_push_element)
{
	TStack<int> st(5);
	ASSERT_NO_THROW(st.Push(10));
}

TEST(TStack, can_pop_element)
{
	TStack<int> st(5);
	st.Push(10);
	EXPECT_EQ(st.Pop(), 10);
}

TEST(TStack, can_get_top_element)
{
	TStack<int> st(5);
	st.Push(10);
	EXPECT_EQ(st.Top(), 10);
}

TEST(TStack, is_empty_returns_true_when_stack_is_empty)
{
	TStack<int> st(5);
	EXPECT_TRUE(st.IsEmpty());
}

TEST(TStack, is_full_returns_true_when_stack_is_full)
{
	TStack<int> st(1);
	st.Push(10);
	EXPECT_TRUE(st.IsFull());
}
