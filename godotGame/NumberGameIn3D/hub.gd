extends CanvasLayer

var number: Array
var operator: String
var content: String
onready var numGenerator: RandomNumberGenerator = RandomNumberGenerator.new()
onready var restSecCount = get_node( "../updateNumTimer" ).get_wait_time()

# Called when the node enters the scene tree for the first time.
func _ready():
	numGenerator.randomize()
	$checkPointTimer.start( restSecCount )

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

func mapFromStrToInt( parameter ):
	var result = 0
	if parameter == " + ":
		result = 1
	elif parameter == " - ":
		result = 2
	return result

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

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	$progressBar.value = $checkPointTimer.time_left / restSecCount * 100

func _on_updateNumTimer_timeout():
	generateContent()
	updateLabel()

func _on_clear_result():
	$resultLabel.text = ""
