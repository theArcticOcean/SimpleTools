extends StaticBody

var numGen: RandomNumberGenerator
var content: String

# Called when the node enters the scene tree for the first time.
func Prepare():
	numGen = RandomNumberGenerator.new()
	numGen.randomize()

func destroied():
	queue_free()

func GetContent():
	return content

func GetRandomLandPos( landPos ):
	var x = numGen.randi_range( -50, 50 ) + landPos[0]
	var y = landPos[1] + 3
	var z = numGen.randi_range( -30, 50 ) + landPos[2]
	return [x, y, z]

func LookAtCamera( cameraPos ):
	var vec = cameraPos - get_node("target").global_transform.origin
	vec = -vec
	var pos = get_node("target").global_transform.origin + vec
	get_node("target").look_at( pos, Vector3(0, 1, 0) )

func HasSamePos(numsPos, newPos):
	var errorLimit = 5
	var result = false
	for numPos in numsPos:
		if abs(numPos[0] - newPos[0]) < errorLimit and \
			abs(numPos[1] - newPos[1]) < errorLimit and \
			abs(numPos[2] - newPos[2]) < errorLimit :
			result = true
			break
	return result

func InitNumber( num, landPos, numsPos ):
	var path : String = "res://objAndPng/number/"
	path = path + str(num) + ".obj"
	content = str(num)
	get_node("target").mesh = load( path )
	var position = GetRandomLandPos( landPos )
	while HasSamePos( numsPos, position ) :
		position = GetRandomLandPos( landPos )

	global_transform.origin = Vector3( position[0], position[1], position[2] )
	print( position )
	return position
