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

QStringList ItemModel::getUniqueValues(const QString &propertyName) const {
    QSet<QString> uniqueValues;

    for (const auto &item : m_items) { // m_items — это ваш внутренний список элементов
        if (propertyName == "Тип") {
            uniqueValues.insert(item.getType());
        } else if (propertyName == "Вид") {
            uniqueValues.insert(item.getKind());
        }
        // Добавляйте дополнительные условия, если нужно
    }

    return QStringList(uniqueValues.begin(), uniqueValues.end());
}

void ItemModel::filterItemsByProperty(const QString &propertyName, const QString &value) {
    if (propertyName.isEmpty()) {
        // Если свойство не выбрано, показываем все элементы
        setItems(m_originalItems);
        return;
    }

    QList<ItemManager> filteredItems;

    for (const auto &item : m_originalItems) {
        if (propertyName == "Тип" && item.getType() == value) {
            filteredItems.append(item);
        } else if (propertyName == "Вид" && item.getKind() == value) {
            filteredItems.append(item);
        }
        // Добавьте дополнительные свойства, если нужно
    }

    setItems(filteredItems);
}


// void ItemModel::filterItems(const QString &query, const QString &filterField) {
//     //qDebug() << "Фильтрация начата. Запрос:" << query << "Поле фильтрации:" << filterField;

//     beginResetModel();
//     m_items.clear();

//     if (query.isEmpty()) {
//         m_items = m_originalItems; // Возвращаем все элементы, если запрос пуст
//     } else {
//         for (const ItemManager &item : m_originalItems) {
//             QString fieldValue;

//             if (filterField == "Тип") {
//                 fieldValue = item.getType();
//             } else if (filterField == "Вид") {
//                 fieldValue = item.getKind();
//             } else if (filterField == "Название") {
//                 fieldValue = item.getName();
//             } else if (filterField == "Вендер") {
//                 fieldValue = item.getManufacturers().join(", ");
//             } else {
//                 fieldValue.clear();
//             }

//             // Проверяем совпадение
//             if (!fieldValue.isEmpty() && fieldValue.contains(query, Qt::CaseInsensitive)) {
//                 m_items.append(item);
//             }
//         }
//     }

//     endResetModel();
//     //qDebug() << "Фильтрация завершена. Количество элементов:" << m_items.size();
// }



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

void ItemModel::filterItems(const QString &searchText, const QString &propertyName, const QString &value, const QString &filter) {
    QList<ItemManager> filteredItems;

    // Если searchText и propertyName пусты, возвращаем оригинальный список
    if (searchText.isEmpty() && propertyName.isEmpty()) {
        setItems(m_originalItems);
        return;
    }

    for (const auto &item : m_originalItems) {
        bool matchesSearch = searchText.isEmpty() ||
                             (filter == "Название" && item.getName().contains(searchText, Qt::CaseInsensitive)) ||
                             (filter == "Вендер" && item.getManufacturers().join(",").contains(searchText, Qt::CaseInsensitive));

        bool matchesProperty = propertyName.isEmpty() ||
                               (propertyName == "Тип" && item.getType() == value) ||
                               (propertyName == "Вид" && item.getKind() == value);

        if (matchesSearch && matchesProperty) {
            filteredItems.append(item);
        }
    }

    setItems(filteredItems);
}




// void ItemModel::filterItemsFromQml(const QString &query, const QString &filterType) {
//     filterItems(query, filterType);
// }
