extends KinematicBody2D

export (int) var moveSpeed = 200

export var velocity = Vector2()
var mouse_in = false
var mouse_pos
var last_mouse_pos
var mouse_vec
var dragging = false
var lastValidPos

func vecUnit( vec ):
	var vecLen = vec.length()
	if abs(vecLen) < 0.000001:
		return vec
	vec.x /= vecLen
	vec.y /= vecLen
	return vec

func vecFromSubPts(v1, v2):
	return Vector2(v1.x - v2.x, v1.y - v2.y)
	
func vecFromSum(v1, v2):
	return Vector2(v1.x + v2.x, v1.y + v2.y)

# Called when the node enters the scene tree for the first time.
func _ready():
	randomize()
	velocity.x = randi()%10
	velocity.y = randi()%10
	velocity = vecUnit( velocity )
	last_mouse_pos = get_viewport().get_mouse_position()
	lastValidPos = self.position

func _process(_delta):
	mouse_pos = get_viewport().get_mouse_position()
	mouse_vec = vecFromSubPts(mouse_pos, last_mouse_pos)
	last_mouse_pos = mouse_pos

	if !get_tree().root.get_node("Node2D").enterWall:
		lastValidPos = self.position
		if dragging && mouse_vec.length() > 0:
			velocity = mouse_vec
		else:
			if velocity.length() > 1:
				velocity = vecUnit(velocity)
				
func _physics_process(delta):
	if Input.is_action_pressed("mouse_left_click") && mouse_in:
		dragging = true
	if !Input.is_action_pressed("mouse_left_click"):
		dragging = false

	if get_tree().root.get_node("Node2D").enterWall && dragging:
		#velocity = -velocity
		set_position( lastValidPos )
		#move_and_slide( -velocity*moveSpeed*5 )
	else:
		if dragging:
			#set_position( mouse_pos )
			move_and_slide( velocity*moveSpeed/5 )
		else:
			move_and_slide( velocity*moveSpeed )
		
func _on_Ball_mouse_entered():
	mouse_in = true

func _on_Ball_mouse_exited():
	mouse_in = false
