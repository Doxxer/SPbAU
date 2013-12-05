from console_input import UserInput
from console_player import Player


player = Player()

def action_foo():
    it.write('--> action foo (pause)')
    player.pause()


def action_bar():
    cur = (player.volume + 0.1) % 1
    player.set_volume(cur)
    it.write('--> action bar (volume up) to %f' % player.volume)


def invalid_input():
    it.write('--> Unknown command')


def stop():
    it.write('# stop')
    #print player.eos_action
    #event_loop.exit()


def eos():
    it.write('# eos')
    #print player.eos_action
    #event_loop.exit()


if __name__ == '__main__':
    f = 'mp3'

    cmd_actions = {('foo', 'f'): action_foo, ('bar', 'b'): action_bar}
    quit_list = ['q', 'quit', 'exit', 'shutdown']

    print 1
    it = UserInput(cmd_actions, quit_list, invalid_input).start()
    print 2
    player.start()
    print 3