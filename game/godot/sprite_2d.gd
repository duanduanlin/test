extends Sprite2D

var speed = 400
var angular_speed = PI
var move_up_down = 0

signal health_changed(old_value, new_value)
var health = 10

func _init():
	print("Hello, world!")

func _ready():
	var timer = get_node("Timer")
	timer.timeout.connect(_on_timer_timeout)

func _process(delta):
	
	#turn around
	var direction = 0
	if Input.is_action_pressed("ui_left"):
		print("turn left")
		direction = -1
	if Input.is_action_pressed("ui_right"):
		print("turn right")
		direction = 1
	rotation += angular_speed * direction * delta
	
	print("rotation:",rotation)
	
	#move
	var velocity = Vector2.ZERO
	if Input.is_action_pressed("ui_up"):
		print("move up")
		if move_up_down != 0:
			move_up_down = 0
			rotate(PI)
		velocity = Vector2.UP.rotated(rotation) * speed
	if Input.is_action_pressed("ui_down"):
		print("move down")
		if move_up_down != 1:
			move_up_down = 1
			rotate(PI)
		velocity = Vector2.UP.rotated(rotation) * speed
	position += velocity * delta


func _on_button_pressed() -> void:
	set_process(not is_processing())

func _on_timer_timeout():
	visible = not visible

func take_damage(amount):
	var old_health = health
	health -= amount
	health_changed.emit(old_health, health)


func _on_health_changed(old_value: Variant, new_value: Variant) -> void:
	if new_value <= 0:
		set_process(false)
