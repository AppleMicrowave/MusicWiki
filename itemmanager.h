#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <QString>
#include <QList>

class ItemManager {
public:
    // Конструктор
    ItemManager(const QString& type,
                const QString& kind,
                const QString& name,
                double price,
                const QString& description,
                const QList<QString>& manufacturers,
                const QString& imagePath);

    // Геттеры
    QString getType() const;
    QString getKind() const;
    QString getName() const;
    double getPrice() const;
    QString getDescription() const;
    QList<QString> getManufacturers() const;
    QString getImagePath() const;

    // Сеттеры
    void setType(const QString& type);
    void setKind(const QString& kind);
    void setName(const QString& name);
    void setPrice(double price);
    void setDescription(const QString& description);
    void setManufacturers(const QList<QString>& manufacturers);
    void setImagePath(const QString& imagePath);

private:
    QString m_type;            // Тип инструмента (Смычковые, Щипковые)
    QString m_kind;            // Разновидность инструмента (Акустическая гитара, Электрогитара и т.д.)
    QString m_name;            // Наименование инструмента
    double m_price;            // Цена
    QString m_description;     // Краткое описание
    QList<QString> m_manufacturers; // Крупные производители
    QString m_imagePath;       // Путь к изображению
};

#endif // ITEMMANAGER_H
