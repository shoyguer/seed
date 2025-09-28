extends Node2D

func _ready() -> void:
	print(Seed.generate_seed_string(Seed.ALL_MIXED, 10))
	get_tree().quit()
	pass
