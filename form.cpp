#include "form.h"
#include "ui_form.h"
#include <QVector>
#include <QFont>
#include <QString>

/* Конструктор */

Form::Form(int s1[], int f1[], int s2[], int f2[], int tf[], int ff[], int i[], int j[], int s, int mas[], int t, int d, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    /* Присвоение значений переменным класса из переменных конструктора */

    this->s=s;
    this->t=t;
    this->d=d;

    for (int n=0;n<15;n++)
    {
        this->s1[n]=s1[n];
        this->f1[n]=f1[n];
        this->f2[n]=f2[n];
        this->s2[n]=s2[n];
        this->tf[n]=tf[n];
        this->ff[n]=ff[n];
        this->i[n]=i[n];
        this->j[n]=j[n];
        this->mas[n]=mas[n];
    }

    make_table(); //создать таблицу

/* Заполнение таблицы числами из массивов s1, s2, f1, f2, tf, ff, i, j, mas */
    for (int n=0;n<15;n++)
    {
        ui->tableWidget->setItem(n,0,new QTableWidgetItem(QString::number(i[n])));
        ui->tableWidget->setItem(n,1,new QTableWidgetItem(QString::number(j[n])));
        ui->tableWidget->setItem(n,2,new QTableWidgetItem(QString::number(f1[n]-s1[n])));
        ui->tableWidget->setItem(n,3,new QTableWidgetItem(QString::number(s1[n])));
        ui->tableWidget->setItem(n,4,new QTableWidgetItem(QString::number(f1[n])));
        ui->tableWidget->setItem(n,5,new QTableWidgetItem(QString::number(s2[n])));
        ui->tableWidget->setItem(n,6,new QTableWidgetItem(QString::number(f2[n])));
        ui->tableWidget->setItem(n,7,new QTableWidgetItem(QString::number(ff[n])));
        ui->tableWidget->setItem(n,8,new QTableWidgetItem(QString::number(tf[n])));
    }
}

/* Деструктор */

Form::~Form()
{
    delete ui;
}

/* Построение графика */

void Form::makePlot()
{
    ui->customPlot->clearPlottables();//очистить поле от предыдущего графика
    QCPBars *fossil = new QCPBars(ui->customPlot->yAxis, ui->customPlot->xAxis);//создаем объект для рисования графика
    QCPBars *fossil2 = new QCPBars(ui->customPlot->yAxis, ui->customPlot->xAxis);//создаем объект для рисования графика
    QVector<double> ticks;//массив значения x
    QVector<double> fossilData;//массив значений y
    QVector<double> fossilData2;//массив значений y
    QVector<QString> labels;
    for (int k=1;k<=N;k++) ticks << k;
    for (int n=0;n<N;n++) fossilData << f1[n];
    for (int n=0;n<N;n++) fossilData2 << s1[n];
    /* Задание значений для оси Y (подписи на оси) */
    for(int x=0;x<N;x++) labels << "(" + QString::number(i[x])+ "," + QString::number(j[x]) + ")";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks,labels);
    ui->customPlot->yAxis->setTicker(textTicker);
    ui->customPlot->yAxis->setBasePen(QPen(Qt::white)); //установка белого цвета цифр
    ui->customPlot->xAxis->setBasePen(QPen(Qt::white)); //для осей Х и Y
    ui->customPlot->xAxis->setTickPen(QPen(Qt::white)); //установка белого цвета черточек
    ui->customPlot->yAxis->setTickPen(QPen(Qt::white)); //для осей Х и Y
    ui->customPlot->yAxis->setSubTickPen(QPen(Qt::white)); //белые черточки на оси Y
    ui->customPlot->xAxis->setSubTickPen(QPen(Qt::white)); //белые черточки на оси Х
    ui->customPlot->yAxis->setTickLabelColor(Qt::white); //белые надписи на оси Y
    ui->customPlot->xAxis->setTickLabelColor(Qt::white); //белые надписи на оси X
    ui->customPlot->setBackground(QBrush(QColor(70, 70, 70))); //задний фон
    ui->customPlot->yAxis->setPadding(30); //насколько график по оси Y отходит от края виджета
    ui->customPlot->xAxis->setPadding(30); //насколько график по оси Х отходит от края виджета
    ui->customPlot->xAxis->setLabel("Время");   //задание названия оси Х
    ui->customPlot->xAxis->setLabelColor(QColor(Qt::white));    //цвет для названия оси Х
    ui->customPlot->xAxis->setLabelPadding(20); //отступ для названия оси Х
    QFont f("Times",14,QFont::Bold);    //выбор шрифта
    ui->customPlot->xAxis->setLabelFont(f); //задание шрифта для надписи оси Х
    ui->customPlot->yAxis->setLabel("Работы");  //задание названия оси Y
    ui->customPlot->yAxis->setLabelColor(QColor(Qt::white));    //цвет для названий оси Y
    ui->customPlot->yAxis->setLabelPadding(20); //отступ для названия оси Y
    ui->customPlot->yAxis->setLabelFont(f);     //задание шрифта для надписи оси Y
    fossil2->setBrush(QColor(70, 70, 70)); //цвет невидимой диаграммы
    fossil2->setPen(QPen(QColor(70, 70, 70))); //контур невидимой диаграммы
    fossil->setBrush(QColor(80, 177, 204)); //цвет диаграммы
    fossil->setPen(QPen(QColor(70, 70, 70))); //цвет контура диаграммы
    ui->customPlot->xAxis->grid()->setVisible(false);   //сделать невидимой сетку для оси Х
    ui->customPlot->yAxis->grid()->setVisible(false);   //сделать невидимой сетку для оси Y

    // Данные:

    fossil2->setData(ticks,fossilData2);
    fossil->setData(ticks, fossilData); //нарисовать график, каждому ticks сопоставится fossilData

    int x_max=0;
    for(int x=0;x<N;x++) if(f1[x]>x_max) x_max=f1[x];
    ui->customPlot->yAxis->setRange(0, 16*N/15);//установка оси x графика
    ui->customPlot->xAxis->setRange(0, x_max);//установка оси y графика
    ui->customPlot->replot();//нарисовать график
}

/* Построение таблицы */

void Form::make_table()
{
    ui->tableWidget->setColumnCount(9); //число столбцов
    ui->tableWidget->setRowCount(15);   //число строк
    ui->tableWidget->setColumnWidth(0,70); //задание ширины столбца 1
    ui->tableWidget->setColumnWidth(1,70); //задание ширины столбца 1
    ui->tableWidget->setColumnWidth(2,120);  //задание ширины столбца 2
    ui->tableWidget->setColumnWidth(3,70);  //задание ширины столбца 3
    ui->tableWidget->setColumnWidth(4,60);  //задание ширины столбца 4
    ui->tableWidget->setColumnWidth(5,70);  //задание ширины столбца 5
    ui->label->setText("Сроки начала и окончания работ"); //задание надписи над таблицей
    ui->label_2->setText("Резервы времени работ");  //задание надписи над таблицей

    /* Задание названий всех столбцов */
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Начальная\nвершина i")));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Конечная\nвершина j")));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Продолжительность\n работы t(i,j)")));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("\n\nРаннее\nначало\ntрн")));
    ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem(tr("\n\nРаннее\nокончание\ntро")));
    ui->tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem(tr("\n\nПозднее\nначало\ntпн")));
    ui->tableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem(tr("\n\nПозднее\nокончание\ntпо")));
    ui->tableWidget->setHorizontalHeaderItem(7, new QTableWidgetItem(tr("\n\nПолный\n резерв Rп")));
    ui->tableWidget->setHorizontalHeaderItem(8, new QTableWidgetItem(tr("\n\nСвободный\n резерв Rc")));

    /* Задание надписей под таблицей */

    ui->label_3->setText(QString("Продолжительность критического пути: %1").arg(s));
    ui->label_3->adjustSize();
    ui->label_5->setText(QString("Критический путь: 1->%1->%2->%3->%4->%5->%6").arg(mas[2]).arg(mas[5]).arg(mas[6]).arg(mas[8]).arg(mas[11]).arg(mas[13]));
    ui->label_5->adjustSize();
    ui->label_4->setText(QString("Ожидаемое время выполнения работ (продолжительность проекта): %1").arg(t));
    ui->label_4->adjustSize();
    ui->label_6->setText(QString("Продолжительность минимального пути: %1").arg(d));
    ui->label_6->adjustSize();
}

/* Построить график */
void Form::on_makeGraph_clicked()
{
    /* Считывание чисел из таблицы. Если в таблице поменять значения,
       то при нажатии на кнопку график перестроится с новыми значениями */
    QString number;
    delete i;
    delete j;
    delete s1;
    delete f1;
    i=new int[N];
    j=new int[N];
    s1=new int[N];
    f1=new int[N];
    for(int k=0;k<N;k++)
    {
        number=ui->tableWidget->item(k,0)->text();
        i[k]=number.toInt();
        number=ui->tableWidget->item(k,1)->text();
        j[k]=number.toInt();
        number=ui->tableWidget->item(k,3)->text();
        s1[k]=number.toInt();
        number=ui->tableWidget->item(k,4)->text();
        f1[k]=number.toInt();
        //number=ui->tableWidget->item(k,5)->text();
        /*s2[k]=number.toInt();
        number=ui->tableWidget->item(k,6)->text();
        f2[k]=number.toInt();
        number=ui->tableWidget->item(k,7)->text();
        tf[k]=number.toInt();
        number=ui->tableWidget->item(k,8)->text();
        ff[k]=number.toInt();*/
    }
    makePlot(); //построить график
}

/* Добавление строки в таблицу */
void Form::on_insertRow_clicked()
{
    //int i;
    N = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(N);
    N++;
}

/* Удаление строки из таблицы */
void Form::on_removeRow_clicked()
{
 //   int i;
    N = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(N-1);
    N--;
}
