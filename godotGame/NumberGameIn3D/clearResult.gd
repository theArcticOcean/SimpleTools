extends StaticBody

var numGen: RandomNumberGenerator
var content: String

# Called when the node enters the scene tree for the first time.
func Prepare():
	numGen = RandomNumberGenerator.new()
	numGen.randomize()

func LookAtCamera():
	var cameraPos = get_tree().root.get_node("World/player/Camera").global_transform.origin
	var vec = cameraPos - get_node("CSGMesh").global_transform.origin
	vec = -vec
	var pos = get_node("CSGMesh").global_transform.origin + vec
	get_node("CSGMesh").look_at( pos, Vector3(0, 1, 0) )

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	LookAtCamera()

# Called when the node enters the scene tree for the first time.
func _ready():
	PutNewPos()

func destroied():
	queue_free()

func GetContent():
	return "clear"

func PutNewPos():
	var _y = get_tree().root.get_node("World/Environment/floorB").global_transform.origin[1]
	var halfX = 50 #size[0] / 2.0
	var halfZ = 50 #size[1] / 2.0
	var x = numGen.randi_range( -halfX, halfX )
	var z = numGen.randi_range( -halfZ, halfZ )
	global_transform.origin = Vector3( x, _y + 3, z )
