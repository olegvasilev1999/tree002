#include <catch.hpp>
#include "queue.cpp"

TEST_CASE("insert")
{
  std::string input{
      "------------14\n"
      "--------12\n"
      "------------11\n"
      "----10\n"
      "------------9\n"
      "--------7\n"
      "------------6\n"
      "--------------------4\n"
      "----------------3\n"};
  tree_t<int> Tree;
  
  Tree.insert(10);
  Tree.insert(12);
  Tree.insert(11);
  Tree.insert(14);
  Tree.insert(7);
  Tree.insert(9);
  Tree.insert(6);
  Tree.insert(3);
  Tree.insert(4);
  
  std::ostringstream ostream;
  Tree.print( ostream );
  
  REQUIRE( input == ostream.str() );
  
}

TEST_CASE("initializer_list")
{
   std::string input{
      "------------14\n"
      "--------12\n"
      "------------11\n"
      "----10\n"
      "------------9\n"
      "--------7\n"
      "------------6\n"
      "--------------------4\n"
      "----------------3\n"};
  tree_t<int> Tree{10,12,11,14,7,9,6,3,4};
  
  std::ostringstream ostream;
  Tree.print( ostream );
  
  REQUIRE( input == ostream.str() );
  
}

TEST_CASE("remove")
{
   std::string input{
      "------------14\n"
      "--------12\n"
      "------------11\n"
      "----10\n"
      "------------9\n"
      "--------7\n"
      "-----------------4\n"
      "-------------3\n"};
  tree_t<int> Tree{10,12,11,14,7,9,6,3,4};
  
  REQUIRE(Tree.remove(6) == 1);
  
  std::ostringstream ostream;
  Tree.print( ostream );
  
  REQUIRE( input == ostream.str() );
  
}

TEST_CASE("operator ==")
{
  tree_t<int> Tree1{10,12,11,14,7,9,6,3,4};
  tree_t<int> Tree2{10,12,11,14,7,9,6,3,4};
  
  REQUIRE( (Tree1 == Tree2) == true );
  
  Tree2.remove(6);
  
  REQUIRE( (Tree1 == Tree2) == false );
}

TEST_CASE("find")
{
  tree_t<int> Tree{10,12,11,14,7,9,6,3,4};
  
  REQUIRE( (Tree.find(6);) == true );
  REQUIRE( (Tree.find(1);) == false );
}

