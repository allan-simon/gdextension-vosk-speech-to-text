# gdextension-vosk-speech-to-text
Godot GDextension allowing to have speech to text in your game using vosk 


## how to use it

```
@onready var vosk := $Vosk

...
var effect : AudioEffectCapture  # See AudioEffect in docs

func _ready() -> void
     # vosk-model-small-fr-0.22 is an audio model you can download
     # on vosk's website, you can replace it by the langage you want
     #
     # the 2nd parameters is a JSON string that allows you to limit the
     # vocabulary that model will recognize, it decrease the chance of ambiguity
     # and increase the accuracy
	   vosk.init("bin/vosk-model-small-fr-0.22", '["foo", "bar"]')

func _process(delta: float) -> void:
	if  !effect.can_get_buffer(buffer_length_frames / 2):
		return

	var data = effect.get_buffer(effect.get_frames_available())

    #
    # basically accept_wave_form is the method to feed it with new audio data
    # (it works with stream and is able to detect change from silence to 'speaking'
    # and will continue buffering as long it's not again silence"
    # so you're supposed to only give it the new data since last time you called it
    # not feed it everytime the whole data.
    #
    # it returns true when it's again silence and it has a final result
	if accept_wave_form_stereo_float(data):
        print(vosk.result())
    else:
        # if it's not yet finalized, you still can get the partial result
        # it can be useful if you want to have result ASAP and you can accept a lower accuracy
		    var partial_result = JSON.parse_string(vosk.partial_result())["partial"]
```

## Interesting part 

This extension use a third party library (libvosk.so) 

to do so we had to add in SConstruct the two lines

```
env.Append(LIBPATH=["bin/"])
env.Append(LIBS=["libvosk"])
```

for exporting things correctly you also need the `[dependencies]` section in your `.gdextension` file

```
[dependencies]

linux.debug.x86_64 = {
    "res://bin/libvosk.so" : ""
}
linux.release.x86_64 = {
    "res://bin/libvosk.so" : ""
}
```


## About Vosk

This project is a simpler wrapper around `libvosk`

you can check this awesome project [there](https://alphacephei.com/vosk/)


