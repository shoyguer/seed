#include "seed.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/object.hpp"
#include "godot_cpp/core/property_info.hpp"


using namespace godot;

VARIANT_ENUM_CAST(Seed::CharType);
VARIANT_ENUM_CAST(Seed::SeedType);

void Seed::_bind_methods()
{
    BIND_ENUM_CONSTANT(NUMBER);
    BIND_ENUM_CONSTANT(CAPITAL);
    BIND_ENUM_CONSTANT(LOWER);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "char_type", PROPERTY_HINT_ENUM, "Number, Capital, Lower"), "set_char_type", "get_char_type");

    BIND_ENUM_CONSTANT(NUMBERS);
    BIND_ENUM_CONSTANT(CAPITAL_ONLY);
    BIND_ENUM_CONSTANT(LOWER_ONLY);
    BIND_ENUM_CONSTANT(ALL_LETTERS);
    BIND_ENUM_CONSTANT(ALL_MIXED);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "seed_type", PROPERTY_HINT_ENUM, "Numbers, Capital Only, Lower Only, All Letters, All Mixed"), "set_seed_type", "get_seed_type");
}
