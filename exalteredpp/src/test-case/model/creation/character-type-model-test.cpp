#include "../thirdparty/catch/catch.hpp"

#include "creation/character_type_model.h"

TEST_CASE("Character type model")
{
  SECTION("should map each type of character to a model")
  {
    for (auto char_type : character::creation::CHARACTER_TYPE_LIST)
      {
        REQUIRE_NOTHROW(character::creation::character_type_model::get_by_character_type(char_type));
      }
  }

  SECTION("should assign model correctly with copy operator and assignment operator")
  {
    auto stub = character::creation::character_type_model::get_by_character_type(character::creation::TYPE_SOLAR_EXALT);

    auto sut_1(stub);
    auto sut_2 = character::creation::character_type_model::get_by_character_type(character::creation::TYPE_MORTAL_HERO);
    sut_2 = stub;

    REQUIRE(sut_1.primary_category_attribute_value          == stub.primary_category_attribute_value        );
    REQUIRE(sut_1.secondary_category_attribute_value        == stub.secondary_category_attribute_value      );
    REQUIRE(sut_1.tertiary_category_attribute_value         == stub.tertiary_category_attribute_value       );
    REQUIRE(sut_1.starting_ability_points                   == stub.starting_ability_points                 );
    REQUIRE(sut_1.max_std_ability_points_on_creation        == stub.max_std_ability_points_on_creation      );
    REQUIRE(sut_1.max_ability_points_on_creation            == stub.max_ability_points_on_creation          );
    REQUIRE(sut_1.min_ability_points_on_favorite_abilities  == stub.min_ability_points_on_favorite_abilities);
    REQUIRE(sut_1.favored_abilities                         == stub.favored_abilities                       );
    REQUIRE(sut_1.caste_abilities                           == stub.caste_abilities                         );
    REQUIRE(sut_1.starting_specialisations                  == stub.starting_specialisations                );
    REQUIRE(sut_1.starting_permanent_essence                == stub.starting_permanent_essence              );
    REQUIRE(sut_1.starting_darkana                          == stub.starting_darkana                        );
    REQUIRE(sut_1.starting_virtue_points                    == stub.starting_virtue_points                  );
    REQUIRE(sut_1.max_std_virtue_points                     == stub.max_std_virtue_points                   );
    REQUIRE(sut_1.max_virtue_points                         == stub.max_virtue_points                       );
    REQUIRE(sut_1.starting_background_points                == stub.starting_background_points              );
    REQUIRE(sut_1.starting_bonus_points                     == stub.starting_bonus_points                   );
    REQUIRE(sut_1.starting_charms                           == stub.starting_charms                         );

    REQUIRE(sut_2.primary_category_attribute_value          == stub.primary_category_attribute_value        );
    REQUIRE(sut_2.secondary_category_attribute_value        == stub.secondary_category_attribute_value      );
    REQUIRE(sut_2.tertiary_category_attribute_value         == stub.tertiary_category_attribute_value       );
    REQUIRE(sut_2.starting_ability_points                   == stub.starting_ability_points                 );
    REQUIRE(sut_2.max_std_ability_points_on_creation        == stub.max_std_ability_points_on_creation      );
    REQUIRE(sut_2.max_ability_points_on_creation            == stub.max_ability_points_on_creation          );
    REQUIRE(sut_2.min_ability_points_on_favorite_abilities  == stub.min_ability_points_on_favorite_abilities);
    REQUIRE(sut_2.favored_abilities                         == stub.favored_abilities                       );
    REQUIRE(sut_2.caste_abilities                           == stub.caste_abilities                         );
    REQUIRE(sut_2.starting_specialisations                  == stub.starting_specialisations                );
    REQUIRE(sut_2.starting_permanent_essence                == stub.starting_permanent_essence              );
    REQUIRE(sut_2.starting_darkana                          == stub.starting_darkana                        );
    REQUIRE(sut_2.starting_virtue_points                    == stub.starting_virtue_points                  );
    REQUIRE(sut_2.max_std_virtue_points                     == stub.max_std_virtue_points                   );
    REQUIRE(sut_2.max_virtue_points                         == stub.max_virtue_points                       );
    REQUIRE(sut_2.starting_background_points                == stub.starting_background_points              );
    REQUIRE(sut_2.starting_bonus_points                     == stub.starting_bonus_points                   );
    REQUIRE(sut_2.starting_charms                           == stub.starting_charms                         );
  }
}
