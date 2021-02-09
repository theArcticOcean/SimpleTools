extends MeshInstance

var speed = 0.2

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

func GetContent():
	return "mace0"

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	var y = global_transform.origin[1]
	y = y + speed
	if y > 13:
		speed = -speed
	if y < 0:
		speed = -speed
	global_transform.origin[1] = y
