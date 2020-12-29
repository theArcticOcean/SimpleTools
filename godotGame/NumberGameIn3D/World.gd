extends Spatial

# Called when the node enters the scene tree for the first time.
func _ready():
	$FallStone/MeshInstance.transform.origin = Vector3( 1, 1, 0 )

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if null == $FallStone/MeshInstance:
		return 
	#$FallStone/MeshInstance.translate( Vector3(0, 0, 1 )*0.1 )
	var fallPos = $FallStone/MeshInstance.transform.origin
	if ( $player/target/Camera.is_position_behind( fallPos ) ):
		 $FallStone/MeshInstance.queue_free()
