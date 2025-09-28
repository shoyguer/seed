#pragma once


#include <godot_cpp/classes/ref_counted.hpp> 

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
    //
protected:
    static void _bind_methods();
private:
    //
};