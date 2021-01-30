extends StaticBody

# Called when the node enters the scene tree for the first time.
func _ready():
	pass

func destroied():
	queue_free()

func InitNumber( num ):
	var path : String = "res://tank_trexhwm_obj/number/"
	path = path + num.to_string() + ".obj"
	get_node("target").mesh = load( path )
