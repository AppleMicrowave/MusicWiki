#ifndef ITEMMODEL_H
#define ITEMMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include "itemmanager.h"

class ItemModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum ItemRoles {
        CategoryRole = Qt::UserRole + 1,
        TypeRole,
        KindRole,
        NameRole,
        PriceRole,
        DescriptionRole,
        ManufacturersRole,
        ImagePathRole
    };

    explicit ItemModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE QStringList getUniqueValues(const QString &propertyName) const;
    Q_INVOKABLE void filterItemsByProperty(const QString &propertyName, const QString &value);

    QHash<int, QByteArray> roleNames() const override;

    void setItems(const QVector<ItemManager> &items);
    void addItem(const ItemManager &item);

public slots:
    Q_INVOKABLE void filterItems(const QString &searchText, const QString &propertyName, const QString &value, const QString &filter);

    //void filterItemsFromQml(const QString &query, const QString &filterField);

private:
    QVector<ItemManager> m_items;         // Хранилище данных для отображения
    QVector<ItemManager> m_originalItems; // Полный список (для фильтрации)
};

#endif // ITEMMODEL_H
