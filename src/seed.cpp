#include "seed.hpp"
#include "godot_cpp/core/class_db.hpp"
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

Ref<RandomNumberGenerator> Seed::generate_rng(const String &new_seed, SeedType seed_type, int max_seed_length)
{
    String final_seed = "";
    
    // If no seed is provided, generate a new one.
    if (new_seed == "") {
        final_seed = generate_seed_string(seed_type, max_seed_length);
    }
    // If seed provided, set it to final_seed.
    else {
        final_seed = new_seed;
    }
    
    // Create new RNG and hash the seed
    Ref<RandomNumberGenerator> new_rng;
    new_rng.instantiate();
    
    return rng_hash_seed(new_rng, final_seed);
}

Ref<RandomNumberGenerator> Seed::rng_hash_seed(Ref<RandomNumberGenerator> new_rng, const String &new_seed)
{
    if (new_rng.is_valid()) {
        new_rng->set_seed(new_seed.hash());
    }
    return new_rng;
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

// Bindings
void Seed::_bind_methods()
{
    ClassDB::bind_static_method("Seed", D_METHOD("generate_seed_string", "seed_type", "max_seed_length"), &Seed::generate_seed_string);
    ClassDB::bind_static_method("Seed", D_METHOD("generate_rng", "new_seed", "seed_type", "max_seed_length"), &Seed::generate_rng);
    ClassDB::bind_static_method("Seed", D_METHOD("rng_hash_seed", "new_rng", "new_seed"), &Seed::rng_hash_seed);

    BIND_ENUM_CONSTANT(NUMBERS);
    BIND_ENUM_CONSTANT(CAPITAL_ONLY);
    BIND_ENUM_CONSTANT(LOWER_ONLY);
    BIND_ENUM_CONSTANT(ALL_LETTERS);
    BIND_ENUM_CONSTANT(ALL_MIXED);
}

VARIANT_ENUM_CAST(Seed::SeedType);