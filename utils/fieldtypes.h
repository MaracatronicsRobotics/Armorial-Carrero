#ifndef FIELDTYPE_HH
#define FIELDTYPE_HH
#include <QString>
namespace FieldTypes {
    enum FieldType {
        VISION,
        SSL2012,
        SSL2015,
        SSL2019,
        VSS2008,
        UNDEFINED
    };
    QString toString(FieldType fieldType);
    FieldTypes::FieldType fromString(const QString &fieldTypeStr);
}
#endif // FIELDTYPE_HH