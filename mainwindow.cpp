#include "mainwindow.h"
#include "ui_mainwindow.h"

int cnt=1;
int chanc=0;
int cont=1;
char sq[3][3]={'\0'};
QString tplayers[50];
QString players[3];
int player=1;
int start=0;
char win = '\0';
QString winners[25];
int wicn=0;
int mode = 2;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Tic Tac Toe");
    //this->setWindowIcon();
    ui->radioButton->setVisible(0);
    ui->radioButton_2->setVisible(0);
    ui->lineEdit_3->setVisible(0);
    ui->pushButton_4->setVisible(0);
    ui->label_9->setVisible(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

char checkwin()
{
    win = '\0';
    for(int i=0;i<3;i++)
    {
        if(sq[i][0] == sq[i][1] && sq[i][1]==sq[i][2] && sq[i][1] != '\0')
        {
            win = sq[i][1];
            break;
        }
        if(sq[0][i] == sq[1][i] && sq[1][i]==sq[2][i] && sq[1][i] != '\0')
        {
            win = sq[1][i];
            break;
        }
    }
    if(sq[0][0] == sq[1][1] && sq[1][1]==sq[2][2] && sq[1][1] != '\0')
        win = sq[1][1];
    if(sq[0][2] == sq[1][1] && sq[1][1]==sq[2][0] && sq[1][1] != '\0')
        win = sq[1][1];
    return win;
}
int minimax(char player1, char player2);
int bestMove(char player1, char player2)
{

    int bestScore = -99;
    int x = -99;
    int y = -99;
    int score = 0;

	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			if (sq[r][c] == '\0')
			{
				sq[r][c] = player1;
                score = -(minimax(player2, player1));
                sq[r][c] = '\0';
                if (score >= bestScore)
				{
                    bestScore = score;
                    x = r;
                    y = c;
                }
            }
        }
    }
    return 10*x + y;
}

int minimax(char player1, char player2)
{

    int bestScore = -99;
    int score = 0;

    if (checkwin() == player1)
        return 1000;

    else if (checkwin() == player2)
        return -1000;

	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			if (sq[r][c] == '\0')
			{
				sq[r][c] = player1;
                score = -(minimax(player2, player1));
                sq[r][c] = '\0';
                if (score >= bestScore)
                    bestScore = score;
            }
        }
    }

    if (bestScore == -9999 || bestScore == 0)
        return 0;

    else if (bestScore < 0)
        return bestScore + 1;

    else if (bestScore > 0)
        return bestScore - 1;
}

void MainWindow::gamePlay()
{
    win='\0';
    for(int i=0;i<3;i++)
    {
        if(sq[i][0] == sq[i][1] && sq[i][1]==sq[i][2] && sq[i][1] != '\0')
        {
            win = sq[i][1];
            break;
        }
        if(sq[0][i] == sq[1][i] && sq[1][i]==sq[2][i] && sq[1][i] != '\0')
        {
            win = sq[1][i];
            break;
        }
    }
    if(sq[0][0] == sq[1][1] && sq[1][1]==sq[2][2] && sq[1][1] != '\0')
        win = sq[1][1];
    if(sq[0][2] == sq[1][1] && sq[1][1]==sq[2][0] && sq[1][1] != '\0')
        win = sq[1][1];

    if(win=='X')
    {
        start=0;
        ui->label_4->setText(players[1]+" Wins");
        return;
    }
    if(win=='O')
    {
        start=0;
        ui->label_4->setText(players[2]+" Wins");
        return;
    }
    chanc++;
    if(chanc == 9)
    {
        ui->label_4->setText("Game draw");
        start=0;
        return;
    }

    if(player==1)
        player=2;
    else
        player=1;
    ui->label_4->setText(players[player]+"'s Turn");
    if(mode == 1 && player == 2)
    {
        int mv = bestMove('O' , 'X');
        int ro = mv / 10;
        int cl = mv % 10;
        sq[ro][cl] = 'O';
        switch(mv)
        {
            case 00:
                ui->toolButton->setText("O");
                break;
            case 01:
                ui->toolButton_2->setText("O");
                break;
            case 02:
                ui->toolButton_3->setText("O");
                break;
            case 10:
                ui->toolButton_4->setText("O");
                break;
            case 11:
                ui->toolButton_5->setText("O");
                break;
            case 12:
                ui->toolButton_6->setText("O");
                break;
            case 20:
                ui->toolButton_7->setText("O");
                break;
            case 21:
                ui->toolButton_8->setText("O");
                break;
            case 22:
                ui->toolButton_9->setText("O");
                break;
        }
        gamePlay();
    }
}

void MainWindow::on_toolButton_clicked()
{
    if(ui->toolButton->text() == "" && start == 1)
    {
        if(player==1)
        {
            ui->toolButton->setText("X");
            sq[0][0] = 'X';
            gamePlay();
        }
        else
        {
            ui->toolButton->setText("O");
            sq[0][0] = 'O';
            gamePlay();
        }
    }
}

void MainWindow::on_toolButton_2_clicked()
{
    if(ui->toolButton_2->text() == "" && start == 1)
    {
        if(player==1)
        {
            ui->toolButton_2->setText("X");
            sq[0][1] = 'X';
            gamePlay();
        }
        else
        {
            ui->toolButton_2->setText("O");
            sq[0][1] = 'O';
            gamePlay();
        }
    }
}

void MainWindow::on_toolButton_3_clicked()
{
    if(ui->toolButton_3->text() == "" && start == 1)
    {
        if(player==1)
        {
            ui->toolButton_3->setText("X");
            sq[0][2] = 'X';
            gamePlay();
        }
        else
        {
            ui->toolButton_3->setText("O");
            sq[0][2] = 'O';
            gamePlay();
        }
    }
}

void MainWindow::on_toolButton_4_clicked()
{
    if(ui->toolButton_4->text() == "" && start == 1)
    {
        if(player==1)
        {
            ui->toolButton_4->setText("X");
            sq[1][0] = 'X';
            gamePlay();
        }
        else
        {
            ui->toolButton_4->setText("O");
            sq[1][0] = 'O';
            gamePlay();
        }
    }
}

void MainWindow::on_toolButton_5_clicked()
{
    if(ui->toolButton_5->text() == "" && start == 1)
    {
        if(player==1)
        {
            ui->toolButton_5->setText("X");
            sq[1][1] = 'X';
            gamePlay();
        }
        else
        {
            ui->toolButton_5->setText("O");
            sq[1][1] = 'O';
            gamePlay();
        }
    }
}

void MainWindow::on_toolButton_6_clicked()
{
    if(ui->toolButton_6->text() == "" && start == 1)
    {
        if(player==1)
        {
            ui->toolButton_6->setText("X");
            sq[1][2] = 'X';
            gamePlay();
        }
        else
        {
            ui->toolButton_6->setText("O");
            sq[1][2] = 'O';
            gamePlay();
        }
    }
}

void MainWindow::on_toolButton_7_clicked()
{
    if(ui->toolButton_7->text() == "" && start == 1)
    {
        if(player==1)
        {
            ui->toolButton_7->setText("X");
            sq[2][0] = 'X';
            gamePlay();
        }
        else
        {
            ui->toolButton_7->setText("O");
            sq[2][0] = 'O';
            gamePlay();
        }
    }
}

void MainWindow::on_toolButton_8_clicked()
{
    if(ui->toolButton_8->text() == "" && start == 1)
    {
        if(player==1)
        {
            ui->toolButton_8->setText("X");
            sq[2][1] = 'X';
            gamePlay();
        }
        else
        {
            ui->toolButton_8->setText("O");
            sq[2][1] = 'O';
            gamePlay();
        }
    }
}

void MainWindow::on_toolButton_9_clicked()
{
    if(ui->toolButton_9->text() == "" && start == 1)
    {
        if(player==1)
        {
            ui->toolButton_9->setText("X");
            sq[2][2] = 'X';
            gamePlay();
        }
        else
        {
            ui->toolButton_9->setText("O");
            sq[2][2] = 'O';
            gamePlay();
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    player=1;
    win = '\0';
    wicn=0;
    chanc=0;
    if(mode == 2)
    players[1]=ui->lineEdit->text();
    players[2]=ui->lineEdit_2->text();
    if(mode == 1)
    {
        players[2] = "CPU";
    }
        ui->radioButton->setVisible(0);
        ui->radioButton_2->setVisible(0);
        ui->lineEdit_3->setVisible(0);
        ui->pushButton_4->setVisible(0);

    ui->label_8->setText(players[1]+" Vs "+players[2]);

    if(players[1] == "" || players[2] == "")
    {
        ui->label_4->setText("Enter Names of players");
    }
    else
    {
        ui->label_4->setText(players[1]+"'s Turn");
        start=1;
    }
    win='\0';
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            sq[i][j]={'\0'};
    ui->toolButton->setText("");
    ui->toolButton_2->setText("");
    ui->toolButton_3->setText("");
    ui->toolButton_4->setText("");
    ui->toolButton_5->setText("");
    ui->toolButton_6->setText("");
    ui->toolButton_7->setText("");
    ui->toolButton_8->setText("");
    ui->toolButton_9->setText("");
}

void MainWindow::on_pushButton_2_clicked()
{
    win='\0';
    cnt=1;
    cont=1;
    player=1;
    win = '\0';
    //mode = 2;
    chanc=0;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            sq[i][j]={'\0'};
    ui->toolButton->setText("");
    ui->toolButton_2->setText("");
    ui->toolButton_3->setText("");
    ui->toolButton_4->setText("");
    ui->toolButton_5->setText("");
    ui->toolButton_6->setText("");
    ui->toolButton_7->setText("");
    ui->toolButton_8->setText("");
    ui->toolButton_9->setText("");
    player=1;
    start=1;
    ui->label_4->setText(players[1]+"'s Turn");
}

void MainWindow::on_pushButton_3_clicked()
{
    if(ui->radioButton->isVisible() == true)
    {
        ui->radioButton->setVisible(0);
        ui->radioButton_2->setVisible(0);
    }
    else
    {
        ui->radioButton->setVisible(1);
        ui->radioButton_2->setVisible(1);
    }
}

void MainWindow::on_lineEdit_3_returnPressed()
{
    if(ui->lineEdit_3->text() == "")
        return;

    if(mode == 1)
    {
        players[1] = ui->lineEdit_3->text();
        players[2] = "CPU";
        ui->label_4->setText("Start the game");
        return;
    }
}

void MainWindow::on_radioButton_clicked()
{
    mode = 1;
    ui->label_6->setText("Single Player");
    ui->lineEdit_3->setVisible(1);
    ui->pushButton_4->setVisible(1);
}

void MainWindow::on_radioButton_2_clicked()
{
    mode = 2;
    ui->label_6->setText("2 Player Game");
    ui->lineEdit_3->setVisible(0);
    ui->pushButton_4->setVisible(0);
}

void MainWindow::on_pushButton_4_clicked()
{
    if(ui->lineEdit_3->text() == "")
        return;

    if(mode == 1)
    {
        players[1] = ui->lineEdit_3->text();
        players[2] = "CPU";
        ui->label_4->setText("Start the game");
        ui->lineEdit->setText(ui->lineEdit_3->text());
        ui->lineEdit_2->setText(players[2]);
        return;
    }

    if(mode == 2)
    {
        players[1] = ui->lineEdit_3->text();
        players[2] = ui->lineEdit_3->text();
        ui->label_4->setText("Start the game");
        return;
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->label_8->setText(ui->label_9->text());
    ui->label_9->setVisible(0);
    win='\0';
    chanc=0;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            sq[i][j]={'\0'};
    ui->toolButton->setText("");
    ui->toolButton_2->setText("");
    ui->toolButton_3->setText("");
    ui->toolButton_4->setText("");
    ui->toolButton_5->setText("");
    ui->toolButton_6->setText("");
    ui->toolButton_7->setText("");
    ui->toolButton_8->setText("");
    ui->toolButton_9->setText("");
    player=1;
    start=1;
    ui->label_4->setText(players[1]+"'s Turn");
}
