#include "TableModel.h"
#include <QDebug>

TableModel::TableModel(QObject *parent) : QAbstractTableModel{parent} {
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
      variant =
          QString::fromStdString("№ %1").arg(m_list.at(index.row()).m_number);
      break;
    }
    case 1: {
      variant = m_list.at(index.row()).m_x;
      break;
    }
    case 2: {
      variant = m_list.at(index.row()).m_y;
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
    /*flags |= Qt::ItemIsEditable;*/        //Разрешение редактирования ячейки
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
      m_list[index.row()].m_number = value.toInt();
      break;
    }
    case 1: {
      m_list[index.row()].m_x = value.toString();
      break;
    }
    case 2: {
      m_list[index.row()].m_y = value.toString();
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
  for (int indexRowTable = 1; indexRowTable <= 4; indexRowTable++) {
    DataModel datamodel;
    datamodel.m_number = indexRowTable;
    datamodel.m_x = QString::fromStdString("%1°14.5").arg(indexRowTable * 5);
    datamodel.m_y = QString::fromStdString("%1°18.54").arg(indexRowTable * 5);
    m_list.append(datamodel);
  }
  emit dataUpdated();
}

void TableModel::deleted(int indexRow) {
  beginRemoveRows(QModelIndex(), indexRow, indexRow);
  m_list.removeAt(indexRow);
  endRemoveRows();

  emit dataUpdated();
}

void TableModel::append() {
  beginResetModel();
  DataModel datamodel;
  int indexRowTable;
  if (m_list.count() == 0)
    indexRowTable = 1;
  else
    indexRowTable = m_list.at(m_list.count() - 1).m_number + 1;
  datamodel.m_number = indexRowTable;
  datamodel.m_x = QString::fromStdString("%1°14.5").arg(indexRowTable * 5);
  datamodel.m_y = QString::fromStdString("%1°18.54").arg(indexRowTable * 5);
  m_list.append(datamodel);
  endResetModel();

  emit dataUpdated();
}
