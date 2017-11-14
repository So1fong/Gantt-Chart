#ifndef FORM_H
#define FORM_H
#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(int s1[], int f1[], int s2[], int f2[], int ff[], int tf[], int i[], int j[], int s, int mas[], int t, int d, QWidget *parent = 0);
    ~Form();
    int *s1=new int[15];
    int *f1=new int[15];
    int s2[15];
    int f2[15];
    int ff[15];
    int tf[15];
    int *i=new int[15];
    int *j=new int[15];
    int s;
    int t;
    int mas[15];
    int d;
    int N = 15;
    void make_table();

private slots:
    void makePlot();
    void on_makeGraph_clicked();
    void on_insertRow_clicked();
    void on_removeRow_clicked();

private:
    Ui::Form *ui;
};

#endif // FORM_H
