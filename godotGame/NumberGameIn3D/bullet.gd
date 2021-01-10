extends Spatial

var speed = 30
var velocity = Vector3()
onready var timer = get_node("Timer")  #onready make sure everything is set up

func _ready():
	timer.set_wait_time( 2 )
	timer.start()
	set_as_toplevel( true )

func start( xform ):
	global_transform = xform
	velocity = global_transform.basis.z * speed

func _process(delta):
	global_transform.origin -= velocity*delta

# if bullet met something, it will be destroyed.
func _on_bullet_body_entered( body ):
	if body is StaticBody:
		body.destroied()
		queue_free()

func _on_Timer_timeout():
	queue_free()
