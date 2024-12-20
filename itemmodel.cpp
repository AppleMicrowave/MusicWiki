#include "itemmodel.h"

ItemModel::ItemModel(QObject *parent)
    : QAbstractListModel(parent) {}

int ItemModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return m_items.size();
}

QVariant ItemModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_items.size())
        return QVariant();

    const ItemManager &item = m_items.at(index.row());

    switch (role) {
    case CategoryRole:
        return item.getCategory();
    case TypeRole:
        return item.getType();
    case KindRole:
        return item.getKind();
    case NameRole:
        return item.getName();
    case PriceRole:
        return item.getPrice();
    case DescriptionRole:
        return item.getDescription();
    case ManufacturersRole:
        return QVariant::fromValue(item.getManufacturers());
    case ImagePathRole:
        return item.getImagePath();
    default:
        return QVariant();
    }
}

void ItemModel::filterItems(const QString &query, const QString &filterField) {
    //qDebug() << "Фильтрация начата. Запрос:" << query << "Поле фильтрации:" << filterField;

    beginResetModel();
    m_items.clear();

    if (query.isEmpty()) {
        m_items = m_originalItems; // Возвращаем все элементы, если запрос пуст
    } else {
        for (const ItemManager &item : m_originalItems) {
            QString fieldValue;

            if (filterField == "Тип") {
                fieldValue = item.getType();
            } else if (filterField == "Вид") {
                fieldValue = item.getKind();
            } else if (filterField == "Название") {
                fieldValue = item.getName();
            } else if (filterField == "Вендер") {
                fieldValue = item.getManufacturers().join(", ");
            } else {
                fieldValue.clear();
            }

            // Проверяем совпадение
            if (!fieldValue.isEmpty() && fieldValue.contains(query, Qt::CaseInsensitive)) {
                m_items.append(item);
            }
        }
    }

    endResetModel();
    //qDebug() << "Фильтрация завершена. Количество элементов:" << m_items.size();
}



QHash<int, QByteArray> ItemModel::roleNames() const {
    return {
        {CategoryRole, "category"},
        {TypeRole, "type"},
        {KindRole, "kind"},
        {NameRole, "name"},
        {PriceRole, "price"},
        {DescriptionRole, "description"},
        {ManufacturersRole, "manufacturers"},
        {ImagePathRole, "imagePath"}
    };
}

void ItemModel::setItems(const QVector<ItemManager> &items) {
    beginResetModel();
    m_items = items;
    m_originalItems = items; // Сохраняем оригинальные данные
    endResetModel();
}

void ItemModel::addItem(const ItemManager &item) {
    beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
    m_items.append(item);
    endInsertRows();
}

void ItemModel::filterItemsFromQml(const QString &query, const QString &filterType) {
    filterItems(query, filterType);
}
