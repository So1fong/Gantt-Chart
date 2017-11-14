#include <QApplication>
#include <QDebug>
#include <form.h>

int n = 15;

/* Функция для вычисления критического пути и параметров сетевого графика */

void Critical_Path (int n, int i[], int j[], int dij[],
               int *s1, int *s2, int *f1, int *f2, int *tf, int *ff)
{
  int k,index,max,min;
  int ti[n],te[n];

  index = 0;
  for (k=0;k<n;k++)
  {
    if ( i[k]==index+1 )  index = i[k];
    ti[k] = 0; te[k] = 9999;
  }
  for (k=0;k<n;k++)
  {
    max = ti[i[k]] + dij[k];
    if ( ti[j[k]]<max ) ti[j[k]] = max;
  }
  te[j[n-1]] = ti[j[n-1]];
  for (k=n-1;k>=0;k--)
  {
    min = te[j[k]] - dij[k];
    if ( te[i[k]]>min ) te[i[k]] = min;
  }
  for (k=0;k<n;k++)
  {
    s1[k] = ti[i[k]]; f1[k] = s1[k] + dij[k];
    f2[k] = te[j[k]]; s2[k] = f2[k] - dij[k];
    tf[k] = f2[k] - f1[k]; ff[k] = ti[j[k]] - f1[k];
  }
}

/* Алгоритм Дейкстры */

void Deikstra(int i[], int j[], int dij[],int *d)
{
    n=9;    //количество вершин в графе
    int a[n][n]; // матрица связей
    int v[n]; // посещенные вершины
    int temp=0;
    int minindex, min;
// Инициализация матрицы связей
    for (int i = 0; i<n; i++)
    {
        for (int j = 0; j<n; j++)
        {
            a[i][j] = 0;
        }
     }
    for (int z = 0; z<15; z++)
    {
        int kkk=i[z]-1;
        int qqq=j[z]-1;
        a[kkk][qqq] = dij[z];
    }

//Инициализация вершин и расстояний
    for (int i = 0; i<n; i++)
    {
        d[i] = 10000;
        v[i] = 1;
    }
    d[0] = 0;
// Шаг алгоритма
    do
    {
        minindex = 10000;
        min = 10000;
        for (int i = 0; i<n; i++)
        { // Если вершину ещё не обошли и вес меньше min
            if ((v[i] == 1) && (d[i]<min))
            { // Переприсваиваем значения
                min = d[i];
                minindex = i;
            }
        }
  // Добавляем найденный минимальный вес
  // к текущему весу вершины
  // и сравниваем с текущим минимальным весом вершины
        if (minindex != 10000)
        {
            for (int i = 0; i<n; i++)
            {
                if (a[minindex][i] > 0)
                {
                    temp = min + a[minindex][i];
                    if (temp < d[i]) d[i] = temp;
                }
            }
        v[minindex] = 0;
        }
    }
    while (minindex < 10000);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setlocale(LC_CTYPE, "Russian");
      // n - общее количество работ по проекту (количество ребер ориентированного графа).
  int i[n]={1,1,1,1,2,3,5,5,4,4,6,6,6,8,7};  // Вектор-пара, представляющая k-ю работу,
  int j[n]={2,4,3,5,4,5,4,6,6,7,7,8,9,9,9};  // которая понимается как стрелка, связыва-
              // ющая событие i[k] с событием j[k]
              // Граф задан массивом ребер:
              // (i[0],j[0]),(i[1],j[1]),...,(i[n-1],j[n-1])
              // Должно быть выполнено:
              // i[0]=1, i[k]<i[k+1], i[k]<j[k].
  int dij[n]={4,6,2,5,3,4,7,6,4,3,5,8,6,4,3};// dij[k] - продолжительность k-й операции.
  int s1[n]; // s1[k] - самый ранний срок начала k-й операции.
  int s2[n]; // s2[k] - самый поздний срок начала k-й.
  int f1[n]; // f1[k] - самый ранний срок завершения k-й.
  int f2[n]; // f2[k] - самый поздний срок завершения k-й операции.
  int tf[n]; // tf[k] - полный резерв времени k-й операции.
  int ff[n]; // ff[k] - свободный резерв времени k-й операции.
  int d[n];
  int k;      // Параметр цикла.

  Critical_Path (n,&i[0],&j[0],&dij[0],&s1[0],&s2[0],&f1[0],&f2[0],&tf[0],&ff[0]);
  // Определение  критического  пути. Критический путь задается
  // стрелками, соединяющими события, для которых полный резерв
  // времени равен нулю.
  int s = 0;
  for (k=0;k<n;k++)
   if ( tf[k]==0 ) s=s+dij[k];

  Deikstra(&i[0],&j[0],&dij[0],&d[0]);
  n=15;

  int mas[n]; //массив с номерами вершин критического пути
  for(k=0;k<n;k++)
      if (tf[k]==0)
      {
          mas[k]=j[k];
      }

  int t = (3*d[8]+2*s)/5; //ожидаемое время выполнения (продолжительность проекта)

  Form graph(&s1[0],&f1[0],&s2[0],&f2[0],&ff[0],&tf[0],&i[0],&j[0],s,&mas[0],t,d[8]);
  graph.show();
  return a.exec();
}
