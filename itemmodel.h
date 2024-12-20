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

    void filterItems(const QString &query);

    QHash<int, QByteArray> roleNames() const override;

    void setItems(const QVector<ItemManager> &items);
    void addItem(const ItemManager &item);

public slots:
    void filterItemsFromQml(const QString &query);

private:
    QVector<ItemManager> m_items; // Хранилище данных
    QVector<ItemManager> m_originalItems; // Оригинальные элементы (полный список)
};

#endif // ITEMMODEL_H
