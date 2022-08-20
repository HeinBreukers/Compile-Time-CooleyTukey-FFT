#pragma once

#include <type_traits>

template<typename T, size_t Point> requires std::is_integral_v<T>
struct fixed
{
    fixed()
    {
        ConstructorBase();
    }

    //TODO look into forwarding
    template <typename I> requires std::is_integral_v<I>
    explicit fixed(I value): 
    m_value(std::move(value<<Point))
    {
        ConstructorBase();
    }

    template <typename I> requires std::is_integral_v<I>
    fixed& operator=(I value)
    {
        m_value = std::move(value<<Point);
        return *this;
    }  

    template <typename F> requires std::is_floating_point_v<F>
    explicit fixed(F value): 
    m_value(std::move(static_cast<T>(value*(1<<Point))))
    {
        ConstructorBase();
    }

    template <typename F> requires std::is_floating_point_v<F>
    fixed& operator =(F value)
    {
        m_value = std::move(static_cast<T>(value*(1<<Point)));
        return *this;
    }

    template <typename I> requires std::is_integral_v<I>
    explicit operator I()
    {
        return static_cast<I>(m_value>>Point);
    }

    template <typename F> requires std::is_floating_point_v<F>
    explicit operator F()
    {
        return static_cast<F>(m_value)/static_cast<F>(1<<Point);
    }


    fixed operator + (const fixed& obj) {
        fixed<T,Point> res;
        res.m_value=m_value+obj.m_value;
        return res;
    }

    fixed operator - (const fixed& obj) {
        fixed<T,Point> res;
        res.m_value=m_value-obj.m_value;
        return res;
    }

    fixed operator * (const fixed& obj) 
    {
        //include unsinged
        fixed<T,Point> res;
        if constexpr(std::is_same_v<T,int8_t>)
        {           
            res.m_value=static_cast<int8_t>( (static_cast<int16_t>(obj.m_value)*static_cast<int16_t>(m_value)) >>Point);            
        }
        if constexpr(std::is_same_v<T,int16_t>)
        {
            res.m_value=static_cast<int16_t>( (static_cast<int32_t>(obj.m_value)*static_cast<int32_t>(m_value)) >>Point);
        }
        if constexpr(std::is_same_v<T,int32_t>)
        {
            res.m_value=static_cast<int32_t>( (static_cast<int64_t>(obj.m_value)*static_cast<int64_t>(m_value)) >>Point);
        }
        if constexpr(std::is_same_v<T,int64_t>)
        {
            //handle overflow error or give warning
        }
        return res;
    }

    fixed operator / (const fixed& obj) 
    {
        //include unsinged
        fixed<T,Point> res;
        if constexpr(std::is_same_v<T,int8_t>)
        {           
            res.m_value=static_cast<int8_t>( (static_cast<int16_t>(m_value)<<Point) / static_cast<int16_t>(obj.m_value));            
        }
        if constexpr(std::is_same_v<T,int16_t>)
        {
            res.m_value=static_cast<int16_t>( (static_cast<int32_t>(m_value)<<Point) / static_cast<int32_t>(obj.m_value));
        }
        if constexpr(std::is_same_v<T,int32_t>)
        {
            res.m_value=static_cast<int32_t>( (static_cast<int64_t>(m_value)<<Point) / static_cast<int64_t>(obj.m_value));
        }
        if constexpr(std::is_same_v<T,int64_t>)
        {
            //handle overflow error or give warning
        }
        return res;
    }

    [[nodiscard]] static constexpr double range() noexcept
    {
        //TODO correct calculation for singed unsigned
        return (1<<(sizeof(T)*8-Point-1))-1;
    }

    [[nodiscard]] static constexpr double precision() noexcept
    {
        return 1.0/(1<<Point);
    }

    private:
    void ConstructorBase()
    {
        static_assert(Point<(sizeof(T)*8));
    }
    T m_value = 0;
};
