# coding=utf-8
import sys
from playlist import Playlist
from console import Console
from player import Player

#region actions...
def action_info():
    """
    Получить информацию о текущем состоянии плеера, режимах воспроизведения и текущей песне

    """
    console.write('*******************')
    console.write(playlist.info)
    console.write('-------------------')
    console.write(player.info)
    console.write('*******************')


def action_toggle_pause():
    """
    Поставить плеер на паузу / снять плеер с паузы
    """
    if player.toggle_pause():
        console.write("--> Плеер %s" % ("играет" if player.playing else "на паузе"))


def action_volume_up():
    """
    Увеличить громкость на 10%

    """
    player.set_volume(min(player.volume + 10, 100))
    console.write("--> Громкость {0}%".format(player.volume))


def action_volume_down():
    """
    Уменьшить громкость на 10%

    """
    player.set_volume(max(player.volume - 10, 0))
    console.write("--> Громкость {0}%".format(player.volume))


def action_set_volume(vol):
    """
    Установить громкость в <param> процентов. <param> - число от 0 до 100
    """
    vol = int(vol)
    if 0 <= vol <= 100:
        player.set_volume(vol)
    console.write("--> Громкость {0}%".format(player.volume))


def action_play():
    """
    Начать играть текущий плейлист с самого начала
    """
    try:
        playlist.play()
        action_info()
    except Exception as ex:
        console.write(ex)


def action_next():
    """
    Играть следующую песню

    """
    try:
        playlist.next()
        action_info()
    except Exception as ex:
        console.write(ex)


def action_change_order_mode():
    """
    Изменить порядок воспроизведения: (как в файле/случайно/в алфавитном порядке)

    """
    try:
        playlist.toggle_order_mode()
        console.write("Порядок воспроизведения изменен на: %s" % playlist.current_order_mode)
    except Exception as ex:
        console.write(ex)


def action_change_repeat_mode():
    """
    Изменить режим повтора: (нет повтора/повторить весь плейлист/повторить текущий трек)

    """
    try:
        playlist.toggle_repeat_mode()
        console.write("Режим повтора изменен на: %s" % playlist.current_repeat_mode)
    except Exception as ex:
        console.write(ex)


def invalid_input():
    console.write(
        "--> Команда не распознана. Введите 'help' (или 'h') для просмотра всех доступных команд и их описаний")


def action_help():
    """
    Почитать информацию о доступных домандах (то, что вы сейчас читаете)
    """
    for keymap, action in cmd_actions.iteritems():
        console.write("'{0}': {1}".format("' | '".join(keymap), str(action.__doc__).strip()))
    console.write("'{0}': {1}".format("' | '".join(console._quit_list), "Выход из плеера"))

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
        ('om', ): action_change_order_mode,
        ('rm', ): action_change_repeat_mode,
    }

    console = Console(cmd_actions, wrong_input_action=invalid_input)

    plst_name = ""
    if len(sys.argv) > 1:
        plst_name = sys.argv[1]
    else:
        action_help()
        exit()

    playlist = Playlist(playlist_file=plst_name)
    player = Player(action_next)
    playlist.set_player(player)
    console.start()