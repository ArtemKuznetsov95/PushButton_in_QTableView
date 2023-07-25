#include "Table.h"
#include "ui_Table.h"
#include <QDebug>
#include <QSignalMapper>

Table::Table(QWidget *parent) : QWidget(parent), ui(new Ui::Table) {
  ui->setupUi(this);
  m_model = new TableModel();
  ui->m_tableView->setModel(m_model);
  ui->m_tableView->verticalHeader()->hide();                                                //Скрытие вертикального заголовка таблицы

  CustomHeaderView *header = new CustomHeaderView(Qt::Horizontal, ui->m_tableView);         //Передача заголовков таблицы в ручное редактирование через вспомогательный класс
  ui->m_tableView->setHorizontalHeader(header);                                             //Установка новых заголовков в таблицу
  ui->m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);          //Растягивание всех столбцов по равному размеру

  connect(header, &QHeaderView::sectionClicked, this, &Table::onSectionClicked);            //Перехват сигнала от нажатия на заголовок столбца
  connect(m_model, &TableModel::dataUpdated, this, &Table::createButton);                   //Перехват сигнала от модели о обновлении модели
  createButton();
}

Table::~Table() { delete ui; }

void Table::createButton() {
  QSignalMapper *signalMapper = new QSignalMapper(this);                                    //Класс собирает сигналы от группы кнопок
  for (int itemTableView = 0; itemTableView < m_model->rowCount(); itemTableView++) {
    int columnButton = 3;
    QPushButton *button = new QPushButton("Удалить точку");
    ui->m_tableView->setIndexWidget(m_model->index(itemTableView, columnButton), button);   //Вставляем кнопку удаления в ячеку
    signalMapper->setMapping(button, itemTableView);                                        //signalMapper сопоставляет кнопку со строкой ее нахождения
    connect(button, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));                      //Сигнал кнопки отлавливает signalMapper
  }
  connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(onBtnClicked(int)));                //signalMapper передает слоту индекс строки при нажатии кнопки
}

void Table::onBtnClicked(int indexRow) {
    m_model->deleted(indexRow);                                                             //Передача индекса строки в модель для удаления
}

void Table::onSectionClicked(int logicalIndex)
{
    (void)logicalIndex;
    if(logicalIndex == 3)
        m_model->append();                                                                  //Если был заголовок третьего стоблца, так как там имитатор кнопки, то сообщаем модели о добавление новой строки
}
