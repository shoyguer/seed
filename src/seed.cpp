#include "seed.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/object.hpp"
#include "godot_cpp/core/property_info.hpp"
#include "godot_cpp/variant/variant.hpp"


using namespace godot;

String Seed::generate_seed_string(SeedType seed_type, int max_seed_length)
{
    String new_seed = "";

    Ref<RandomNumberGenerator> aux_rng;
    aux_rng.instantiate();
    aux_rng->randomize();
    
    for (int i = 0; i < max_seed_length; i++) {
        Array char_types = get_char_types(seed_type);
        int type = char_types[aux_rng->randi_range(0, char_types.size() - 1)];
        new_seed += get_char(static_cast<CharType>(type), aux_rng);
    }

    return new_seed;
}

// Private methods
Array Seed::get_char_types(SeedType seed_type)
{
    Array types;
    
    switch (seed_type) {
        case NUMBERS:
            types.push_back(NUMBER);
            break;
        case CAPITAL_ONLY:
            types.push_back(CAPITAL);
            break;
        case LOWER_ONLY:
            types.push_back(LOWER);
            break;
        case ALL_LETTERS:
            types.push_back(CAPITAL);
            types.push_back(LOWER);
            break;
        case ALL_MIXED:
            types.push_back(NUMBER);
            types.push_back(CAPITAL);
            types.push_back(LOWER);
            break;
    }
    
    return types;
}

String Seed::get_char(CharType type, Ref<RandomNumberGenerator> aux_rng)
{
    String string_char = "";
    
    switch (type) {
        case NUMBER:
            // UNICODE 0-9 (48-57)
            string_char = String::chr(aux_rng->randi_range(48, 57));
            break;
        case CAPITAL:
            // UNICODE A-Z (65-90)
            string_char = String::chr(aux_rng->randi_range(65, 90));
            break;
        case LOWER:
            // UNICODE a-z (97-122)
            string_char = String::chr(aux_rng->randi_range(97, 122));
            break;
    }
    
    return string_char;
}

// Setgets
void Seed::set_rng_seed(const String &new_seed)
{
    rng_seed = new_seed;
}

String Seed::get_rng_seed() const
{
    return rng_seed;
}

// Bindings
void Seed::_bind_methods()
{
    ClassDB::bind_static_method("Seed", D_METHOD("generate_seed_string", "seed_type", "max_seed_length"), &Seed::generate_seed_string);

    ClassDB::bind_method(D_METHOD("set_rng_seed", "new_seed"), &Seed::set_rng_seed);
    ClassDB::bind_method(D_METHOD("get_rng_seed"), &Seed::get_rng_seed);

    ADD_PROPERTY(PropertyInfo(Variant::STRING, "rng_seed"), "set_rng_seed", "get_rng_seed");

    BIND_ENUM_CONSTANT(NUMBER);
    BIND_ENUM_CONSTANT(CAPITAL);
    BIND_ENUM_CONSTANT(LOWER);

    BIND_ENUM_CONSTANT(NUMBERS);
    BIND_ENUM_CONSTANT(CAPITAL_ONLY);
    BIND_ENUM_CONSTANT(LOWER_ONLY);
    BIND_ENUM_CONSTANT(ALL_LETTERS);
    BIND_ENUM_CONSTANT(ALL_MIXED);
}

VARIANT_ENUM_CAST(Seed::CharType);
VARIANT_ENUM_CAST(Seed::SeedType);