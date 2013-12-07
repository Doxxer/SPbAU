# coding=utf-8
def sec_to_time(sec=None):
    """
    Переводит время в секундах в формат MM:SS
    @param sec:
    """
    if not sec:
        sec = 0
    return "{0:02d}:{1:02d}".format(int(sec // 60), int(sec % 60))