#pragma once


#include "godot_cpp/variant/string.hpp"
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/random_number_generator.hpp> 

class Seed : public godot::RefCounted 
{
    GDCLASS(Seed, godot::RefCounted)

public:
    enum CharType {
        NUMBER,
        CAPITAL,
        LOWER
    };

    enum SeedType {
        NUMBERS,
        CAPITAL_ONLY,
        LOWER_ONLY,
        ALL_LETTERS,
        ALL_MIXED
    };
    
    static godot::String generate_seed_string(SeedType seed_type = ALL_MIXED, int max_seed_length = 12);

protected:
    static void _bind_methods();

private:
    godot::String rng_seed;

    godot::String get_rng_seed() const;
    void set_rng_seed(const godot::String &new_seed);

    static godot::Array get_char_types(SeedType seed_type);
    static godot::String get_char(CharType type, godot::Ref<godot::RandomNumberGenerator> aux_rng);
};