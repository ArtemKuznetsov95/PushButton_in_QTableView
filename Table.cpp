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
    CustomDelegateView *delegate = new CustomDelegateView(this);                            //Ручное редактирование ячеек
    ui->m_tableView->setItemDelegate(delegate);
    connect(delegate, &CustomDelegateView::signalClicked, [this](QModelIndex index) {
        int result = QMessageBox::warning(this, "Предупреждение!", "Подтвердите удаление", QMessageBox::Yes, QMessageBox::No);
        if(result == QMessageBox::Yes)
            this->onBtnClicked(index);
    });
}

void Table::onBtnClicked(QModelIndex index) {
    m_model->deleted(index.row());                                                          //Передача индекса строки в модель для удаления
}

void Table::onSectionClicked(int logicalIndex)
{
    (void)logicalIndex;
    if(logicalIndex == 3)
        m_model->append();                                                                  //Если был заголовок третьего стоблца, так как там имитатор кнопки, то сообщаем модели о добавление новой строки
}
