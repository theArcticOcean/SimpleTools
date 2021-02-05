extends StaticBody

var numGen: RandomNumberGenerator

# Called when the node enters the scene tree for the first time.
func Prepare():
	numGen = RandomNumberGenerator.new()
	numGen.randomize()

func destroied():
	queue_free()

func GetRandomLandPos( _y ):
	var x = numGen.randi_range( -50, 50 )
	var y = _y
	var z = numGen.randi_range( -30, 50 )
	return [x, y, z]

func LookAtCamera( cameraPos ):
	var vec = cameraPos - get_node("target").global_transform.origin
	vec = -vec
	var pos = get_node("target").global_transform.origin + vec
	get_node("target").look_at( pos, Vector3(0, 1, 0) )

func InitNumber( num, type, _y ):
	var path : String = "res://tank_trexhwm_obj/number/"
	path = path + str(num) + ".obj"
	get_node("target").mesh = load( path )
	var position
	if type == 0:
		position = GetRandomLandPos( _y )
		global_transform.origin = Vector3( position[0], position[1], position[2] )
	print( position )
