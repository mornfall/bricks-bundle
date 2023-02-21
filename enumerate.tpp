#include <iostream>
#include <iomanip>
#include "brick-unit"
#include "brick-nat"
#include "brick-enumerate"

int main()
{
    using tup_2 = std::tuple< brq::nat, brq::nat >;
    using tup_3 = std::tuple< brq::nat, brq::nat, brq::nat >;
    using list  = std::vector< brq::nat >;
    using set   = std::set< brq::nat >;

    std::vector< tup_2 > tup_2_order =
    {
        { 0, 0 },
        { 0, 1 }, { 1, 0 }, { 1, 1 },
        { 0, 2 }, { 1, 2 }, { 2, 0 }, { 2, 1 }, { 2, 2 }
    };

    std::vector< list > list_order =
    {
        {},
        { 0 },
        { 1 }, { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 },
        { 2 }, { 0, 2 }, { 1, 2 }, { 2, 0 }, { 2, 1 }, { 2, 2 },
               { 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 }, { 0, 1, 1 },
               { 1, 0, 0 }, { 1, 1, 0 }, { 1, 0, 1 }, { 1, 1, 1 },
               { 0, 0, 2 }, { 1, 0, 2 }, { 0, 1, 2 }, { 1, 1, 2 },
               { 0, 2, 0 }, { 1, 2, 0 }, { 0, 2, 1 }, { 1, 2, 1 },
               { 0, 2, 2 }, { 1, 2, 2 }, { 2, 0, 0 }, { 2, 1, 0 },
               { 2, 2, 0 }, { 2, 0, 1 }, { 2, 1, 1 }, { 2, 2, 1 },
               { 2, 0, 2 }, { 2, 1, 2 }, { 2, 2, 2 },
        { 3 }, { 0, 3 }, { 1, 3 }, { 2, 3 }, { 3, 0 }, { 3, 1 }, { 3, 2 }, { 3, 3 }
    };

    std::vector< set > set_order =
    {
        {}, { 0 }, { 1 }, { 0, 1 }, { 2 }, { 0, 2 }, { 1, 2 }, { 0, 1, 2 }
    };

    brq::test_case( "tuple" ) = [=]
    {
        int i = 0;

        for ( auto t : tup_2_order )
        {
            ASSERT_EQ( brq::tuple_enum< 2 >( i ), t, i );
            i ++;
        }
    };

    brq::test_case( "tuple bounded" ) = [=]
    {
        int i = 0;

        for ( auto t : tup_2_order )
        {
            ASSERT_EQ( brq::enumerate::tuple< 2 >( i, std::tuple( 3, 3 ) ), t, i );
            i ++;
        }
    };

    brq::test_case( "list" ) = [=]
    {
        int i = 0;

        for ( auto l : list_order )
        {
            ASSERT_EQ( l, brq::list_enum( i ), i );
            i ++;
        }
    };

    brq::test_case( "set" ) = [=]
    {
        int i = 0;

        for ( auto l : set_order )
        {
            ASSERT_EQ( l, brq::set_enum( i ), i );
            i ++;
        }
    };
}
