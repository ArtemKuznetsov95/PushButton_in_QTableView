#include "TableModel.h"
#include <QDebug>

TableModel::TableModel(QObject *parent) : QAbstractTableModel{parent} {

    for(int i = 1; i < 4; i++) {
        double x = i * 10.2;
        double y = i * 100.3;

        m_db_list.append(DataModel(i, x, y));
    }
    this->updateModel();
}

int TableModel::rowCount(const QModelIndex &parent) const {
  (void)parent;
  return m_list.size();
}

int TableModel::columnCount(const QModelIndex &parent) const {
  (void)parent;
  return 4;
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();
  QVariant variant;
  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    switch (index.column()) {
    case 0: {
        if(role == Qt::DisplayRole) {
            variant = QString::fromStdString("№ %1").arg(m_list.at(index.row()).m_number);
        }else if(role == Qt::EditRole) {
            variant = m_list.at(index.row()).m_number;
        }
      break;
    }
    case 1: {
        if(role == Qt::DisplayRole) {
      variant = getCoordAsString(m_list.at(index.row()).m_x);
        }else if(role == Qt::EditRole) {
            variant = m_list.at(index.row()).m_x;
        }
      break;
    }
    case 2: {
        if(role == Qt::DisplayRole) {
      variant = getCoordAsString(m_list.at(index.row()).m_y);
        }else if(role == Qt::EditRole) {
            variant = m_list.at(index.row()).m_y;
        }
      break;
    }
    }
  }
  if (role == Qt::TextAlignmentRole)
    return Qt::AlignCenter;                 //Центральное расположения текста в ячейке
  return variant;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation,
                                int role) const {
  if (role != Qt::DisplayRole)
    return QVariant();
  if (orientation == Qt::Horizontal) {
    switch (section) {
    case 0:
      return QString("Номер точки");
    case 1:
      return QString("Широта");
    case 2:
      return QString("Долгота");
    }
  }
  return QAbstractTableModel::headerData(section, orientation, role);
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const {
  Qt::ItemFlags flags = QAbstractTableModel::flags(index);

  if (index.isValid()) {
    flags |= Qt::ItemIsEditable;        //Разрешение редактирования ячейки
  }
  flags |= Qt::ItemIsSelectable;        //Выделение объекта

  return flags;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
  if (!index.isValid())
    return false;
  if (role == Qt::EditRole) {
    switch (index.column()) {
    case 0: {
        QChar num = 0x2116;
      m_list[index.row()].m_number = value.toString().remove(num).toInt();
      break;
    }
    case 1: {
      m_list[index.row()].m_x = value.toDouble();
      break;
    }
    case 2: {
      m_list[index.row()].m_y = value.toDouble();
      break;
    }
    }
    emit dataChanged(index, index);
    return true;
  }
  return false;
}

void TableModel::updateModel() {
  m_list.clear();
 for(auto item : m_db_list) {
    m_list.append(item);
  }
  emit dataUpdated();
}

void TableModel::deleted(int indexRow) {
  beginRemoveRows(QModelIndex(), indexRow, indexRow);
  m_list.removeAt(indexRow);
  endRemoveRows();

  emit dataUpdated();
}

void TableModel::append(QList<QPair<double, double>> list) {

  beginResetModel();

  int indexRowTable;
  if (m_list.count() == 0)
    indexRowTable = 1;
  else
    indexRowTable = m_list.at(m_list.count() - 1).m_number + 1;

  for(auto item : list) {
    DataModel datamodel(indexRowTable, item.first, item.second);
  m_list.append(datamodel);
  }
  endResetModel();

  emit dataUpdated();
}

QString TableModel::getCoordAsString(double coord) const
{
    int degree = std::floor(coord);
    double mins = ((coord - degree) * 3600) / 60;
    QString str;
    if(mins == 0) {
        return QString("%1°").arg(QString::number(degree));
    }
    else {
        return QString("%1°%2").arg(QString::number(degree), QString::number(mins));
    }
}

