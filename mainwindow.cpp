#include <QtGui>
#include "mainwindow.h"
#include "ui_mainwindow.h"

struct State
{
    int flag;
    double value;
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),icon0(":/icons/0.png"),
    icon1(":/icons/1.png"),icon2(":/icons/2.png"),
    icon11(":/icons/11.png"),icon22(":/icons/22.png")

{
    hardLevel=1;
    ui->setupUi(this);
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            pushButtonList[i][j]=new QPushButton;

            pushButtonList[i][j]->setFixedSize(40,40);
            pushButtonList[i][j]->setIconSize(QSize(40,40));

            connect(pushButtonList[i][j],SIGNAL(clicked()),this,SLOT(buttons_clicked()));
            ui->gridLayout->addWidget(pushButtonList[i][j],i,j);
        }
    for(int i=1;i<9;i++)
        pushButtonList[i][0]->setText(QString::number(i));
    for(int j=1;j<9;j++)
        pushButtonList[0][j]->setText(QString::number(j));

    init();
}

void MainWindow::init()
{
    c=1;
    num1=2;
    num2=2;
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
        {
            if(i==0||i==9||j==0||j==9)
                a[i][j]=-1;
            else
                a[i][j]=0;
        }
    a[4][4]=1;
    a[4][5]=2;
    a[5][4]=2;
    a[5][5]=1;
    pArray();
    ui->label_2->setText("2");
    ui->label_4->setText("2");
    ui->label_5->setText(QString::fromLocal8Bit("黑棋落子"));
    pushButtonList[0][0]->setIcon(icon11);
    if(hardLevel==1)
        ui->label_8->setText(QString::fromLocal8Bit("低"));
    else if(hardLevel==2)
        ui->label_8->setText(QString::fromLocal8Bit("中"));
    else
        ui->label_8->setText(QString::fromLocal8Bit("高"));

}

void MainWindow::pArray()
{
    for(int i=1;i<=8;i++)
        for(int j=1;j<=8;j++)
        {
            if (a[i][j]==0)
            {
                pushButtonList[i][j]->setIcon(icon0);
            }
            else if (a[i][j]==1)
            {
                pushButtonList[i][j]->setIcon(icon1);
            }
            else if (a[i][j]==2)
            {
                pushButtonList[i][j]->setIcon(icon2);
            }
        }
}

int MainWindow::SF1Array(int i, int j)
{
    int x,y,n;
    if(a[i][j-1]==2||a[i][j+1]==2||a[i-1][j]==2||a[i+1][j]==2||a[i-1][j-1]==2||a[i+1][j-1]==2||a[i-1][j+1]==2||a[i+1][j+1]==2){
        n=0;

        //横向
        if(a[i][j-1]==2)
        {
            x=i;
            y=j-1;
            while(x>=1&&x<=8&&y>=1&&y<=8&&a[x][y]==2)
            {
                y--;
            }
            if(a[x][y]==1)
            {
                for(y=y+1;y<=j-1;y++)
                {
                    a[x][y]=1;
                    num1++;
                    num2--;
                    n++;
                }
            }
        }
        if(a[i][j+1]==2)
        {
            x=i;
            y=j+1;
            while(x>=1&&x<=8&&y>=1&&y<=8&&a[x][y]==2)
            {
                y++;
            }
            if(a[x][y]==1)
            {
                for(y=y-1;y>=j+1;y--)
                {
                    a[x][y]=1;
                    num1++;
                    num2--;
                    n++;
                }
            }
        }

        //纵向
        if(a[i-1][j]==2)
        {
            x=i-1;
            y=j;
            while(x>=1&&x<=8&&y>=1&&y<=8&&a[x][y]==2)
            {
                x--;
            }
            if(a[x][y]==1)
            {
                for(x=x+1;x<=i-1;x++)
                {
                    a[x][y]=1;
                    num1++;
                    num2--;
                    n++;
                }
            }
        }
        if(a[i+1][j]==2)
        {
            x=i+1;
            y=j;
            while(x>=1&&x<=8&&y>=1&&y<=8&&a[x][y]==2)
            {
                x++;
            }
            if(a[x][y]==1)
            {
                for(x=x-1;x>=i+1;x--)
                {
                    a[x][y]=1;
                    num1++;
                    num2--;
                    n++;
                }
            }
        }

        //对角线
        if(a[i-1][j-1]==2)
        {
            x=i-1;
            y=j-1;
            while(x>=1&&x<=8&&y>=1&&y<=8&&a[x][y]==2)
            {
                x--;
                y--;
            }
            if(a[x][y]==1)
            {
                for(x=x+1,y=y+1;x<=i-1||y<=j-1;x++,y++)
                {
                    a[x][y]=1;
                    num1++;
                    num2--;
                    n++;
                }
            }
        }
        if(a[i+1][j+1]==2)
        {
            x=i+1;
            y=j+1;
            while(x>=1&&x<=8&&y>=1&&y<=8&&a[x][y]==2)
            {
                x++;
                y++;
            }
            if(a[x][y]==1)
            {
                for(x=x-1,y=y-1;x>=i+1||y>=j+1;x--,y--)
                {
                    a[x][y]=1;
                    num1++;
                    num2--;
                    n++;
                }
            }
        }

        //逆对角线
        if(a[i+1][j-1]==2)
        {
            x=i+1;
            y=j-1;
            while(x>=1&&x<=8&&y>=1&&y<=8&&a[x][y]==2)
            {
                x++;
                y--;
            }
            if(a[x][y]==1)
            {
                for(x=x-1,y=y+1;x>=i+1||y<=j-1;x--,y++)
                {
                    a[x][y]=1;
                    num1++;
                    num2--;
                    n++;
                }
            }
        }
        if(a[i-1][j+1]==2)
        {
            x=i-1;
            y=j+1;
            while(x>=1&&x<=8&&y>=1&&y<=8&&a[x][y]==2)
            {
                x--;
                y++;
            }
            if(a[x][y]==1)
            {
                for(x=x+1,y=y-1;x<=i-1||y>=j+1;x++,y--)
                {
                    a[x][y]=1;
                    num1++;
                    num2--;
                    n++;
                }
            }
        }
        if(n==0){
            a[i][j]=0;
            //	QPArray();
            return 4;}
    }
    else
    {
        a[i][j]=0;
        //QPArray();
        return 4;
    }
    if(num1+num2==64)
    {
        if(num1>num2) return 1;
        if(num1<num2) return 2;
        else return 3;
    }
    else if(num1==0||num2==0)
    {
        if(num2==0) return 1;
        if(num1==0) return 2;
        else return 3;
    }
    else
    {
        return 0;
    }
}

int MainWindow::SF2Array(int i, int j)
{
    int x,y,n;
    if(a[i][j-1]==1||a[i][j+1]==1||a[i-1][j]==1||a[i+1][j]==1||a[i-1][j-1]==1||a[i+1][j-1]==1||a[i-1][j+1]==1||a[i+1][j+1]==1){
        n=0;
        //横向
        if(a[i][j-1]==1)
        {
            x=i;
            y=j-1;
            while(x>=1&&x<=8&&y>=1&&y<=8&&a[x][y]==1)
            {
                y--;
            }
            if(a[x][y]==2)
            {
                for(y=y+1;y<=j-1;y++)
                {
                    a[x][y]=2;
                    num2++;
                    num1--;
                    n++;
                }
            }
        }
        if(a[i][j+1]==1)
        {
            x=i;
            y=j+1;
            while(x>=1&&x<=8&&y>=1&&y<=8&&a[x][y]==1)
            {
                y++;
            }
            if(a[x][y]==2)
            {
                for(y=y-1;y>=j+1;y--)
                {
                    a[x][y]=2;
                    num2++;
                    num1--;
                    n++;
                }
            }
        }

        //纵向
        if(a[i-1][j]==1)
        {
            x=i-1;
            y=j;
            while(x>=1&&x<=8&&y>=1&&y<=8&&a[x][y]==1)
            {
                x--;
            }
            if(a[x][y]==2)
            {
                for(x=x+1;x<=i-1;x++)
                {
                    a[x][y]=2;
                    num2++;
                    num1--;
                    n++;
                }
            }
        }
        if(a[i+1][j]==1)
        {
            x=i+1;
            y=j;
            while(x>=1&&x<=8&&y>=1&&y<=8&&a[x][y]==1)
            {
                x++;
            }
            if(a[x][y]==2)
            {
                for(x=x-1;x>=i+1;x--)
                {
                    a[x][y]=2;
                    num2++;
                    num1--;
                    n++;
                }
            }
        }

        //对角线
        if(a[i-1][j-1]==1)
        {
            x=i-1;
            y=j-1;
            while(x>=1&&x<=8&&y>=1&&y<=8&&a[x][y]==1)
            {
                x--;
                y--;
            }
            if(a[x][y]==2)
            {
                for(x=x+1,y=y+1;x<=i-1||y<=j-1;x++,y++)
                {
                    a[x][y]=2;
                    num2++;
                    num1--;
                    n++;
                }
            }
        }
        if(a[i+1][j+1]==1)
        {
            x=i+1;
            y=j+1;
            while(x>=1&&x<=8&&y>=1&&y<=8&&a[x][y]==1)
            {
                x++;
                y++;
            }
            if(a[x][y]==2)
            {
                for(x=x-1,y=y-1;x>=i+1||y>=j+1;x--,y--)
                {
                    a[x][y]=2;
                    num2++;
                    num1--;
                    n++;
                }
            }
        }

        //逆对角线
        if(a[i+1][j-1]==1)
        {
            x=i+1;
            y=j-1;
            while(x>=1&&x<=8&&y>=1&&y<=8&&a[x][y]==1)
            {
                x++;
                y--;
            }
            if(a[x][y]==2)
            {
                for(x=x-1,y=y+1;x>=i+1||y<=j-1;x--,y++)
                {
                    a[x][y]=2;
                    num2++;
                    num1--;
                    n++;
                }
            }
        }
        if(a[i-1][j+1]==1)
        {
            x=i-1;
            y=j+1;
            while(x>=1&&x<=8&&y>=1&&y<=8&&a[x][y]==1)
            {
                x--;
                y++;
            }
            if(a[x][y]==2)
            {
                for(x=x+1,y=y-1;x<=i-1||y>=j+1;x++,y--)
                {
                    a[x][y]=2;
                    num2++;
                    num1--;
                    n++;
                }
            }
        }
        if(n==0){
            a[i][j]=0;
            //		QPArray();
            return 4;}
    }
    else
    {
        a[i][j]=0;
        //		QPArray();
        return 4;
    }
    if(num1+num2==64)
    {
        if(num1>num2) return 1;
        if(num1<num2) return 2;
        else return 3;
    }
    else if(num1==0||num2==0)
    {
        if(num2==0) return 1;
        if(num1==0) return 2;
        else return 3;
    }
    else
    {
        return 0;
    }
}



void MainWindow::buttons_clicked()
{
    QPushButton *pushButton=(QPushButton *)sender();
    int m=0,n=0;
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            if(pushButton==pushButtonList[i][j])
            {
                m=i;
                n=j;
                break;
            }
        }
    if(m==0&&n==0)
    {
        if(c==1)
        {
            c=2;
            ui->label_5->setText(QString::fromLocal8Bit("白棋落子"));
            pushButtonList[0][0]->setIcon(icon22);
            aiDo();
        }
    }

    if(m==0||n==0)
        return;

    if(a[m][n]==0)
    {
        /////
        if(c==1)
        {
            num1++;
            a[m][n]=1;
            int g=SF1Array(m,n);

            pArray();
            ui->label_2->setText(QString::number(num1));
            ui->label_4->setText(QString::number(num2));

            if(g!=4){
                if(g!=0)
                {
                    if(g==1)
                    {

                        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("黑方获胜！"));
                        init();
                    }
                    if(g==2)
                    {

                        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("白方获胜！"));
                        init();
                    }
                    if(g==3)
                    {

                        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("平局！"));
                        init();
                    }
                }
                else
                {

                    c=2;
                    ui->label_5->setText(QString::fromLocal8Bit("白棋落子"));
                    pushButtonList[0][0]->setIcon(icon22);
                    aiDo();

                }

            }
            else
                num1--;

        }

       /* else
        {
            num2++;
            a[m][n]=2;
            int g=SF2Array(m,n);

            pArray();
            ui->label_2->setText(QString::number(num1));
            ui->label_4->setText(QString::number(num2));

            if(g!=4){
                if(g!=0)
                {
                    if(g==1)
                    {
                        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("黑方获胜！"));
                        init();
                    }
                    if(g==2)
                    {
                        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("白方获胜！"));
                        init();
                    }
                    if(g==3)
                    {
                         QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("平局！"));
                        init();
                    }
                }
                else
                {

                    c=1;
                    ui->label_5->setText(QString::fromLocal8Bit("黑棋落子"));
                    pushButtonList[0][0]->setIcon(icon11);
                }

            }
            else
                num2--;

        }*/




        /////
    }
    else
        return;



}

void MainWindow::aiDo()
{
    if(hardLevel==1)
        aiDo1();
    else if(hardLevel==2)
        aiDo2();
    else
        aiDo3();
}

void MainWindow::aiDo1()
{
    QTime dieTime = QTime::currentTime().addMSecs(1000);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    int h;
    for(int r=1;r<65;r++)
    {
        int p=(r-1)/8+1;
        int q=(r-1)%8+1;

        if(a[p][q]==0)
        {
            num2++;
            a[p][q]=2;
            h=SF2Array(p,q);

            pArray();
            ui->label_2->setText(QString::number(num1));
            ui->label_4->setText(QString::number(num2));

            if(h!=4)
                break;
            else
                num2--;
        }
   }

    if(h!=0&&h!=4)
    {
        if(h==1)
        {
            QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("黑方获胜！"));
            init();
        }
        if(h==2)
        {
            QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("白方获胜！"));
            init();
        }
        if(h==3)
        {
             QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("平局！"));
            init();
        }
    }
    else
    {

        c=1;
        ui->label_5->setText(QString::fromLocal8Bit("黑棋落子"));
        pushButtonList[0][0]->setIcon(icon11);
    }
}

void MainWindow::aiDo2()
{
    QTime dieTime = QTime::currentTime().addMSecs(1000);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    State stateTable[8][8];

    int back_num1,back_num2,back_a[10][10];



    int h=-1;
    for(int r=1;r<65;r++)
    {
        int p=(r-1)/8+1;
        int q=(r-1)%8+1;

        if(a[p][q]==0)
        {
            back_num1=num1;
            back_num2=num2;
            for(int i=0;i<10;i++)
                for(int j=0;j<10;j++)
                    back_a[i][j]=a[i][j];

            num2++;
            a[p][q]=2;
            h=SF2Array(p,q);


            if(h!=4)
            {


                if(h!=0)
                {
                    pArray();
                    ui->label_2->setText(QString::number(num1));
                    ui->label_4->setText(QString::number(num2));
                    break;
                }
                else
                {
                    stateTable[p-1][q-1].flag=1;
                    stateTable[p-1][q-1].value=num2-num1;
                    num1=back_num1;
                    num2=back_num2;
                    for(int i=0;i<10;i++)
                        for(int j=0;j<10;j++)
                            a[i][j]=back_a[i][j];
                }



            }
            else
            {
                num2--;
                stateTable[p-1][q-1].flag=0;
            }
        }
        else
        {
            stateTable[p-1][q-1].flag=0;
        }
   }

        if(h==1)
        {
            QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("黑方获胜！"));
            init();
        }
        else if(h==2)
        {
            QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("白方获胜！"));
            init();
        }
        else if(h==3)
        {
             QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("平局！"));
            init();
        }
        else
        {
            int hasFlag=0,isFirst=1,max_x=0,max_y=0;
            double max_value;
            for(int i=0;i<8;i++)
                for(int j=0;j<8;j++)
                {
                    if(stateTable[i][j].flag==1)
                    {
                        hasFlag=1;
                        if(isFirst==1)
                        {
                            max_value=stateTable[i][j].value;
                            max_x=i+1;
                            max_y=j+1;
                            isFirst=0;
                        }
                        else
                        {
                            if(stateTable[i][j].value>max_value)
                            {
                                max_value=stateTable[i][j].value;
                                max_x=i+1;
                                max_y=j+1;
                            }
                        }

                    }
                }



            if(hasFlag==1)
            {
               /* QString str="max_value:";
                str.append(QString::number(max_value));
                 str.append(" max_x:");
                 str.append(QString::number(max_x));
                 str.append(" max_y:");
                  str.append(QString::number(max_y));
                QMessageBox::information(this,QString::fromLocal8Bit("提示"),str);*/

                 num2++;
                 a[max_x][max_y]=2;
                 SF2Array(max_x,max_y);
                 pArray();
                 ui->label_2->setText(QString::number(num1));
                 ui->label_4->setText(QString::number(num2));


            }


            c=1;
            ui->label_5->setText(QString::fromLocal8Bit("黑棋落子"));
            pushButtonList[0][0]->setIcon(icon11);

        }



}

void MainWindow::aiDo3()
{
    QTime dieTime = QTime::currentTime().addMSecs(1000);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    State stateTable[8][8];

    int back_num1,back_num2,back_a[10][10];



    int h=-1;
    for(int r=1;r<65;r++)
    {
        int p=(r-1)/8+1;
        int q=(r-1)%8+1;

        if(a[p][q]==0)
        {
            back_num1=num1;
            back_num2=num2;
            for(int i=0;i<10;i++)
                for(int j=0;j<10;j++)
                    back_a[i][j]=a[i][j];

            num2++;
            a[p][q]=2;
            h=SF2Array(p,q);


            if(h!=4)
            {


                if(h!=0)
                {
                    pArray();
                    ui->label_2->setText(QString::number(num1));
                    ui->label_4->setText(QString::number(num2));
                    break;
                }
                else
                {
                    stateTable[p-1][q-1].flag=1;
                    stateTable[p-1][q-1].value=computePositonValue(p,q);
                    num1=back_num1;
                    num2=back_num2;
                    for(int i=0;i<10;i++)
                        for(int j=0;j<10;j++)
                            a[i][j]=back_a[i][j];
                }



            }
            else
            {
                num2--;
                stateTable[p-1][q-1].flag=0;
            }
        }
        else
        {
            stateTable[p-1][q-1].flag=0;
        }
   }

        if(h==1)
        {
            QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("黑方获胜！"));
            init();
        }
        else if(h==2)
        {
            QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("白方获胜！"));
            init();
        }
        else if(h==3)
        {
             QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("平局！"));
            init();
        }
        else
        {
            int hasFlag=0,isFirst=1,max_x=0,max_y=0;
            double max_value;
            for(int i=0;i<8;i++)
                for(int j=0;j<8;j++)
                {
                    if(stateTable[i][j].flag==1)
                    {
                        hasFlag=1;
                        if(isFirst==1)
                        {
                            max_value=stateTable[i][j].value;
                            max_x=i+1;
                            max_y=j+1;
                            isFirst=0;
                        }
                        else
                        {
                            if(stateTable[i][j].value>max_value)
                            {
                                max_value=stateTable[i][j].value;
                                max_x=i+1;
                                max_y=j+1;
                            }
                        }

                    }
                }



            if(hasFlag==1)
            {
               /* QString str="max_value:";
                str.append(QString::number(max_value));
                 str.append(" max_x:");
                 str.append(QString::number(max_x));
                 str.append(" max_y:");
                  str.append(QString::number(max_y));
                QMessageBox::information(this,QString::fromLocal8Bit("提示"),str);*/

                 num2++;
                 a[max_x][max_y]=2;
                 SF2Array(max_x,max_y);
                 pArray();
                 ui->label_2->setText(QString::number(num1));
                 ui->label_4->setText(QString::number(num2));


            }


            c=1;
            ui->label_5->setText(QString::fromLocal8Bit("黑棋落子"));
            pushButtonList[0][0]->setIcon(icon11);

        }

}

double MainWindow::computePositonValue(int x, int y)
{
    double xValue,yValue;
    int temp;
    temp=((x-1)<(8-x))?(x-1):(8-x);
    xValue=pow(2,3-temp);
    temp=((y-1)<(8-y))?(y-1):(8-y);
    yValue=pow(2,3-temp);
    return xValue*xValue+yValue*yValue;
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_action_triggered()
{
    QMessageBox::about(this, QString::fromLocal8Bit("关于 本程序"),
            QString::fromLocal8Bit("<h2>黑白棋 v 1.1</h2>"
               "<p>Copyright &copy; 2012 3090104493@zju.edu.cn.</p>"
               "<p>更新增加电脑AI，支持人机对战</p>"
               "<p>低级:AI使用first fit</p>"
               "<p>中级:用棋子数为权值</p>"
               "<p>高级:用位置为权值</p>"
               "<p>这 是一个小demo，各种bugs不负责。</p>"
               "<p>完成日期:2012-1-4</p>"));    //设置关于页面显示的内容
}

void MainWindow::on_action_2_triggered()
{
    init();
}

void MainWindow::on_action_4_triggered()
{
     hardLevel=1;
     init();
}

void MainWindow::on_action_5_triggered()
{
    hardLevel=2;
    init();
}

void MainWindow::on_action_6_triggered()
{
    hardLevel=3;
    init();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    this->setWindowOpacity(1-value/100.0);
}
