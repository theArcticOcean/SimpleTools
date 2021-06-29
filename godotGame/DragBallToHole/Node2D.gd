extends Node2D

export (bool) var enterWall = false

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.
	
# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass

func _on_WallTop_body_entered(body):
	$Ball.velocity.y = -$Ball.velocity.y
	enterWall = true

func _on_WallLeft_body_entered(body):
	$Ball.velocity.x = -$Ball.velocity.x
	enterWall = true

func _on_WallBottom_body_entered(body):
	$Ball.velocity.y = -$Ball.velocity.y
	enterWall = true

func _on_WallRight_body_entered(body):
	$Ball.velocity.x = -$Ball.velocity.x
	enterWall = true

func _on_WallTop_body_exited(body):
	enterWall = false

func _on_WallLeft_body_exited(body):
	enterWall = false

func _on_WallBottom_body_exited(body):
	enterWall = false

func _on_WallRight_body_exited(body):
	enterWall = false
