// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Jule Schatz                    Environment : ubuntu:bionic               //
//  Date ......: 2023/12/29                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"
#include <vector>

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "group.hpp"
#include "volunteer.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

// Volunteer Class Test

TEST_CASE("Volunteer Class : GetName", "[volunteer-name]") {
  Volunteer v1("volunteer_1", 1, 1, 1);
  REQUIRE(v1.GetName() == "volunteer_1");
}

TEST_CASE("Volunteer Class : GetBuildingExperience",
          "[volunteer-building-experience]") {
  Volunteer v1("volunteer_1", 5, 2, 1);
  REQUIRE(v1.GetBuildingExperience() == 5);
}

TEST_CASE("Volunteer Class : GetPhysicalStamina",
          "[volunteer-physical-stamina]") {
  Volunteer v1("volunteer_1", 5, 2, 1);
  REQUIRE(v1.GetPhysicalStamina() == 2);
}

TEST_CASE("Volunteer Class : IsReturning", "[volunteer-returning]") {
  Volunteer v1("volunteer_1", 5, 5, 1);
  REQUIRE(v1.IsReturning() == true);

  Volunteer v2("volunteer_2", 5, 5, 0);
  REQUIRE(v2.IsReturning() == false);
}

// Group Class Tests

TEST_CASE("Group Class : Constructor", "[group-constructor]") {
  Group g = Group();
  REQUIRE(g.GetAvgBuildingExp() == 0);
  REQUIRE(g.GetAvgStamina() == 0);
  REQUIRE(g.GetReturningMembers() == 0);
}

TEST_CASE("Group Class : Add 1 Volunteer", "[group-add-one-volunteer]") {
  Group g = Group();
  Volunteer v1("volunteer_1", 10, 8, 1);
  g.AddVolunteer(v1);

  REQUIRE(g.GetAvgBuildingExp() == 10);
  REQUIRE(g.GetAvgStamina() == 8);
  REQUIRE(g.GetReturningMembers() == 1);
}

TEST_CASE("Group Class : Average Building Experience Basic",
          "[group-average-building-experience-basic]") {
  Group g = Group();
  Volunteer v1("volunteer_1", 10, 8, 1);
  Volunteer v2("volunteer_2", 2, 5, 0);
  g.AddVolunteer(v1);
  g.AddVolunteer(v2);

  REQUIRE(g.GetAvgBuildingExp() == 6);
}

TEST_CASE("Group Class : Average Physical Stamina Basic",
          "[group-average-physical-stamina-basic]") {
  Group g = Group();
  Volunteer v1("volunteer_1", 10, 8, 1);
  Volunteer v2("volunteer_2", 2, 5, 0);
  g.AddVolunteer(v1);
  g.AddVolunteer(v2);

  REQUIRE(g.GetAvgStamina() == (13.0) / 2);
}

TEST_CASE("Group Class : Returning Basic", "[group-returning-basic]") {
  Group g = Group();
  Volunteer v1("volunteer_1", 10, 8, 0);
  Volunteer v2("volunteer_2", 2, 5, 0);
  g.AddVolunteer(v1);
  g.AddVolunteer(v2);

  REQUIRE(g.GetReturningMembers() == 0);
}

TEST_CASE("Group Class : << operator", "[group-output]") {
  Group g = Group();
  std::ostringstream os;

  // It's just making sure this compiles and doesn't crash
  os << g;
}

TEST_CASE("Group Class : Random Volunteer", "[group-random]") {
  Group g = Group();
  Volunteer v1("volunteer_1", 10, 8, 0);
  Volunteer v2("volunteer_2", 10, 8, 0);
  Volunteer v3("volunteer_3", 10, 8, 0);

  g.AddVolunteer(v1);
  g.AddVolunteer(v2);
  g.AddVolunteer(v3);

  Volunteer randVol = g.GetRandomVolunteer();
}

/////////////////////////////////////////////////////////////////////////////////////////////