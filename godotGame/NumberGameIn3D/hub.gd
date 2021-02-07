extends CanvasLayer

var number: Array
var operator: String
var content: String
onready var numGenerator: RandomNumberGenerator = RandomNumberGenerator.new()
onready var restSecCount = get_node( "checkPointTimer" ).get_wait_time()
export var g_PlayerAlive: bool = true

func ShowGameOverUI( gameOver ):
	if gameOver:
		$gameOverLabel.show()
		$restartButton.show()
		get_tree().root.get_node("World/Environment").set_visible( false )
		get_tree().root.get_node("World/player").set_visible( false )
		get_tree().root.get_node("World/musics/BGM").stop()
		get_tree().root.get_node("World/musics/failBGM").play()
		g_PlayerAlive = false
		$checkPointTimer.stop()
	else:
		$gameOverLabel.hide()
		$restartButton.hide()
		get_tree().root.get_node("World/Environment").set_visible( true )
		get_tree().root.get_node("World/player").set_visible( true )
		$resultLabel.text = ""
		get_tree().root.get_node("World/musics/BGM").play()
		get_tree().root.get_node("World/musics/failBGM").stop()
		g_PlayerAlive = true
		generateContent()
		updateLabel()
		$checkPointTimer.start()

# Called when the node enters the scene tree for the first time.
func _ready():
	numGenerator.randomize()
	ShowGameOverUI( false )
	$checkPointTimer.start( restSecCount )
	$checkPointTimer.connect("timeout", get_tree().root.get_node("World"), "_on_checkPointTimer_timeout" )
	$restartButton.connect("button_up", get_tree().root.get_node("World"), "_on_restartButton_down" )

func GetCalculateResult():
	var result = -1
	if operator == " + ":
		result = number[0] + number[1]
	elif operator == " - ":
		result = number[0] - number[1]
	return result

func updateLabel():
	content = String( number[0] ) + operator + String( number[1] ) + " = "
	$questionLabel.text = content

func mapFromIntToStr( parameter ):
	var result = " ? "
	if parameter == 1:
		result = " + "
	elif parameter == 2:
		result = " - "
	return result

func generateContent():
	number.clear()
	number.append( numGenerator.randi_range( 1, 99 ) )
	number.append( numGenerator.randi_range( 1, 99 ) )
	var opetatorNum = numGenerator.randi_range( 1, 2 )
	if number[0] < number[1] and opetatorNum == 2:
		var tmp = number[0]
		number[0] = number[1]
		number[1] = tmp

	operator = mapFromIntToStr( opetatorNum )

func IsResultRight():
	var result = $resultLabel.text.to_int()
	print( str(result) + " vs " + str(GetCalculateResult()) )
	if result == GetCalculateResult():
		return true
	return false

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	$progressBar.value = $checkPointTimer.time_left / restSecCount * 100

func _on_checkPointTimer_timeout():
	if IsResultRight():
		generateContent()
		updateLabel()
		$resultLabel.text = ""
	else:
		if g_PlayerAlive:
			ShowGameOverUI( true )

func _on_clear_result():
	$resultLabel.text = ""

func _on_restartButton_button_up():
	ShowGameOverUI( false )
