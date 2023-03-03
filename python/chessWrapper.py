
import ctypes as ct

chessLib = ct.CDLL("./bin/chess")

chessLib.initGame()

arr = ((ct.c_char_p * 8) * 8)()
chessLib.readBoard(arr)

def printboard(arr):
    for row in range(8):
        print()
        for col in range(8):
            print(arr[7-row][7-col].decode("utf-8"), end = " ")

def getBoard(arr: int[8][8]) -> int[8][8]:
    return None

printboard(arr)

