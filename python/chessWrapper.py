
import ctypes as ct

chessLib = ct.CDLL("./bin/chess.so")

chessLib.initGame()

arr = ((ct.c_char_p * 8) * 8)()
chessLib.readBoard(arr)

def printboard(arr):
    for row in range(8):
        print()
        for col in range(8):
            print(arr[7-row][7-col].decode(), end = " ")
    print()

printboard(arr)
chessLib.tryTurn(1,1,1,2,"wp".encode(),"--".encode())
chessLib.readBoard(arr)
printboard(arr)

chessLib.tryTurn(1,6,1,5,"bp".encode(),"--".encode())
chessLib.readBoard(arr)
printboard(arr)

