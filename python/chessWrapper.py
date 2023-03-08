
import ctypes as ct

chessLib = ct.CDLL("./bin/chess.dll")

class chessGame():

    def __init__(self):
        chessLib.initGame()
        self.board = [["--"]*8 for i in range(8)]
        self.updateBoard()

    def updateBoard(self):
        arr = ((ct.c_char_p * 8) * 8)()
        chessLib.readBoard(arr)
        for x in range(8):
            for y in range(8):
                self.board[x][y] = arr[x][y].decode("utf-8")

    def tryTurn(self, fx, fy, tx, ty, mp, cp):
        return int(chessLib.tryTurn(fx, fy, tx, ty, mp.encode(), cp.encode()))

    def printBoard(self):
        for row in range(8):
            print()
            for col in range(8):
                print(self.arr[7-row][7-col].decode(), end = " ")
        print()

    def getPiece(self,x,y) -> str:
        return self.board[x][y]


