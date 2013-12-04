import pyglet
from pyglet.media import Player

pyglet.options['debug_media'] = False

event_loop = pyglet.app.EventLoop()
player = Player()


def stop():
    print 'stop'
    #print player.eos_action
    #event_loop.exit()


def eos():
    print 'eos'
    #print player.eos_action
    #event_loop.exit()


def qqqq(dt):
    print player.playing, player.event_types, player.volume, player.time, player.position, player.source


f = 'wav'

player.push_handlers(on_player_eos=stop, on_eos=eos)

source = pyglet.media.load("sound.%s" % f)
pyglet.clock.schedule_interval(qqqq, 1)
player.queue(source)

player.volume = 1
player.play()

event_loop.run()

