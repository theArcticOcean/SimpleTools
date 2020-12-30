extends Spatial

var musicContainer : Node

func _ready():
	musicContainer = preload( "res://musics.tscn" ).instance()
	$FallStone/MeshInstance.transform.origin = Vector3( 1, 1, 0 )

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if null == $FallStone/MeshInstance:
		return 
	#$FallStone/MeshInstance.translate( Vector3(0, 0, 1 )*0.1 )
	var fallPos = $FallStone/MeshInstance.transform.origin
	if ( $player/Camera.is_position_behind( fallPos ) ):
		 $FallStone/MeshInstance.queue_free()

func _physics_process( delta ):
	if Input.is_action_pressed("jump"):
		var player:AudioStreamPlayer3D = musicContainer.get_node( "explose" ).duplicate()
		player.stream = player.stream.duplicate()
		player.stream.loop = false
		player.global_transform.origin = $player/Camera.global_transform.origin
		player.play()
		$"/root".add_child( player )
		player.connect( "finished", player, "queue_free" )
