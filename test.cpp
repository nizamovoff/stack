#include "stack.h"
#include <stack>
#include <assert.h>

int main() {
    // Push, Pop, Top
    {
        Stack<int> st;
        st.Push(1);
        st.Push(2);
        st.Push(3);
        assert(st.Top() == 3);

        st.Pop();
        st.Pop();
        assert(st.Top() == 1);
        st.Pop();
    }

    // Empty, Size, Clear
    {
        Stack<int> st;

        assert(st.Empty() == true);
        st.Push(1);
        st.Push(2);
        st.Push(10);
        assert(st.Size() == 3);
        assert(st.Top() == 10);
        assert(st.Empty() == false);

        st.Clear();
        st.Clear();
        assert(st.Empty() == true);
    }

    // copy semantics
    {
        Stack<std::string> st1;
        st1.Push("abc");
        st1.Push("string");
        st1 = st1;

        Stack<std::string> st2;
        st2 = st1;
        assert(st2.Top() == "string");

        Stack<std::string> st3 = st1;
        st3.Pop();
        assert(st3.Top() == "abc");

        st1 = st2 = st3;
        st1.Pop();
        assert(st1.Empty() == true);
    }

    // move semantics
    {
        Stack<double> st1;
        double value = static_cast<double>(22) / static_cast<double>(7);

        st1.Push(3.14);
        st1.Push(value);

        Stack<double> st2 = std::move(st1), st3;
        assert(st2.Size() == 2);
        assert(st2.Top() == value);
        assert(st1.Empty() == true);

        st3 = std::move(st2);
        assert(st3.Size() == 2);
        assert(st3.Top() == value);
        assert(st2.Empty() == true);
    }

    // Swap
    {
        int value = 10;
        Stack<int> st1;
        st1.Push(5);
        Stack<int> st2 = st1;
        st2.Push(value);

        assert(st1.Size() == 1);
        assert(st2.Size() == 2);

        st1.Swap(st2);

        assert(st1.Size() == 2);
        assert(st2.Size() == 1);
        assert(st1.Top() == value);
    }
}