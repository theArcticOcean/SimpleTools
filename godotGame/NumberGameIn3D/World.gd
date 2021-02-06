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
	$updateNumTimer.start( 10 )

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	for number in numbers:
		if null != number:
			number.LookAtCamera( $player/Camera.global_transform.origin )

func PutNumbers():
	print( "===> PutNumbers <===" )
	for i in range(0, 9):
		var number = NUMBER_OBJ.instance()
		number.Prepare()
		var _y = get_node("Environment/land").global_transform.origin[1] + 3
		number.InitNumber( i, 0, _y )
		numbers.append( number )
		add_child( number )

func _on_updateNumTimer_timeout():
	for number in numbers:
		if null != number:
			number.destroied()
	numbers.clear()
	PutNumbers()
	clear_instance.PutNewPos()
