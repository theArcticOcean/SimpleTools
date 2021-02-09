extends CPUParticles

# Called when the node enters the scene tree for the first time.
func _ready():
	hide()

func LookAtCamera():
	var cameraPos = get_node("../player/Camera").global_transform.origin
	var vec = cameraPos - global_transform.origin
	vec = -vec
	var pos = global_transform.origin + vec
	look_at( pos, Vector3(0, 1, 0) )

func updateMesh( num, pos ):
	var path : String = "res://objAndPng//number/"
	path = path + str(num) + ".obj"
	set_mesh( load( path ) )
	global_transform.origin = pos
	LookAtCamera()

func showExplode():
	$showTimer.start()
	show()

func _on_showTimer_timeout():
	hide()
