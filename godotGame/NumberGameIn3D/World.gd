extends Spatial

const NUMBER_OBJ = preload("res://number.tscn")
const CLEAR_OBJ = preload("res://clearResult.tscn")
var numbers = []
var clear_instance

# Called when the node enters the scene tree for the first time.
func _ready():
	clear_instance = CLEAR_OBJ.instance()
	get_node( "hub" ).generateContent()
	get_node( "hub" ).updateLabel()
	PutNumbers()
	clear_instance.Prepare()
	add_child( clear_instance )	
	clear_instance.PutNewPos()

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	for number in numbers:
		if null != number:
			number.LookAtCamera( $player/Camera.global_transform.origin )

func PutNumbers():
	var posArray = []
	posArray.append( get_node("Environment/land").global_transform.origin )
	posArray.append( get_node("Environment/floorA").global_transform.origin )
	posArray.append( get_node("Environment/floorB").global_transform.origin )
	for i in range(0, 3):
		var pos = posArray[i]
		for j in range(0, 10):
			var number = NUMBER_OBJ.instance()
			number.Prepare()
			number.InitNumber( j, pos )
			numbers.append( number )
			add_child( number )

func _on_checkPointTimer_timeout():
	for number in numbers:
		if null != number:
			number.destroied()
	numbers.clear()
	if $hub.IsResultRight():
		PutNumbers()
		clear_instance.PutNewPos()

func _on_restartButton_down():
	for number in numbers:
		if null != number:
			number.destroied()
	numbers.clear()
	PutNumbers()
	clear_instance.PutNewPos()

func _on_generate_right_result():
	for number in numbers:
		if null != number:
			number.destroied()
	numbers.clear()
	PutNumbers()
	clear_instance.PutNewPos()
