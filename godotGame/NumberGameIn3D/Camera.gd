extends Camera

export var min_distance = 5
export var max_distance = 10
export var angle_v_adjust = 0.0
var max_height = 2.0
var min_height = 0
var last_player_pos
var player

# Called when the node enters the scene tree for the first time.
func _ready():
	player = get_parent()
	set_as_toplevel( true )
	last_player_pos = player.global_transform.origin

func _physics_process(delta):
	var target_pos: Vector3 = player.global_transform.origin
	var camera_pos: Vector3 = global_transform.origin
	var vec = target_pos - last_player_pos
	global_transform.origin += vec
	last_player_pos = target_pos

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
