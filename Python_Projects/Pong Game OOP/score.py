from turtle import Turtle

class Score(Turtle):

    def __init__(self):
        super().__init__()
        self.color("white")
        self.penup()
        self.hideturtle()
        self.l_side=0
        self.r_side=0
        self.update()

    def update(self):
        self.clear()
        self.goto(-100,200)
        self.write(self.l_side,align="center",font=("Arial",50,"normal"))
        self.goto(100,200)
        self.write(self.r_side, align="center", font=("Arial", 50, "normal"))

    def l_point(self):
        self.l_side += 1
        self.update()

    def r_point(self):
        self.r_side += 1
        self.update()
