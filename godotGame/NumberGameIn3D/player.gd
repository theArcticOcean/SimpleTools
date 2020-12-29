extends KinematicBody

var gravity= -ProjectSettings.get_setting( "physics/3d/default_gravity" )*2
const SPEED = 7
const ACCELERATION = 3
const DE_ACCELERATION = 5
var velocity = Vector3(0, 0, 0)
var cam

# Called when the node enters the scene tree for the first time.
func _ready():
	cam = $target/Camera

func _physics_process(delta):
	var cameraTrans:Transform = $target/Camera.get_global_transform()
	var vec = Vector3(0, 0, 0)
	vec.x = Input.get_action_strength( "move_right" ) - Input.get_action_strength( "move_left" )
	vec.z = Input.get_action_strength("move_down") - Input.get_action_strength("move_up")

	var YZMatrix = cameraTrans.basis.rotated( cameraTrans.basis.x, cameraTrans.basis.get_euler().x )
	vec = YZMatrix.xform( vec )
	if vec.length() > 0:
		vec /= vec.length()
	
	velocity.y += delta*gravity
	"""var tmp = vec * SPEED
	velocity.x = tmp.x
	velocity.z = tmp.z"""
	
	# avoid change too fast, create smooth effect.
	var horizontalVec = velocity
	horizontalVec.y = 0
	print( horizontalVec )
	var acceleration
	if vec.dot( horizontalVec ) > 0:
		acceleration = ACCELERATION
	else:
		acceleration = DE_ACCELERATION

	var targetVec = vec * SPEED
	horizontalVec = horizontalVec.linear_interpolate( targetVec, acceleration * delta )
	velocity.x = horizontalVec.x
	velocity.z = horizontalVec.z
	
	velocity = move_and_slide( velocity, Vector3.UP )

	if Input.is_action_pressed("jump"):
		velocity.y -= delta * gravity * 3
	if Input.is_action_pressed("turn_head"):
		rotate_y( PI/180 )
		cam.rotate_y( PI/180 )
