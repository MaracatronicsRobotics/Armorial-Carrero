#include "fieldtypes.h"
namespace FieldTypes {
QString toString(FieldType fieldType) {
    switch(fieldType) {
        case VISION:  return "Vision data";
        case SSL2012: return "SSL 2012";
        case SSL2015: return "SSL 2015";
        case SSL2019: return "SSL 2019";
        case VSS2008: return "VSS 2008";
        default:      return "undefined";
    }
}
FieldType fromString(const QString &fieldTypeStr) {
    if(fieldTypeStr=="Vision data") return VISION;
    if(fieldTypeStr=="SSL 2012") return SSL2012;
    if(fieldTypeStr=="SSL 2015") return SSL2015;
    if(fieldTypeStr=="SSL 2019") return SSL2019;
    if(fieldTypeStr=="VSS 2008") return VSS2008;
    return UNDEFINED;
}
}