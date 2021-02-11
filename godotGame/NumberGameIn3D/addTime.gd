extends Area

var speed = 3
var radius = 0
var A
var B
var C
var R = 20

# Called when the node enters the scene tree for the first time.
func _ready():
	A = global_transform.origin[0]
	B = global_transform.origin[1]
	C = global_transform.origin[2]

func GetContent():
	return "addTime"

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	radius = radius + delta*speed
	var x = cos(radius) * R + A
	var z = sin(radius) * R + C
	global_transform.origin = Vector3( x, B, z )
	if radius > PI*2:
		radius -= PI*2
