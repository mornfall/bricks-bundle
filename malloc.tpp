#include "brick-malloc"
#include "brick-unit"
#include <set>

int main()
{
    using namespace brq::mm;

    brq::test_case( "parts" ) = []
    {
        ptr< void > b( from_parts( 1, 7, 13 ) );
        ASSERT_EQ( b.s_group(), 7 );
        ASSERT_EQ( b.a_group(), 1 );
        ASSERT_EQ( b, ptr< void >( b.get() ) );
    };

    brq::test_case( "size" ) = []
    {
        for ( int i = 1; i < 8 * 1024 * 1024 + 10; ++i )
        {
            int a = i <= 1024       ? 4 :
                    i <= 4096       ? 16 :
                    i <= 32 * 1024  ? 128 :
                    i <= 512 * 1024 ? 2048 :
                    i <= 8192 * 1024 ? 32 * 1024 : 512 * 1024;

            ptr< void > p( from_size( i ) );
            ASSERT_EQ( brq::align( i, a ), p.size(), p );
        }

        int max = 128 * 1024 * 1024;
        ptr< void > p( from_size( max ) );
        ASSERT_EQ( max, p.size(), p );
    };

    brq::test_case( "from_ptr index 0" ) = []
    {
        for ( int i = 1; i < 8 * 1024 * 1024 + 10; ++i )
        {
            ptr< void > p( from_size( i ) );
            ptr< void > q( p.get() );
            ASSERT_EQ( p, q );
        }
    };

    brq::test_case( "from_ptr" ) = []
    {
        for ( int a = 1; a < 6; ++a )
            for ( int s : { 0, 1, 2, 3, 4, 7, 8, 9, 15, 16, 17, 255, 256 } )
                for ( int idx : { 0, 1, 2, 3, 4, 1023, 1024, 1025, 10 * 1024, 16 * 1204, 16 * 1024 + 1 } )
                {
                    if ( idx * size( a, s ) >= 1ull << 36 )
                        continue;

                    ptr< void > p( from_parts( a, s, idx ) );
                    ASSERT_EQ( p, ptr< void >( p.get() ) );
                }
    };

    brq::test_case( "alloc free alloc" ) = []
    {
        int *y = brq::malloc< int >();
        *y = 7;
        brq::free( y );
        int *z = brq::malloc< int >();
        ASSERT_EQ( y, z );
    };

    brq::test_case( "alloc free alloc many" ) = []
    {
        const int count = 512 * 1024;
        int **ptrs = brq::malloc< int * >( count );
        std::set< int * > used;

        for ( int i = 0; i < count; ++i )
        {
            auto ptr = ptrs[ i ] = brq::malloc< int >();
            *ptr = i;
            ASSERT( !used.count( ptr ) );
            used.insert( ptr );
        }

        for ( int i = 15; i < count; i += 33 )
        {
            brq::free( ptrs[ i ] );
            used.erase( ptrs[ i ] );
            ptrs[ i ] = nullptr;
        }

        for ( int i = 0; i < count; ++i )
            if ( !ptrs[ i ] )
            {
                auto ptr = ptrs[ i ] = brq::malloc< int >();
                *ptr = i;
                ASSERT( !used.count( ptr ) );
                used.insert( ptr );
            }

        for ( int i = 0; i < count; ++i )
            ASSERT_EQ( *ptrs[ i ], i );
    };
}
