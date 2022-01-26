#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE DynamicStringArrayTests
#include <boost/test/unit_test.hpp>
#include "DynamicStringArray.hpp"

BOOST_AUTO_TEST_SUITE( DynamicStringArrayTests)

BOOST_AUTO_TEST_CASE( addEntry_getEntryTest ) 
{
    DynamicStringArray obj;
    obj.addEntry ( "Ana" );
    obj.addEntry ( "are" );
    obj.addEntry ( "mere" );
    BOOST_CHECK ( obj.getEntry(2)->compare("mere") == 0 );
}

BOOST_AUTO_TEST_CASE ( deleteEntryTest )
{
    DynamicStringArray obj;
    obj.addEntry ( "Ana" );
    obj.addEntry ( "are" );
    obj.addEntry ( "mere" );
    BOOST_CHECK_MESSAGE ( (obj.deleteEntry ( "mere" ) != true && obj.getLength() !=2 ), 
                         "Deletion failed for " << *obj.getEntry(2) ) ;
}

BOOST_AUTO_TEST_CASE( getEntryTest )
{
    DynamicStringArray obj1, obj2 ;
    obj1.addEntry ( "Ana" );
    obj1.addEntry ( "are" );
    if ( obj1.getEntry(2) -> compare ( "Ana") != 0 )
        BOOST_ERROR ( "Index is out of bounds." ) ;
}

BOOST_AUTO_TEST_CASE( getLengthTest )
{
    DynamicStringArray obj;
    int length = 0 ;
    obj.addEntry ( "Ana" );
    obj.addEntry ( "are" );
    obj.addEntry ( "mere" );
    BOOST_CHECK( obj.getLength() == 3 );
    obj.addEntry ( "mere" );
    BOOST_CHECK( obj.getLength() == 4 );
}

BOOST_AUTO_TEST_CASE( copyConstructorTest )
{
    DynamicStringArray obj;
    obj.addEntry( "Ana" );
    DynamicStringArray objCopy1;
    objCopy1= obj;
    if(obj.getLength() != objCopy1.getLength() )
        BOOST_FAIL( "Copy not done correctly" );

    DynamicStringArray objCopy2;
    obj.addEntry ( "are" );
    obj.addEntry ( "mere" );
    objCopy2 = obj;
    if(objCopy2.getLength() == obj.getLength() ) {
        for( int i = 0 ; i < objCopy2.getLength() ; i++ ) 
            if( objCopy2.getEntry (i) != obj.getEntry (i) ) {
                BOOST_FAIL( "Copy not done correctly" ); 
                break;
                }
    } 
}

BOOST_AUTO_TEST_CASE( overloadAssignmentTest )
{
    DynamicStringArray obj1, obj2;
    obj1.addEntry ( "Ana" );
    obj2.addEntry ( "mere" );
    obj1 = obj2;
    BOOST_CHECK( obj1.getLength() == obj2.getLength() );
}

BOOST_AUTO_TEST_CASE( defaultConstructorTest )
{
    DynamicStringArray obj;
    if(obj.getLength()!=0 && obj.getEntry(0) != nullptr )
        BOOST_FAIL( "Initialization failed" );
}

BOOST_AUTO_TEST_SUITE_END()