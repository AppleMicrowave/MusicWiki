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

void ItemModel::filterItems(const QString &query) {
    QString lowerQuery = query.toLower();
    if (query.isEmpty()) {
        // Если запрос пустой, сбрасываем фильтр
        beginResetModel();
        m_items = m_originalItems;
        endResetModel();
        return;
    }

    QVector<ItemManager> filteredItems;
    for (const auto &item : m_originalItems) {
        if (item.getName().toLower().contains(lowerQuery) ||
            item.getKind().toLower().contains(lowerQuery)) {
            filteredItems.append(item);
        }
    }

    beginResetModel();
    m_items = filteredItems;
    endResetModel();
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

void ItemModel::filterItemsFromQml(const QString &query) {
    filterItems(query);
}
