#pragma once


template<typename T>
struct Wrapper
{
    Wrapper()
    {
        m_constructed=true;
    }

    ~Wrapper()
    {
        m_destructed=true;
    }

    Wrapper(const Wrapper& other)
    {
        m_copied=true;
        value = other.value;
    }

    Wrapper(Wrapper&& other)
    {
        m_moved=true;
        value = other.value;
    }

/*
    Wrapper operator+(const Wrapper& other)
    {
        fmt::print("+ operator\n");
        return value+other.value;
    }

    Wrapper operator-(const Wrapper& other)
    {
        fmt::print("- operator\n");
        return value-other.value;
    }

    Wrapper& operator=(const Wrapper&other)
    {
        fmt::print("Copy Assign\n");
        value=other.value;
        return *this;
    }
*/
    T value;
private:
    bool m_constructed = false;
    bool m_destructed = false;
    bool m_copied = false;
    bool m_moved = false;
};
