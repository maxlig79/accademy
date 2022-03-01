#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE DynamicArrayTests
#include <boost/test/unit_test.hpp>
#include "DynamicArray.hpp"

BOOST_AUTO_TEST_SUITE( DynamicArrayTests)

BOOST_AUTO_TEST_CASE( addEntry_getEntryTest ) 
{
    DynamicArray <std::string > obj;
    obj.addEntry ( "Ana" );
    obj.addEntry ( "are" );
    obj.addEntry ( "mere" );
    BOOST_CHECK ( obj.getEntry(2)->compare("mere") == 0 );
}

BOOST_AUTO_TEST_CASE ( deleteEntryTest )
{
    DynamicArray <std::string > obj;
    obj.addEntry ( "Ana" );
    obj.addEntry ( "are" );
    obj.addEntry ( "mere" );
    BOOST_CHECK_MESSAGE ( (obj.deleteEntry ( "mere" ) != true && obj.getLength() !=2 ), 
                         "Deletion failed for " << *obj.getEntry(2) ) ;
}

BOOST_AUTO_TEST_CASE( getEntryTest )
{
    DynamicArray <std::string > obj1, obj2 ;
    obj1.addEntry ( "Ana" );
    obj1.addEntry ( "are" );
    if ( obj1.getEntry(2) == nullptr )
        BOOST_ERROR ( "Index is out of bounds." ) ;
}

BOOST_AUTO_TEST_CASE( getLengthTest )
{
    DynamicArray <std::string > obj;
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
    DynamicArray <std::string > obj ;
    obj.addEntry( "Ana" ) ;
    obj.addEntry ( "are" ) ;
    obj.addEntry ( "mere" ) ;
    DynamicArray <std::string > objCopy ;
    objCopy= obj ; 
    BOOST_CHECK (objCopy.getLength() == obj.getLength() ) ;
    for( int i = 0; i < objCopy.getLength(); i++ )
        BOOST_CHECK (*objCopy.getEntry(i) == *obj.getEntry(i)) ;
}

BOOST_AUTO_TEST_CASE( overloadAssignmentTest )
{
    DynamicArray <std::string > obj1, obj2;
    obj1.addEntry ( "Ana" );
    obj2.addEntry ( "mere" );
    obj1 = obj2;
    BOOST_CHECK( obj1.getLength() == obj2.getLength() );
}

BOOST_AUTO_TEST_CASE( defaultConstructorTest )
{
    DynamicArray <std::string > obj;
    if(obj.getLength()!=0 && obj.getEntry(0) != nullptr )
        BOOST_FAIL( "Initialization failed" );
}

BOOST_AUTO_TEST_CASE( ContainerConstructorTest )
{
    DynamicArray <std::string > obj (     DynamicArray <std::string >  ( std::vector<std::string > {"Ana", "are", "mere"} ) ) ;
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

BOOST_AUTO_TEST_CASE( MoveOperationsTest )
{
    std::vector<std::string> str {"Radu", "are", "masina"};
    DynamicArray <std::string > obj1 (str) ;
    DynamicArray <std::string > objMove ( std::move(obj1) ) ;

    BOOST_CHECK ( objMove.getLength() ==3 );
    BOOST_CHECK( *objMove.getEntry(0) == "Radu" ) ;
    BOOST_CHECK( *objMove.getEntry(1) == "are" ) ;
    BOOST_CHECK( *objMove.getEntry(2) == "masina" ) ;
    
    DynamicArray <std::string > obj2( DynamicArray <std::string > (std::vector<std::string> {"Ana", "are", "mere"} ) ) ;
    DynamicArray <std::string > objMAO;
    objMAO = std::move (obj2);
    BOOST_CHECK ( objMAO.getLength() ==3 );
    BOOST_CHECK( *objMAO.getEntry(0) == "Ana" ) ;
    BOOST_CHECK( *objMAO.getEntry(1) == "are" ) ;
    BOOST_CHECK( *objMAO.getEntry(2) == "mere" ) ;
}

BOOST_AUTO_TEST_SUITE_END()