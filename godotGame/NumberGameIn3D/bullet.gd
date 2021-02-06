extends Spatial

var speed = 50
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
	
func ClearResult():
	get_tree().root.get_node("World/hub/resultLabel").text = ""

func AppendResult( value ):
	get_tree().root.get_node("World/hub/resultLabel").text = get_tree().root.get_node("World/hub/resultLabel").text + str(value)

# if bullet met something, it will be destroyed.
func _on_bullet_body_entered( body ):
	if body is StaticBody:
		var content = body.GetContent()
		var number = content.to_int()
		if number >= 0 and number < 10:
			AppendResult( number )
		body.destroied()
		get_tree().root.get_node("World/musics").playExplose( body.global_transform.origin, "explose" )
		queue_free()

func _on_Timer_timeout():
	queue_free()
