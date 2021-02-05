extends Spatial

# Called when the node enters the scene tree for the first time.
func _ready():
	get_node( "hub" ).generateContent()
	get_node( "hub" ).updateLabel()
	get_node( "updateNumTimer" ).start( 10 )

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
