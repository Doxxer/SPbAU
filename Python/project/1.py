import random
import pyglet

def f():
     print('done playing the sound')

sound = pyglet.media.load("sound.wav")

player = sound.play()
player.volume = random.random()
player.push_handlers(on_eos=f)

pyglet.clock.schedule_once(lambda dt: pyglet.app.exit(), delay=10)
pyglet.app.run()
