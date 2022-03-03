#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE DynamicArrayTests
#include <boost/test/unit_test.hpp>
#include "DynamicArray.hpp"

BOOST_AUTO_TEST_SUITE( DynamicArrayTests)
/*---------------------------------------------------
            Integer array tested
---------------------------------------------------*/

    BOOST_AUTO_TEST_CASE( Integer_addEntry_getEntryTest ) 
    {
        DynamicArray < int > obj;
        obj.addEntry ( 5 );
        obj.addEntry ( 6 );
        obj.addEntry ( 7 );
        BOOST_CHECK( *obj.getEntry(0) == 5 );
        BOOST_CHECK( *obj.getEntry(1) == 6 );
        BOOST_CHECK( *obj.getEntry(2) == 7 );
        BOOST_CHECK(  obj.getEntry(3) == nullptr );
    }

    BOOST_AUTO_TEST_CASE ( Integer_deleteEntry_getLengthTest )
    {
        DynamicArray < int> obj;
        obj.addEntry ( 1 );
        obj.addEntry ( 2 );
        obj.addEntry ( 3 );
        obj.deleteEntry ( 1 );
        BOOST_CHECK( *obj.getEntry(0) == 2 );
        BOOST_CHECK(  obj.getLength() == 2 );
        BOOST_CHECK(  obj.deleteEntry ( 9 ) == false);

    }

    BOOST_AUTO_TEST_CASE( Integer_copyConstructorTest )
    {
        DynamicArray < int > obj ;
        obj.addEntry( 1 ) ;
        obj.addEntry ( 3 ) ;
        obj.addEntry ( 5 ) ;
        DynamicArray < int > objCopy ;
        objCopy= obj ; 
        BOOST_CHECK (objCopy.getLength() == obj.getLength() ) ;
        for( int i = 0; i < objCopy.getLength(); i++ )
            BOOST_CHECK (*objCopy.getEntry(i) == *obj.getEntry(i)) ;
    }

    BOOST_AUTO_TEST_CASE( Integer_overloadAssignmentTest )
    {
        DynamicArray < int > obj1, obj2;
        obj1.addEntry ( 4 );
        obj1.addEntry ( 5 );
        obj2.addEntry ( 8 );
        obj1 = obj2;
        BOOST_CHECK( obj1.getLength() == obj2.getLength() );
    }

    BOOST_AUTO_TEST_CASE( Integer_defaultConstructorTest )
    {
        DynamicArray < int > obj;
        if(obj.getLength()!=0 && obj.getEntry(0) != nullptr )
            BOOST_FAIL( "Initialization failed" );
    }

    BOOST_AUTO_TEST_CASE( Integer_ContainerConstructorTest )
    {
        DynamicArray < int > obj (     DynamicArray < int >  ( std::vector< int > { 2, 4 , 6 } ) ) ;
        if( obj.getLength() == 3 ){
            BOOST_CHECK_MESSAGE ( *obj.getEntry(0) == 2 , 
                                "Container Constructor succesful for  " << *obj.getEntry(0) ) ;
            BOOST_CHECK_MESSAGE ( *obj.getEntry(1) == 4 , 
                                "Container Constructor succesful for  " << *obj.getEntry(1) ) ;
            BOOST_CHECK_MESSAGE ( *obj.getEntry(2) == 6 , 
                                "Container Constructor succesful for  " << *obj.getEntry(2) ) ; 
        } else {
            BOOST_FAIL ( "Initialization failed" ) ;
        }
    }

    BOOST_AUTO_TEST_CASE( Integer_MoveOperationsTest )
    {
        std::vector< int > obj { 1, 2, 3};
        DynamicArray < int > obj1 (obj) ;
        DynamicArray < int > objMove ( std::move(obj1) ) ;

        BOOST_CHECK ( objMove.getLength() ==3 );
        BOOST_CHECK( *objMove.getEntry(0) == 1 ) ;
        BOOST_CHECK( *objMove.getEntry(1) == 2 ) ;
        BOOST_CHECK( *objMove.getEntry(2) == 3 ) ;
        
        DynamicArray < int > obj2( DynamicArray < int > (std::vector< int > { 4 , 5 , 6 } ) ) ;
        DynamicArray < int  > objMAO;
        objMAO = std::move (obj2);
        BOOST_CHECK ( objMAO.getLength() ==3 );
        BOOST_CHECK( *objMAO.getEntry(0) == 4 ) ;
        BOOST_CHECK( *objMAO.getEntry(1) == 5 ) ;
        BOOST_CHECK( *objMAO.getEntry(2) == 6 ) ;
    }

/*---------------------------------------------------
            String array tested
---------------------------------------------------*/

    BOOST_AUTO_TEST_CASE( String_addEntry_getEntryTest ) 
    {
        DynamicArray < std::string > obj;
        obj.addEntry ( "Ana" );
        obj.addEntry ( "are" );
        obj.addEntry ( "mere" );
        BOOST_CHECK ( obj.getEntry(2)->compare("mere") == 0 );
    }

    BOOST_AUTO_TEST_CASE ( String_deleteEntryTest )
    {
        DynamicArray < std::string > obj;
        obj.addEntry ( "Ana" );
        obj.addEntry ( "are" );
        obj.addEntry ( "mere" );
        BOOST_CHECK_MESSAGE ( (obj.deleteEntry ( "mere" ) != true && obj.getLength() !=2 ), 
                            "Deletion failed for " << *obj.getEntry(2) ) ;
    }

    BOOST_AUTO_TEST_CASE( String_getEntryTest )
    {
        DynamicArray < std::string > obj1, obj2 ;
        obj1.addEntry ( "Ana" );
        obj1.addEntry ( "are" );
        BOOST_CHECK ( obj1.getEntry(2) == nullptr );
    }

    BOOST_AUTO_TEST_CASE( String_getLengthTest )
    {
        DynamicArray < std::string > obj;
        int length = 0 ;
        obj.addEntry ( "Ana" );
        obj.addEntry ( "are" );
        obj.addEntry ( "mere" );
        BOOST_CHECK( obj.getLength() == 3 );
        obj.addEntry ( "mere" );
        BOOST_CHECK( obj.getLength() == 4 );
    }

    BOOST_AUTO_TEST_CASE( String_copyConstructorTest )
    {
        DynamicArray <std::string > obj ;
        obj.addEntry( "Ana" ) ;
        obj.addEntry ( "are" ) ;
        obj.addEntry ( "mere" ) ;
        DynamicArray < std::string > objCopy ;
        objCopy= obj ; 
        BOOST_CHECK (objCopy.getLength() == obj.getLength() ) ;
        for( int i = 0; i < objCopy.getLength(); i++ )
            BOOST_CHECK (*objCopy.getEntry(i) == *obj.getEntry(i)) ;
    }

    BOOST_AUTO_TEST_CASE( String_overloadAssignmentTest )
    {
        DynamicArray < std::string > obj1, obj2;
        obj1.addEntry ( "Ana" );
        obj2.addEntry ( "mere" );
        obj1 = obj2;
        BOOST_CHECK( obj1.getLength() == obj2.getLength() );
    }

    BOOST_AUTO_TEST_CASE( String_defaultConstructorTest )
    {
        DynamicArray < std::string > obj;
        if(obj.getLength()!=0 && obj.getEntry(0) != nullptr )
            BOOST_FAIL( "Initialization failed" );
    }

    BOOST_AUTO_TEST_CASE( String_ContainerConstructorTest )
    {
        DynamicArray < std::string > obj (     DynamicArray < std::string >  ( std::vector< std::string > {"Ana", "are", "mere"} ) ) ;
        if( obj.getLength() == 3 ){
            BOOST_CHECK_MESSAGE ( *obj.getEntry(0) == "Ana" , 
                                "Container Constructor succesful for  " << *obj.getEntry(0) ) ;
            BOOST_CHECK_MESSAGE ( *obj.getEntry(1) == "are" , 
                                "Container Constructor succesful for  " << *obj.getEntry(1) ) ;
            BOOST_CHECK_MESSAGE ( *obj.getEntry(2) == "mere" , 
                                "Container Constructor succesful for  " << *obj.getEntry(2) ) ; 
        } else {
            BOOST_FAIL ( "Initialization failed" ) ;
        }
    }

    BOOST_AUTO_TEST_CASE( String_MoveOperationsTest )
    {
        std::vector< std::string> str {"Radu", "are", "masina"};
        DynamicArray < std::string > obj1 (str) ;
        DynamicArray < std::string > objMove ( std::move(obj1) ) ;

        BOOST_CHECK ( objMove.getLength() ==3 );
        BOOST_CHECK( *objMove.getEntry(0) == "Radu" ) ;
        BOOST_CHECK( *objMove.getEntry(1) == "are" ) ;
        BOOST_CHECK( *objMove.getEntry(2) == "masina" ) ;
        
        DynamicArray < std::string > obj2( DynamicArray < std::string > (std::vector< std::string> {"Ana", "are", "mere"} ) ) ;
        DynamicArray < std::string > objMAO;
        objMAO = std::move (obj2);
        BOOST_CHECK ( objMAO.getLength() ==3 );
        BOOST_CHECK( *objMAO.getEntry(0) == "Ana" ) ;
        BOOST_CHECK( *objMAO.getEntry(1) == "are" ) ;
        BOOST_CHECK( *objMAO.getEntry(2) == "mere" ) ;
    }

BOOST_AUTO_TEST_SUITE_END()