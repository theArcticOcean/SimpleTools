extends Node

# Called when the node enters the scene tree for the first time.
func _ready():
	$BGM.stream.loop = true
	$BGM.global_transform = get_parent().get_node("player").global_transform
	$BGM.play()

func playExplose( position ):
	var player:AudioStreamPlayer3D = $explose.duplicate()
	player.stream = player.stream.duplicate()
	player.stream.loop = false
	player.global_transform.origin = position
	player.play()
	$"/root".add_child( player )
	player.connect( "finished", player, "queue_free" )

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	$BGM.global_transform = get_parent().get_node("player").global_transform
