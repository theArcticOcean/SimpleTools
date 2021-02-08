extends Node

# Called when the node enters the scene tree for the first time.
func _ready():
	$BGM.stream.loop = true
	$BGM.play()

func playExplose( position, type ):
	var player:AudioStreamPlayer3D = null
	if type == "explose":
		player = $explose.duplicate()
	elif type == "fire":
		player = $fire.duplicate()

	player.stream = player.stream.duplicate()
	player.stream.loop = false
	player.global_transform.origin = position
	player.play()
	add_child( player )
	player.connect( "finished", player, "queue_free" )

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
