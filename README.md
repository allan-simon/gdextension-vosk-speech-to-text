# gdextension-vosk-speech-to-text
Godot GDextension allowing to have speech to text in your game using vosk 


## Interesting part 

This extension use a third party library (libvosk.so) 

to do so we had to add in SConstruct the two lines

```
env.Append(LIBPATH=["bin/"])
env.Append(LIBS=["libvosk"])
```
