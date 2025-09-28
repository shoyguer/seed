@tool
class_name RNG
extends RefCounted
## Random Number Generator utility class with static functions for seeded randomization.
##
## This class provides a centralized way to handle RNG with consistent seeding across the game.


#region Variables
## Character type constants
enum {
	## Number character type
	NUMBER,
	## Capital alphabet character type
	CAPITAL_ALPHABET,
	## Lower alphabet character type
	LOWER_ALPHABET,
}

## Defines the type of characters to use in seed generation.
enum SeedType {
	## Only numbers (0-9)
	NUMBERS,
	## Only capital letters (A-Z)
	CAPITAL_ONLY,
	## Only lowercase letters (a-z)
	LOWER_ONLY,
	## Both capital and lowercase letters (A-Z, a-z)
	ALL_LETTERS,
	## Numbers, capital and lowercase letters mixed (0-9, A-Z, a-z)
	ALL_MIXED
}

static var rng: RandomNumberGenerator = null
static var rng_seed: String = ""
#endregion


#region RNG Functions
## Generates a new random number generator (RNG) with a seed.
## [param new_seed] The seed to use for the RNG. If empty, a new seed will be generated.
## [param seed_type] The type of characters to use in seed generation.
## [param max_seed_length] The maximum number of characters in the generated seed.
static func generate_rng(
	new_seed: String = "",
	seed_type: SeedType = SeedType.ALL_MIXED,
	max_seed_length: int = 12
) -> void:
	var final_seed: String = ""
	
	# If no seed is provided, generate a new one.
	if new_seed == "":
		final_seed = generate_seed_string(seed_type, max_seed_length)
	# If seed provided, set it to final_seed.
	else:
		final_seed = new_seed
	
	rng_seed = final_seed

	_rng_hash(final_seed)


## Hashes the given seed and sets it to the [member rng].
## [param new_seed] The seed to hash and set.
static func _rng_hash(new_seed: String) -> void:
	rng = RandomNumberGenerator.new()
	rng.seed = hash(new_seed)


## Generates a random multi-purpose RNG seed based on the provided parameters.
## [param seed_type] The type of characters to use in seed generation.
## [param max_seed_length] The maximum number of characters in the generated seed.
static func generate_seed_string(seed_type: SeedType = SeedType.ALL_MIXED, max_seed_length: int = 12) -> String:
	var new_seed: String = ""

	var aux_rng := RandomNumberGenerator.new()
	aux_rng.randomize()
	
	for i in range(max_seed_length):
		var char_types: Array[int] = _get_available_char_types(seed_type)
		var type: int = char_types[aux_rng.randi_range(0, char_types.size() - 1)]
		new_seed += _get_string_char(type, aux_rng)

	return new_seed


## Returns the available character types based on the provided seed_type.
## [param seed_type] The type of characters to use in seed generation.
static func _get_available_char_types(seed_type: SeedType) -> Array[int]:
	var types: Array[int] = []
	
	match seed_type:
		SeedType.NUMBERS:
			types = [NUMBER]
		SeedType.CAPITAL_ONLY:
			types = [CAPITAL_ALPHABET]
		SeedType.LOWER_ONLY:
			types = [LOWER_ALPHABET]
		SeedType.ALL_LETTERS:
			types = [CAPITAL_ALPHABET, LOWER_ALPHABET]
		SeedType.ALL_MIXED:
			types = [NUMBER, CAPITAL_ALPHABET, LOWER_ALPHABET]
	
	return types


## Returns a random char of the given type.
## [param type] The type of character to generate (NUMBER, CAPITAL_ALPHABET, LOWER_ALPHABET).
## [param aux_rng] The auxiliary RNG to use for generating the character.
static func _get_string_char(type: int, aux_rng: RandomNumberGenerator) -> String:
	var string_char: String = ""
	match type:
		NUMBER:
			string_char = String.chr(aux_rng.randi_range(48, 57)) # UNICODE 0-9
		
		CAPITAL_ALPHABET:
			string_char = String.chr(aux_rng.randi_range(65, 90)) # UNICODE A-Z
		
		LOWER_ALPHABET:
			string_char = String.chr(aux_rng.randi_range(97, 122)) # UNICODE a-z
	
	return string_char
#endregion
