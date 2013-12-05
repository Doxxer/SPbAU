from console_input import UserInput
from console_player import Player


def action_info():
    it.write('*******************')
    it.write("playing: {0}".format(player.playing))
    it.write("eos: {0}".format(player._player.eos_action))
    it.write("source: {0}".format(player._player.source))
    it.write("events: {0}".format(player._player.event_types))
    it.write('*******************')


def action_pause():
    it.write('--> action toggle_pause')
    player.toggle_pause()


def action_bar():
    cur = (player.volume + 0.1) % 1
    player.set_volume(cur)
    it.write('--> action bar (volume up) to %f' % player.volume)


def action_add():
    it.write('--> action add')
    f = 'wav'
    player.add("sound.%s" % f)


def action_add2():
    it.write('--> action add mp3')
    f = 'mp3'
    player.add("sound.%s" % f)


def action_next():
    it.write('--> action next')
    player._player.next_source()


def invalid_input():
    it.write('--> Unknown command')


if __name__ == '__main__':
    cmd_actions = {('p',): action_pause, ('bar', 'b'): action_bar, ('a',): action_add,
                   ('aa',): action_add2, ('info', 'i'): action_info, ('n'): action_next}

    it = UserInput(cmd_actions)
    player = Player(it.write)
    it.start()
