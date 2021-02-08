extends Spatial

var speed = 50
var velocity = Vector3()
onready var timer = get_node("Timer")  #onready make sure everything is set up
signal sig_clear_result
signal sig_generate_right_result

func _ready():
	timer.set_wait_time( 2 )
	timer.start()
	set_as_toplevel( true )	
	connect( "sig_clear_result", get_tree().root.get_node("World/hub"), "_on_clear_result" )
	connect( "sig_generate_right_result", get_tree().root.get_node("World"), "_on_generate_right_result" )

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
		if content == "clear":
			print( content )
			emit_signal("sig_clear_result")
		else:
			var number = content.to_int()
			if number >= 0 and number < 10:
				AppendResult( number )
				body.destroied()
				get_tree().root.get_node("World/musics").playExplose( body.global_transform.origin, "explose" )
				if get_tree().root.get_node("World/hub").OnChooseNumber():
					emit_signal( "sig_generate_right_result" )
		queue_free()

func _on_Timer_timeout():
	queue_free()
