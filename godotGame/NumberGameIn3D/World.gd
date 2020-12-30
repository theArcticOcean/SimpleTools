extends Spatial

var musicContainer:Resource

func _ready():
	musicContainer = preload( "res://musics.tscn" )
	$FallStone/MeshInstance.transform.origin = Vector3( 1, 1, 0 )

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if null == $FallStone/MeshInstance:
		return 
	#$FallStone/MeshInstance.translate( Vector3(0, 0, 1 )*0.1 )
	var fallPos = $FallStone/MeshInstance.transform.origin
	if ( $player/Camera.is_position_behind( fallPos ) ):
		 $FallStone/MeshInstance.queue_free()

	if Input.is_action_pressed("jump"):
		var player = musicContainer.get_node( "explose" ).duplicate()
		musicContainer.stream = player.stream.duplicate()
		player.position = $player/Camera.global_transform.origin
		player.play()
		$"/world".add_child( player )
		player.connect( "finished", player, "queue_free" )
