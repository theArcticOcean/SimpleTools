extends KinematicBody

var gravity= -ProjectSettings.get_setting( "physics/3d/default_gravity" )*2
const SPEED = 7
const ACCELERATION = 3
const DE_ACCELERATION = 5
var velocity = Vector3(0, 0, 0)
var nothing_pressed

# Called when the node enters the scene tree for the first time.
func _ready():
	pass

func _input( event ):
	if event.is_pressed():
		nothing_pressed = false
	else:
		nothing_pressed = true

func _physics_process( delta ):
	if Input.is_action_pressed("turn_head"):
		if Input.is_action_pressed( "move_left" ):
			rotate_y( PI/180 )
			$Camera.rotate_y( PI/180 )
		elif Input.is_action_pressed( "move_right" ):
			rotate_y( -PI/180 )
			$Camera.rotate_y( -PI/180 )

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
