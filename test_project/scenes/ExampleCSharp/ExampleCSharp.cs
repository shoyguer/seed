using Godot;

/// <summary>
/// Example script demonstrating the Seed plugin
/// </summary>
public partial class ExampleCSharp : Node2D
{
	public override void _Ready()
	{
		// Try to access Seed class using ClassDB
		var seed = ClassDB.Instantiate("Seed").AsGodotObject();
		
		if (seed == null)
		{
			GD.PrintErr("Failed to create Seed instance");
			return;
		}
		
		// Generate different types of seed strings
		GD.Print($"Numbers only: {seed.Call("generate_seed_string", 0, 8)}");
		GD.Print($"Letters only: {seed.Call("generate_seed_string", 3, 10)}");
		GD.Print($"Mixed chars: {seed.Call("generate_seed_string", 4, 12)}");
		
		// Create RNG with custom seed
		string customSeed = "MyGameWorld2024";
		var rng1 = seed.Call("generate_rng", customSeed).AsGodotObject();
		GD.Print($"Custom seed RNG: {rng1.Call("randi_range", 1, 100)}");
		
		// Auto-generated seed RNG
		var rng2 = seed.Call("generate_rng", "", 4, 12).AsGodotObject();
		GD.Print($"Auto seed RNG: {rng2.Call("randf")}");
		
		// Demonstrate reproducible randomization
		GD.Print("\n___\nReproducible test:");
		string testSeed = "TestSeed123";
		var rngA = seed.Call("generate_rng", testSeed).AsGodotObject();
		var rngB = seed.Call("generate_rng", testSeed).AsGodotObject();
		GD.Print($"Same seed, same results: {rngA.Call("randf").Equals(rngB.Call("randf"))}");
		
		// Simple procedural generation
		GD.Print("\n___\nProcedural world:");
		var worldRng = seed.Call("generate_rng", "WorldSeed").AsGodotObject();
		string[] terrains = {"Mountain", "Forest", "Desert"};
		for (int i = 0; i < 3; i++)
		{
			string terrain = terrains[worldRng.Call("randi_range", 0, 2).AsInt32()];
			int size = worldRng.Call("randi_range", 50, 200).AsInt32();
			GD.Print($"  {terrain} (Size: {size})");
		}
		
		// Close game
		GetTree().Quit();
	}
}
