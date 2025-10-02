extends Node2D
## Example script demonstrating the Seed plugin

func _ready() -> void:
	# Generate different types of seed strings
	print("Numbers only: ", Seed.generate_seed_string(Seed.NUMBERS, 8))
	print("Letters only: ", Seed.generate_seed_string(Seed.ALL_LETTERS, 10))
	print("Mixed chars: ", Seed.generate_seed_string(Seed.ALL_MIXED, 12))
	
	# Create RNG with custom seed
	var custom_seed = "MyGameWorld2024"
	var rng1 = Seed.generate_rng(custom_seed)
	print("Custom seed RNG: ", rng1.randi_range(1, 100))
	
	# Auto-generated seed RNG
	var rng2 = Seed.generate_rng("", Seed.ALL_MIXED, 12)
	print("Auto seed RNG: ", rng2.randf())
	
	# Demonstrate reproducible randomization
	print("\n___\nReproducible test:")
	var test_seed = "TestSeed123"
	var rng_a = Seed.generate_rng(test_seed)
	var rng_b = Seed.generate_rng(test_seed)
	print("Same seed, same results: ", rng_a.randf() == rng_b.randf())
	
	# Simple procedural generation
	print("\n___\nProcedural world:")
	var world_rng = Seed.generate_rng("WorldSeed")
	for i in range(3):
		var terrain = ["Mountain", "Forest", "Desert"][world_rng.randi_range(0, 2)]
		var size = world_rng.randi_range(50, 200)
		print("  %s (Size: %d)" % [terrain, size])
	
	# Close game
	get_tree().quit()
