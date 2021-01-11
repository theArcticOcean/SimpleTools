extends KinematicBody

var gravity= -ProjectSettings.get_setting( "physics/3d/default_gravity" )*6
const SPEED = 14
const ACCELERATION = 3
const DE_ACCELERATION = 5
var velocity = Vector3(0, 0, 0)
var mouse_sensitivity = 0.2
var nothing_pressed
export var captured : bool = true; # Does not let the mouse leave the screen
var bullect_move_vec = Vector3()
const FIREBALL = preload("res://bullet.tscn")
onready var musicContainer: Node = get_parent().get_node("musics")

# Called when the node enters the scene tree for the first time.
func _ready():
	pass

func _unhandled_input(event):
	if Input.is_action_just_pressed( "Shooting" ):
		var fireball = FIREBALL.instance()
		add_child( fireball )
		fireball.start( $Position3D.global_transform )
		musicContainer.playExplose( $Camera.global_transform.origin )

func _input( event ):
	if event is InputEventMouseMotion:
		rotate_y( deg2rad(-event.relative.x * mouse_sensitivity ))
	if event.is_pressed():
		nothing_pressed = false
	else:
		nothing_pressed = true

func _physics_process( delta ):
	if Input.is_action_just_pressed("KEY_ESCAPE"):
		captured = !captured

	if captured:
		# Locks the mouse in the center of the screen
		Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED);
	else:
		# Unlocks the mouse from the center of the screen
		Input.set_mouse_mode(Input.MOUSE_MODE_VISIBLE);

	if Input.is_action_pressed("turn_head"):
		if Input.is_action_pressed( "move_left" ):
			rotate_y( PI/180 )
		elif Input.is_action_pressed( "move_right" ):
			rotate_y( -PI/180 )

		return

	var cameraTrans:Transform = $Camera.get_global_transform()
	var vec = Vector3(0, 0, 0)
	vec.x = Input.get_action_strength( "move_right" ) - Input.get_action_strength( "move_left" )
	vec.z = Input.get_action_strength("move_down") - Input.get_action_strength("move_up")

	var YZMatrix = cameraTrans.basis.rotated( cameraTrans.basis.x, cameraTrans.basis.get_euler().x )
	vec = YZMatrix.xform( vec )
	if vec.length() > 0:
		vec /= vec.length()
	
	velocity.y += delta*gravity
	if nothing_pressed:
		velocity.y += delta*gravity

	# avoid change too fast, create smooth effect.
	var horizontalVec = velocity
	horizontalVec.y = 0
	var acceleration
	if vec.dot( horizontalVec ) > 0:
		acceleration = ACCELERATION
	else:
		acceleration = DE_ACCELERATION

	var targetVec = vec * SPEED
	if Input.is_action_pressed("speed_up"):
		targetVec = targetVec * 3

	horizontalVec = horizontalVec.linear_interpolate( targetVec, acceleration * delta )
	velocity.x = horizontalVec.x
	velocity.z = horizontalVec.z
	
	velocity = move_and_slide( velocity, Vector3.UP )

	if Input.is_action_pressed("jump"):
		velocity.y -= delta * gravity * 3
