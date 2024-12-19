#include "ItemManager.h"

// Конструктор
ItemManager::ItemManager(const QString& category,
                         const QString& type,
                         const QString& kind,
                         const QString& name,
                         double price,
                         const QString& description,
                         const QList<QString>& manufacturers,
                         const QString& imagePath)
    :  m_category(category),
    m_type(type),
    m_kind(kind),
    m_name(name),
    m_price(price),
    m_description(description),
    m_manufacturers(manufacturers),
    m_imagePath(imagePath)
    {}

// Геттеры
QString ItemManager::getCategory() const { return m_category; }
QString ItemManager::getType() const { return m_type; }
QString ItemManager::getKind() const { return m_kind; }
QString ItemManager::getName() const { return m_name; }
double ItemManager::getPrice() const { return m_price; }
QString ItemManager::getDescription() const { return m_description; }
QList<QString> ItemManager::getManufacturers() const { return m_manufacturers; }
QString ItemManager::getImagePath() const { return m_imagePath; }


// Сеттеры
void ItemManager::setCategory(const QString& category) { m_category = category; }
void ItemManager::setKind(const QString& kind) { m_kind = kind; }
void ItemManager::setName(const QString& name) { m_name = name; }
void ItemManager::setPrice(double price) { m_price = price; }
void ItemManager::setDescription(const QString& description) { m_description = description; }
void ItemManager::setManufacturers(const QList<QString>& manufacturers) { m_manufacturers = manufacturers; }
void ItemManager::setImagePath(const QString& imagePath) { m_imagePath = imagePath; }
