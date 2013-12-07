# coding=utf-8
from console import Console
from player import Player

#region actions...
from playlist import Playlist


def action_info():
    console.write('*******************')
    console.write(playlist.info)
    console.write('-------------------')
    console.write(player.info)
    console.write('*******************')


def action_toggle_pause():
    if player.toggle_pause():
        console.write('--> player %s' % ('played' if player.playing else 'paused'))


def action_volume_up():
    player.set_volume(min(player.volume + 10, 100))
    console.write("--> volume is {0}% now".format(player.volume))


def action_volume_down():
    player.set_volume(max(player.volume - 10, 0))
    console.write("--> volume is {0}% now".format(player.volume))


def action_set_volume(vol):
    vol = int(vol)
    if 0 <= vol <= 100:
        player.set_volume(vol)
    console.write("--> volume is {0}% now".format(player.volume))


def action_play():
    try:
        playlist.play()
        action_info()
    except Exception as ex:
        console.write(ex)


def action_next():
    if playlist.next():
        action_info()


def action_prev():
    try:
        player.play("sound.mp3")
        action_info()
    except Exception as ex:
        console.write(ex)


def action_change_order_mode():
    if playlist.toggle_mode():
        console.write("Порядок воспроизведения изменен на: %s" % playlist.current_order_mode)


def invalid_input():
    console.write("--> Unknown command. Type 'help' to view available commands...")


def action_help():
    # todo написать нормальную справку распарсив Docs
    console.write(cmd_actions)
    console.write(console._quit_list)

#endregion

if __name__ == '__main__':
    cmd_actions = {
        ('help', 'h', ): action_help,
        ('pause', 'p',): action_toggle_pause,
        ('volume up', 'vup', 'vu',): action_volume_up,
        ('volume down', 'vdown', 'vd',): action_volume_down,
        ('volume set', 'vs', ): action_set_volume,
        ('info', 'i'): action_info,
        ('play', ): action_play,
        ('next', 'n', ): action_next,
        ('prev', 'pr', ): action_prev,
        ('current_order_mode', 'm'): action_change_order_mode,
    }

    console = Console(cmd_actions, wrong_input_action=invalid_input)
    playlist = Playlist(playlist_file='1.plst')
    player = Player(action_next)
    playlist.set_player(player)
    console.start()
