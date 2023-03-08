import chessWrapper as cw
from tkinter import *

class Chessboard(Canvas):

    images = []
    pieces = ["wp","wN","wB","wR","wQ","wK","bp","bN","bB","bR","bQ","bK"]
    chessboard = cw.chessGame()
    fx = 0
    fy = 0
    tx = 0
    ty = 0
    mp = ""
    cp = ""

    def __init__(self, master=None, cnf={}, **kw):
        Canvas.__init__(self, master=None, cnf={}, **kw)
        #load images
        for x in range(12):
            self.images.append(PhotoImage(file=f"./assets/{self.pieces[x]}.png", name=self.pieces[x]))
        self.drawBoard()
        self.drawPieces()
    
    def drawBoard(self):
        for x in range(8):
            for y in range(8):
                if ((x + y) % 2) == 0:
                    self.create_rectangle(x*100, y*100, x*100 + 100, y*100 + 100, fill="white",outline="white", tags="board")

    def drawPieces(self):
        for x in range(8):
            for y in range(8):
                self.delete(f"x{x}y{y}")
                if self.chessboard.board[x][y] != "--":
                    self.create_image(x*100 + 50, y*100 + 50, image=self.images[self.getImageIndex(self.chessboard.getPiece(x,y))], tags=f"x{x}y{y}")

    def getImageIndex(self, pieceName:str):
        for x in range(12):
            if pieceName == self.images[x].name:
                return x
        return NONE
    
    def mouseDown(self,e):
        self.fx = int(e.x/100)
        self.fy = int(e.y/100)
        self.mp = self.chessboard.getPiece(int(e.x/100),int(e.y/100))
        
        if self.mp != "--":
            self.delete(f"x{int(e.x/100)}y{int(e.y/100)}")
            self.create_image(e.x,e.y, image=self.images[self.getImageIndex(self.mp)], tags = "moving")

    def move(self, e):
        if self.mp != "--":
            self.delete("moving")
            self.create_image(e.x,e.y, image=self.images[self.getImageIndex(self.mp)], tags = "moving")

    def mouseUp(self, e):
        self.delete("moving")

        self.tx = int(e.x/100)
        self.ty = int(e.y/100)
        self.cp = self.chessboard.getPiece(int(e.x/100),int(e.y/100))

        self.chessboard.tryTurn(fy=self.fx, fx=self.fy, ty=self.tx, tx=self.ty, mp=self.mp, cp=self.cp)
        self.chessboard.updateBoard()
        self.drawPieces()

root = Tk()
root.title("Ultra Deluxe Chess")

app_width = 800
app_height = 800

root.geometry(f"{app_width}x{app_height}")

canvas = Chessboard(root, width=app_width,height=app_height, bg="green")

canvas.bind("<B1-Motion>",canvas.move)

canvas.bind("<Button-1>",canvas.mouseDown)

canvas.bind("<ButtonRelease-1>",canvas.mouseUp)

canvas.pack()

root.mainloop()